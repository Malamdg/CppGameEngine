#include "Spring.h"


Spring::Spring(Vector3D* position, float elasticity, float lenght, float C)
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
Spring::Spring(Particle* particle, float elasticity, float lenght, float C)
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
Spring::Spring(RigidBody* rb, float elasticity, float lenght, float C)
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

Spring::~Spring()
{
	delete m_pointPosition;
	delete m_particle;
	delete m_rigidBody;
}

void Spring::updateForce(Particle* particle, float duration)
{
	if (m_pointPosition != nullptr) updateForPoint(particle, duration);
	else if (m_particle != nullptr) updateForParticle(particle, duration);
	else updateForRigidBody(particle, duration);
}
void Spring::updateForce(RigidBody* rb, float duration, Vector3D* rbPoint)
{
	if (m_pointPosition != nullptr) updateForPoint(rb, duration, rbPoint);
	else if (m_particle != nullptr) updateForParticle(rb, duration, rbPoint);
	else updateForRigidBody(rb, duration, rbPoint);
}


void Spring::updateForPoint(Particle* particle, float duration)
{
	Vector3D direction = (*m_pointPosition - particle->getPosition());

	if (particle->getInverseMass() != 0 && !(direction == Vector3D()))
	{
		float invMass = particle->getInverseMass();
		/* l-l0 distance computation */
		float distance = m_l0 - direction.Norm();

		/* Force director vector */
		direction.Normalize();

		/* Velocity of the particle on the particle-fixation axis by projection */
		float velocityProj = particle->getVelocity() * direction;

		/* Calculation of natural pulse */
		m_w = sqrt(invMass * m_k);
		/* Calculation of the depreciation rate */
		m_z = m_C * invMass / 2 * m_w;

		float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

		Vector3D res = direction * coeff;
		particle->addForce(res);
	}
}
void Spring::updateForPoint(RigidBody* rb, float duration, Vector3D* rbPoint)
{
	Vector3D worldPoint = rb->getWorldPosition(rbPoint);
	Vector3D direction = ((*m_pointPosition) - worldPoint);

	if (rb->getInverseMass() != 0 && !(direction == Vector3D()))
	{
		float invMass = rb->getInverseMass();
		/* l-l0 distance computation */
		float distance = m_l0 - direction.Norm();

		/* Force director vector */
		direction.Normalize();

		/* Velocity of the particle on the particle-fixation axis by projection */
		float velocityProj = rb->getVelocity() * direction;

		/* Calculation of natural pulse */
		m_w = sqrt(invMass * m_k);
		/* Calculation of the depreciation rate */
		m_z = m_C * invMass / 2 * m_w;

		float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);


		Vector3D res = direction * coeff;
		rb->addForce(res, (*rbPoint));
	}
}

void Spring::updateForParticle(Particle* particle, float duration)
{
	Vector3D direction = (m_particle->getPosition() - particle->getPosition());

	if (particle->getInverseMass() != 0 && !(direction == Vector3D()))
	{
		float invMass = particle->getInverseMass();
		/* l-l0 distance computation */
		float distance = m_l0 - direction.Norm();

		/* Force director vector */
		direction.Normalize();

		/* Velocity of the particle on the particle-fixation axis by projection */
		float velocityProj = particle->getVelocity() * direction;

		/* Calculation of natural pulse */
		m_w = sqrt(invMass * m_k);
		/* Calculation of the depreciation rate */
		m_z = m_C * invMass / 2 * m_w;

		float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

		Vector3D res = direction * coeff;
		particle->addForce(res);
	}
}
void Spring::updateForParticle(RigidBody* rb, float duration, Vector3D* rbPoint)
{
	Vector3D worldPoint = rb->getWorldPosition(rbPoint);
	Vector3D direction = (m_particle->getPosition() - worldPoint);

	if (rb->getInverseMass() != 0 && !(direction == Vector3D()))
	{
		float invMass = rb->getInverseMass();
		/* l-l0 distance computation */
		float distance = m_l0 - direction.Norm();

		/* Force director vector */
		direction.Normalize();

		/* Velocity of the particle on the particle-fixation axis by projection */
		float velocityProj = rb->getVelocity() * direction;

		/* Calculation of natural pulse */
		m_w = sqrt(invMass * m_k);
		/* Calculation of the depreciation rate */
		m_z = m_C * invMass / 2 * m_w;

		float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

		Vector3D res = direction * coeff;
		rb->addForce(res, (*rbPoint));
	}
}

void Spring::updateForRigidBody(Particle* particle, float duration)
{
	Vector3D direction = (m_rigidBody->getPosition() - particle->getPosition());

	if (particle->getInverseMass() != 0 && !(direction == Vector3D()))
	{
		float invMass = particle->getInverseMass();
		/* l-l0 distance computation */
		float distance = m_l0 - direction.Norm();

		/* Force director vector */
		direction.Normalize();

		/* Velocity of the particle on the particle-fixation axis by projection */
		float velocityProj = particle->getVelocity() * direction;

		/* Calculation of natural pulse */
		m_w = sqrt(invMass * m_k);
		/* Calculation of the depreciation rate */
		m_z = m_C * invMass / 2 * m_w;

		float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

		Vector3D res = direction * coeff;
		particle->addForce(res);
	}
}
void Spring::updateForRigidBody(RigidBody* rb, float duration, Vector3D* rbPoint)
{
	Vector3D worldPoint = rb->getWorldPosition(rbPoint);
	Vector3D direction = (m_rigidBody->getPosition() - worldPoint);

	if (rb->getInverseMass() != 0 && !(direction == Vector3D()))
	{
		float invMass = rb->getInverseMass();
		/* l-l0 distance computation */
		float distance = m_l0 - direction.Norm();

		/* Force director vector */
		direction.Normalize();

		/* Velocity of the particle on the particle-fixation axis by projection */
		float velocityProj = rb->getVelocity() * direction;

		/* Calculation of natural pulse */
		m_w = sqrt(invMass * m_k);
		/* Calculation of the depreciation rate */
		m_z = m_C * invMass / 2 * m_w;

		float coeff = (-m_w * m_w * distance) - (2 * m_z * m_w * velocityProj);

		Vector3D res = direction * coeff;
		rb->addForce(res, (*rbPoint));
	}
}