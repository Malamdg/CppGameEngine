#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector3D.h"

class ParticleFriction : public ParticleForceGenerator {
	/* first coefficient friction */
	float m_k1 = 0.05;

	/* second coefficient friction */
	float m_k2 = 0.01;

	/* particle's speed */
	Vector3D m_velocity = Vector3D();

	/*
	class constructor

	@param velocity, particle's speed
	*/
	ParticleFriction::ParticleFriction(Vector3D velocity) : m_velocity(velocity) {}

	/*
	update the particle's gravity

	@param *particle, the particle to update
	@param duration, frame duration when the gravity applies
	*/
	virtual void updateForce(Particle* particle, float duration) {
		float norm_v = m_velocity.Norm();
		float coeff = m_k1 * norm_v + m_k2*norm_v*norm_v;
		Vector3D direction = m_velocity;
		direction.Normalize();
		particle->addForce(direction*coeff);
	}
};