#pragma once

#include "Sphere.h"

Sphere::Sphere(Vector3D* center, float radius)
	:
	Collider(center),
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
bool Sphere::intersect(Collider* collider, Vector3D* direction, float* penetration)
{
	// The sphere can only intersect with spheres
	if (instanceof<Sphere>(collider))
	{
		return intersect(collider);
	}
	else return false;
}

bool Sphere::intersect(Sphere* collider)
{
	Vector3D direction = getPosition() - collider->getPosition();
	return abs(direction.Norm()) < m_radius + collider->getRadius();
}