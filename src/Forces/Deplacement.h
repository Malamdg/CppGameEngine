#pragma once

#include "ForceGenerator.h"

class Deplacement : public ForceGenerator {

private:

	/* Force's Deplacement*/
	Vector3D m_force;

public:
	/*
	class constructor

	@param deplacementForce, value of the force's deplacement
	*/
	Deplacement(float deplacementForce);

	/*
	class desctructor
	*/
	~Deplacement();

	/*
	update the particle's force

	@param *particle, the particle to update
	@param duration, frame duration when the force applies
	*/
	virtual void updateForce(Particle* particle, float duration);

	/*
	update the RigidBody's force

	@param *rb, the RigidBody to update
	@param duration, frame duration when the force applies
	*/
	virtual void updateForce(RigidBody* rb, float duration);
};
