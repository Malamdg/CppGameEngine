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

	bool hasContact() const;
	Vector3D* getContactPoint() const;
	Vector3D* getNormal() const;
	float getPenetration() const;
	RigidBody* getBody(int i = 0) const;
	float getRestitution() const;
	float getFriction() const;

};