#pragma once

#include "Collider.h"
#include "Sphere.h"
#include "Plane.h"

class Box : public Collider
{
private:

<<<<<<< Updated upstream
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

=======
	/*  */
	Vector3D* m_right;
	/*  */
	Vector3D* m_top;
	/*  */
	Vector3D* m_foward;

	bool intersection(Box* collider, Vector3D* direction, float* penetration);
	bool intersection(Plane* collider, Vector3D* direction, float* penetration);

public:
	/*
	
	*/
	Box(Vector3D* position, Vector3D* axe1, Vector3D* axe2, Vector3D* axe3);
>>>>>>> Stashed changes

	/* Class Destructor */
	~Box();

<<<<<<< Updated upstream
	/*
	translate the box

	@param translation, vector to translate the box
	*/
	virtual void translate(Vector3D* translation);

	/*
	rotate the box

	@param rotation, a quaternion ot rotate the box
=======
	template<typename Base, typename T>
	inline bool instanceof(const T* ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}

	/*
	
>>>>>>> Stashed changes
	*/
	void setRotation(Quaternion* rotation);

	Vector3D getRight();
	Vector3D getTop();
	Vector3D getForward();
	Vector3D getAxis(int i);

	/*
<<<<<<< Updated upstream
	to detect a collision with another Collider

	@param Collider, the other Collider
=======
	
>>>>>>> Stashed changes
	*/
	bool intersect(Collider* collider, Vector3D* direction, float* penetration);
};
