#include "ParticleFriction.h"

ParticleFriction::ParticleFriction(float k1, float k2) 
	: m_k1(k1), m_k2(k2) 
{}

ParticleFriction::~ParticleFriction() { }

void ParticleFriction::updateForce(Particle* particle, float duration)
{
	m_velocity = particle->getVelocity();
	float norm_v = m_velocity.Norm();

	/* Computation of the velocity-dependant coeff according to the given formula */
	float coeff = m_k1 * norm_v + m_k2 * norm_v * norm_v;

	Vector3D direction = m_velocity;

	/* Force director vector */
	direction.Normalize();
	particle->addForce(direction * (-coeff));
}
