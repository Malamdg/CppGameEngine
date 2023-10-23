#include "Blob.h"
#include "Particle.h"
#include "SpringParticleParticle.h"

Blob::Blob(Particle core) 
	: 
	m_core(core)
{
	m_particles = std::list<Particle*>();

	m_particles.push_back(&m_core);
	m_particles.push_back(new Particle(10, m_core.getPosition() + Vector3D(0, 10)));
	m_particles.push_back(new Particle(10, m_core.getPosition() + Vector3D(10, 0)));
	m_particles.push_back(new Particle(10, m_core.getPosition() + Vector3D(0, -10)));
	m_particles.push_back(new Particle(10, m_core.getPosition() + Vector3D(-10, 0)));
};

Blob::~Blob() {}

void Blob::linkParticles(ParticleForceRegistry* forceRegistry) {
	for (Particle* particle : m_particles) {
		SpringParticleParticle* springCoreParticle = new SpringParticleParticle(&m_core);
		forceRegistry->add(particle, springCoreParticle);
	}
}

Particle Blob::getCore() {
	return m_core;
}

std::list<Particle*> Blob::getParticles() {
	return m_particles;
}

void Blob::merge(Particle* particle) {
	m_particles.push_back(particle);
}