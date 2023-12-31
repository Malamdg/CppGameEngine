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
	/*
	class constructor

	@param particle, the other particle linked to the Elastic
	@param elasticity, the elasticity of the spring
	@param lenght, the lenght of the spring
	@param C, a coefficient
	*/
	Spring(Particle* particle, float elasticity = 1, float lenght = 10, float C = 1);
	/*
	class constructor

	@param rb, the other RigidBody linked to the Elastic
	@param elasticity, the elasticity of the spring
	@param lenght, the lenght of the spring
	@param C, a coefficient
	*/
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
	/*
	update the RigidBody's force

	@param *rb, the RigidBody to update
	@param duration, frame duration when the spring's force applies
	*/
	void updateForce(RigidBody* rb, float duration, Vector3D* rbPoint = new Vector3D());


private:
	/*
	update the object's force when it is linked to a point

	@param *particle, the particle to update
	@param duration, frame duration when the spring's force applies
	*/
	void updateForPoint(Particle* particle, float duration);
	/*
	update the object's force when it is linked to a point

	@param *rb, the RigidBody to update
	@param duration, frame duration when the spring's force applies
	*/
	void updateForPoint(RigidBody* rb, float duration, Vector3D* rbPoint = new Vector3D());

	/*
	update the object's force when it is linked to a particle

	@param *particle, the particle to update
	@param duration, frame duration when the spring's force applies
	*/
	void updateForParticle(Particle* particle, float duration);
	/*
	update the object's force when it is linked to a particle

	@param *rb, the RigidBody to update
	@param duration, frame duration when the spring's force applies
	*/
	void updateForParticle(RigidBody* rb, float duration, Vector3D* rbPoint = new Vector3D());

	/*
	update the object's force when it is linked to a RigidBody

	@param *particle, the particle to update
	@param duration, frame duration when the spring's force applies
	*/
	void updateForRigidBody(Particle* particle, float duration);
	/*
	update the object's force when it is linked to a RigidBody

	@param *rb, the RigidBody to update
	@param duration, frame duration when the spring's force applies
	*/
	void updateForRigidBody(RigidBody* rb, float duration, Vector3D* rbPoint = new Vector3D());
};
