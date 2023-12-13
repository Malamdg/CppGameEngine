#pragma once
#include "Octree.h"
#include "../Forces/ForceRegistry.h"
#include "../Forces/Friction.h"
#include "../RigidBody.h"
#include <Octree.h>
#include <GameObject.h>

class RBCollision;

class RBCollisionHandler
{
public :
	/*
	Definition of the struct CollisionRegistration

	contact, a collision's contact
	*/
	struct CollisionRegistration
	{
		Contact* contact;
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
	typedef list<GameObject*> Registry;

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
	void handleCollision(float duration, ForceRegistry* forceRegistry, Octree* tree);

	/*
 	To manage collision with sphere

	@param duration, frame duration
	@param forceRegistry, to add the forces generated
 	*/
	void broadPhase(float duration, ForceRegistry* forceRegistry);

	/*
	To manage narrow collision with bounding boxes

	@param duration, frame duration
	@param forceRegistry, to add the forces generated
	*/
	void narrowPhase(float duration, ForceRegistry* forceRegistry, GameObject* go1, GameObject* go2);

	/*
	To create a Registry from a box of the octree

	@param rb1, the first GameObject
	@param rb2, the second GameObject
	*/
	void addcollision(Contact* contact);

	void computeCollision(float duration, ForceRegistry* forceRegistry);

private:
	Registry m_registry;

	list<pair<GameObject*, GameObject*>> m_pairs;

	RegistryCollision m_collisionregistry;
};