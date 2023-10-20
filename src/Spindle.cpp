#include "Spindle.h"

Spindle::Spindle(Vector3D* attachPoint, float length)
	: m_attachPoint(attachPoint),
	  m_attachParticle(nullptr),
	  m_length(length)
{ }

Spindle::Spindle(Particle* attachParticle, float length)
	: m_attachPoint(nullptr),
	  m_attachParticle(attachParticle),
	  m_length(length)
{ }

Spindle::~Spindle() { }

void Spindle::updateForce(Particle* particle, float duration)
{
	if (m_attachPoint != nullptr) updateForPoint(particle);
	else updateForParticle(particle);
}

void Spindle::updateForPoint(Particle* particle)
{
	Vector3D vectorBetweenParticles = *m_attachPoint - particle->getPosition();

	if (vectorBetweenParticles.Norm() != m_length)
	{
		float displacement = vectorBetweenParticles.Norm() - m_length;

		// We don't need to calculate ponderated displacement as the point is supposed unmovable

		particle->addPosition((vectorBetweenParticles * displacement));

		// No impulse to add there because it is considered a static collision
	}
}

void Spindle::updateForParticle(Particle* particle)
{
	Vector3D vectorBetweenParticles = m_attachParticle->getPosition() - particle->getPosition();

	if (vectorBetweenParticles.Norm() != m_length)
	{
		float displacement = vectorBetweenParticles.Norm() - m_length;
		float firstMass = 1 / m_attachParticle->getInverseMass();
		float secondMass = 1 / particle->getInverseMass();

		float firstDisplacement = secondMass / (firstMass + secondMass) * displacement;
		float secondDisplacement = -1 * firstMass / (firstMass + secondMass) * displacement;

		// This ensure the length of the spindle is always the same
		m_attachParticle->addPosition((vectorBetweenParticles * firstDisplacement));
		particle->addPosition((vectorBetweenParticles * secondDisplacement));

		// No impulse to add there because it is considered a static collision
	}
}