#include "Gravity.h"

/*
class constructor

@param gravity, the vector associated to gravity
*/
Gravity::Gravity(Vector3D gravity)
	: 
	ForceGenerator(),
	m_gravity(gravity)
{ }

/*
class destructor
*/
Gravity::~Gravity() { }

/*
update the particle's gravity

@param *particle, the particle to update
@param duration, frame duration when the gravity applies
*/
void Gravity::updateForce(Particle* particle, float duration)
{
	if (particle->getInverseMass() != 0)
	{
		Vector3D gravity = m_gravity * (1 / particle->getInverseMass());
		particle->addForce(gravity);
	}
}
void Gravity::updateForce(RigidBody* rb, float duration, Vector3D *rbPoint)
{
	if (rb->getInverseMass() != 0)
	{
		Vector3D gravity = m_gravity * (1 / rb->getInverseMass());
		rb->addForce(gravity);
	}
}