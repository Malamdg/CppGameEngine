#include "Cable.h"

Cable::Cable(Vector3D* attachPoint, float length)
	: Collision(),
	  m_attachPoint(attachPoint),
	  m_attachParticle(nullptr),
	  m_length(length)
{ }

Cable::Cable(Particle* attachParticle, float length)
	: Collision(),
	  m_attachPoint(nullptr),
	  m_attachParticle(attachParticle),
	  m_length(length)
{ }

Cable::~Cable() { }

void Cable::update(Particle* particle)
{
	if (m_attachPoint != nullptr) updateForPoint(particle);
	else updateForParticle(particle);
}

void Cable::updateForPoint(Particle* particle)
{
	Vector3D vectorBetweenPoints = *m_attachPoint - particle->getPosition();

	if (vectorBetweenPoints.Norm() > m_length)
	{
		float displacement = vectorBetweenPoints.Norm() - m_length;
		vectorBetweenPoints.Normalize();

		// We don't need to calculate ponderated displacement as the point is supposed unmovable

		Vector3D displacementVector = vectorBetweenPoints * displacement;
		particle->addPosition(displacementVector);

		// Then we need to add an impulse
	}
}

void Cable::updateForParticle(Particle* particle)
{
	Vector3D vectorBetweenParticles = m_attachParticle->getPosition() - particle->getPosition();
	
	if (vectorBetweenParticles.Norm() > m_length)
	{
		float displacement = vectorBetweenParticles.Norm() - m_length;
		vectorBetweenParticles.Normalize();

		if (m_attachParticle->getInverseMass() == 0)
		{
			Vector3D displacementVector = vectorBetweenParticles * displacement;
			particle->addPosition(displacementVector);
		}
		else if (particle->getInverseMass() == 0)
		{
			Vector3D displacementVector = vectorBetweenParticles * displacement * -1;
			m_attachParticle->addPosition(displacementVector);
		}
		else
		{
			float firstMass = 1 / m_attachParticle->getInverseMass();
			float secondMass = 1 / particle->getInverseMass();

			float firstDisplacement = secondMass / (firstMass + secondMass) * displacement;
			float secondDisplacement = -1 * firstMass / (firstMass + secondMass) * displacement;

			Vector3D firstDisplacementVector = vectorBetweenParticles * firstDisplacement;
			Vector3D secondDisplacementVector = vectorBetweenParticles * secondDisplacement;

			// This ensure the length of the cable is always the same
			m_attachParticle->addPosition(firstDisplacementVector);
			particle->addPosition(secondDisplacementVector);
		}

		// Then we need to add an impulse
	}
}