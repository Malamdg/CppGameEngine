#include "BlobCollisionHandler.h"

BlobCollisionHandler::BlobCollisionHandler(Blob* blob): m_blob(blob)
{

}

BlobCollisionHandler::~BlobCollisionHandler()
{

}

void BlobCollisionHandler::handleCollision(std::list<Particle*> particles, ParticleForceRegistry* forceRegistry, CollisionHandler* collisionHandler)
{
	// processing blob particles one by one
	for (int i = 0; i < m_blob->m_particles.size(); i++)
	{
		std::list<Particle*>::iterator firstParticle = (*m_blob).m_particles.begin();
		std::advance(firstParticle, i);

		bool inBlob = false;
		// for the i-th particle, we check if it collide one (or more) of the other
		for (int y = 0; y < particles.size(); y++)
		{
			std::list<Particle*>::iterator secondParticle = particles.begin();
			std::advance(secondParticle, y);

			// Compute the vector between both particles
			Vector3D vectorBetweenParticles = (*firstParticle)->getPosition() - (*secondParticle)->getPosition();
			float sumOfRadius = (*firstParticle)->getRadius() + (*secondParticle)->getRadius();

			inBlob = (std::find(m_blob->m_particles.begin(), m_blob->m_particles.end(), (*secondParticle)) != m_blob->m_particles.end());

			// If the particles are closer than the sum of their radius, they are colliding
			if (vectorBetweenParticles.Norm() <= sumOfRadius && !inBlob) // not intersted in intern colliding, purpouse here is to find particles to merge into blob
			{
				if ((*secondParticle)->getInverseMass() != 0.0) // don't merge with particles that aren't movable
				{
					m_blob->merge((*secondParticle), forceRegistry, collisionHandler);
				}
			}
		}
	}
}
