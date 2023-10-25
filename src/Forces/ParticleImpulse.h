#pragma once

#include "../Particle.h"
#include "ParticleForceGenerator.h"
#include "../Vector3D.h"

class ParticleImpulse : public ParticleForceGenerator
{
private:
	/* Impulsion Force */
	Vector3D m_impulsion;

public:
	/*
	class constructor

	@param impulse, the vector associated to the impulsion's force
	*/
	ParticleImpulse(Vector3D impulse);

	/*
	class destructor
	*/
	~ParticleImpulse();

	/*
	update the particle's gravity

	@param *particle, the particle to update
	@param duration, frame duration when the gravity applies
	*/
	void updateForce(Particle* particle, float duration) override;
};