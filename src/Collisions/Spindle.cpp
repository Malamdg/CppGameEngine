#include "Spindle.h"

Spindle::Spindle(Vector3D* attachPoint, float length)
	: Collision(),
	// linking the spindle to the point 
	  m_attachPoint(attachPoint),
	// the spindle is already linked, it can't also be attached to another particle
	  m_attachParticle(nullptr),
	  m_length(length)
{ }

Spindle::Spindle(Particle* attachParticle, float length)
	: Collision(),
	// the spindle is already linked, it can't also be attached to a point
	  m_attachPoint(nullptr),
	// linking the spindle to the other particle
	  m_attachParticle(attachParticle),
	  m_length(length)
{ }

Spindle::~Spindle() { }

void Spindle::update(Particle* particle)
{
	// if the particle is bound to an attachment point
	if (m_attachPoint != nullptr) updateForPoint(particle);
	// the particle is linked to another particle
	else updateForParticle(particle);
}

void Spindle::updateForPoint(Particle* particle)
{
	Vector3D vectorBetweenPoints = *m_attachPoint - particle->getPosition();

	if (vectorBetweenPoints.Norm() != m_length)
	{
		float displacement = vectorBetweenPoints.Norm() - m_length;
		vectorBetweenPoints.Normalize();

		// We don't need to calculate ponderated displacement as the point is supposed unmovable

		Vector3D displacementVector = vectorBetweenPoints * displacement;
		particle->addPosition(displacementVector);

		// No impulse to add there because it is considered a static collision
	}
}

void Spindle::updateForParticle(Particle* particle)
{
	Vector3D vectorBetweenParticles = m_attachParticle->getPosition() - particle->getPosition();

	if (vectorBetweenParticles.Norm() != m_length)
	{
		float displacement = vectorBetweenParticles.Norm() - m_length;
		vectorBetweenParticles.Normalize();

		// the first particle has an inifinite mass and can't move
		if (m_attachParticle->getInverseMass() == 0)
		{
			Vector3D displacementVector = vectorBetweenParticles * displacement;
			particle->addPosition(displacementVector);
		}
		// the second particle has an inifinite mass and can't move
		else if (particle->getInverseMass() == 0)
		{
			Vector3D displacementVector = vectorBetweenParticles * displacement * -1;
			m_attachParticle->addPosition(displacementVector);
		}
		else
		{
			float firstMass = 1 / m_attachParticle->getInverseMass();
			float secondMass = 1 / particle->getInverseMass();

			float firstDisplacement = -1 * secondMass / (firstMass + secondMass) * displacement;
			float secondDisplacement = firstMass / (firstMass + secondMass) * displacement;

			Vector3D firstDisplacementVector = vectorBetweenParticles * firstDisplacement;
			Vector3D secondDisplacementVector = vectorBetweenParticles * secondDisplacement;

			// This ensure the length of the spindle is always the same
			m_attachParticle->addPosition(firstDisplacementVector);
			particle->addPosition(secondDisplacementVector);
		}

		// No impulse to add there because it is considered a static collision
	}
}
