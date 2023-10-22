#include "Cable.h"

Cable::Cable(Particle* firstParticle, Particle* secondParticle, float length)
	: m_firstParticle(firstParticle),
	  m_secondParticle(secondParticle),
	  m_length(length)
{ }

Cable::~Cable() { }

void Cable::Update()
{
	Vector3D vectorBetweenParticles = m_firstParticle->getPosition() - m_secondParticle->getPosition();
	
	if (vectorBetweenParticles.Norm() > m_length)
	{
		float displacement = vectorBetweenParticles.Norm() - m_length;
		float firstMass = 1 / m_firstParticle->getInverseMass();
		float secondMass = 1 / m_secondParticle->getInverseMass();

		float firstDisplacement = secondMass / (firstMass + secondMass) * displacement;
		float secondDisplacement = -1 * firstMass / (firstMass + secondMass) * displacement;

		// This separate the two particles

		// TODO : Add those two lines once the branch are merged

		//m_firstParticle->addPosition((vectorBetweenParticles * firstDisplacement));
		//m_secondParticle->addPosition((vectorBetweenParticles * secondDisplacement));

		// Then we need to add an impulse
	}
}