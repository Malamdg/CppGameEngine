#include "CollisionHandler.h"

CollisionHandler::CollisionHandler()
{

}

CollisionHandler::~CollisionHandler()
{

}

void CollisionHandler::handleCollision(std::list<Particle*> particles)
{
	for (CollisionRegistration registration : m_registry)
	{
		registration.collision->update(registration.particle);
	}

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
				float displacement = sumOfRadius - vectorBetweenParticles.Norm();
				vectorBetweenParticles.Normalize();

				Vector3D vRel = (*firstParticle)->getVelocity() - (*secondParticle)->getVelocity();

				if ((*firstParticle)->getInverseMass() == 0 && (*secondParticle)->getInverseMass() == 0)
				{
					// If both mass are infinite we rather just ignore the collision
				}
				else if ((*firstParticle)->getInverseMass() == 0)
				{
					Vector3D displacementVector = vectorBetweenParticles * displacement * -1;
					(*secondParticle)->addPosition(displacementVector);

					// Impulsion
					float K = (vRel * vectorBetweenParticles * ((*firstParticle)->getCoefficientRestitution() + 1)) / ((*firstParticle)->getInverseMass() + (*secondParticle)->getInverseMass());
					Vector3D velocityModifier = vectorBetweenParticles * K * (*secondParticle)->getInverseMass();
					(*secondParticle)->addVelocity(velocityModifier);

				}
				else if ((*secondParticle)->getInverseMass() == 0)
				{
					Vector3D displacementVector = vectorBetweenParticles * displacement;
					(*firstParticle)->addPosition(displacementVector);

					// Impulsion
					float K = (vRel * vectorBetweenParticles * ((*secondParticle)->getCoefficientRestitution() + 1)) / ((*firstParticle)->getInverseMass() + (*secondParticle)->getInverseMass());
					Vector3D velocityModifier = vectorBetweenParticles * K * (*firstParticle)->getInverseMass();
					(*firstParticle)->addVelocity(velocityModifier * -1);
				}
				else
				{
					float firstMass = (1 / (*firstParticle)->getInverseMass());
					float secondMass = (1 / (*secondParticle)->getInverseMass());

					float firstDisplacement = secondMass / (firstMass + secondMass) * displacement;
					float secondDisplacement = -1 * firstMass / (firstMass + secondMass) * displacement;

					Vector3D firstDisplacementVector = vectorBetweenParticles * firstDisplacement;
					Vector3D secondDisplacementVector = vectorBetweenParticles * secondDisplacement;

					// This separate the two particles
					(*firstParticle)->addPosition(firstDisplacementVector);
					(*secondParticle)->addPosition(secondDisplacementVector);

					// Impulsion
					float firstK = (vRel * vectorBetweenParticles * ((*secondParticle)->getCoefficientRestitution() + 1)) / ((*firstParticle)->getInverseMass() + (*secondParticle)->getInverseMass());
					float secondK = (vRel * vectorBetweenParticles * ((*firstParticle)->getCoefficientRestitution() + 1)) / ((*firstParticle)->getInverseMass() + (*secondParticle)->getInverseMass());
					Vector3D firstVelocityModifier = vectorBetweenParticles * firstK * (*firstParticle)->getInverseMass();
					Vector3D secondVelocityModifier = vectorBetweenParticles * secondK * (*secondParticle)->getInverseMass();
					(*firstParticle)->addVelocity(firstVelocityModifier * -1);
					(*secondParticle)->addVelocity(secondVelocityModifier);
				}
			}
		}
	}
}

void CollisionHandler::add(Particle* particle, Collision* collision)
{
	CollisionRegistration collisionRegistration;
	collisionRegistration.particle = particle;
	collisionRegistration.collision = collision;
	m_registry.push_back(collisionRegistration);
}