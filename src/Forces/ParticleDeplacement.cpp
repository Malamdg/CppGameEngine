#include "ParticleDeplacement.h"

ParticleDeplacement::ParticleDeplacement(float deplacementForce)
	:
	ParticleForceGenerator(),
	m_force(Vector3D(deplacementForce))
{ }

ParticleDeplacement::~ParticleDeplacement() { }

void ParticleDeplacement::updateForce(Particle* particle, float duration)
{
	if (particle->getInverseMass() != 0)
	{
		particle->addForce(m_force * (1 / particle->getInverseMass()));
	}
}