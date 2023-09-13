#include "Particle.h"


Particle::Particle(int radius,
	Vector3D position = Vector3D(),
	Vector3D velocity = Vector3D(),
	Vector3D acceleration = Vector3D(),
	float masse = 0,
	float gravity = 9.8)
	:
	ofSpherePrimitive(),
	m_position(position),
	m_velocity(velocity),
	m_masse(masse),
	m_velocityInit(velocity)
{
	this->setRadius(radius);
	this->setPosition(position.v3());
	m_acceleration = m_masse * m_gravity;
}

Particle::~Particle(){}

void Particle::Update()
{
	//Deux intégration
	m_position += m_velocity;
}

float Particle::getInverseMasse()
{
	return 1 / m_masse;
}