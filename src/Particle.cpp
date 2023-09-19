#include "Particle.h"


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

void Particle::Update()
{
	//Deux intégration
	m_position += m_velocity;

	this->setPosition(m_position.v3());
}

float Particle::getInverseMasse()
{
	return 1 / m_masse;
}