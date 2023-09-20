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

	Vector3D m_color;

public:
	Particle(int radius = 10,
		Vector3D position = Vector3D(),
		Vector3D velocity = Vector3D(),
		float masse = 0,
		Vector3D gravity = Vector3D(0, -9.8, 0));
	~Particle();

	void Update();

	float getInverseMasse();

	void setColor(Vector3D v);
	Vector3D getColor();
};