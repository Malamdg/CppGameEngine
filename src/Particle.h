#pragma once
#include "Vector3D.h"


class Particle : public ofSpherePrimitive
{
private:
	Vector3D m_position;
	Vector3D m_velocity;
	Vector3D m_acceleration;
	float m_invertedMass;
	Vector3D m_gravity;

	Vector3D m_velocityInit;
	float m_drag_coef = 0.005;
	Vector3D m_color;

	/*
	* private function to implement Euler integration
	*/
	Vector3D integrate(function<Vector3D(float)> f, float interval[2], int N = 100);

	/*
	* private method to update acceleration given the duration of the frame
	*/
	void updateAcceleration(float duration);

	/*
	* private method to update velocity given the duration of the frame
	*/
	void updateVelocity(float duration);
	
	/*
	* private method to update position given the duration of the frame
	*/
	void updatePosition(float duration);

public:
	/*
	* class constructor
	* @param radius, the radius of the particle set to 10 by default
	* @param position, a vector to set the initial position of the particle
	* @param velocity, a vector to set the initial velocity of the particle
	* @param masse, the mass of the particle set to 0 (it is a particle)
	* @param gravity, set to earth gravity but can be updated
	*
	* NOTE : Gravity is normally constant and could have been global.
	* However, here it is specific to each particle, which allows greater modularity.
	*/
	Particle(int radius = 10,
		Vector3D position = Vector3D(),
		Vector3D velocity = Vector3D(),
		float invertedMass = 0,
		Vector3D gravity = Vector3D(0, -9.8, 0));
	~Particle();

	/*
	* public method to be called in ofMain's update
	* do the update job to the particle
	*/
	void Update();

	/*
	* set the particle's mass
	* 
	* @param mass, the particle's mass
	*/
	void setMass(float mass);

	/*
	* get the inverse of the particle's
	* 
	* @return the inverse of the particle's mass
	*/
	float getInverseMass();
};
