#pragma once
#include "DataStructures/Vector3D.h"


class Particle : public ofSpherePrimitive
{
private:
	Vector3D m_position;
	Vector3D m_velocity;
	Vector3D m_acceleration;
	float m_invertedMass;

	Vector3D m_velocityInit;
	float m_drag_coef = 0.005;
	Vector3D m_color;
	Vector3D m_accumForce;

	float m_frictionK1;
	float m_frictionK2;

	// When a collision occurs, the coefficient is used to know the amount of energy absorbed by the particle (if coeff = 1, then nothing is absorbed)
	float m_coefficientRestitutions = 1;

	/*
	private function to implement Euler integration

 	@param f, the function to integrate
  	@param interval[2], integration terminals
   	@param N, number of steps
	*/
	Vector3D integrate(function<Vector3D(float)> f, float interval[2], int N = 100);

	/*
	* private method to update acceleration given the duration of the frame
	*/
	void updateAcceleration();

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
		float coefficientRestitution = 1,
		float frictionK1 = 0,
		float frictionK2 = 0);

	/*
	* class destructor
	*/
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

	/*
	add a Force to the particle

	@param Force, the new Force applied to the particle
	*/
	void addForce(const Vector3D& force);

	/*
	clear the force accumulator assigned to the particle
	*/
	void clearAccum();

	/*
	Getter Velocity

	@return the velocity of the particle
	*/
	Vector3D getVelocity();

	/*
	To add a velocity to the current velocity

	@param velocity, the velocity to add
	*/
	void addVelocity(Vector3D velocity);

	/*
	get the position of the particle

	@return the position of the particle
	*/
	Vector3D getPosition();

	/*
	add a vector to the current position of the particle

	@param newPosition, the vector added to the current position
	*/
	void addPosition(Vector3D newPosition);

	/*
	get the Acceleration of the particle

	@return the Acceleration of the particle
	*/
	Vector3D getAcceleration();

	/*
	get the coefficient of restitution

	@return the coefficient of restitution
	*/
	float getCoefficientRestitution();

	/*
	get the first friction's coefficient of the particle

	@return the first friction's coefficient
	*/
	float getK1();
	/*
	get the second friction's coefficient of the particle

	@return the second friction's coefficient
	*/
	float getK2();
};
