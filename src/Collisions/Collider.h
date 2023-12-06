#pragma once

#include <Vector3D.h>
#include <Quaternion.h>


class Collider
{
private:
	Vector3D* m_planecenter;

public:
	/*
	class constructor for a Collider
	*/
	Collider(Vector3D* center);

	/* Class Destructor */
	~Collider();

	/*
	translate a Collider

	@param translation, vector to translate the collider
	*/
	virtual void translate(Vector3D* translation);

	/*
	rotate a Collider

	@param rotation, a quaternion to rotate the collider
	*/
	virtual void rotate(Quaternion* rotation);

	/*
	to detect a collision bewteen Colliders

	@param collider, the other collider
	*/
	virtual bool intersect(Collider* collider);
};