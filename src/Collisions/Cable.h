#pragma once
#include "ParticleForceGenerator.h"
#include "Particle.h"

class Cable : public ParticleForceGenerator
{
private:
/* The cable can only be linked to a Point or another Particle, never both */
	/* Point attached to the particle */
	Vector3D* m_attachPoint;
	/* Other particle attached to the cable */
	Particle* m_attachParticle;
	/* Cable length */
	float m_length;

public:
	/*
	class constructor for a cable between a particle and a point

	@param attachPoint, the point to wich the particle is attached
 	@param length, the cable length
	*/
	Cable(Vector3D* attachPoint, float length);
	/*
	class constructor for a cable betweentwo particles

	@param particle, the particle attached
 	@param length, the cable length
	*/
	Cable(Particle* attachParticle, float length);

	/*
	class destructor
	*/
	~Cable();

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
