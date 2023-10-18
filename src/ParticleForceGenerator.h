#include "Particle.h"

class ParticleForceGenerator
{
public:

	/*
	update the particle's force

	@param *particle, the particle to update
	@param duration, frame duration when the force applies
	*/
	virtual void updateForce(Particle* particle, float duration = 0);
};