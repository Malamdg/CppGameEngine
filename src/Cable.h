#pragma once
#include "ParticleForceGenerator.h"
#include "Particle.h"

class Cable : public ParticleForceGenerator
{
private:
	Vector3D* m_attachPoint;
	Particle* m_attachParticle;
	float m_length;

public:
	Cable(Vector3D* attachPoint, float length);
	Cable(Particle* attachParticle, float length);

	~Cable();

	void updateForce(Particle* particle, float duration = 0) override;

protected:
	void updateForPoint(Particle* particle);
	void updateForParticle(Particle* particle);

};