#include "RigidBody.h"

RigidBody::RigidBody(of3dPrimitive* primitive,
	Vector3D centerOfMass,
	Vector3D position,
	Vector3D initVelocity,
	Quaternion orientation,
	Vector3D initAngVelocity,
	float invertedMass,
	float dragCoeff,
	float frictionK1,
	float frictionK2,
	float coeffRestitutions)
	: m_primitive(primitive),
	m_centerOfMass(centerOfMass),
	m_position(position),
	m_velocity(initVelocity),
	m_orientation(orientation),
	m_matrixOrientation(Matrix3::FromQuaternion(orientation)),
	m_angularVelocity(initAngVelocity),
	m_invertedMass(invertedMass),
	m_drag_coef(dragCoeff),
	m_frictionK1(frictionK1),
	m_frictionK2(frictionK2),
	m_coeffRestitutions(coeffRestitutions)
{}

RigidBody::~RigidBody()
{
	delete m_primitive;
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
	}
}

float RigidBody::getInverseMass() { return m_invertedMass; }

void RigidBody::addForce(const Vector3D& force)
{
	m_accumForce = m_accumForce + force;
}

void RigidBody::clearAccum()
{
	m_accumForce[0] = 0;
	m_accumForce[1] = 0;
	m_accumForce[2] = 0;
}

Vector3D RigidBody::getVelocity() { return m_velocity; }

void RigidBody::addVelocity(Vector3D velocity)
{
	m_velocity = m_velocity + velocity;
}

Vector3D RigidBody::getPosition() { return m_position; }

void RigidBody::addPosition(Vector3D position)
{
	m_position = m_position + position;
}

Vector3D RigidBody::getAcceleration() { return m_acceleration; }

float RigidBody::getCoefficientRestitution() { return m_coeffRestitutions; }

float RigidBody::getK1() { return m_frictionK1; }

float RigidBody::getK2() { return m_frictionK2; }

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
	clearAccum();
}

void RigidBody::updateVelocity(float duration)
{
	float interval[2] = { 0.0, duration };

	Vector3D acceleration = m_acceleration;

	function<Vector3D(float)> a = [acceleration](float t) {return acceleration; };

	// velocity is acceleration after integration
	m_velocity += integrate(a, interval);
}

void RigidBody::updatePosition(float duration)
{
	float interval[2] = { 0.0, duration };
	Vector3D velocity = m_velocity;

	function<Vector3D(float)> v = [velocity](float t) {return velocity; };

	// position is velocity after integration
	m_position += integrate(v, interval);

	m_primitive->setPosition(m_position.v3());
}

void RigidBody::updateOrientation(float duration)
{
	Quaternion fromAngularVelocity = Quaternion(0, m_angularVelocity);

	Quaternion angularVariation = (fromAngularVelocity * m_orientation) * (duration / 2);

	m_orientation = m_orientation + angularVariation;
	m_matrixOrientation = Matrix3::FromQuaternion(m_orientation);

	m_primitive->setOrientation(m_orientation.q());
}

of3dPrimitive* RigidBody::getPrimitives() const { return m_primitive; }
