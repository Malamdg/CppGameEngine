#include "Elastic.h"

Elastic::Elastic(Vector3D* position, float elasticity, float lenght, float C)
	:
	m_pointPosition(position),
	m_particle(nullptr),
	m_rigidBody(nullptr),
	m_k(elasticity),
	m_l0(lenght),
	m_C(C),
	m_z(0),
	m_w(0)
{}
Elastic::Elastic(Particle* particle, float elasticity, float lenght, float C)
	:
	m_pointPosition(nullptr),
	m_particle(particle),
	m_rigidBody(nullptr),
	m_k(elasticity),
	m_l0(lenght),
	m_C(C),
	m_z(0),
	m_w(0)
{}
Elastic::Elastic(RigidBody* rb, float elasticity, float lenght, float C)
	:
	m_pointPosition(nullptr),
	m_particle(nullptr),
	m_rigidBody(rb),
	m_k(elasticity),
	m_l0(lenght),
	m_C(C),
	m_z(0),
	m_w(0)
{}

Elastic::~Elastic() 
{
	delete m_pointPosition;
	delete m_particle;
	delete m_rigidBody;
}

void Elastic::updateForce(Particle* particle, float duration)
{
	if (m_pointPosition != nullptr) updateForPoint(particle, duration);
	else if (m_particle != nullptr) updateForParticle(particle, duration);
	else updateForRigidBody(particle, duration);
}

void Elastic::updateForce(RigidBody* rb, float duration)
{
	if (m_pointPosition != nullptr) updateForPoint(rb, duration);
	else if (m_particle != nullptr) updateForParticle(rb, duration);
	else updateForRigidBody(rb, duration);
}

void Elastic::updateForPoint(Particle* particle, float duration)
{
	Vector3D direction = (*m_pointPosition - particle->getPosition());

	/* l-l0 distance computation */
	float distance = m_l0 - direction.Norm();

	if (particle->getInverseMass() != 0 && !(direction == Vector3D()) && distance < 0)
	{

		float invMass = particle->getInverseMass();


		/* Force director vector */
		direction.Normalize();

		/* Velocity of the particle on the particle-fixation axis by projection */
		float velocityProj = particle->getVelocity() * direction;

		/* Calculation of natural frequency */
		m_w = sqrt(invMass * m_k);
		/* Calculation of the depreciation rate */
		m_z = m_C * invMass / 2 * m_w;

		float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

		particle->addForce(direction * coeff * duration);
	}
}
void Elastic::updateForPoint(RigidBody* rb, float duration)
{
	Vector3D direction = (*m_pointPosition - rb->getPosition());

	/* l-l0 distance computation */
	float distance = m_l0 - direction.Norm();

	if (rb->getInverseMass() != 0 && !(direction == Vector3D()) && distance < 0)
	{

		float invMass = rb->getInverseMass();


		/* Force director vector */
		direction.Normalize();

		/* Velocity of the particle on the particle-fixation axis by projection */
		float velocityProj = rb->getVelocity() * direction;

		/* Calculation of natural frequency */
		m_w = sqrt(invMass * m_k);
		/* Calculation of the depreciation rate */
		m_z = m_C * invMass / 2 * m_w;

		float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

		rb->addForce(direction * coeff * duration);
	}
}

void Elastic::updateForParticle(Particle* particle, float duration)
{
	Vector3D direction = (m_particle->getPosition() - particle->getPosition());

	/* l-l0 distance computation */
	float distance = m_l0 - direction.Norm();

	if (particle->getInverseMass() != 0 && !(direction == Vector3D()) && distance < 0)
	{

		float invMass = particle->getInverseMass();

		/* Force director vector */
		direction.Normalize();

		/* Velocity of the particle on the particle-fixation axis by projection */
		float velocityProj = particle->getVelocity() * direction;

		/* Calculation of natural pulse */
		m_w = sqrt(invMass * m_k);
		/* Calculation of the depreciation rate */
		m_z = m_C * invMass / 2 * m_w;

		float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

		particle->addForce(direction * coeff * duration);
	}
}
void Elastic::updateForParticle(RigidBody* rb, float duration)
{
	Vector3D direction = (m_particle->getPosition() - rb->getPosition());

	/* l-l0 distance computation */
	float distance = m_l0 - direction.Norm();

	if (rb->getInverseMass() != 0 && !(direction == Vector3D()) && distance < 0)
	{

		float invMass = rb->getInverseMass();

		/* Force director vector */
		direction.Normalize();

		/* Velocity of the particle on the particle-fixation axis by projection */
		float velocityProj = rb->getVelocity() * direction;

		/* Calculation of natural pulse */
		m_w = sqrt(invMass * m_k);
		/* Calculation of the depreciation rate */
		m_z = m_C * invMass / 2 * m_w;

		float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

		rb->addForce(direction * coeff * duration);
	}
}

void Elastic::updateForRigidBody(Particle* particle, float duration)
{
	Vector3D direction = (m_rigidBody->getPosition() - particle->getPosition());

	/* l-l0 distance computation */
	float distance = m_l0 - direction.Norm();

	if (particle->getInverseMass() != 0 && !(direction == Vector3D()) && distance < 0)
	{

		float invMass = particle->getInverseMass();

		/* Force director vector */
		direction.Normalize();

		/* Velocity of the particle on the particle-fixation axis by projection */
		float velocityProj = particle->getVelocity() * direction;

		/* Calculation of natural pulse */
		m_w = sqrt(invMass * m_k);
		/* Calculation of the depreciation rate */
		m_z = m_C * invMass / 2 * m_w;

		float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

		particle->addForce(direction * coeff * duration);
	}
}
void Elastic::updateForRigidBody(RigidBody* rb, float duration)
{
	Vector3D direction = (m_rigidBody->getPosition() - rb->getPosition());

	/* l-l0 distance computation */
	float distance = m_l0 - direction.Norm();

	if (rb->getInverseMass() != 0 && !(direction == Vector3D()) && distance < 0)
	{

		float invMass = rb->getInverseMass();

		/* Force director vector */
		direction.Normalize();

		/* Velocity of the particle on the particle-fixation axis by projection */
		float velocityProj = rb->getVelocity() * direction;

		/* Calculation of natural pulse */
		m_w = sqrt(invMass * m_k);
		/* Calculation of the depreciation rate */
		m_z = m_C * invMass / 2 * m_w;

		float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

		rb->addForce(direction * coeff * duration);
	}
}