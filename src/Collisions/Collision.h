#pragma once
#include "../Particle.h"
#include "CollisionHandler.h"

class Collision
{
public:
	Collision();

	~Collision();

	virtual void update(Particle* particle);
};