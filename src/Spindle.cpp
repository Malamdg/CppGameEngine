#include "Spindle.h"

Spindle::Spindle(Particle* firstParticle, Particle* secondParticle, float length)
	: m_firstParticle(firstParticle),
	  m_secondParticle(secondParticle),
	  m_length(length)
{ }

Spindle::~Spindle() { }

void Spindle::Update()
{
	Vector3D vectorBetweenParticles = m_firstParticle->getPosition() - m_secondParticle->getPosition();
	
	if (vectorBetweenParticles.Norm() != m_length)
	{
		float displacement = vectorBetweenParticles.Norm() - m_length;
		float firstMass = 1 / m_firstParticle->getInverseMass();
		float secondMass = 1 / m_secondParticle->getInverseMass();

		float firstDisplacement = secondMass / (firstMass + secondMass) * displacement;
		float secondDisplacement = -1 * firstMass / (firstMass + secondMass) * displacement;

		// This ensure the length of the spindle is always the same
		m_firstParticle->addPosition((vectorBetweenParticles * firstDisplacement));
		m_secondParticle->addPosition((vectorBetweenParticles * secondDisplacement));

		// No impulse to add there because it is considered a static collision
	}
}