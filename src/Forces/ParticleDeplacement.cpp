#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector3D.h"

class ParticleDeplacement : public ParticleForceGenerator {

private:

	/* Force's Deplacement*/
	Vector3D m_force;

public:
	/*
	class constructor

	@param deplacementForce, value of the force's deplacement
	*/
	ParticleDeplacement::ParticleDeplacement(float deplacementForce)
		:
		ParticleForceGenerator(),
		m_force(Vector3D(deplacementForce))
	{ }

	ParticleDeplacement::~ParticleDeplacement() { }

	/*
	update the particle's force

	@param *particle, the particle to update
	@param duration, frame duration when the force applies
	*/
	virtual void updateForce(Particle* particle, float duration)
	{
		if (particle->getInverseMass() != 0)
		{
			particle->addForce(m_force * (1 / particle->getInverseMass()));
		}
	}
};