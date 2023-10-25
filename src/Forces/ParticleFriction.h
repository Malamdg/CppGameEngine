#pragma once

#include "../Particle.h"
#include "ParticleForceGenerator.h"
#include "../Vector3D.h"

class ParticleFriction : public ParticleForceGenerator
{
private:
	/* first coefficient friction */
	float m_k1;

	/* second coefficient friction */
	float m_k2;

	/* particle's speed */
	Vector3D m_velocity = Vector3D();

public:
	/*
	class constructor

	@param velocity, particle's speed
	*/
	ParticleFriction(float k1, float k2);

	/*
	class destructor
	*/
	~ParticleFriction();

		/*
	update the particle's force

	@param *particle, the particle to update
	@param duration, frame duration when the friction applies
	*/
	void updateForce(Particle* particle, float duration) override;
};