#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector3D.h"

class ParticleGravity : public ParticleForceGenerator{
	
private:
	/* constant of gravity */
	Vector3D m_gravity;

public:
	/*
	class constructor

	@param gravity, the vector associated to gravity
	*/
	ParticleGravity::ParticleGravity(Vector3D gravity)
		: 
		ParticleForceGenerator(),
		m_gravity(gravity)
	{ }

	ParticleGravity::~ParticleGravity() { }

	/*
	update the particle's gravity

	@param *particle, the particle to update
	@param duration, frame duration when the gravity applies
	*/
	virtual void updateForce(Particle* particle, float duration) 
	{
		particle->addForce(m_gravity * (1 / particle->getInverseMass()));
	}
};