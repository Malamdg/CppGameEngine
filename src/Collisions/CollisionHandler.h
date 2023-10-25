#pragma once
#include "Collision.h"
#include "../Particle.h"

class Collision;

class CollisionHandler
{
public:
	/*
	Definition of the struct CollisionRegistration

	particle, particle to which the collision is applied
	collision, yhe collision
	*/
	struct CollisionRegistration
	{
		Particle* particle;
		Collision* collision;
	};

	/*
	Create the type Registry

	Dynamic table of CollisionRegistration
	*/
	typedef std::vector<CollisionRegistration> Registry;

	/*
	Constructor
	*/
	CollisionHandler();

	/*
	Destructor
	*/
	~CollisionHandler();

	/*
 	To manage the collision of all particles

   	@param particles, the particles consider
	@param duration, frame duration
 	*/
	void handleCollision(std::list<Particle*> particles, float duration);

	/*
	Add a Particle to Registry

	@param particle, the particle to add
	@param collision, the collision associated to the particle
	*/
	void add(Particle* particle, Collision* collision);

private:
	Registry m_registry;
};
