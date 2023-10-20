#pragma once
#include "ParticleForceGenerator.h"
#include "Particle.h"

class Spindle : public ParticleForceGenerator
{
private:
	Vector3D* m_attachPoint;
	Particle* m_attachParticle;
	float m_length;

public:
	Spindle(Vector3D* attachPoint, float length);
	Spindle(Particle* attachParticle, float length);

	~Spindle();

	void updateForce(Particle* particle, float duration = 0) override;

protected:
	void updateForPoint(Particle* particle);
	void updateForParticle(Particle* particle);
};