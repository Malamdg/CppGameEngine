#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector3D.h"

class ParticleFriction : public ParticleForceGenerator {
	/* first coefficient friction */
	float m_k1;

	/* second coefficient friction */
	float m_k2;

	/* particle's speed */
	Vector3D m_velocity = Vector3D();

	/*
	class constructor

	@param velocity, particle's speed
	*/
	ParticleFriction::ParticleFriction(float k1, float k2) : m_k1(k1), m_k2(k2) {}

	/*
	update the particle's gravity

	@param *particle, the particle to update
	@param duration, frame duration when the gravity applies
	*/
	virtual void updateForce(Particle* particle, float duration) {
		m_velocity = particle->getVelocity();
		float norm_v = m_velocity.Norm();
		float coeff = m_k1 * norm_v + m_k2*norm_v*norm_v;
		Vector3D direction = m_velocity;
		direction.Normalize();
		particle->addForce(direction*coeff);
	}
};