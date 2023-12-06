#pragma once
#include "Collision.h"
#include "../Forces/ForceGenerator.h"
#include "../Particle.h"
#include "Box.h"
#include "Sphere.h"

class Plane :
{
private:
	Vector3D* m_planecenter;

	Vector3D* m_normal;

public:
	/*
	class constructor for a Spindle between a particle and a point

	@param attachPoint, the point to wich the particle is attached
 	@param length, the cable length
	*/
	Plane(Vector3D* planecenter, Vector3D* normal);

	/* Class Destructor */
	~Plane();

	/*
translate a sphere

@param translation, vector to translate the sphere
*/
	void translate(Vector3D* translation);

	/*
	rotate a sphere

	@param rotation, a quaternion ot rotate the sphere
	*/
	void rotate(Quaternion* rotation);

	/*
	to detect a collision bewteen two spheres

	@param sphere, the other sphere
	*/
	bool intersect(Sphere* sphere);

	/*
	update the cable between a particle and another particle

	@param particle, the particle to update
	*/
	void intersect(Plane* plane);

	/*
	update the cable between a particle and another particle

	@param particle, the particle to update
	*/
	void intersect(Box* box);
};
