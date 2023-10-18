#include "CollisionHandler.h"

void handleCollision(std::list<Particle*> particles)
{
	for (int i = 0; i < particles.size() - 1; i++)
	{
		std::list<Particle*>::iterator firstParticle = particles.begin();
		std::advance(firstParticle, i);

		for (int y = i + 1; y < particles.size(); y++)
		{
			std::list<Particle*>::iterator secondParticle = particles.begin();
			std::advance(secondParticle, y);

			float distance = (*firstParticle)->getPosition().distance((*secondParticle)->getPosition());
			float sumOfRadius = (*firstParticle)->getRadius() + (*secondParticle)->getRadius();

			if (distance <= sumOfRadius)
			{
				// Here we handle the collision between particles
			}
		}
	}
}
