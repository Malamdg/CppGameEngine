#pragma once
#include "Collider.h"
#include "Box.h"
#include "Sphere.h"

class Plane : public Collider
{
private:

	Vector3D* m_normal;

public:
	/*
	class constructor for a Spindle between a particle and a point

	@param attachPoint, the point to wich the particle is attached
 	@param length, the cable length
	*/
	Plane(Vector3D* normal);

	/* Class Destructor */
	~Plane();

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
	virtual bool intersect(Collider* Collider);
};
