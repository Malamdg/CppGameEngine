#pragma once

#include <Collider.h>


Collider::Collider(Vector3D* center)
	:
	m_center(center)
{}

Collider::~Collider()
{
	delete m_center;
}

void Collider::setPosition(Vector3D* translation) {}

void Collider::setRotation(Quaternion* rotation) {}

Vector3D* Collider::getPosition() { return m_center; }

bool Collider::intersect(Collider* collider) {}