#include "GameObject.h"

GameObject::GameObject() {}

GameObject::GameObject(RigidBody* rigidBody, Box* boxCollider, Sphere* encompassingSphere) :
	m_rigidBody(rigidBody),
	m_boxCollider(boxCollider),
	m_encompassingSphere(encompassingSphere)
{}