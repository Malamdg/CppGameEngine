#pragma once

#include "ForceGenerator.h"

class Elastic : public ForceGenerator {

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

	/* Oscilation frenquency */
	float m_w;

public:
	/*
	class constructor

	@param position, the position of the point where the spring is attached
	@param elasticity, the elasticity of the spring
	@param lenght, the lenght of the spring
	@param C, a coefficient value
	*/
	Elastic(Vector3D* position, float elasticity = 1, float lenght = 10, float C = 1);
	/*
	class constructor

	@param particle, the other particle linked to the Elastic
	@param elasticity, the elasticity of the spring
	@param lenght, the lenght of the spring
	@param C, a coefficient value
	*/
	Elastic(Particle* particle, float elasticity = 1, float lenght = 10, float C = 1);

	/*
	class constructor

	@param rb, the other RigidBody linked to the Elastic
	@param elasticity, the elasticity of the spring
	@param lenght, the lenght of the spring
	@param C, a coefficient value
	*/
	Elastic(RigidBody* rb, float elasticity = 1, float lenght = 10, float C = 1);

	/*
	class desctructor
	*/
	~Elastic();

	/*
	update the object's force

	@param particle, pointer to the particle to update
	@param duration, frame duration when the spring's force applies
	*/
	virtual void updateForce(Particle* particle, float duration);
	/*
	update the object's force

	@param rb, pointer to the RigidBody to update
	@param duration, frame duration when the elastic's force applies
	*/
	virtual void updateForce(RigidBody* rb, float duration, Vector3D* rbPoint = new Vector3D());


private:
	/*
	update the object's force in case it is linked to a point

	@param particle, pointer to the particle to update
	@param duration, frame duration when the elastic's force applies
	*/
	void updateForPoint(Particle* particle, float duration);
	/*
	update the object's force in case it is linked to a point

	@param rb, pointer to the RigidBody to update
	@param duration, frame duration when the elastic's force applies
	*/
	void updateForPoint(RigidBody* rb, float duration, Vector3D* rbPoint = new Vector3D());

	/*
	update the object's force in case it is linked to a particle

	@param particle, pointer to the particle to update
	@param duration, frame duration when the elastic's force applies
	*/
	void updateForParticle(Particle* particle, float duration);
	/*
	update the object's force in case it is linked to a particle

	@param rb, pointer to the RigidBody to update
	@param duration, frame duration when the elastic's force applies
	*/
	void updateForParticle(RigidBody* rb, float duration, Vector3D* rbPoint = new Vector3D());

	/*
	update the object's force in case it is linked to a RigidBody

	@param particle, pointer to the particle to update
	@param duration, frame duration when the elastic's force applies
	*/
	void updateForRigidBody(Particle* particle, float duration);
	/*
	update the object's force in case it is linked to a RigidBody

	@param rb, pointer to the RigidBody to update
	@param duration, frame duration when the elastic's force applies
	*/
	void updateForRigidBody(RigidBody* rb, float duration, Vector3D* rbPoint = new Vector3D());
};
