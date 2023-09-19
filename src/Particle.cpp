#include "Particle.h"

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
	m_masse(masse),
	m_velocityInit(velocity) 
{
	this->setRadius(radius);
	this->setPosition(position.v3());
	m_acceleration = m_gravity;
}

Particle::~Particle(){}

/*
update position 
update the position of a particle using particle's parameters
*/

@return
void Particle::Update()
{
	//Deux intégration
	m_position += m_velocity;

	this->setPosition(m_position.v3());
}

/*
get the inverse of the particle's mass

@return the inverse of the particle's mass
*/
float Particle::getInverseMasse()
{
	return 1 / m_masse;
}
