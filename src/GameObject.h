#pragma once

#include <RigidBody.h>
#include <Box.h>
#include <Plane.h>
#include <Sphere.h>

class GameObject
{
private:
	RigidBody* m_rigidBody;
	Collider* m_collider;
	Sphere* m_encompassingSphere;

public:
	/*
 	Empty Constructor
 	*/
	GameObject();

	/*
 	Class Constructor

  	@param rigidBody, the rigid body composing the GameObject
     	@param boxCollider, the box collider associated to the rigid body
      	@param encompassingSphere, the sphere encompassing the rigid body
  	*/
	GameObject(RigidBody* rigidBody, Collider* boxCollider, Sphere* encompassingSphere);

	/*
 	Class Destructor
 	*/
	~GameObject();

	/*
 	to update all the GameObject's component
 	*/
	void update();

    	/*
   	To draw the GameObject
	
	@param color, the color for the dipslay
	*/
	void draw(ofColor color = ofColor(0, 255, 255), bool drawCollider = false, bool drawSphere = false);

	/*
 	To set the position of the GameObject

  	@param position, the new position for the GameObject
 	*/
	void setPosition(Vector3D position);

	/*
 	To get the rigidbody associated to the Game Object

  	@return the RigidBody of the GameObject
  	*/
	RigidBody* getRigidBody();

	/*
 	To get the collider associated to the Game Object

  	@return the collider of the GameObject
  	*/
	Collider* getCollider();

	/*
 	To get the encompssing sphere associated to the Game Object

  	@return the sphere of the GameObject
  	*/
	Sphere* getSphere();
};
