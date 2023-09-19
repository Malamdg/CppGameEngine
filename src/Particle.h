#pragma once
#include "Vector3D.h"


class Particle : public ofSpherePrimitive
{
private:
	Vector3D m_position;
	Vector3D m_velocity;
	Vector3D m_acceleration;
	float m_masse;
	Vector3D m_gravity;

	Vector3D m_velocityInit;

public:
	Particle(int radius = 10,
		Vector3D position = Vector3D(),
		Vector3D velocity = Vector3D(),
		float masse = 0,
		Vector3D gravity = Vector3D(0, 0, -9.8));
	~Particle();

	void Update();

	float getInverseMasse();
};