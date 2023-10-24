#include "Blob.h"
#include "Particle.h"
#include "Forces/SpringParticleParticle.h"

Blob::Blob(Particle* core) 
	: 
	m_core(core)
{
	m_particles = std::list<Particle*>();

	m_particles.push_back(m_core);
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(0, 10)));
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(10, 0)));
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(0, -10)));
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(-10, 0)));
};

Blob::~Blob() {}

void Blob::linkParticles(ParticleForceRegistry* forceRegistry) {
	int i = 0;
	for (Particle* particle : m_particles) {
		if (i == 0) {// dont link core to itself
			i++;
			continue;
		}
		SpringParticleParticle* springCoreParticle = new SpringParticleParticle(m_core);
		forceRegistry->add(particle, springCoreParticle);
	}
}

Particle* Blob::getCore() {
	return m_core;
}

void Blob::merge(Particle* particle) {
	m_particles.push_back(particle);
}