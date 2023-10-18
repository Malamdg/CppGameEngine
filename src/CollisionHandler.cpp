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

			Vector3D vectorBetweenParticles = (*firstParticle)->getPosition() - (*secondParticle)->getPosition();
			float sumOfRadius = (*firstParticle)->getRadius() + (*secondParticle)->getRadius();

			if (vectorBetweenParticles.Norm() <= sumOfRadius)
			{
				// Here we handle the collision between particles
				//std::cout << "Particle " << i << " collide with particle " << y << std::endl;

				float displacement = sumOfRadius - vectorBetweenParticles.Norm();
				float firstMass = (1 / (*firstParticle)->getInverseMass());
				float secondMass = (1 / (*secondParticle)->getInverseMass());

				float firstDisplacement = secondMass / (firstMass + secondMass) * displacement;
				float secondDisplacement = -1 * firstMass / (firstMass + secondMass) * displacement;

				// This should become addForce when possible
				(*firstParticle)->addPosition((vectorBetweenParticles * firstDisplacement));
				(*secondParticle)->addPosition((vectorBetweenParticles * secondDisplacement));
			}
		}
	}
}
