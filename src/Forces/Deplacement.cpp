#include "Deplacement.h"

Deplacement::Deplacement(float deplacementForce)
	:
	ForceGenerator(),
	m_force(Vector3D(deplacementForce))
{ }

Deplacement::~Deplacement() { }

void Deplacement::updateForce(Particle* particle, float duration)
{
	if (particle->getInverseMass() != 0)
	{
		particle->addForce(m_force * (1 / particle->getInverseMass()));
	}
}
void Deplacement::updateForce(RigidBody* rb, float duration)
{
	if (rb->getInverseMass() != 0)
	{
		rb->addForce(m_force * (1 / rb->getInverseMass()));
	}
}