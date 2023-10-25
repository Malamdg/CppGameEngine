#pragma once
#include "../Particle.h"
#include "CollisionHandler.h"

class Collision
{
public:
	/*
 	Class Constructor
 	*/
	Collision();

	/*
 	Class Destructor
 	*/
	~Collision();

	/*
 	To update the particle's behaviour when a collision occurs
  	@param particle, the particle to update
  	*/
	virtual void update(Particle* particle);
};
