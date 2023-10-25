#include "CollisionHandler.h"

CollisionHandler::CollisionHandler()
{

}

CollisionHandler::~CollisionHandler()
{

}

void CollisionHandler::handleCollision(std::list<Particle*> particles, float duration, ParticleForceRegistry* forceRegistry)
{
	for (CollisionRegistration registration : m_registry)
	{
		registration.collision->update(registration.particle);
	}

	// processing particles one by one
	for (int i = 0; i < particles.size() - 1; i++)
	{
		std::list<Particle*>::iterator firstParticle = particles.begin();
		std::advance(firstParticle, i);

		// for the i-th particle, we check if it collide one (or more) of the other
		for (int y = i + 1; y < particles.size(); y++)
		{
			std::list<Particle*>::iterator secondParticle = particles.begin();
			std::advance(secondParticle, y);

			// Compute the vector between both particles
			Vector3D vectorBetweenParticles = (*firstParticle)->getPosition() - (*secondParticle)->getPosition();
			float sumOfRadius = (*firstParticle)->getRadius() + (*secondParticle)->getRadius();

			// If the particles are closer than the sum of their radius, they are colliding
			if (vectorBetweenParticles.Norm() <= sumOfRadius)
			{
				float displacement = sumOfRadius - vectorBetweenParticles.Norm();
				vectorBetweenParticles.Normalize();

				Vector3D relativeVelocity = (*firstParticle)->getVelocity() - (*secondParticle)->getVelocity();
				if ((*firstParticle)->getInverseMass() == 0 && (*secondParticle)->getInverseMass() == 0)
				{
					// If both mass are infinite we rather just ignore the collision
				}
				// The first particle's mass is infinite
				else if ((*firstParticle)->getInverseMass() == 0)
				{
					// management of rest contact
					float particleAcceleration_proj = (*secondParticle)->getAcceleration() * vectorBetweenParticles; // on récêpère l'acceleration de la particule et on la projette sur n
					float velocity_proj = (*secondParticle)->getVelocity() * vectorBetweenParticles; // projection on vector n

					// We want to replace the particle out of the other watever the case
					Vector3D displacementVector = vectorBetweenParticles * displacement * -1;
					(*secondParticle)->addPosition(displacementVector);

					// if contact is not a rest contact
					if (!(std::abs(particleAcceleration_proj * duration) > std::abs(velocity_proj)))
					{
						// then we add an impulsion
						float K = (relativeVelocity * vectorBetweenParticles * ((*firstParticle)->getCoefficientRestitution() + 1)) / ((*firstParticle)->getInverseMass() + (*secondParticle)->getInverseMass());
						Vector3D velocityModifier = vectorBetweenParticles * (K * (*secondParticle)->getInverseMass());
						(*secondParticle)->addVelocity(velocityModifier);
						// the first particle is not affected according to newton's second law
					}
					else
					{
						// We garanty the velocity is 0
						(*secondParticle)->addVelocity(vectorBetweenParticles * velocity_proj);

						forceRegistry->add(*secondParticle, new ParticleFriction((*firstParticle)->getK1(), (*firstParticle)->getK2()));
					}

				}
				else if ((*secondParticle)->getInverseMass() == 0)
				{
					// management of rest contact
					float particleAcceleration_proj = (*firstParticle)->getAcceleration() * vectorBetweenParticles; // on récêpère l'acceleration de la particule et on la projette sur n
					float velocity_proj = (*firstParticle)->getVelocity() * vectorBetweenParticles; // projection on vector n

					// We want to replace the particle out of the other watever the case
					Vector3D displacementVector = vectorBetweenParticles * displacement * -1;
					(*firstParticle)->addPosition(displacementVector);

					// if contact is not a rest contact
					if (!(std::abs(particleAcceleration_proj * duration) > std::abs(velocity_proj)))
					{
						// then we add an impulsion
						float K = (relativeVelocity * vectorBetweenParticles * ((*secondParticle)->getCoefficientRestitution() + 1)) / ((*firstParticle)->getInverseMass() + (*secondParticle)->getInverseMass());
						Vector3D velocityModifier = vectorBetweenParticles * (K * (*firstParticle)->getInverseMass());
						(*firstParticle)->addVelocity(velocityModifier * -1);
						// the second particle is not affected according to newton's second law
					}
					else
					{
						// We garanty the velocity is 0
						(*firstParticle)->addVelocity(vectorBetweenParticles * velocity_proj);

						forceRegistry->add(*secondParticle, new ParticleFriction((*secondParticle)->getK1(), (*firstParticle)->getK2()));
					}
				}
				else
				{
					float firstMass = (1 / (*firstParticle)->getInverseMass());
					float secondMass = (1 / (*secondParticle)->getInverseMass());

					// Third Newton's law
					float firstDisplacement = secondMass / (firstMass + secondMass) * displacement;
					float secondDisplacement = -1 * firstMass / (firstMass + secondMass) * displacement;

					Vector3D firstDisplacementVector = vectorBetweenParticles * firstDisplacement;
					Vector3D secondDisplacementVector = vectorBetweenParticles * secondDisplacement;

					// This separate the two particles
					(*firstParticle)->addPosition(firstDisplacementVector);
					(*secondParticle)->addPosition(secondDisplacementVector);

					// No rest contact if there is no static particle

					// Impulsion
					float firstK = (relativeVelocity * vectorBetweenParticles * ((*secondParticle)->getCoefficientRestitution() + 1)) / ((*firstParticle)->getInverseMass() + (*secondParticle)->getInverseMass());
					float secondK = (relativeVelocity * vectorBetweenParticles * ((*firstParticle)->getCoefficientRestitution() + 1)) / ((*firstParticle)->getInverseMass() + (*secondParticle)->getInverseMass());
					Vector3D firstVelocityModifier = vectorBetweenParticles * (firstK * (*firstParticle)->getInverseMass());
					Vector3D secondVelocityModifier = vectorBetweenParticles * (secondK * (*secondParticle)->getInverseMass());
					(*firstParticle)->addVelocity(firstVelocityModifier * -1);
					(*secondParticle)->addVelocity(secondVelocityModifier);
				}
			}
		}
	}

	m_registry.empty();
}

void CollisionHandler::add(Particle* particle, Collision* collision)
{
	CollisionRegistration collisionRegistration;
	collisionRegistration.particle = particle;
	collisionRegistration.collision = collision;
	m_registry.push_back(collisionRegistration);
}