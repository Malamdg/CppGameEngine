#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector3D.h"

class ParticleFriction : public ParticleForceGenerator {
	/* coefficient of static friction */
	float m_mus;

	/* coefficient of kinetik friction */
	float m_muk;

	/*
	class constructor

	@param mus, coefficient of static friction
	@param muk, coefficient of kinetik friction
	*/
	ParticleFriction::ParticleFriction(float mus, float muk) : m_mus(mus), m_muk(muk) {}

	/*
	update the particle's gravity

	@param *particle, the particle to update
	@param duration, frame duration when the gravity applies
	*/
	virtual void updateForce(Particle* particle, float duration) {
		particle->addForce(m_mus * (1 / particle->getInverseMass());
	}
};