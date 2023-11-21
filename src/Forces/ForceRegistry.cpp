#include "ForceRegistry.h"

ForceRegistry::ForceRegistry()
{
	m_particleRegistry = ParticleRegistry();
	m_rigidBodyRegistry = RigidBodyRegistry();
}

ForceRegistry::~ForceRegistry() { }


void ForceRegistry::add(Particle* particle, ForceGenerator* Fg)
{
	// Create a new registration
	ParticleForceRegistration forceRegistration;
	// filling the registration
	forceRegistration.particle = particle;
	forceRegistration.Fg = Fg;
	// add the registration to the registry
	m_particleRegistry.push_back(forceRegistration);
}
void ForceRegistry::add(RigidBody* rb, ForceGenerator* Fg)
{
	// Create a new registration
	RigidBodyForceRegistration forceRegistration;
	// filling the registration
	forceRegistration.rigidbody = rb;
	forceRegistration.Fg = Fg;
	// add the registration to the registry
	m_rigidBodyRegistry.push_back(forceRegistration);
}

void ForceRegistry::remove(Particle* particle, ForceGenerator* Fg)
{
	// finding the right particle/force combination in the registry
	for (auto it = m_particleRegistry.begin(); it != m_particleRegistry.end(); it++)
	{
		if (it->particle == particle && it->Fg == Fg)
		{
			m_particleRegistry.erase(it);
		}
	}
}
void ForceRegistry::remove(RigidBody* rb, ForceGenerator* Fg)
{
	// finding the right rigidbody/force combination in the registry
	for (auto it = m_rigidBodyRegistry.begin(); it != m_rigidBodyRegistry.end(); it++)
	{
		if (it->rigidbody == rb && it->Fg == Fg)
		{
			m_rigidBodyRegistry.erase(it);
		}
	}
}

void ForceRegistry::clear()
{
	m_particleRegistry.clear();
	m_rigidBodyRegistry.clear();
}

void ForceRegistry::updateForces(float duration)
{
	// for each registration, we compute the force applied to the corresponding particle
	for (auto it = m_particleRegistry.begin(); it != m_particleRegistry.end(); it++)
	{
		it->Fg->updateForce(it->particle, duration);
	}
	// for each registration, we compute the force applied to the corresponding rigidbody
	for (auto it = m_rigidBodyRegistry.begin(); it != m_rigidBodyRegistry.end(); it++)
	{
		it->Fg->updateForce(it->rigidbody, duration);
	}

	m_particleRegistry.clear();
	m_rigidBodyRegistry.clear();
}
