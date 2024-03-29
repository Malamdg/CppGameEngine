#pragma once

#include "Box.h"
#include <Matrix3.h>

Box::Box(RigidBody* rb, Vector3D center, Vector3D axe1, Vector3D axe2, Vector3D axe3) :
	Collider(rb, center),
	m_right(axe1),
	m_top(axe2),
	m_forward(axe3)
{}

Box::Box(RigidBody* rb, Vector3D center, Vector3D dimension) :
	Collider(rb, center),
	m_right(Vector3D(dimension.x(), 0, 0)),
	m_top(Vector3D(0, dimension.y(), 0)),
	m_forward(Vector3D(0, 0, dimension.z()))
{}

Box::~Box() {}

void Box::update()
{
	setPosition(getRigidBody()->getPosition());
	setRotation(getRigidBody()->getOrientation());
}

void Box::setRotation(Quaternion rotation)
{
	float normRight = m_right.Norm();
	float normTop = m_top.Norm();
	float normForward = m_forward.Norm();

	// Allignement des axes avec le rep�re
	m_right = Vector3D(m_right.Norm(), 0, 0);
	m_top = Vector3D(0, m_top.Norm(), 0);
	m_forward = Vector3D(0, 0, m_forward.Norm());

	Matrix3 rotationM = Matrix3::FromQuaternion(rotation);
	m_right = rotationM * m_right;
	m_top = rotationM * m_top;
	m_forward = rotationM * m_forward;

	// Normalize and extend to norn to guaranty that the float do not mess up the sizes
	m_right.Normalize();
	m_top.Normalize();
	m_forward.Normalize();

	m_right = m_right * normRight;
	m_top = m_top * normTop;
	m_forward = m_forward * normForward;
}

Vector3D Box::getRight() { return m_right; }
Vector3D Box::getTop() { return m_top; }
Vector3D Box::getForward() { return m_forward; }
Vector3D Box::getAxis(int i) 
{
	if (i == 0) return getRight();
	if (i == 1) return getTop();
	if (i == 2) return getForward();
	else return Vector3D();
}

Vector3D* Box::getVertices()const
{
	Vector3D* vertices = new Vector3D[8];

	vertices[0] = m_right;
	vertices[0] = vertices[0] + m_top;
	vertices[0] = vertices[0] + m_forward;
	vertices[0] = vertices[0] + m_center;

	vertices[1] = m_right * -1;
	vertices[1] = vertices[1] + m_top;
	vertices[1] = vertices[1] + m_forward;
	vertices[1] = vertices[1] + m_center;

	vertices[2] = m_right;
	vertices[2] = vertices[2] + m_top * -1;
	vertices[2] = vertices[2] + m_forward;
	vertices[2] = vertices[2] + m_center;

	vertices[3] = m_right;
	vertices[3] = vertices[3] + m_top;
	vertices[3] = vertices[3] + m_forward * -1;
	vertices[3] = vertices[3] + m_center;

	vertices[4] = m_right * -1;
	vertices[4] = vertices[4] + m_top * -1;
	vertices[4] = vertices[4] + m_forward;
	vertices[4] = vertices[4] + m_center;

	vertices[5] = m_right * -1;
	vertices[5] = vertices[5] + m_top;
	vertices[5] = vertices[5] + m_forward * -1;
	vertices[5] = vertices[5] + m_center;

	vertices[6] = m_right;
	vertices[6] = vertices[6] + m_top * -1;
	vertices[6] = vertices[6] + m_forward * -1;
	vertices[6] = vertices[6] + m_center;

	vertices[7] = m_right * -1;
	vertices[7] = vertices[7] + m_top * -1;
	vertices[7] = vertices[7] + m_forward * -1;
	vertices[7] = vertices[7] + m_center;

	return vertices;
}
Vector3D* Box::getAxes(Box* collider)
{
	Vector3D* axes = new Vector3D[15];

	// Axis for self faces
	axes[0] = getAxis(0);
	axes[1] = getAxis(1);
	axes[2] = getAxis(2);

	// Axis for collider faces
	axes[3] = collider->getAxis(0);
	axes[4] = collider->getAxis(1);
	axes[5] = collider->getAxis(2);

	// Edge-Edge axis
	axes[6] = axes[0] * axes[3];
	axes[7] = axes[0] * axes[4];
	axes[8] = axes[0] * axes[5];
	axes[9] = axes[1] * axes[3];
	axes[10] = axes[1] * axes[4];
	axes[11] = axes[1] * axes[5];
	axes[12] = axes[2] * axes[3];
	axes[13] = axes[2] * axes[4];
	axes[14] = axes[2] * axes[5];

	return axes;
}

