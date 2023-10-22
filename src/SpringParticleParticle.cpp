#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector3D.h"

class SpringParticleParticle : public ParticleForceGenerator {
	
private:
	/* Particle attached */
	Particle* m_particle;

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

	@param elasticity, elasticity constant
	*/
	SpringParticleParticle::SpringParticleParticle(Particle* particle, float elasticity = 1, float lenght = 10, float C = 0)
		:
		m_particle(particle),
		m_k(elasticity),
		m_l0(lenght),
		m_C(C),
		m_z(0),
		m_w(0)
	{}

	/*
	class desctructor
	*/
	SpringParticleParticle::~SpringParticleParticle() { }

	/*
	update the particle's force

	@param *particle, the particle to update
	@param duration, frame duration when the spring's force applies
	*/
	virtual void updateForce(Particle* particle, float duration)
	{
		Vector3D direction = (m_particle->getPosition() - particle->getPosition());

		if (!(direction == Vector3D()))
		{

			float invMass = particle->getInverseMass();
			/* l-l0 distance computation */
			float distance = m_l0 - direction.Norm();

			/* Force director vector */
			direction.Normalize();

			/* Velocity of the particle on the particle-fixation axis by projection */
			float velocityProj = particle->getVelocity() * direction;

			/* Calculation of natural frequency */
			m_w = sqrt(invMass * m_k);
			/* Calculation of the depreciation rate */
			m_z = m_C * invMass / 2 * m_w;

			float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

			/*std::cout << "Direction : " << direction.toString() << std::endl;
			std::cout << "distance : " << distance << std::endl;
			std::cout << "Projection : " << velocityProj << std::endl;
			std::cout << "Force z : " << (direction * coeff * duration).z() << std::endl;
			std::cout << "Coefficient : " << coeff << std::endl;*/

			particle->addForce(direction * coeff * duration);
		}
	}
};
