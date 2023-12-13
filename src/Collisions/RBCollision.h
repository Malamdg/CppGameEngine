#pragma once
#include "CollisionHandler.h"
#include "../RigidBody.h"

class RBCollision
{
public:
	/*
 	Class Constructor
 	*/
    RBCollision();

	/*
 	Class Destructor
 	*/
	~RBCollision();

	/*
 	To update the RigidBody's behaviour when a collision occurs
  	@param rb, the RigidBody to update
  	*/
	virtual void update(RigidBody* rb);
};
