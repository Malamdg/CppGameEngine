#pragma once

#include <Vector3D.h>
#include <Quaternion.h>


class Collider
{
private:
	Vector3D* m_center;

public:
	/*
	class constructor for a Collider

	@param center, the center of the collider
	*/
	Collider(Vector3D* center);

	/* Class Destructor */
	~Collider();
	
	template<typename Base, typename T>
	inline bool instanceof(const T* ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}

	/*
	translate a Collider

	@param translation, vector to translate the collider
	*/
	void setPosition(Vector3D* translation);

	/*
	rotate a Collider

	@param rotation, a quaternion to rotate the collider
	*/
	virtual void setRotation(Quaternion* rotation);

	Vector3D* getPosition();

	/*
	to detect a collision bewteen Colliders

	@param collider, the other collider
	*/
	virtual bool intersect(Collider* collider);
};