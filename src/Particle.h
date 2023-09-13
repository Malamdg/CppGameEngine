#pragma once
#include "Vector3D.h"


class Particle : ofSpherePrimitive
{

private:

	Vector3D m_position;
	Vector3D m_velocity;
	Vector3D m_acceleration;
	float m_masse;


public:
	Particle(int radius, Vector3D position = Vector3D(),
		Vector3D velocity = Vector3D(),
		Vector3D acceleration = Vector3D(),
		float masse = 0);
	~Particle();

	float getInverseMasse();

};