#pragma once

#include "Plane.h"
#include <Matrix3.h>

Plane::Plane(RigidBody* rb, Vector3D center, Vector3D* normal, float width, float length)
	:
	Collider(rb, center),
	m_normal(*normal)
{
	// Orthonormal basis of world
	Vector3D top = Vector3D(0.f, 1.f, 0.f);
	Vector3D right = Vector3D(1.f, 0.f, 0.f);
	Vector3D forward = Vector3D(0.f, 0.f, 1.f);

	// Recenter on plane and keep vectors normed
	top = top + m_center;
	right = right + m_center;
	forward = forward + m_center;

	top.Normalize();
	right.Normalize();
	forward.Normalize();

	// Rotate them to align with plane
	top = Matrix3::FromQuaternion(m_rigidbody->getOrientation()) * top;
	right = Matrix3::FromQuaternion(m_rigidbody->getOrientation()) * right;
	forward = Matrix3::FromQuaternion(m_rigidbody->getOrientation()) * forward;

	// Prevent float approximation at maximum
	top.Normalize();
	right.Normalize();
	forward.Normalize();


	// Initialize the values
	if (m_normal == top) {
		m_right = right * (width / 2);
		m_forward = forward * (length / 2);
	}
	
	if (m_normal == right) {
		m_right = forward * (width / 2);
		m_forward = top * (length / 2);
	}

	if (m_normal == forward) {
		m_right = top * (width / 2);
		m_forward = right * (length / 2);
	}
}

Plane::~Plane() {}

void Plane::setPosition(Vector3D position) {
	Collider::setPosition(position);
}

void Plane::rotate(Quaternion* rotation)
{
	float normRight = m_right.Norm();
	float normForward = m_forward.Norm();

	// Allignement des axes avec le repère
	m_right = Vector3D(m_right.Norm(), 0, 0);
	m_forward = Vector3D(0, 0, m_forward.Norm());

	Matrix3 rotationM = Matrix3::FromQuaternion(*rotation);
	m_normal = rotationM * m_normal;
	m_right = rotationM * m_right;
	m_forward = rotationM * m_forward;

	// Normalize and extend to norn to guaranty that the float do not mess up the sizes
	m_normal.Normalize();
	m_right.Normalize();
	m_forward.Normalize();

	m_right = m_right * normRight;
	m_forward = m_forward * normForward;
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

}