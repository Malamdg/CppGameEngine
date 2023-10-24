#include "Blob.h"
#include "Particle.h"

Blob::Blob(Particle* core) 
	: 
	m_core(core),
	m_springCoreParticle(new SpringParticleParticle(m_core, .5, 15, .1))
{
	m_particles = std::list<Particle*>();

	m_particles.push_back(m_core);
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(0, 100), Vector3D(), 5));
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(100, 0), Vector3D(), 5));
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(0, -100), Vector3D(), 5));
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(-100, 0), Vector3D(), 5));
};

Blob::~Blob() {}

void Blob::linkParticles(ParticleForceRegistry* forceRegistry) {
	int i = 0;
	for (Particle* particle : m_particles) {
		if (i == 0) {// dont link core to itself
			i++;
			continue;
		}
		forceRegistry->add(particle, m_springCoreParticle);
	}
}

Particle* Blob::getCore() {
	return m_core;
}

void Blob::merge(Particle* particle) {
	m_particles.push_back(particle);
}