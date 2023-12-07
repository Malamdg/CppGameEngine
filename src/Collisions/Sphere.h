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
	bool intersect(Sphere* collider);

public:
	/*
	class constructor for a Sphere
	
	@param radius, the radius of the sphere 
	@param center, the point at the center of the sphere
	*/
	Sphere(Vector3D* center, float radius);

	/* Class Destructor */
	~Sphere();

	template<typename Base, typename T>
	inline bool instanceof(const T* ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}

<<<<<<< Updated upstream
	/*
	to set the new orientation of the sphere

	@param rotation, the rotation applied to get the new orientation
	*/
	virtual void setRotation(Quaternion* rotation);
=======
	void setRotation(Quaternion* rotation);
>>>>>>> Stashed changes

	/*
	to get the radius of the sphere

	@return the radius of the sphere
	*/
	float getRadius();

	/*
	to detect a collision with another Collider

	@param Collider, the other Collider
	*/
	bool intersect(Collider* collider, Vector3D* direction = nullptr, float* penetration = nullptr);

};
