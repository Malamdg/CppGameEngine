#pragma once

#include<Sphere.h>

Sphere::Sphere(Vector3D* center, float radius)
	:
	Collider(center),
	m_radius(radius)
{ }

/* Class Destructor */
Sphere::~Sphere() { }

/*
translate a sphere

@param translation, vector to translate the sphere
*/
void Sphere::translate(Vector3D* translation) {}

/*
rotate a sphere

@param rotation, a quaternion ot rotate the sphere
*/
void Sphere::rotate(Quaternion* rotation) {}

/*
to detect a collision bewteen two spheres

@param sphere, the other sphere
*/
bool Sphere::intersect(Collider* collider) {}