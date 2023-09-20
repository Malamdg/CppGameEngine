#pragma once
#include "Vector3D.h"


class Particle : public ofSpherePrimitive
{
private:
	Vector3D m_position;
	Vector3D m_velocity;
	Vector3D m_acceleration;
	float m_invertedMasse;
	Vector3D m_gravity;

	Vector3D m_velocityInit;
	float m_dumping = 0.01;
	Vector3D m_color;

public:
	Particle(int radius = 10,
		Vector3D position = Vector3D(),
		Vector3D velocity = Vector3D(),
		float invertedMasse = 0,
		Vector3D gravity = Vector3D(0, -9.8, 0));
	~Particle();

	void Update();

	void setMasse(float masse);
	float getInverseMasse();

};