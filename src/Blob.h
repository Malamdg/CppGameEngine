#pragma once
#include "Particle.h"
#include "Vector3D.h"
#include "Forces/ParticleForceRegistry.h"
#include "Forces/SpringParticleParticle.h"
#include "Collisions/Cable.h"

class Blob {
private:
	float m_springLength;
	Particle* m_core;
	SpringParticleParticle* m_springCoreParticle;
	Cable* m_cableCoreParticle;

public:
	std::list<Particle*> m_particles;

	Blob(Particle* core = new Particle());
	~Blob();

	Particle* getCore();
	void merge(Particle* particle);
	void linkParticles(ParticleForceRegistry* forceRegistry);

};