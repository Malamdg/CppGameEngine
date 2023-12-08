#pragma once

#include "Collider.h"
#include "Sphere.h"
#include "Plane.h"

class Box : public Collider
{
private:

	/* the first demi-axis (with the right fac) */
	Vector3D* m_right;
	/* the second demi-axis (with the top face) */
	Vector3D* m_top;
	/* the third demi-axis (with the front face) */
	Vector3D* m_foward;

	/*
 	Manage the intersection between the box and another box

  	@param collider, the other box colliding the box
   	@param direction, the direction of the penetration
    	@param penetration, the depth of the penetration
  	*/
	bool intersection(Box* collider, Vector3D* direction, float* penetration);

	/*
 	Manage the intersection between the box and a plane

  	@param collider, the plane colliding the box
   	@param direction, the direction of the penetration
    	@param penetration, the depth of the penetration
  	*/
	bool intersection(Plane* collider, Vector3D* direction, float* penetration);

public:
	/*
	class constructor

	@param demiaxis1, the first demi - axis(with the top face)
	@param demiaxis2, the second demi - axis(with the front face)
	@param demiaxis3, third demi - axis(with the right face)
	@param center, the center of the box
	*/
	Box(Vector3D* position, Vector3D* axe1, Vector3D* axe2, Vector3D* axe3);

	/* Class Destructor */
	~Box();

	template<typename Base, typename T>
	inline bool instanceof(const T* ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}

	/*
	rotate the box

	@param rotation, a quaternion ot rotate the box
	*/
	void setRotation(Quaternion* rotation);

	/*
	to get the right demi-axis

	@return the right demi-axis
	*/
	Vector3D getRight();
	/*
	to get the top demi-axis

	@return the top demi-axis
	*/
	Vector3D getTop();
	/*
	to get the forward demi-axis

	@return the forward demi-axis
	*/
	Vector3D getForward();
	/*
	to get the i-th demi-axis

	@return the i-th demi-axis
	*/
	Vector3D getAxis(int i);

	/*
	to detect a collision with another Collider

	@param Collider, the other Collider
	*/
	bool intersect(Collider* collider, Vector3D* direction, float* penetration);
};
