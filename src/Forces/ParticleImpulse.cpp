#include "ParticleImpulse.h"

ParticleImpulse::ParticleImpulse(Vector3D impulse)
	:
	ParticleForceGenerator(),
	m_impulsion(impulse)
{ }

ParticleImpulse::~ParticleImpulse() { }

void ParticleImpulse::updateForce(Particle* particle, float duration)
{
	if (particle->getInverseMass() != 0)
	{
		particle->addForce(m_impulsion * (1 / particle->getInverseMass()) * duration);
	}
}