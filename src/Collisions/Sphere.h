#pragma once

#include "Collider.h"
#include "Box.h"
#include "Plane.h"

class Sphere : public Collider
{
private:

	/* Radius of the sphere */
	float m_radius;

public:
	/*
	class constructor for a Sphere

	@param center, the point at the center of the sphere
 	@param radius, the radius of the sphere
	*/
	Sphere(Vector3D* center, float radius);

	/* Class Destructor */
	~Sphere();

	/*
	translate a sphere

	@param translation, vector to translate the sphere
	*/
	virtual void translate(Vector3D* translation);

	/*
	rotate a sphere

	@param rotation, a quaternion ot rotate the sphere
	*/
	virtual void rotate(Quaternion* rotation);

	/*
	to detect a collision bewteen two spheres 

	@param sphere, the other sphere
	*/
	virtual bool intersect(Collider* collider);

};
