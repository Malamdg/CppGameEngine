#pragma once

#include "Collider.h"

class Plane : public Collider
{

private:
	/* The normal vector of the plane */
	Vector3D m_normal;
	/* The dimensions of the plane */
	float m_width, m_length;

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
	update the plane position and rotation according to the rigodbody's movement
	*/
	void update() override;

	/*
	translate the plane

	@param position, the new position of the plane
	*/
	virtual void setPosition(Vector3D position);

	/*
	to get the normal of a plane

	@return the normal of the plane
	*/
	Vector3D getNormal();

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

	/*
	to draw the collider
	*/
	virtual void draw() override;
};
