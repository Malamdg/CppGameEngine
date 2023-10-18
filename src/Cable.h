#pragma once
#include "Particle.h"

class Cable
{
private:
	Particle* m_firstParticle;
	Particle* m_secondParticle;
	float m_length;

public:
	Cable(Particle* firstParticle, Particle* secondParticle, float length);

	~Cable();

	void Update();

};