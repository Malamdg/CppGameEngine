#pragma once

#include "DataStructures/Vector3D.h"
#include "DataStructures/Quaternion.h"
#include "DataStructures/Matrix3.h"
#include "DataStructures/Matrix4.h"

class RigidBody
{
private:
	list<of3dPrimitive*> m_primitives;

	// Handle center of masse
	Vector3D m_centerOfMass;

	Vector3D m_position;

	Vector3D m_velocity;

	Quaternion m_orientation;

	Vector3D m_angularVelocity;

	float m_invertedMass;

	// Volume Box dimensions
	float m_length; // forward
	float m_width;	// right
	float m_height; // top

	float m_frictionK1;
	float m_frictionK2;

	// When a collision occurs, the coefficient is used to know the amount of energy absorbed by the RigidBody (if coeff = 1, then nothing is absorbed)
	float m_coeffRestitutions = 1;

	// Display center of mass
	ofSpherePrimitive* m_centerMass;

	// Accelerations
	Vector3D m_acceleration;
	Vector3D m_angularAcceleration;

	// Rotation
	Matrix3 m_matrixOrientation;

	// Transform matrix
	Matrix4 m_transformMatrix;

	// Inertia Tensors
	Matrix3 m_massCenterIntertiaTensor;

	Matrix3 m_invertedInertiaTensor;

	Vector3D m_accumForce;
	Vector3D m_accumTorque;

public:
	
	/*
	class constructor

	@param primitives, list of primitives and relatives position in the rigidbody
 	@param position, the position of the Rigidbody
  	@param initVelocity, the initial velocity
   	@param orientation, the orientation of the Rigidbody (it is not a RigidBody so the direction matters)
	@param initAngVelocity, the initial angular velocity of the RigidBody (it is not a RigidBody so the angular velocity matters)
    	@param invertedMass, inverted mass of the RigidBody
    	@param dragCoeff,
   	@param frictionK1, first coefficient of friction
    	@param frictionK2, second coefficient of friction
    	@param coeffRestitutions, coeffecient of restitution ; the coefficient is used to know the amount of energy absorbed by the RigidBody (if coeff = 1, then nothing is absorbed)
	*/
	RigidBody(list<pair<of3dPrimitive*, Vector3D>> primitives = list<pair<of3dPrimitive*, Vector3D>>(),
		Vector3D centerOfMass = Vector3D(),
		Vector3D position = Vector3D(),
		Vector3D initVelocity = Vector3D(),
		Quaternion orientation = Quaternion::Identity(),
		Vector3D initAngVelocity = Vector3D(),
		float invertedMass = 0,
		float length = 0,
		float width = 0,
		float height = 0,
		float frictionK1 = 0,
		float frictionK2 = 0,
		float coeffRestitutions = 1
	);

	/*
	class constructor from a RigidBody

  	@param rb, the RigidBody
 	*/
	RigidBody(RigidBody& rb);

	/*
	class destructor
 	*/
	~RigidBody();

	/*
	function to implement Euler integration

 	@param f, the function to integrate
  	@param interval[2], integration terminals
   	@param N, number of steps
	*/
	Vector3D integrate(function<Vector3D(float)> f, float interval[2], int N = 100);

	/*
	private method to update acceleration given the duration of the frame
	*/
	void updateAcceleration();

	/*
	private method to update velocity given the duration of the frame

  	@param duration, duration of the frame
	*/
	void updateVelocity(float duration);

	/*
	private method to update position given the duration of the frame
	
  	@param duration, duration of the frame
	*/
	void updatePosition(float duration);

	/*
	private method to update orientation given the duration of the frame
	
  	@param duration, duration of the frame
 	*/
	void updateOrientation(float duration);

	void updateTransformMatrix();

	void updateInertiaTensor();
	/*
	public method to be called in ofMain's update
	do the update job to the RigidBody
	*/
	void Update();

	/*
	get the inverse of the RigidBody's
	
	@return the inverse of the RigidBody's mass
	*/
	float getInverseMass();

	/*
	add a Force to the RigidBody on the center of mass
	if local point is diff from 0,0 then it generates a torque
	@param Force, the new Force applied to the RigidBody
	*/
	void addForce(const Vector3D& force, const Vector3D& localPoint = Vector3D());

	/*
	clear the force accumulator assigned to the RigidBody
	*/
	void clearAccum();

	/*
	Getter Velocity

	@return the velocity of the RigidBody
	*/
	Vector3D getVelocity() const;

	/*
	To add a velocity to the current velocity

	@param velocity, the velocity to add
	*/
	void addVelocity(Vector3D velocity);

	/*
	get the position of the RigidBody

	@return the position of the RigidBody
	*/
	Vector3D getPosition() const;

	/*
	To set the position of the RigidBody

	@param position, the new positions
	*/
	void setPosition(Vector3D position);

	/*
	add a vector to the current position of the RigidBody

	@param position, the vector added to the current position
	*/
	void addPosition(Vector3D position);

	/*
	get the Acceleration of the RigidBody

	@return the Acceleration of the RigidBody
	*/
	Vector3D getAcceleration() const;

	/*
	get the coefficient of restitution

	@return the coefficient of restitution
	*/
	float getCoefficientRestitution() const;

	/*
	get the first coefficient of friction

	@return the first coefficient of friction
	*/
	float getK1() const;
	/*
	get the second coefficient of friction

	@return the second coefficient of friction
	*/
	float getK2() const;

	// Get a given local point coordinates in world coordinates
	// @return the Vector3D of point in world coordinates
	Vector3D getWorldPosition(Vector3D* localPoint);

	// Get a given world point coordinates in local coordinates
	// @return the Vector3D of point in local coordinates
	Vector3D getLocalPosition(Vector3D* worldPoint);

	/*
	get the primitives

	@return the list of primitives
	*/
	list<of3dPrimitive*> getPrimitives() const;

	/*
	add a primitive to the RigidBody (to change its shape)

	@param primitive, the primitive to add
 	@param position, the position of the primitive
	*/
	void addPrimitive(of3dPrimitive* primitive, Vector3D position);
};
