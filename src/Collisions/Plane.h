#pragma once

#include "Collider.h"
#include "Box.h"
#include "Sphere.h"

class Plane : public Collider
{

private:
	/* The normal vector of the plane */
	Vector3D* m_normal;

public:
	/*
	class constructor

	@param normal, the normal vector of the plane
 	@param center, the center of the plane
	*/
	Plane(Vector3D* normal, Vector3D* center);

	/* Class Destructor */
	~Plane();

	/*
	translate the plane

	@param translation, vector to translate the plane
	*/
	virtual void translate(Vector3D* translation);

	/*
	rotate the plane

	@param rotation, a quaternion to rotate the plane
	*/
	virtual void rotate(Quaternion* rotation);

	/*
	to detect a collision with another Collider

	@param Collider, the other Collider
	*/
	virtual bool intersect(Collider* Collider);
};
