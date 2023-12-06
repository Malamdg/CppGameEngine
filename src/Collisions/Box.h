#pragma once
#include "Collider.h"
#include "Sphere.h"
#include "Plane.h"

class Box : public Collider
{
private:

	/* the first demi-axis (with the top face) */
	Vector3D* m_demiaxis1;
	/* the second demi-axis (with the front face) */
	Vector3D* m_demiaxis2;
	/* the third demi-axis (with the right face) */
	Vector3D* m_demiaxis3;

public:
	/*
	class constructor

	@param demiaxis1, the first demi-axis (with the top face)
	@param demiaxis2, the second demi-axis (with the front face)
	@param demiaxis3, third demi-axis (with the right face)
 	@param center, the center of the box
	*/
	Box(Vector3D* demiaxis1, Vector3D* demiaxis2, Vector3D* demiaxis3, Vector3D* center);


	/* Class Destructor */
	~Box();

	/*
	translate the box

	@param translation, vector to translate the box
	*/
	virtual void translate(Vector3D* translation);

	/*
	rotate the box

	@param rotation, a quaternion ot rotate the box
	*/
	virtual void rotate(Quaternion* rotation);

	/*
	to detect a collision with another Collider

	@param Collider, the other Collider
	*/
	virtual bool intersect(Collider* Collider);
};
