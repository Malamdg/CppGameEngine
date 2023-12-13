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

void Plane::update()
{
	setPosition(m_rigidbody->getPosition());
	rotate(&m_rigidbody->getOrientation());
}

void Plane::setPosition(Vector3D position) {
	Collider::setPosition(position);
}

Vector3D Plane::getNormal()
{
	return m_normal;
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
	return list<Contact*>();
}

void Plane::draw()
{
	ofBoxPrimitive boxPrimitive(m_width, .1, m_length);
	boxPrimitive.setOrientation(getRigidBody()->getOrientation().q());
	boxPrimitive.setPosition(getPosition().v3());

	boxPrimitive.drawWireframe();

	ofCylinderPrimitive cylinderPrimitive = ofCylinderPrimitive();
	cylinderPrimitive.setRadius(.2f);
	cylinderPrimitive.setHeight(10.f);
	cylinderPrimitive.setOrientation(getRigidBody()->getOrientation().q());
	cylinderPrimitive.setPosition((getPosition() + Vector3D(0, 5)).v3());
	
	cylinderPrimitive.draw();
	
	ofConePrimitive conePrimitive = ofConePrimitive();
	conePrimitive.setRadius(.5f);
	conePrimitive.setHeight(-.8f);
	conePrimitive.setOrientation(getRigidBody()->getOrientation().q());
	conePrimitive.setPosition((getPosition() + Vector3D(0, 10)).v3()); 
	
	conePrimitive.draw();
}
