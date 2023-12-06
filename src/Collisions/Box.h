#pragma once
#include "Collider.h"
#include "Sphere.h"
#include "Plane.h"

class Box : public Collider
{
private:

	/* Other particle attached to the spindle */
	Vector3D* m_demiaxis1;
	/* spindle length */
	Vector3D* m_demiaxis2;
	/* spindle length */
	Vector3D* m_demiaxis3;

public:
	/*
	class constructor for a Spindle between a particle and a point

	@param attachPoint, the point to wich the particle is attached
 	@param length, the cable length
	*/
	Box(Vector3D* attachPoint, float length);


	/* Class Destructor */
	~Box();

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