list<Contact*> Box::intersect(Collider* collider)
{
	if (instanceof<Box>(collider))
	{
		return intersection((Box*)collider);
	}
	if (instanceof<Plane>(collider))
	{
		return intersection((Plane*)collider);
	}
	return list<Contact*>();
}

list<Contact*> Box::intersection(Box* collider)
{
	list<Contact*> res = list<Contact*>();
	
	Vector3D toCenter = getPosition() - collider->getPosition();

	float bestPenetration = FLT_MAX;
	int bestCase = -1;

	Vector3D contactNormal;
	Vector3D contactPoint;

	Vector3D* vertices = getVertices();
	Vector3D* axes = getAxes(collider);

	for (int i = 0; i < 15; i++)
	{
		float projection = axes[i].Norm();
	}

	// On fait un test de collision pour les 15 axes de s�paration
	for (int i = 0; i < 14; i++)
	{
		Vector3D& axis = axes[i];

		// Projection of the boxes on the axis
		float selfProject = transformToAxis(axis);
		float colliderProject = collider->transformToAxis(axis);

		float distance = abs(toCenter * axis);

		float penetration = selfProject + colliderProject - distance;

		// If no penetration, no collision data
		if (penetration < 0) return res;
		// Else we keep note of the best penetration and the index of its axis
		if (penetration < bestPenetration)
		{
			bestPenetration = penetration;
			bestCase = i;
		}
	}

	// Normale a la face dans le cadre d une collision face-vertex
	Vector3D& normal = axes[bestCase];
	// Store the best axis-major, in case we run into almost parallel edge collisions later
	int bestSingleAxis = bestCase;

	// Si bestCase est compris entre 0 et 2, c est un contacte face-vertex, avec une face de la premiere boite
	if (bestCase < 3)
	{
		// fillPointFaceBoxBox

		if (normal * toCenter > 0)
		{
			normal = normal * -1;
		}

		Vector3D vertex = Vector3D(1, 1, 1);
		if (collider->getAxis(0) * normal < 0) vertex.x(-1);
		if (collider->getAxis(1) * normal < 0) vertex.y(-1);
		if (collider->getAxis(2) * normal < 0) vertex.z(-1);

		vertex =
			collider->getAxis(0) * vertex.x() +
			collider->getAxis(1) * vertex.y() +
			collider->getAxis(2) * vertex.z();

		Contact* contact = new Contact(&vertex, &normal, bestPenetration, getRigidBody(), collider->getRigidBody());
		res.push_back(contact);
		return res;
	}
	// Sinon, si bestCase est compris entre 3 et 5, c est un contacte face-vertex, avec une face de la deuxieme boite
	else if (bestCase < 6)
	{
		if (normal * (toCenter * -1) > 0)
		{
			normal = normal * -1;
		}

		Vector3D vertex = Vector3D(1, 1, 1);
		if (getAxis(0) * normal < 0) vertex.x(-1);
		if (getAxis(1) * normal < 0) vertex.y(-1);
		if (getAxis(2) * normal < 0) vertex.z(-1);

		vertex =
			getAxis(0) * vertex.x() +
			getAxis(1) * vertex.y() +
			getAxis(2) * vertex.z();

		Contact* contact = new Contact(&vertex, &normal, bestPenetration, collider->getRigidBody(), getRigidBody());
		res.push_back(contact);
		return res;
	}
	// Sinon c est un contact edge-edge
	else
	{
		bestCase -= 6;
		int selfAxisIndex = bestCase / 3;
		int colliderAxisIndex = bestCase % 3;
		Vector3D& selfAxis = getAxis(selfAxisIndex);
		Vector3D& colliderAxis = collider->getAxis(selfAxisIndex);
		Vector3D axis = selfAxis ^ colliderAxis;
		axis.Normalize();

		if (axis * toCenter > 0) axis = axis * -1;

		Vector3D ptOnSelfEdge = Vector3D(1, 1, 1);
		Vector3D ptOnColliderEdge = Vector3D(1, 1, 1);
		for (int i = 0; i < 3; i++)
		{
			if (i == selfAxisIndex) ptOnSelfEdge[i] = 0;
			else if (getAxis(i) * axis > 0) ptOnSelfEdge[i] = -1;

			if (i == colliderAxisIndex) ptOnColliderEdge[i] = 0;
			else if (collider->getAxis(i) * axis < 0) ptOnColliderEdge[i] = -1;
		}

		ptOnSelfEdge = 
			getAxis(0) * ptOnSelfEdge.x() +
			getAxis(1) * ptOnSelfEdge.y() +
			getAxis(2) * ptOnSelfEdge.z();
		ptOnColliderEdge =
			getAxis(0) * ptOnColliderEdge.x() +
			getAxis(1) * ptOnColliderEdge.y() +
			getAxis(2) * ptOnColliderEdge.z();

		Vector3D vertex = getContactPoint(
			ptOnSelfEdge, selfAxis, getAxis(selfAxisIndex).Norm(),
			ptOnColliderEdge, colliderAxis, collider->getAxis(colliderAxisIndex).Norm(),
			bestSingleAxis > 2);

		Contact* contact = new Contact(&vertex, &axis, bestPenetration, getRigidBody(), collider->getRigidBody());
		res.push_back(contact);
		return res;
	}

	return res;
}

