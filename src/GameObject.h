#pragma once

#include <RigidBody.h>
#include <Box.h>
#include <Sphere.h>

class GameObject
{
private:
	RigidBody* m_rigidBody;
	Collider* m_collider;
	Sphere* m_encompassingSphere;

public:
	GameObject();

	GameObject(RigidBody* rigidBody, Box* boxCollider, Sphere* encompassingSphere);

	~GameObject();

	void update();

	void draw(ofColor color);

	void setPosition(Vector3D position);

	RigidBody* getRigidBody();
	Collider* getCollider();
	Sphere* getSphere();
};