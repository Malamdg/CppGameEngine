#pragma once

#include "ForceGenerator.h"

class Spring : public ForceGenerator
{
private:
	/* Point positon */
	Vector3D* m_pointPosition;

	Particle* m_particle;

	RigidBody* m_rigidBody;

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
	Spring(Vector3D* position, float elasticity = 1, float lenght = 10, float C = 1);
	Spring(Particle* particle, float elasticity = 1, float lenght = 10, float C = 1);
	Spring(RigidBody* rb, float elasticity = 1, float lenght = 10, float C = 1);

	/*
	class desctructor
	*/
	~Spring();

	/*
	update the particle's force

	@param *particle, the particle to update
	@param duration, frame duration when the spring's force applies
	*/
	void updateForce(Particle* particle, float duration);
	void updateForce(RigidBody* rb, float duration);


private:
	void updateForPoint(Particle* particle, float duration);
	void updateForPoint(RigidBody* rb, float duration);

	void updateForParticle(Particle* particle, float duration);
	void updateForParticle(RigidBody* rb, float duration);

	void updateForRigidBody(Particle* particle, float duration);
	void updateForRigidBody(RigidBody* rb, float duration);
};