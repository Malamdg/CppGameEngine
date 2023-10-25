#pragma once
#include "Particle.h"
#include "Vector3D.h"
#include "Forces/ParticleForceRegistry.h"
#include "Forces/SpringParticleParticle.h"

class Blob {
private:
	// The particle at the centre of the blob
	Particle* m_core;
	SpringParticleParticle* m_springCoreParticle;

public:
	std::list<Particle*> m_particles;

        /*
      	class constructor

       	@param core, the particle at the centre of the blob
       	*/
	Blob(Particle* core = new Particle());

       	/*
       	class destructor
      	*/
	~Blob();

        /*
       	Get the core of the blob

       	@return the core of the blob
       	*/
	Particle* getCore();

	/*
	Merge the particle in the blob

	@param particle, the particle to add to the blob
       	*/
	void merge(Particle* particle);
        
       	/*
       	Link a particle yo the blob

       	@param forceRegistry, to create a link
       	*/
	void linkParticles(ParticleForceRegistry* forceRegistry);
};
