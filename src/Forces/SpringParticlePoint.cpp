#include "SpringParticlePoint.h"

SpringParticlePoint::SpringParticlePoint(Vector3D position, float elasticity, float lenght, float C)
	:
	m_pointPosition(position),
	m_k(elasticity),
	m_l0(lenght),
	m_C(C),
	m_z(0),
	m_w(0)
{}

SpringParticlePoint::~SpringParticlePoint() { }

void SpringParticlePoint::updateForce(Particle* particle, float duration) 
{
	Vector3D direction = (m_pointPosition - particle->getPosition());
		
	if(particle->getInverseMass() != 0 && !(direction == Vector3D()))
	{
		float invMass = particle->getInverseMass();
		/* l-l0 distance computation */
		float distance = m_l0 - direction.Norm();

		/* Force director vector */
		direction.Normalize();

		/* Velocity of the particle on the particle-fixation axis by projection */
		float velocityProj = particle->getVelocity() * direction;

		/* Calculation of natural pulse */
		m_w = sqrt(invMass * m_k);
		/* Calculation of the depreciation rate */
		m_z = m_C * invMass / 2 * m_w;

		float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

		particle->addForce(direction * coeff);
	}
}
