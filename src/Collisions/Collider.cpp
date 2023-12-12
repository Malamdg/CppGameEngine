#pragma once

#include <Collider.h>


Collider::Collider(RigidBody& rb, Vector3D& center)
	:
	m_center(center),
	m_rigidbody(rb)
{}

Collider::~Collider() {}

void Collider::setPosition(Vector3D* translation) {}

void Collider::setRotation(Quaternion* rotation) {}

Vector3D Collider::getPosition() { return m_center; }

RigidBody& Collider::getRigidBody() { return m_rigidbody; }

list<Contact*> Collider::intersect(Collider* collider) { return list<Contact*>(); }

