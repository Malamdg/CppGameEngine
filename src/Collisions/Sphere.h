#pragma once

#include "Collider.h"
#include "Box.h"
#include "Plane.h"

class Sphere : public Collider
{
protected:

	/* Radius of the sphere */
	float m_radius;

	bool intersect(Sphere* collider);

public:
	/*
	class constructor for a Sphere

	@param center, the point at the center of the sphere
 	@param radius, the radius of the sphere
	*/
	Sphere(Vector3D* center, float radius);

	/* Class Destructor */
	~Sphere();

	template<typename Base, typename T>
	inline bool instanceof(const T* ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}

	virtual void setRotation(Quaternion* rotation);

	float getRadius();

	/*
	to detect a collision bewteen two spheres 

	@param sphere, the other sphere
	*/
	virtual bool intersect(Collider* collider);

};
