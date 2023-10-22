#include "Particle.h"
#include "ParticleForceRegistry.h"

ParticleForceRegistry::ParticleForceRegistry()
{
	m_registry = Registry();
}

ParticleForceRegistry::~ParticleForceRegistry() { }


void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* Fg)
{
	ParticleForceRegistration forceRegistration;
	forceRegistration.particle = particle;
	forceRegistration.Fg = Fg;
	m_registry.push_back(forceRegistration);
}

void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* Fg)
{
	for (auto it = m_registry.begin(); it != m_registry.end(); it++)
	{
		if (it->particle == particle && it->Fg == Fg)
		{
			m_registry.erase(it);
		}
	}
}

void ParticleForceRegistry::clear()
{
	m_registry.clear();
}

void ParticleForceRegistry::updateForces(float duration)
{
	for (auto it = m_registry.begin(); it != m_registry.end(); it++)
	{
		it->Fg->updateForce(it->particle, duration);
	}

	m_registry.clear();
}
