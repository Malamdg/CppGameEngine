#include "CollisionHandler.h"

void handleCollision(std::list<Particle*> particles)
{
	// First loop to test all particles
	for (int i = 0; i < particles.size() - 1; i++)
	{
		std::list<Particle*>::iterator firstParticle = particles.begin();
		std::advance(firstParticle, i);

		// Second loop to test contactof the i-th particle with every other
		for (int y = i + 1; y < particles.size(); y++)
		{
			std::list<Particle*>::iterator secondParticle = particles.begin();
			std::advance(secondParticle, y);

			// Computation of the vector between the two particles
			Vector3D vectorBetweenParticles = (*firstParticle)->getPosition() - (*secondParticle)->getPosition();
			float sumOfRadius = (*firstParticle)->getRadius() + (*secondParticle)->getRadius();

			// To check if the particles are closer than the sum of their radius (in this case, there is a collision)
			if (vectorBetweenParticles.Norm() <= sumOfRadius)
			{
				float displacement = sumOfRadius - vectorBetweenParticles.Norm();
				vectorBetweenParticles.Normalize();

				Vector3D vRel = (*firstParticle)->getVelocity() - (*secondParticle)->getVelocity();

				// Case where the first particle has infinite mass
				if ((*firstParticle)->getInverseMass() == 0)
				{
					Vector3D displacementVector = vectorBetweenParticles * displacement * -1;
					(*secondParticle)->addPosition(displacementVector);

					// Impulsion
					float K = (vRel * vectorBetweenParticles * ((*firstParticle)->getCoefficientRestitution() - 1)) / ((*firstParticle)->getInverseMass() + (*secondParticle)->getInverseMass());
					Vector3D velocityModifier = vectorBetweenParticles * K * (*secondParticle)->getInverseMass();0
					(*secondParticle)->addVelocity(velocityModifier);
					// The first particle is not affected according to Newton's second law as its mass is infinite

				}
				// Case where the second particle has infinite mass
				else if ((*secondParticle)->getInverseMass() == 0)
				{
					Vector3D displacementVector = vectorBetweenParticles * displacement;
					(*firstParticle)->addPosition(displacementVector);

					// Impulsion
					float K = (vRel * vectorBetweenParticles * ((*secondParticle)->getCoefficientRestitution() - 1)) / ((*firstParticle)->getInverseMass() + (*secondParticle)->getInverseMass());
					Vector3D velocityModifier = vectorBetweenParticles * K * (*firstParticle)->getInverseMass();
					(*firstParticle)->addVelocity(velocityModifier * -1);
					// The second particle is not affected according to Newton's second law as its mass is infinite
				}
				// In this case both particles have finite mass and will be affected by the collision
				else
				{
					float firstMass = (1 / (*firstParticle)->getInverseMass());
					float secondMass = (1 / (*secondParticle)->getInverseMass());

					// Third Newton's law
					float firstDisplacement = secondMass / (firstMass + secondMass) * displacement;
					float secondDisplacement = -1 * firstMass / (firstMass + secondMass) * displacement;

					// Same director vector but opposite direction (-1 in the previous lines)
					Vector3D firstDisplacementVector = vectorBetweenParticles * firstDisplacement;
					Vector3D secondDisplacementVector = vectorBetweenParticles * secondDisplacement;

					// This separate the two particles
					(*firstParticle)->addPosition(firstDisplacementVector);
					(*secondParticle)->addPosition(secondDisplacementVector);

					// Impulsion
					float firstK = (vRel * vectorBetweenParticles * ((*secondParticle)->getCoefficientRestitution() - 1)) / ((*firstParticle)->getInverseMass() + (*secondParticle)->getInverseMass());
					float secondK = (vRel * vectorBetweenParticles * ((*firstParticle)->getCoefficientRestitution() - 1)) / ((*firstParticle)->getInverseMass() + (*secondParticle)->getInverseMass());
					Vector3D firstVelocityModifier = vectorBetweenParticles * firstK * (*firstParticle)->getInverseMass();
					Vector3D secondVelocityModifier = vectorBetweenParticles * secondK * (*secondParticle)->getInverseMass();
					(*firstParticle)->addVelocity(firstVelocityModifier * -1);
					(*secondParticle)->addVelocity(secondVelocityModifier);
				}
			}
		}
	}
}
