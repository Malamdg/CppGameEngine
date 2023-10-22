#pragma once
#include "ParticleForceGenerator.h"
#include "Particle.h"

class Spindle : public ParticleForceGenerator
{
private:
/* The spindle can only be linked to a Point or another Particle, never both */
	/* Point attached to the particle */
	Vector3D* m_attachPoint;
	/* Other particle attached to the spindle */
	Particle* m_attachParticle;
	/* spindle length */
	float m_length;

public:
	/*
	class constructor for a Spindle between a particle and a point

	@param attachPoint, the point to wich the particle is attached
 	@param length, the cable length
	*/
	Spindle(Vector3D* attachPoint, float length);

	/*
	class constructor for a Spindle between two particles

	@param attachPoint, the point to wich the particle is attached
 	@param length, the cable length
	*/
	Spindle(Particle* attachParticle, float length);

	/* Class Destructor */
	~Spindle();

	/*
	inherited method, update the force applied to a particle

	@param particle, the particle to update
 	@param duration, frame's duration
	*/
	void updateForce(Particle* particle, float duration = 0) override;

protected:
	/*
	update the cable between a particle and a point

	@param particle, the particle to update
	*/
	void updateForPoint(Particle* particle);

	/*
	update the cable between a particle and another particle

	@param particle, the particle to update
	*/
	void updateForParticle(Particle* particle);
};
