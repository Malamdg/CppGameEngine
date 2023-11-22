#pragma once
#include "../Particle.h"
#include "../RigidBody.h"

class ForceGenerator
{
public:
	/*
	Class Constructor
	*/
	ForceGenerator();

	/*
	Class Destructor
	*/
	~ForceGenerator();

	/*
	update the particle's force

	@param *particle, the particle to update
	@param duration, frame duration when the force applies
	*/
	virtual void updateForce(Particle* particle, float duration = 0);

	/*
	update the rigidBody's force

	@param *rb, the rigidbody to update
	@param duration, frame duration when the force applies
	*/
	virtual void updateForce(RigidBody* rb,  float duration = 0, Vector3D* rbPoint = new Vector3D());
};