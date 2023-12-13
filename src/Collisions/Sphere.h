#pragma once

#include "Collider.h"
#include "Box.h"
#include "Plane.h"

class Sphere : public Collider
{

private:

	/* Radius of the sphere */
	float m_radius;

	/* 
	Check the intersection with another sphere
	
	@param collider, the other sphere
	@return true if there is a collision
	*/
	Contact* intersection(Sphere* collider);

public:
	/*
	class constructor for a Sphere
	
	@param rb, the rigidbody of the sphere
	@param radius, the radius of the sphere 
	@param center, the point at the center of the sphere
	*/
	Sphere(RigidBody* rb, Vector3D center, float radius);

	/* Class Destructor */
	~Sphere();

	template<typename Base, typename T>
	inline bool instanceof(const T* ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}

	/*
 	to update the sphere position
 	*/
	void update() override;

	/*
	to set the new orientation of the sphere

	@param rotation, the rotation applied to get the new orientation
	*/
	void setRotation(Quaternion rotation) override;


	/*
	to get the radius of the sphere

	@return the radius of the sphere
	*/
	float getRadius();

	/*
	to detect a collision with another Collider

	@param Collider, the other Collider
	*/
	list<Contact*> intersect(Collider* collider) override;

	/*
 	to draww the sphere
 	*/
	void draw() override;
};
