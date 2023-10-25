#include "Particle.h"

/*
Gravity is normally constant and could have been global. 
However, here it is specific to each particle, which allows greater modularity.
*/
Particle::Particle(int radius,
	Vector3D position,
	Vector3D velocity,
	float invertedMass,
	float coefficientRestitution,
	float frictionK1,
	float frictionK2)
	:
	ofSpherePrimitive(),
	m_position(position),
	m_velocity(velocity),
	m_acceleration(0),
	m_invertedMass(invertedMass),
	m_coefficientRestitutions(coefficientRestitution),
	m_frictionK1(frictionK1),
	m_frictionK2(frictionK2),
	m_velocityInit(velocity),
	m_accumForce(Vector3D())
{
	this->setRadius(radius);
	this->setPosition(position.v3());
}

Particle::~Particle(){}


void Particle::Update()
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

void Particle::setMass(float mass)
{
	if (mass <= 0)
	{
		throw std::exception("Mass has to be strictly positive - setting an infini masse");
		m_invertedMass = 0;
	}
	else m_invertedMass = 1 / mass;
}

float Particle::getInverseMass()  
{
	return m_invertedMass;
}

void Particle::addForce(const Vector3D &force) 
{
	m_accumForce = m_accumForce + force;
	std::cout << m_accumForce.toString() << std::endl;
}

void Particle::clearAccum()
{
	m_accumForce[0] = 0;
	m_accumForce[1] = 0;
	m_accumForce[2] = 0;
}

Vector3D Particle::integrate(function<Vector3D(float)> f, float interval[2], int N)
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

void Particle::updateAcceleration() {
	m_acceleration = m_accumForce * m_invertedMass;
	clearAccum();
}

void Particle::updateVelocity(float duration) {
	float interval[2] = { 0.0, duration };

	Vector3D acceleration = m_acceleration;

	function<Vector3D(float)> a = [acceleration](float t) {return acceleration; };

	// velocity is acceleration after integration
	m_velocity += integrate(a, interval);
}

void Particle::updatePosition(float duration) {
	float interval[2] = { 0.0, duration };
	Vector3D velocity = m_velocity;

	function<Vector3D(float)> v = [velocity](float t) {return velocity; };
	
	// position is velocity after integration
	m_position += integrate(v, interval);

	this->setPosition(m_position.v3());
}

Vector3D Particle::getPosition()
{
	return m_position;
}

void Particle::addPosition(Vector3D newPosition)
{
	m_position = m_position + newPosition;
}

Vector3D Particle::getAcceleration()
{
	return m_acceleration;
}

Vector3D Particle::getVelocity() { return m_velocity; }

void Particle::addVelocity(Vector3D velocity)
{
	m_velocity = m_velocity + velocity;
}

float Particle::getCoefficientRestitution()
{
	return m_coefficientRestitutions;
}

float Particle::getK1() { return m_frictionK1; }
float Particle::getK2() { return m_frictionK2; }