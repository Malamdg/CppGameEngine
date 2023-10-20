#include "Particle.h"
#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{

public:

	/*
	Definition of the struct ParticleForceRegistration

	particle, particle to which the force is applied
	Fg, the generator of the force
	*/
	struct ParticleForceRegistration
	{
		Particle* particle;
		ParticleForceGenerator* Fg;
	};

	/*
	Create the type Registry

	Dynamic table of ParticleForceRegistration
	*/
	typedef std::vector<ParticleForceRegistration> Registry;

	/*
	Constructor
	*/
	ParticleForceRegistry();

	/*
	Destructor
	*/
	~ParticleForceRegistry();

	/*
	Add a Particle to Registry

	@param particle, the particle to add
	@param Fg, the Force Generator associated to the particle
	*/
	void add(Particle* particle, ParticleForceGenerator* Fg);

	/*
	Remove a Particle from the Registry

	@param particle, the particle to remove
	@param Fg, the Force Generator associated to the particle
	*/
	void remove(Particle* particle, ParticleForceGenerator* Fg);

	/*
	Clear the Registry

	NOTE : the clearance does not delete the particles and the ParticleForceGenerator in it
	*/
	void clear();

	/*
	Update the force applied to each particle

	@param duration, frame duration when the force applies
	*/
	void updateForces(float duration);

private:
	Registry m_registry;

};