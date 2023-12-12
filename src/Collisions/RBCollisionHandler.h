#pragma once
#include "RBCollision.h"
#include "Octree.h"
#include "../Forces/ForceRegistry.h"
#include "../Forces/Friction.h"
#include "../RigidBody.h"

class RBCollision;

class RBCollisionHandler
{
public :
	/*
	Definition of the struct CollisionRegistration

	rb1, the first RigidBody
	rb2, the second RigidBody
	*/
	struct CollisionRegistration
	{
		RigidBody* rb1;
		RigidBody* rb2;
	};

	/*
	Create the type Registry

	Dynamic table of CollisionRegistration
	*/
	typedef std::vector<CollisionRegistration> RegistryCollision;

	/*
	Create the type Registry

	Dynamic table of CollisionRegistration to keep potential collision
	*/
	typedef std::vector<RigidBody> Registry;

	/*
	Constructor
	*/
	RBCollisionHandler();

	/*
	Destructor
	*/
	~RBCollisionHandler();

	/*
	To manage the collision of all RigidBodies

	@param duration, frame duration
	@param forceRegistry, to add the forces generated
	*/
	void handleCollision(float duration, ForceRegistry* forceRegistry);

	/*
 	To manage collision with sphere

	@param duration, frame duration
	@param forceRegistry, to add the forces generated
 	*/
	void wideCollision(float duration, ForceRegistry* forceRegistry);

	/*
	To manage narrow collision with bounding boxes

	@param duration, frame duration
	@param forceRegistry, to add the forces generated
	*/
	void narrowCollision(float duration, ForceRegistry* forceRegistry, RigidBody* rb1, RigidBody* rb2);

	/*
	To create a Registry from a box of the octree
	*/
	void generateRegistry();


	/*
	To create a Registry from a box of the octree

	@param rb1, the first RigidBody
	@param rb2, the second RigidBody
	*/
	void addcollision(RigidBody* rb1, RigidBody* rb2);

private:
	Registry m_registry;

	RegistryCollision m_collisionregistry;

	Octree m_octree;
};