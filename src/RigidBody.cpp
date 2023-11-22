#include "RigidBody.h"

RigidBody::RigidBody(list<pair<of3dPrimitive*, Vector3D>> primitives,
	//Vector3D centerOfMass,
	Vector3D position,
	Vector3D initVelocity,
	Quaternion orientation,
	Vector3D initAngVelocity,
	float invertedMass,
	float radius,
	float frictionK1,
	float frictionK2,
	float coeffRestitutions)
	: m_primitives(),
	//m_centerOfMass(centerOfMass),
	m_position(position),
	m_velocity(initVelocity),
	m_orientation(orientation),
	m_matrixOrientation(Matrix3::FromQuaternion(orientation)),
	m_angularVelocity(initAngVelocity),
	m_invertedMass(invertedMass),
	m_radius(radius),
	m_frictionK1(frictionK1),
	m_frictionK2(frictionK2),
	m_coeffRestitutions(coeffRestitutions)
{
	m_centerMass = new ofSpherePrimitive();
	m_centerMass->setRadius(.25);

	m_primitives.push_back(m_centerMass);
	
	for (pair<of3dPrimitive*, Vector3D> primitive : primitives)
	{
		primitive.first->setParent(*m_centerMass);
		primitive.first->setPosition(primitive.second.v3());

		m_primitives.push_back(primitive.first);
	}

	m_invertedInertiaTensor = Matrix3::Identity() * (2.5 * m_invertedMass / (m_radius * m_radius));
}

RigidBody::RigidBody(RigidBody& rb)
	: m_position(rb.m_position),
	m_velocity(rb.m_velocity),
	m_orientation(rb.m_orientation),
	m_matrixOrientation(rb.m_matrixOrientation),
	m_angularVelocity(rb.m_angularVelocity),
	m_invertedMass(rb.m_invertedMass),
	m_radius(rb.m_radius),
	m_frictionK1(rb.m_frictionK1),
	m_frictionK2(rb.m_frictionK2),
	m_coeffRestitutions(rb.m_coeffRestitutions),
	m_invertedInertiaTensor(rb.m_invertedInertiaTensor)
{
	m_centerMass = new ofSpherePrimitive();
	m_centerMass->setRadius(.25);

	m_primitives.push_back(m_centerMass);

	bool firstPrimitive = true;
	for (of3dPrimitive* primitive : rb.m_primitives)
	{
		if (firstPrimitive)
		{
			firstPrimitive = false;
			continue;
		}

		of3dPrimitive* primitiveCopy = new of3dPrimitive(*primitive);

		primitiveCopy->setParent(*m_centerMass);
		primitiveCopy->setPosition(primitive->getPosition());

		m_primitives.push_back(primitiveCopy);
	}
}

RigidBody::~RigidBody()
{
}

void RigidBody::Update()
{
	float fps, duration;
	fps = ofGetFrameRate();

	// if no fps no movement && avoid division by zero
	if (fps != 0) {
		duration = 1 / fps;
		updateAcceleration();
		updateVelocity(duration);
		updatePosition(duration);
		updateOrientation(duration);
	}
}

float RigidBody::getInverseMass() { return m_invertedMass; }

void RigidBody::addForce(const Vector3D& force, const Vector3D& localPoint)
{
	m_accumForce = m_accumForce + force;
	Vector3D torque = localPoint ^ force;
	m_accumTorque = m_accumTorque + torque;
}

void RigidBody::clearAccum()
{
	m_accumForce[0] = 0;
	m_accumForce[1] = 0;
	m_accumForce[2] = 0;	

	m_accumTorque[0] = 0;
	m_accumTorque[1] = 0;
	m_accumTorque[2] = 0;
}

Vector3D RigidBody::getVelocity() { return m_velocity; }

void RigidBody::addVelocity(Vector3D velocity)
{
	m_velocity = m_velocity + velocity;
}

Vector3D RigidBody::getPosition() { return m_position; }

void RigidBody::setPosition(Vector3D position)
{
	m_position = position;
}

void RigidBody::addPosition(Vector3D position)
{
	m_position = m_position + position;
}

Vector3D RigidBody::getAcceleration() { return m_acceleration; }

float RigidBody::getCoefficientRestitution() { return m_coeffRestitutions; }

float RigidBody::getK1() { return m_frictionK1; }

float RigidBody::getK2() { return m_frictionK2; }

Vector3D RigidBody::getPointWorldPosition(Vector3D* localPoint)
{
	// Apply object's rotation inverse
	Matrix3 inverseRot = m_matrixOrientation.Inverse();
	Vector3D worldPosition = inverseRot * (*localPoint);
	
	// Is a translatable point
	worldPosition.w(1);

	// Translate the point back to have world (0,0,0) as origin
	Matrix4 inverseTranslation = Matrix4::Identity();
	inverseTranslation.at(0, 3) = m_position.x();
	inverseTranslation.at(1, 3) = m_position.y();
	inverseTranslation.at(2, 3) = m_position.z();
	worldPosition = inverseTranslation * worldPosition;

	return worldPosition;
}

Vector3D RigidBody::integrate(function<Vector3D(float)> f, float interval[2], int N)
{
	// interval over which we integrate
	float h = (interval[1] - interval[0]) / N;
	Vector3D u = Vector3D();
	// euler algorithm
	for (int k = 0; k < N; k++) {
		u += f(interval[0] + k * h) * h;
	}

	return u;
}

void RigidBody::updateAcceleration()
{
	m_acceleration = m_accumForce * m_invertedMass;
	m_angularAcceleration = m_invertedInertiaTensor * m_accumTorque;
	clearAccum();
}

void RigidBody::updateVelocity(float duration)
{
	float interval[2] = { 0.0, duration };

	Vector3D acceleration = m_acceleration;
	Vector3D angularAcceleration = m_acceleration;

	function<Vector3D(float)> a = [acceleration](float t) {return acceleration; };
	function<Vector3D(float)> a_angular = [angularAcceleration](float t) {return angularAcceleration; };

	// velocity is acceleration after integration
	m_velocity += integrate(a, interval);
	
	float damp = pow(.75, duration);
    m_angularVelocity = m_angularVelocity * damp;
	m_angularVelocity = m_angularVelocity + m_angularAcceleration * duration;
}

void RigidBody::updatePosition(float duration)
{
	float interval[2] = { 0.0, duration };
	Vector3D velocity = m_velocity;

	function<Vector3D(float)> v = [velocity](float t) {return velocity; };

	// position is velocity after integration
	m_position += integrate(v, interval);

	m_centerMass->setPosition(m_position.v3());
}

void RigidBody::updateOrientation(float duration)
{
	Quaternion angularVariation = Quaternion(0, m_angularVelocity);

	angularVariation = angularVariation * .5f;
	angularVariation = angularVariation * m_orientation;
	angularVariation = angularVariation * duration;

	m_orientation = m_orientation + angularVariation;
	m_orientation.Normalize();
	m_matrixOrientation = Matrix3::FromQuaternion(m_orientation);

	m_centerMass->setOrientation(m_orientation.q());
}

list<of3dPrimitive*> RigidBody::getPrimitives() const { return m_primitives; }

void RigidBody::addPrimitive(of3dPrimitive* primitive, Vector3D position)
{
	primitive->setParent(*m_centerMass);
	primitive->setPosition(position.v3());
	m_primitives.push_back(primitive);
}