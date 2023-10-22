#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector3D.h"

class ParticleImpulse : public ParticleForceGenerator {

private:
	/* Impulsion Force */
	Vector3D m_impulsion;

public:
	/*
	class constructor

	@param impulse, the vector associated to the impulsion's force
	*/
	ParticleImpulse::ParticleImpulse(Vector3D impulse)
		:
		ParticleForceGenerator(),
		m_impulsion(impulse)
	{ }

	ParticleImpulse::~ParticleImpulse() { }

	/*
	update the particle's gravity

	@param *particle, the particle to update
	@param duration, frame duration when the gravity applies
	*/
	virtual void updateForce(Particle* particle, float duration)
	{
		if(particle->getInverseMass() != 0)
		{
			particle->addForce(m_impulsion * (1 / particle->getInverseMass()) * duration);
		}
	}
};