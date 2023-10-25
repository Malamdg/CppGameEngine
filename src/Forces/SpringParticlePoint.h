#pragma once

#include "../Particle.h"
#include "ParticleForceGenerator.h"
#include "../Vector3D.h"

class SpringParticlePoint : public ParticleForceGenerator
{
private:
	/* Point positon */
	Vector3D m_pointPosition;

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

	@param position, the position of the point where the spring is attached
	@param elasticity, the elasticity of the spring
	@param lenght, the lenght of the spring
	@param C, a coefficient
	*/
	SpringParticlePoint(Vector3D position, float elasticity = 1, float lenght = 10, float C = 1);

	/*
	class desctructor
	*/
	~SpringParticlePoint();

	/*
	update the particle's force

	@param *particle, the particle to update
	@param duration, frame duration when the spring's force applies
	*/
	void updateForce(Particle* particle, float duration) override;
};