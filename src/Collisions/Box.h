#pragma once
#include "Collision.h"
#include "../Forces/ForceGenerator.h"
#include "../Particle.h"
#include "Sphere.h"
#include "Plane.h"

class Box :
{
private:
	Vector3D* m_center;
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
