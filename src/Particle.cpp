#include "Particle.h"

/*
Gravity is normally constant and could have been global. 
However, here it is specific to each particle, which allows greater modularity.
*/
Particle::Particle(int radius,
	Vector3D position,
	Vector3D velocity,
	float invertedMass)
	:
	ofSpherePrimitive(),
	m_position(position),
	m_velocity(velocity),
	m_acceleration(0),
	m_invertedMass(invertedMass),
	m_velocityInit(velocity),
	m_accumForce(0)
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
	m_accumForce += force;
}

void Particle::clearAccum()
{
	m_accumForce = Vector3D();
}

Vector3D Particle::integrate(function<Vector3D(float)> f, float interval[2], int N)
{
	float h = (interval[1] - interval[0]) / N;
	Vector3D u = Vector3D();
	for (int k = 0; k < N; k++) {
		u += f(interval[0] + k * h) * h;
	}

	return u;
}

void Particle::updateAcceleration() {
	m_acceleration = m_accumForce * m_invertedMass;
	m_accumForce = 0;
}

void Particle::updateVelocity(float duration) {
	float interval[2] = { 0.0, duration };

	Vector3D acceleration = m_acceleration;

	function<Vector3D(float)> a = [acceleration](float t) {return acceleration; };

	m_velocity += integrate(a, interval);
}

void Particle::updatePosition(float duration) {
	float interval[2] = { 0.0, duration };
	Vector3D velocity = m_velocity;

	function<Vector3D(float)> v = [velocity](float t) {return velocity; };
	
	m_position += integrate(v, interval);

	this->setPosition(m_position.v3());

	/////////////////////////////////////////////////////////////
	/// todo remove if when forces generators are implemented ///
	/////////////////////////////////////////////////////////////

	// floor is attained - add friction
	if (m_position.y() <= 0) {
		// first time floor is attained
		if (m_velocity.y() < 0) {
			m_acceleration[1] = 0;
			m_velocity[1] = 0;
			m_position[1] = 0;
		}
		
		// if x velocity is not null
		if (m_velocity.x() > 0) {
			// Add drag coefficient to simulate friction
			m_velocity -= m_velocity * m_drag_coef * m_invertedMass; // divide by mass to be coherent with FPD
		}

		// Do put coefficent to 0 only once
		if (m_velocity.x() <= 0) {
			m_velocity[0] = 0;
			m_acceleration[0] = 0;
		}
	}
}

Vector3D Particle::getVelocity() { return m_velocity; }

Vector3D Particle::getPosition() { return m_position; }

void Particle::addPosition(Vector3D newPosition)
{
	m_position = m_position + newPosition;
}