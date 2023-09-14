#include "Particle.h"
#include "MathHelper.h"
#include "ofMain.h"

Particle::Particle(int radius,
	Vector3D position,
	Vector3D velocity,
	float masse,
	float gravity)
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
	float time, fps;
	fps = ofGetFrameRate();
	// avoid division by zero
	time = fps == 0 ? -1 : 1 / fps;

	// if no fps no movement 
	if (time != -1) {
		// integrate acceleration to update velocity
		m_velocity += integrate(m_acceleration, time);

		// integrate speed to update position
		m_position += integrate(m_velocity, time);
	}
}

float Particle::getInverseMasse()
{
	return 1 / m_masse;
}