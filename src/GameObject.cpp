#include "GameObject.h"

GameObject::GameObject() :
	m_rigidBody(new RigidBody()),
	m_boxCollider(new Box(m_rigidBody, &m_rigidBody->getPosition(), new Vector3D(1, 0, 0), new Vector3D(0, 1, 0), new Vector3D(0, 0, 1))),
	m_encompassingSphere(new Sphere(m_rigidBody, &m_rigidBody->getPosition(), 2))
{}

GameObject::GameObject(RigidBody* rigidBody, Box* boxCollider, Sphere* encompassingSphere) :
	m_rigidBody(rigidBody),
	m_boxCollider(boxCollider),
	m_encompassingSphere(encompassingSphere)
{}

GameObject::~GameObject()
{
	delete m_rigidBody;
	delete m_boxCollider;
	delete m_encompassingSphere;
}

void GameObject::update()
{
	m_rigidBody->Update();
	m_boxCollider->update();
	m_encompassingSphere->update();
}

void GameObject::draw()
{

}