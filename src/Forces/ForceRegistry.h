
#pragma once
#include "ForceGenerator.h"

class ForceRegistry
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
		ForceGenerator* Fg;
	};

	/*
	Definition of the struct ParticleForceRegistration

	rigidbody, rigidbody to which the force is applied
	Fg, the generator of the force
	*/
	struct RigidBodyForceRegistration
	{
		RigidBody* rigidbody;
		ForceGenerator* Fg;
		Vector3D* rbPoint;
	};


	/*
	Create the type Registry

	Dynamic table of ParticleForceRegistration
	*/
	typedef std::vector<ParticleForceRegistration> ParticleRegistry;

	/*
	Create the type Registry

	Dynamic table of RigidBodyForceRegistration
	*/
	typedef std::vector<RigidBodyForceRegistration> RigidBodyRegistry;

	/*
	Constructor
	*/
	ForceRegistry();

	/*
	Destructor
	*/
	~ForceRegistry();

	/*
	Add a Particle to Registry

	@param particle, the particle to add
	@param Fg, the Force Generator associated to the particle
	*/
	void add(Particle* particle, ForceGenerator* Fg);

	/*
	Add a RigidBody to Registry

	@param rb, the RigidBody to add
	@param Fg, the Force Generator associated to the RigidBody
	*/
	void add(RigidBody* rb, ForceGenerator* Fg, Vector3D* rbPoint = new Vector3D());
	
	/*
	Remove a Particle from the Registry

	@param particle, the particle to remove
	@param Fg, the Force Generator associated to the particle
	*/
	void remove(Particle* particle, ForceGenerator* Fg);

	/*
	Remove a RigidBody from the Registry

	@param RigidBody, the RigidBody to remove
	@param Fg, the Force Generator associated to the RigidBody
	*/
	void remove(RigidBody* rb, ForceGenerator* Fg);

	/*
	Clear the Registry

	NOTE : the clearance does not delete the particles and the ForceGenerator in it
	*/
	void clear();

	/*
	Update the force applied to each particle

	@param duration, frame duration when the force applies
	*/
	void updateForces(float duration);

private:
	ParticleRegistry m_particleRegistry;
	RigidBodyRegistry m_rigidBodyRegistry;

};
