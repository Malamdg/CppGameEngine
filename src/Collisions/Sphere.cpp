#pragma once

#include<Sphere.h>

Sphere::Sphere(Vector3D* center, float radius)
	:
	Collider(center),
	m_radius(radius)
{ }

/* Class Destructor */
Sphere::~Sphere() { }

void Sphere::setPosition(Vector3D* position) { m_center = position; }
void Sphere::setRotation(Quaternion* rotation) {}

Vector3D* Sphere::getPosition() { return m_center; }
float Sphere::getRadius() { return m_radius; }

/*
to detect a collision bewteen two spheres

@param sphere, the other sphere
*/
bool Sphere::intersect(Collider* collider) 
{
	if (instanceof<Sphere>(collider))
	{
		return intersect(collider);
	}
}

bool Sphere::intersect(Sphere* collider)
{
	return abs(m_center - collider->getPosition()) < m_radius + collider->getRadius() ;
}