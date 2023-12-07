#include "RigidBody.h"

RigidBody::RigidBody(list<pair<of3dPrimitive*, Vector3D>> primitives,
	Vector3D centerOfMass,
	Vector3D position,
	Vector3D initVelocity,
	Quaternion orientation,
	Vector3D initAngVelocity,
	float invertedMass,
	float length,
	float width,
	float height, 
	float frictionK1,
	float frictionK2,
	float coeffRestitutions)
	: m_primitives(),
	m_centerOfMass(centerOfMass),
	m_position(position),
	m_velocity(initVelocity),
	m_orientation(orientation),
	m_matrixOrientation(Matrix3::FromQuaternion(orientation)),
	m_angularVelocity(initAngVelocity),
	m_invertedMass(invertedMass),
	m_length(length),
	m_width(width),
	m_height(height),
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

	if (Vector3D() == m_centerOfMass) {
		m_centerOfMass = m_position;
	}

	m_massCenterIntertiaTensor = Matrix3::Zeros();
	m_massCenterIntertiaTensor.at(0, 0) = 1.f / (12.f * m_invertedMass)* ((m_height * m_height) + (m_width * m_width));
	m_massCenterIntertiaTensor.at(1, 1) = 1.f / (12.f * m_invertedMass)* ((m_length * m_length) + (m_width * m_width));
	m_massCenterIntertiaTensor.at(2, 2) = 1.f / (12.f * m_invertedMass)* ((m_length * m_length) + (m_height * m_height));

	updateTransformMatrix();
	updateInertiaTensor();
}

RigidBody::RigidBody(RigidBody& rb)
	: m_position(rb.m_position),
	m_velocity(rb.m_velocity),
	m_orientation(rb.m_orientation),
	m_matrixOrientation(rb.m_matrixOrientation),
	m_angularVelocity(rb.m_angularVelocity),
	m_invertedMass(rb.m_invertedMass), 
	m_length(rb.m_length),
	m_width(rb.m_width),
	m_height(rb.m_height),
	m_frictionK1(rb.m_frictionK1),
	m_frictionK2(rb.m_frictionK2),
	m_coeffRestitutions(rb.m_coeffRestitutions),
	m_invertedInertiaTensor(rb.m_invertedInertiaTensor)
{
	m_centerMass = new ofSpherePrimitive();
	m_centerMass->setRadius(.25);

	m_primitives.push_back(m_centerMass);

	// Creating the shape of the RigidBody from the Primitive composing it
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

	if (Vector3D() == m_centerOfMass) {
		m_centerOfMass = m_position;
	}

	m_massCenterIntertiaTensor = Matrix3::Zeros();
	m_massCenterIntertiaTensor.at(0, 0) = 1.f / (12.f * m_invertedMass) * ((m_height * m_height) + (m_width * m_width));
	m_massCenterIntertiaTensor.at(1, 1) = 1.f / (12.f * m_invertedMass) * ((m_length * m_length) + (m_width * m_width));
	m_massCenterIntertiaTensor.at(2, 2) = 1.f / (12.f * m_invertedMass) * ((m_length * m_length) + (m_height * m_height));

	updateTransformMatrix();
	updateInertiaTensor();
}

RigidBody::~RigidBody()
{
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
	// Newton's law
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

	float damp = pow(.6, duration);
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
	m_centerOfMass += integrate(v, interval);

	m_centerMass->setPosition(m_centerOfMass.v3());

	updateTransformMatrix();
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

	updateTransformMatrix();

	// parallel axis
	updateInertiaTensor();
}

void RigidBody::updateTransformMatrix() {
	m_transformMatrix = Matrix4::augment(m_matrixOrientation, m_position);
}

void RigidBody::updateInertiaTensor() {
	float x, y, z;
	Vector3D localCoordinateCenterOfMass = m_centerOfMass - m_position;

	x = localCoordinateCenterOfMass.x();
	y = localCoordinateCenterOfMass.y();
	z = localCoordinateCenterOfMass.z();

	Matrix3 translateMatrix = Matrix3();

	translateMatrix.at(0, 0) = y * y + z * z;
	translateMatrix.at(0, 1) = -x * y;
	translateMatrix.at(0, 2) = -x * z;

	translateMatrix.at(1, 0) = -x * y;
	translateMatrix.at(1, 1) = x * x + z * z;
	translateMatrix.at(1, 2) = -y * z;

	translateMatrix.at(2, 0) = -x * z;
	translateMatrix.at(2, 1) = -y * z;
	translateMatrix.at(2, 2) = x * x + y * y;

	translateMatrix *= 1.f / m_invertedMass;

	cout << "Translate Matrix = " << translateMatrix.toString() << endl;
	cout << "Jcm = " << m_massCenterIntertiaTensor.toString() << endl;
	
	Matrix3 inertiaTensor = m_massCenterIntertiaTensor + translateMatrix;
	
	cout << "J' = " << inertiaTensor.toString() << endl;
	
	m_invertedInertiaTensor = inertiaTensor.Inverse();

	cout << "J-1 = " << m_invertedInertiaTensor.toString() << endl;

	Matrix3 transposedOrentation = m_matrixOrientation.Transposed();
	m_invertedInertiaTensor = m_matrixOrientation * m_invertedInertiaTensor;
	m_invertedInertiaTensor = m_invertedInertiaTensor * transposedOrentation;

	cout << "J-1' = " << m_invertedInertiaTensor.toString() << endl;
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
		updateTransformMatrix();
	}
}

float RigidBody::getInverseMass() { return m_invertedMass; }

void RigidBody::addForce(const Vector3D& force, const Vector3D& localPoint)
{
	// add the force to all the registry
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

Vector3D RigidBody::getVelocity() const { return m_velocity; }

void RigidBody::addVelocity(Vector3D velocity)
{
	m_velocity = m_velocity + velocity;
}

Vector3D RigidBody::getPosition() const { return m_position; }

void RigidBody::setPosition(Vector3D position)
{
	m_position = position;
}

void RigidBody::addPosition(Vector3D position)
{
	m_position = m_position + position;
}

Vector3D RigidBody::getAcceleration() const { return m_acceleration; }

float RigidBody::getCoefficientRestitution() const { return m_coeffRestitutions; }

float RigidBody::getK1() const { return m_frictionK1; }

float RigidBody::getK2() const { return m_frictionK2; }

Vector3D RigidBody::getWorldPosition(Vector3D* localPoint)
{
	Matrix4 invertTransform = m_transformMatrix.Inverse();
	Vector3D worldPoint = invertTransform * *localPoint;
	return worldPoint;
}

Vector3D RigidBody::getLocalPosition(Vector3D* worldPoint)
{
	Vector3D localPoint = m_transformMatrix * *worldPoint;
	return localPoint;
}

list<of3dPrimitive*> RigidBody::getPrimitives() const { return m_primitives; }

void RigidBody::addPrimitive(of3dPrimitive* primitive, Vector3D position)
{
	primitive->setParent(*m_centerMass);
	primitive->setPosition(position.v3());
	m_primitives.push_back(primitive);
}
