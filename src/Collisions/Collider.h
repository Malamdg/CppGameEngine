#pragma once

#include <Vector3D.h>
#include <Quaternion.h>
#include <Contact.h>


class Collider
{
protected:
	Vector3D m_center;
	RigidBody* m_rigidbody;

public:
	/*
	class constructor for a Collider

	@param center, the center of the collider
	*/
	Collider(RigidBody* rb, Vector3D center);

	/* Class Destructor */
	~Collider();
	
	template<typename Base, typename T>
	inline bool instanceof(const T* ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}

	virtual void update() {}

	/*
	set the position of a collider

	@param position, the new position of the collider
	*/
	void setPosition(Vector3D position);

	/*
	rotate a Collider

	@param rotation, a quaternion to rotate the collider
	*/
	virtual void setRotation(Quaternion rotation);

	/*
	get the position of the collider

	@return, the position of the collider
	*/
	Vector3D getPosition();


	/*
	get the rigidbody of the collider

	@return, the rigidbody of the collider
	*/
	RigidBody* getRigidBody();


	/*
	to detect a collision bewteen Colliders

	@param collider, the other collider
	@return a list of contacts
	*/
	virtual list<Contact*> intersect(Collider* collider);

	virtual void draw() {}
};