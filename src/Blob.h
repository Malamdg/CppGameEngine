#pragma once
#include "Particle.h"
#include "Vector3D.h"
#include "Forces/ParticleForceRegistry.h"

class Blob {
private:
	Particle* m_core;

public:
	std::list<Particle*> m_particles;

	Blob(Particle* core = new Particle());
	~Blob();

	Particle* getCore();
	void merge(Particle* particle);
	void linkParticles(ParticleForceRegistry* forceRegistry);

};