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
	float masse,
	Vector3D gravity)
	:
	ofSpherePrimitive(),
	m_position(position),
	m_velocity(velocity),
	m_gravity(gravity),
	m_acceleration(gravity),
	m_masse(masse),
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

		// when floor is attained
		if (m_position[2] <= 0) {
			m_acceleration[2] = 0;
			m_velocity[2] = 0;
		}
	}
}

/*
get the inverse of the particle's mass

@return the inverse of the particle's mass
*/
float Particle::getInverseMasse()
{
	return 1 / m_masse;
}

void Particle::setColor(Vector3D v)
{
	m_color = v;
}

Vector3D Particle::getColor()
{
	return m_color;
}