#include "Cable.h"

Cable::Cable(Vector3D* attachPoint, float length)
	: m_attachPoint(attachPoint),
	  m_attachParticle(nullptr),
	  m_length(length)
{ }

Cable::Cable(Particle* attachParticle, float length)
	: m_attachPoint(nullptr),
	  m_attachParticle(attachParticle),
	  m_length(length)
{ }

Cable::~Cable() { }

void Cable::updateForce(Particle* particle, float duration)
{
	if (m_attachPoint != nullptr) updateForPoint(particle);
	else updateForParticle(particle);
}

void Cable::updateForPoint(Particle* particle)
{
	Vector3D vectorBetweenParticles = *m_attachPoint - particle->getPosition();

	if (vectorBetweenParticles.Norm() > m_length)
	{
		float displacement = vectorBetweenParticles.Norm() - m_length;

		// We don't need to calculate ponderated displacement as the point is supposed unmovable

		particle->addPosition((vectorBetweenParticles * displacement));

		// Then we need to add an impulse
	}
}

void Cable::updateForParticle(Particle* particle)
{
	Vector3D vectorBetweenParticles = m_attachParticle->getPosition() - particle->getPosition();
	
	if (vectorBetweenParticles.Norm() > m_length)
	{
		float displacement = vectorBetweenParticles.Norm() - m_length;

		if (m_attachParticle->getInverseMass() == 0)
		{
			particle->addPosition((vectorBetweenParticles * displacement));
		}
		else if (particle->getInverseMass() == 0)
		{
			m_attachParticle->addPosition((vectorBetweenParticles * displacement));
		}
		else
		{
			float firstMass = 1 / m_attachParticle->getInverseMass();
			float secondMass = 1 / particle->getInverseMass();

			float firstDisplacement = secondMass / (firstMass + secondMass) * displacement;
			float secondDisplacement = -1 * firstMass / (firstMass + secondMass) * displacement;

			// This ensure the length of the cable is always the same
			m_attachParticle->addPosition((vectorBetweenParticles * firstDisplacement));
			particle->addPosition((vectorBetweenParticles * secondDisplacement));
		}

		// Then we need to add an impulse
	}
}