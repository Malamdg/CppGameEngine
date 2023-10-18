#include "Particle.h"
#include "MathHelper.h"

/*
Gravity is normally constant and could have been global. 
However, here it is specific to each particle, which allows greater modularity.
*/
Particle::Particle(int radius,
	Vector3D position,
	Vector3D velocity,
	float invertedMass,
	Vector3D gravity)
	:
	ofSpherePrimitive(),
	m_position(position),
	m_velocity(velocity),
	m_gravity(gravity),
	m_acceleration(gravity),
	m_invertedMass(invertedMass),
	m_velocityInit(velocity)
{
	this->setRadius(radius);
	this->setPosition(position.v3());
}

Particle::~Particle(){}


void Particle::Update()
{
	float fps;
	fps = ofGetFrameRate();

	// if no fps no movement && avoid division by zero
	if (fps != 0) {
		float interval[2] = { 0, 1 / fps }; // integrate on frame duration = 1 / fps

		// integrate acceleration to update velocity
		const Vector3D acceleration = m_acceleration;
		function<Vector3D(float)> a = [acceleration](float t) { return acceleration; }; // function of acceleration over time
		m_velocity += integrate(a, interval);

		// integrate velocity to update position
		const Vector3D velocity = m_velocity;
		function<Vector3D(float)> v = [velocity](float t) { return velocity; }; // function of velocity over time
		m_position += integrate(v, interval);

		this->setPosition(m_position.v3());

		// floor is attained
		if (m_position.y() <= 0) {
			// first time 
			if (m_velocity.y() < 0) {
				m_acceleration[1] = 0;
				m_velocity[1] = 0;
				m_position[1] = 0;
			}
			
			// if x velocity is not null
			if (m_velocity.x() > 0) {
				// Add drag coefficient to simulate friction
				m_acceleration += m_velocity * -m_drag_coef * m_invertedMass; // divide by mass to be coherent with FPD
			}

			// Do put coefficent to 0 only once
			if (m_velocity.x() <= 0) {
				m_velocity[0] = 0;
				m_acceleration[0] = 0;
			}
		}
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

Vector3D Particle::getPosition()
{
	return m_position;
}