#pragma once

#include <Collider.h>


Collider::Collider(RigidBody* rb, Vector3D center) :
	m_center(center),
	m_rigidbody(rb)
{}

Collider::~Collider()
{
	delete m_rigidbody;
}

void Collider::setPosition(Vector3D position)
{
	m_center = position;
}

void Collider::setRotation(Quaternion rotation) {}

Vector3D Collider::getPosition() { return m_center; }

RigidBody* Collider::getRigidBody() { return m_rigidbody; }

list<Contact*> Collider::intersect(Collider* collider) { return list<Contact*>(); }