list<Contact*> Box::intersection(Plane* collider)
{
	list<Contact*> contacts = list<Contact*>();
	Contact* contact;
	Vector3D* vertices = getVertices();
	Vector3D normal = collider->getNormal();

	Vector3D vertex, projectionPoint;
	float t, centerPosition;
	// Position of this center's relatively to the plane
	centerPosition = normal * (m_center - collider->getPosition());
	centerPosition = centerPosition < 0 ? -1 : 1;

	for (int i = 0; i < 8; i++) {
		vertex = vertices[i];
		t = normal * (vertex - collider->getPosition());
		projectionPoint = normal * t;
		projectionPoint = vertex - projectionPoint;
		
		if (t * centerPosition <= 0) {
			contact = new Contact(&vertex, &normal, abs(t) / 2, collider->getRigidBody(), getRigidBody());
			contacts.push_back(contact);
		}
	}



	return contacts;
}

float Box::transformToAxis(Vector3D& axis)
{
	Vector3D halfSize = Vector3D(m_right.Norm(), m_top.Norm(), m_forward.Norm());
	return
		halfSize.x() * abs(axis * getRight().Normalized()) +
		halfSize.y() * abs(axis * getTop().Normalized()) +
		halfSize.z() * abs(axis * getForward().Normalized());
}

Vector3D Box::getContactPoint(Vector3D& pOne, Vector3D& dOne, float oneSize, Vector3D& pTwo, Vector3D& dTwo, float twoSize, bool useOne)
{
	Vector3D toSt, cOne, cTwo;
	float dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
	float denom, mua, mub;

	smOne = dOne.Norm2();
	smTwo = dTwo.Norm2();
	dpOneTwo = dTwo * dOne;

	toSt = pOne - pTwo;
	dpStaOne = dOne * toSt;
	dpStaTwo = dTwo * toSt;

	denom = smOne * smTwo - dpOneTwo * dpOneTwo;

	if (abs(denom) < 10e-4) return useOne ? pOne : pTwo;

	mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
	mub = (smOne * dpStaTwo - dpOneTwo * dpStaOne) / denom;

	if (mua > oneSize || mua < -oneSize ||
		mub > twoSize || mub < -twoSize)
	{
		return useOne ? pOne : pTwo;
	}
	else
	{
		cOne = dOne * mua;
		cOne = pOne + cOne;
		cTwo = dTwo * mub;
		cTwo = pTwo + cTwo;

		Vector3D res = cOne + cTwo;
		res = res * .5f;

		return res;
	}
}

void Box::draw()
{
	Vector3D boxSize(getAxis(0).Norm() * 2, getAxis(1).Norm() * 2, getAxis(2).Norm() * 2);

	// Calcul de l'orientation de la box
	Vector3D uA = getAxis(0).Normalized();
	Vector3D uB = getAxis(1).Normalized();
	Vector3D uC = getAxis(2).Normalized();

	Matrix3 r(uA, uB, uC);
	float aX = atan(r.at(3, 2) / r.at(3, 3));
	float aY = asin(-1 * r.at(3, 1));
	float aZ = atan(r.at(2, 1) / r.at(1, 1));
	Quaternion boxOrientation = Quaternion::Euler(aX, aY, aZ);

	ofBoxPrimitive boxPrimitive(boxSize.x(), boxSize.y(), boxSize.z());
	boxPrimitive.setOrientation(getRigidBody()->getOrientation().q());
	boxPrimitive.setPosition(getPosition().v3());

	boxPrimitive.drawWireframe();

	Vector3D* vertices = getVertices();
	for (int i = 0; i < 8; i++)
	{
		ofSpherePrimitive vertex = ofSpherePrimitive();
		vertex.setRadius(.2f);
		vertex.setPosition(vertices[i].v3());

		vertex.draw();
	}
}