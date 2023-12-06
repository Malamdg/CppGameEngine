#pragma once
#include "RBCollision.h"
#include "../Forces/ForceRegistry.h"
#include "../Forces/Friction.h"
#include "../RigidBody.h"

class RBCollision;

class RBCollisionHandler
{
public
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

	@param particle, the particle to add
	@param collision, the collision associated to the particle
	*/
	void generateRegistry();

private:
	Registry m_registry;

	Octree m_octree;
};
