#pragma once
#include "Collision.h"
#include "../Particle.h"

class Collision;

class CollisionHandler
{
public:
	struct CollisionRegistration
	{
		Particle* particle;
		Collision* collision;
	};

	typedef std::vector<CollisionRegistration> Registry;

	CollisionHandler();

	~CollisionHandler();

	void handleCollision(std::list<Particle*> particles, float duration);

	void add(Particle* particle, Collision* collision);

private:
	Registry m_registry;
};
