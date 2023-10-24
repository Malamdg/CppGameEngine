#include "../Particle.h"
#include "ParticleForceGenerator.h"
#include "../Vector3D.h"

class ElasticParticlePoint : public ParticleForceGenerator {

private:
	/* Point positon */
	Vector3D m_pointPosition;

	/* elasticity constant */
	float m_k;

	/* length at sleep */
	float m_l0;

	/* Damping Coefficient */
	float m_C;

	/* Damping ratio */
	float m_z;

	/* Oscilation frenquency */
	float m_w;

public:
	/*
	class constructor

	@param position, the position of the point where the spring is attached
	@param elasticity, the elasticity of the spring
	@param lenght, the lenght of the spring
	@param C, a coefficient value
	*/
	ElasticParticlePoint::ElasticParticlePoint(Vector3D position, float elasticity = 1, float lenght = 10, float C = 1)
		:
		m_pointPosition(position),
		m_k(elasticity),
		m_l0(lenght),
		m_C(C),
		m_z(0),
		m_w(0)
	{}

	/*
	class desctructor
	*/
	ElasticParticlePoint::~ElasticParticlePoint() { }

	/*
	update the particle's force

	@param particle, pointer to the particle to update
	@param duration, frame duration when the srping's force applies
	*/
	virtual void updateForce(Particle* particle, float duration)
	{
		Vector3D direction = (m_pointPosition - particle->getPosition());
		
		/* l-l0 distance computation */
		float distance = m_l0 - direction.Norm();

		if (particle->getInverseMass() != 0 && !(direction == Vector3D()) && distance < 0)
		{

			float invMass = particle->getInverseMass();
			

			/* Force director vector */
			direction.Normalize();

			/* Velocity of the particle on the particle-fixation axis by projection */
			float velocityProj = particle->getVelocity() * direction;

			/* Calculation of natural frequency */
			m_w = sqrt(invMass * m_k);
			/* Calculation of the depreciation rate */
			m_z = m_C * invMass / 2 * m_w;

			float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

			particle->addForce(direction * coeff * duration);
		}
	}
};
