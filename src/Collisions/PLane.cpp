#pragma once

#include "Plane.h"
#include <Matrix3.h>

Plane::Plane(RigidBody* rb, Vector3D center, Vector3D* normal, float width, float length)
	:
	Collider(rb, center),
	m_normal(*normal),
	m_width(width),
	m_length(length)
{
}

Plane::~Plane() {}

void Plane::setPosition(Vector3D position) {
	Collider::setPosition(position);
}

void Plane::rotate(Quaternion* rotation)
{
	Matrix3 rotationM = Matrix3::FromQuaternion(*rotation);
	m_normal = rotationM * m_normal;

	// Normalize again to guaranty that the floats do not mess up the sizes
	m_normal.Normalize();
}

list<Contact*> Plane::intersect(Collider* collider)
{
	if (instanceof<Box>(collider))
	{
		return intersection((Box*)collider);
	}
	return list<Contact*>();
}

list<Contact*> Plane::intersection(Box* box) 
{
	list<Contact*> contacts = list<Contact*>();
	Contact* contact;
	Vector3D* vertices = box->getVertices();
	Vector3D vertex, point;
	float t;

	for (int i = 0; i < 8; i++) {
		vertex = vertices[i];

		point = vertex - m_center;
		t = m_normal * point;
		point = m_normal * t;
		point = vertex - point;

		if (t <= 0) {
			contact = new Contact(&vertex, &m_normal, t, box->getRigidBody(), getRigidBody());
		}
	}

	return contacts;
}