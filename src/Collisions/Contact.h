#pragma once

#include <Vector3D.h>
#include <RigidBody.h>

class Contact
{
private:

	Vector3D* m_contactPoint;
	Vector3D* m_normal;
	float m_penetration;
	RigidBody* m_body1;
	RigidBody* m_body2;
	float m_restitution;
	float m_friction;

	/*
 	To compute the coefficient of Restitution

 	@return the coefficient
  	*/
	float calculateRestitution();

	/*
 	To compute the coefficient of Friction

 	@return the coefficient
  	*/
	float calculateFriction();

public:

	/*
 	Class Constructor

  	@param contactPosition, the position of the contact
   	@param normalContact, the normal of the contact
    	@param penetration, the depth of the penetration
     	@param body1, the first RigidBody implied
      	@param body2, the second RigidBody implied
  	*/
	Contact(Vector3D* contactPosition,
	Vector3D* normalContact,
	float penetration,
	RigidBody* body1,
	RigidBody* body2);
	/*
 	Class Destructor
  	*/
	~Contact();

	Vector3D* getContactPoint() const;

	/*
 	To get the normal of the contact

	@return the normal vector
  	*/
	Vector3D* getNormal() const;

	/*
 	To get the penetration depth

	@return the depth
  	*/
	float getPenetration() const;

	/*
 	To get the i-th RigidBody implied

 	@param i, the number of the RigidBody to get
	@return the i-th RigidBody
  	*/
	RigidBody* getBody(int i = 0) const;

	/*
 	To get the restitution coefficient

	@return the coefficient
  	*/
	float getRestitution() const;

	/*
 	To get the friction coefficient

	@return the coefficient
  	*/
	float getFriction() const;

};
