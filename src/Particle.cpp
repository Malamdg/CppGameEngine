#include "Particle.h"
#include "MathHelper.h"

/*
class constructor
Gravity is normally constant and could have been global. 
However, here it is specific to each particle, which allows greater modularity.
*/
Particle::Particle(int radius,
	Vector3D position,
	Vector3D velocity,
	float invertedMasse,
	Vector3D gravity)
	:
	ofSpherePrimitive(),
	m_position(position),
	m_velocity(velocity),
	m_gravity(gravity),
	m_acceleration(gravity),
	m_invertedMasse(invertedMasse),
	m_velocityInit(velocity)
{
	this->setRadius(radius);
	this->setPosition(position.v3());
	this->setColor(Vector3D());
}

Particle::~Particle(){}

/*
update position
update the position of a particle using particle's parameters
*/
void Particle::Update()
{
	float fps;
	fps = ofGetFrameRate();

	// if no fps no movement && avoid division by zero
	if (fps != 0) {
		float interval[2] = { 0, 1 / fps };

		// integrate acceleration to update velocity
		const Vector3D acceleration = m_acceleration;
		auto a = [acceleration](float t) { return acceleration; };
		m_velocity += integrate(a, interval);

		// integrate velocity to update position
		const Vector3D velocity = m_velocity;
		function<Vector3D(float)> v = [velocity](float t) { return velocity; };
		m_position += integrate(v, interval);

		this->setPosition(m_position.v3());

		// floor is attained
		if (m_position[1] <= 0) {
			// first time 
			if (m_velocity[1] < 0) {
				m_acceleration[1] = 0;
				m_velocity[1] = 0;
			}
			
			if (m_velocity[0] > 0 || m_velocity[2] > 0) {
				// Add drag coefficient to simulate friction
				m_acceleration += m_velocity * -m_dumping * this->getInverseMasse(); // divide by mass to be coherent with FPD
			}

			// Do put coefficent to 0 only once
			if (m_velocity[0] < 0) {
				m_velocity[0] = 0;
			}
			
			// Do put coefficent to 0 only once
			if (m_velocity[2] < 0) {
				m_velocity[2] = 0;
			}
		}
	}
}


void Particle::setMasse(float masse)
{
	if (masse <= 0)
	{
		throw std::exception("Masse has to be strictly positive - setting an infini masse");
		m_invertedMasse = 0;
	}
	else m_invertedMasse = 1 / masse;
}

/*
get the inverse of the particle's mass

@return the inverse of the particle's mass
*/
float Particle::getInverseMasse()
{
	return m_invertedMasse;
}

void Particle::setColor(Vector3D v)
{
	m_color = v;
}

Vector3D Particle::getColor()
{
	return m_color;
}