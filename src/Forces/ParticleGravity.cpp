#include "../Particle.h"
#include "ParticleGravity.h"
#include "../Vector3D.h"

/*
class constructor

@param gravity, the vector associated to gravity
*/
ParticleGravity::ParticleGravity(Vector3D gravity)
	: 
	ParticleForceGenerator(),
	m_gravity(gravity)
{ }

/*
class destructor
*/
ParticleGravity::~ParticleGravity() { }

/*
update the particle's gravity

@param *particle, the particle to update
@param duration, frame duration when the gravity applies
*/
void ParticleGravity::updateForce(Particle* particle, float duration)
{
	if (particle->getInverseMass() != 0)
	{
		particle->addForce(m_gravity * (1 / particle->getInverseMass()));
	}
}