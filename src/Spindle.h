#pragma once
#include "Particle.h"

class Spindle
{
private:
	Particle* m_firstParticle;
	Particle* m_secondParticle;
	float m_length;

public:
	Spindle(Particle* firstParticle, Particle* secondParticle, float length);

	~Spindle();

	void Update();

};