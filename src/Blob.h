#pragma once
#include "Particle.h"
#include "DataStructures/Vector3D.h"
#include "Forces/ForceRegistry.h"
#include "Forces/Spring.h"
#include "Collisions/Cable.h"
#include "Collisions/Spindle.h"
#include "Collisions/CollisionHandler.h"

class Blob {
private:
	// The particle at the center of the blob
	Particle* m_core;
	// The length of the spring between the core and the other particles composing the blob
	float m_springLength;
	Spring* m_springCoreParticle;
	Cable* m_cableCoreParticle;
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

    	@return a pointer to the core of the blob
    	*/
	Particle* getCore();

	/*
	Split the particles from the blob
    	*/
	void split();
	
	/*
	Merge the particle in the blob

	@param particle, the particle to add to the blob
    	*/
	void merge(Particle* particle, ForceRegistry* forceRegistry, CollisionHandler* collisionHandler);
        
    	/*
    	Link all particles in the blob to the core

   	@param forceRegistry, to create a link
    	@param collisionHandler, to manage collisions
    	*/
	void linkParticles(ForceRegistry* forceRegistry, CollisionHandler* collisionHandler);
	
	/*
	* Link a particle to the core of the blob

  	@param particle, the particle to link
   	@param forceRegistry, to create a link
    	@param collisionHandler, to manage collisions
	*/
	void linkParticle(Particle* particle, ForceRegistry* forceRegistry, CollisionHandler* collisionHandler);
};
