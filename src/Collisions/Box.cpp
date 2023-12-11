#pragma once

#include "Box.h"
#include <Matrix3.h>

Box::Box(RigidBody* rb, Vector3D* center, Vector3D* axe1, Vector3D* axe2, Vector3D* axe3)
	:
	Collider(rb, center),
	m_right(axe1),
	m_top(axe2),
	m_forward(axe3)
{}

Box::~Box()
{
	delete m_right;
	delete m_top;
	delete m_forward;
}

void Box::setRotation(Quaternion* rotation)
{
	Matrix3 rotationM = Matrix3::FromQuaternion(*rotation);
	*m_right = rotationM * *m_right;
	*m_top = rotationM * *m_top;
	*m_forward = rotationM * *m_forward;
}

Vector3D Box::getRight() { return *m_right; }
Vector3D Box::getTop() { return *m_top; }
Vector3D Box::getForward() { return *m_forward; }
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

	vertices[0] = (*m_right);
	vertices[0] = vertices[0] + (*m_top);
	vertices[0] = vertices[0] + (*m_forward);

	vertices[1] = (*m_right) * -1;
	vertices[1] = vertices[1] + (*m_top);
	vertices[1] = vertices[1] + (*m_forward);

	vertices[2] = (*m_right);
	vertices[2] = vertices[2] + (*m_top) * -1;
	vertices[2] = vertices[2] + (*m_forward);

	vertices[3] = (*m_right);
	vertices[3] = vertices[3] + (*m_top);
	vertices[3] = vertices[3] + (*m_forward) * -1;

	vertices[4] = (*m_right) * -1;
	vertices[4] = vertices[4] + (*m_top) * -1;
	vertices[4] = vertices[4] + (*m_forward);

	vertices[5] = (*m_right) * -1;
	vertices[5] = vertices[5] + (*m_top);
	vertices[5] = vertices[5] + (*m_forward) * -1;

	vertices[6] = (*m_right);
	vertices[6] = vertices[6] + (*m_top) * -1;
	vertices[6] = vertices[6] + (*m_forward) * -1;

	vertices[7] = (*m_right) * -1;
	vertices[7] = vertices[7] + (*m_top) * -1;
	vertices[7] = vertices[7] + (*m_forward) * -1;

	return vertices;
}
Vector3D* Box::getAxes(Box* collider)
{
	Vector3D* axes = new Vector3D[15];
	axes[0] = getAxis(0);
	axes[1] = getAxis(1);
	axes[2] = getAxis(2);
	axes[3] = collider->getAxis(0);
	axes[4] = collider->getAxis(1);
	axes[5] = collider->getAxis(2);

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
	
	Vector3D boxDir = getPosition() - collider->getPosition();

	Vector3D contactNormal;
	float minPenetration = FLT_MAX;
	Vector3D contactPoint;

	Vector3D* vertices = getVertices();
	Vector3D* axes = getAxes(collider);

	for (int i = 0; i < 15; i++)
	{
		float projection = axes[i].Norm();
	}


	for (int i = 0; i < 2; i++)
	{
		Vector3D currentAxe = getAxis(i);
		float projCA = currentAxe.Norm();

		currentAxe.Normalize();

		float projDirection = abs(boxDir * currentAxe);

		for (int j = 0; j < 2; j++)
		{
			Vector3D otherAxe = collider->getAxis(j);
			float projOA = abs(otherAxe * currentAxe);

			float currentPenetration = projCA + projOA - projDirection;
			if (currentPenetration > 0)
			{
				if (currentPenetration < minPenetration)
				{
					minPenetration = currentPenetration;
					
					if(boxDir * otherAxe < 0) contactNormal = otherAxe * (- 1);
					else contactNormal = otherAxe;

					contactNormal.Normalize();
				}
			}
		}
	}

	return res;
}

list<Contact*> Box::intersection(Plane* collider)
{
	return list<Contact*>();
}

