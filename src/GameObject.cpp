#include "GameObject.h"

GameObject::GameObject() :
	m_rigidBody(new RigidBody()),
	m_collider(new Box(m_rigidBody, m_rigidBody->getPosition(), Vector3D(1, 0, 0), Vector3D(0, 1, 0), Vector3D(0, 0, 1))),
	m_encompassingSphere(new Sphere(m_rigidBody, m_rigidBody->getPosition(), 2))
{}

GameObject::GameObject(RigidBody* rigidBody, Box* boxCollider, Sphere* encompassingSphere) :
	m_rigidBody(rigidBody),
	m_collider(boxCollider),
	m_encompassingSphere(encompassingSphere)
{}

GameObject::~GameObject()
{
	delete m_rigidBody;
	delete m_collider;
	delete m_encompassingSphere;
}

void GameObject::update()
{
	m_rigidBody->Update();
	m_collider->update();
	m_encompassingSphere->update();
}

void GameObject::draw(ofColor color, bool drawCollider, bool drawSphere)
{
	ofSetColor(color);
	for (of3dPrimitive* primitive : m_rigidBody->getPrimitives())
	{
		primitive->draw();
	}

	if (drawCollider)
	{
		ofSetColor(255, 0, 0);
		m_collider->draw();
	}

	if (drawSphere)
	{
		ofSetColor(0, 255, 0);
		m_encompassingSphere->draw();
	}
}

void GameObject::setPosition(Vector3D position)
{
	m_rigidBody->setPosition(position);
	m_collider->setPosition(position);
	m_encompassingSphere->setPosition(position);
}

RigidBody* GameObject::getRigidBody() { return m_rigidBody; }
Collider* GameObject::getCollider() { return m_collider; }
Sphere* GameObject::getSphere() { return m_encompassingSphere; }