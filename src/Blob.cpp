#include "Blob.h"
#include "Particle.h"

Blob::Blob(Particle* core)
	:
	m_core(core),
	m_springLength(25.),
	m_springCoreParticle(new SpringParticleParticle(m_core, 15, m_springLength, 5)),
	m_cableCoreParticle(new Cable(m_core, 2 * m_springLength))
{
	m_particles = std::list<Particle*>();

	m_particles.push_back(m_core);
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(0, m_springLength), Vector3D(), .1));
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(m_springLength, 0), Vector3D(), .1));
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(0, -m_springLength), Vector3D(), .1));
	m_particles.push_back(new Particle(10, m_core->getPosition() + Vector3D(-m_springLength, 0), Vector3D(), .1));
};

Blob::~Blob() {}

void Blob::linkParticles(ParticleForceRegistry* forceRegistry, CollisionHandler* collisionHandler) {
	int i = 0;
	for (Particle* particle : m_particles) {
		if (i == 0) {// dont link core to itself
			i++;
			continue;
		}
		forceRegistry->add(particle, m_springCoreParticle);
		//collisionHandler->add(particle, m_cableCoreParticle);
	}
}

Particle* Blob::getCore() {
	return m_core;
}

void Blob::merge(Particle* particle) {
	m_particles.push_back(particle);
}