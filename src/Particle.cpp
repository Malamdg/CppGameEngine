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
	m_acceleration(acceleration),
	m_masse(masse),
	m_velocityInit(velocity)
{
	this->setRadius(radius);
	this->setPosition(position.v3());
}

Particle::~Particle(){}

void Particle::Update()
{

}

float Particle::getInverseMasse()
{
	return 1 / m_masse;
}