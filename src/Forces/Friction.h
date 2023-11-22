#pragma once

#include "ForceGenerator.h"

class Friction : public ForceGenerator
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
	Friction(float k1, float k2);

	/*
	class destructor
	*/
	~Friction();

	/*
	update the particle's force

	@param *particle, the particle to update
	@param duration, frame duration when the friction applies
	*/
	void updateForce(Particle* particle, float duration) override;

	/*
	update the RigidBody's force

	@param *rb, the RigidBody to update
	@param duration, frame duration when the friction applies
	*/
	void updateForce(RigidBody* rb, float duration) override;
};
