#pragma once
#include "Collision.h"
#include "../Forces/ForceGenerator.h"
#include "../Particle.h"
#include "Box.h"
#include "Plane.h"

class Sphere :
{
private:
	/* Center of the sphere */
	Vector3D* m_center;
	/* Radius of the sphere */
	Particle* m_radius;

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
