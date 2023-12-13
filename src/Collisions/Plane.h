#pragma once

#include "Collider.h"
#include "Box.h"
#include "Sphere.h"

class Plane : public Collider
{

private:
	/* The normal vector of the plane */
	Vector3D m_normal;
	/* The forward dimension of the plane */
	Vector3D m_forward;
	/* The right dimension of the plane */
	Vector3D m_right;

	/*
	Handle a collision with a box

	@param Collider, the other Collider
	*/
	list<Contact*> intersection(Box* box);

public:
	/*
	class constructor

	@param normal, the normal vector of the plane
 	@param center, the center of the plane
	*/
	Plane(RigidBody* rb, Vector3D center, Vector3D* normal, float width, float length);

	/* Class Destructor */
	~Plane();

	/*
	translate the plane

	@param position, the new position of the plane
	*/
	virtual void setPosition(Vector3D position);

	/*
	rotate the plane

	@param rotation, a quaternion to rotate the plane
	*/
	virtual void rotate(Quaternion* rotation);

	/*
	to detect a collision with another Collider

	@param Collider, the other Collider
	*/
	virtual list<Contact*> intersect(Collider* Collider) override;	
};
