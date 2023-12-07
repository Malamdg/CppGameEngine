#pragma once

#include "Collider.h"
#include "Sphere.h"
#include "Plane.h"

class Box : public Collider
{
private:

	/* the first demi-axis (with the top face) */
	Vector3D* m_right;
	/* the second demi-axis (with the front face) */
	Vector3D* m_top;
	/* the third demi-axis (with the right face) */
	Vector3D* m_foward;

	bool intersection(Box* collider, Vector3D* direction, float* penetration);
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

	Vector3D getRight();
	Vector3D getTop();
	Vector3D getForward();
	Vector3D getAxis(int i);

	/*
	to detect a collision with another Collider

	@param Collider, the other Collider
	*/
	bool intersect(Collider* collider, Vector3D* direction, float* penetration);
};
