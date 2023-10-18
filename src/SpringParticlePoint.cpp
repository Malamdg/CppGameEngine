#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector3D.h"

class SpringParticlePoint : public ParticleForceGenerator {
	/* elasticity constant */
	float m_k;

	/* length at sleep */
	float m_l0;

	/*
	class constructor

	@param elasticity, elasticity constant
	*/
	SpringParticlePoint::SpringParticlePoint(float elasticity) : m_k(elasticity) {}

	/*
	update the particle's gravity

	@param *particle, the particle to update
	@param duration, frame duration when the gravity applies
	*/
	virtual void updateForce(Particle* particle, float duration) 
	{
		particle->addForce(m_k * (1 / particle->getInverseMass()));
	}
};