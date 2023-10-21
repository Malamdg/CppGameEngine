#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector3D.h"

class SpringParticlePoint : public ParticleForceGenerator {
	
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

	@param elasticity, elasticity constant
	*/
	SpringParticlePoint::SpringParticlePoint(Vector3D position, float elasticity = 1, float lenght = 10, float C = 0)
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
	SpringParticlePoint::~SpringParticlePoint() { }

	/*
	update the particle's gravity

	@param *particle, the particle to update
	@param duration, frame duration when the gravity applies
	*/
	virtual void updateForce(Particle* particle, float duration) 
	{
		Vector3D direction = (m_pointPosition - particle->getPosition());
		
		if(!(direction == Vector3D()))
		{

			float invMass = particle->getInverseMass();
			float distance = m_l0 - direction.Norm();

			direction.Normalize();

			float velocityProj = particle->getVelocity() * direction;

			m_w = sqrt(invMass * m_k);
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