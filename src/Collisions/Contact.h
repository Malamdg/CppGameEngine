#pragma once

#include <Vector3D.h>
#include <RigidBody.h>

class Contact
{
private:

	bool contact;
	Vector3D* contactPoint;
	Vector3D* normal;
	float penetration;
	RigidBody* body1;
	RigidBody* body2;
	float restitution;
	float friction;

	float calculateRestitution();
	float calculateFriction();

public:

	Contact();
	Contact(Vector3D* contactPosition,
	Vector3D* normalContact,
	float penetration,
	RigidBody* body1,
	RigidBody* body2);
	~Contact();

	Vector3D* getContactPoint() const;
	Vector3D* getNormal() const;
	float getPenetration() const;
	RigidBody* getBody(int i = 0) const;
	float getRestitution() const;
	float getFriction() const;

};