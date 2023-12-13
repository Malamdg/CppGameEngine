#pragma once

#include "Sphere.h"

Sphere::Sphere(RigidBody* rb, Vector3D* center, float radius)
	:
	Collider(rb, center),
	m_radius(radius)
{ }

/* Class Destructor */
Sphere::~Sphere() { }

/* The sphere doesn't need to rotate */
void Sphere::setRotation(Quaternion* rotation) {}

float Sphere::getRadius() { return m_radius; }

/*
to detect a collision bewteen two spheres

@param sphere, the other sphere
*/
list<Contact*> Sphere::intersect(Collider* collider)
{
	list<Contact*> res = list<Contact*>();
	
	// The sphere can only intersect with spheres
	if (instanceof<Sphere>(collider))
	{
		Contact* contact = intersection((Sphere*)collider);
		if(contact != nullptr) res.push_back(contact);
	}
	return res;
}

Contact* Sphere::intersection(Sphere* collider)
{
	Contact* res = nullptr;

	Vector3D direction = getPosition() - collider->getPosition();
	if (pow(direction.Norm(),2) < pow(m_radius + collider->getRadius(), 2))
	{
		Vector3D* normal = new Vector3D(direction);
		normal->Normalize();

		float penetration = m_radius + collider->getRadius() - direction.Norm();
		
		Vector3D* contact = new Vector3D(getPosition() - (*normal * m_radius));
		res = new Contact(contact,
			normal,
			penetration,
			getRigidBody(),
			collider->getRigidBody());
	}
	return res;
}