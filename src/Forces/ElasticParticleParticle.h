#pragma once

#include "../Particle.h"
#include "ParticleForceGenerator.h"
#include "../DataStructures/Vector3D.h"


class ElasticParticleParticle : public ParticleForceGenerator {

private:
	/* Particle attached */
	Particle* m_particle;

	/* elasticity constant */
	float m_k;

	/* length at sleep */
	float m_l0;

	/* Damping Coefficient */
	float m_C;

	/* Damping ratio */
	float m_z;

	/* Oscilation pulse */
	float m_w;

public:
	/*
	class constructor

	@param particle, the pointer to the particle where the spring is attached
	@param elasticity, the elasticity of the spring
	@param lenght, the lenght of the spring
	@param C, a coefficient
	*/
	ElasticParticleParticle(Particle* particle, float elasticity = 1, float lenght = 10, float C = 1);

	/*
	class desctructor
	*/
	~ElasticParticleParticle();

	/*
	update the particle's force

	@param particle, pointer to the particle to update
	@param duration, frame duration when the elastic's force applies
	*/
	virtual void updateForce(Particle* particle, float duration);
};