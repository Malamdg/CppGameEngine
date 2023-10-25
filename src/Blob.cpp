#include "Blob.h"
#include "Particle.h"

Blob::Blob(Particle* core)
	:
	// to define the characteristics of the blob
	m_core(core),
	m_springLength(25.),
	m_springCoreParticle(new SpringParticleParticle(m_core, 1000, m_springLength, .05)),
	m_cableCoreParticle(new Cable(m_core, 2 * m_springLength))
{
	m_particles = std::list<Particle*>();

	// to arrange the particles around the core
	m_particles.push_back(m_core);
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(0, m_springLength), Vector3D(), .1));
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(m_springLength, 0), Vector3D(), .1));
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(0, -m_springLength), Vector3D(), .1));
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(-m_springLength, 0), Vector3D(), .1));
};

Blob::~Blob() {}

Particle* Blob::getCore() {
	return m_core;
}

void Blob::split() {
	// remove particles from m_particles except for the core
	for (int i = 0; i < m_particles.size() - 1; i++)
	{
		m_particles.pop_back();
	}
}

void Blob::merge(Particle* particle, ParticleForceRegistry* forceRegistry, CollisionHandler* collisionHandler) {
	m_particles.push_back(particle);
	linkParticle(particle, forceRegistry, collisionHandler);
}

void Blob::linkParticles(ParticleForceRegistry* forceRegistry, CollisionHandler* collisionHandler) {
	int i = 0;
	for (Particle* particle : m_particles) {
		if (i == 0) {// dont link core to itself
			i++;
			continue;
		}
		linkParticle(particle, forceRegistry, collisionHandler);
	}
}

void Blob::linkParticle(Particle* particle, ParticleForceRegistry* forceRegistry, CollisionHandler* collisionHandler) {
	// We add the spring between the core and the surrounding particle created to the forceregistry
	forceRegistry->add(particle, m_springCoreParticle);
	// We add the create a cable between the core an the surrounding particle to ensure that particle doesn't go too far 
	collisionHandler->add(particle, m_cableCoreParticle);
}