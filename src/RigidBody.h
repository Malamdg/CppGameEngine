#pragma once

#include "DataStructures/Vector3D.h"
#include "DataStructures/Quaternion.h"

class RigidBody
{
private:
	of3dPrimitive* m_primitive; // Only one for now, if we want to expand it to create complex objects, we can turn this into a list later

	// Deplacement du centre de masse depuis la position
	Vector3D m_centerOfMass;

	Vector3D m_position;
	Vector3D m_direction;
	Vector3D m_velocity;
	Vector3D m_acceleration;
	Quaternion m_angularVelocity;
	float m_invertedMass;

	float m_drag_coef;
	Vector3D m_accumForce;

	float m_frictionK1;
	float m_frictionK2;

	// When a collision occurs, the coefficient is used to know the amount of energy absorbed by the particle (if coeff = 1, then nothing is absorbed)
	float m_coeffRestitutions = 1;

	/*
	* private function to implement Euler integration
	*/
	

public:
	RigidBody(of3dPrimitive* primitive = new ofBoxPrimitive(),
		Vector3D centerOfMass = Vector3D(),
		Vector3D position = Vector3D(),
		Vector3D direction = Vector3D(1, 0, 0),
		Vector3D initVelocity = Vector3D(),
		float invertedMass = 0,
		float dragCoeff = 0,
		float frictionK1 = 0,
		float frictionK2 = 0,
		float coeffRestitutions = 1);

	~RigidBody();
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
	/*
	* public method to be called in ofMain's update
	* do the update job to the particle
	*/
	void Update();

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

	void addVelocity(Vector3D velocity);

	/*
	get the position of the particle

	@return the position of the particle
	*/
	Vector3D getPosition();

	/*
	add a vector to the current position of the particle

	@param position, the vector added to the current position
	*/
	void addPosition(Vector3D position);

	Vector3D getAcceleration();

	/*
	get the coefficient of restitution

	@return the coefficient of restitution
	*/
	float getCoefficientRestitution();

	float getK1();
	float getK2();

	of3dPrimitive* getPrimitives() const;
};