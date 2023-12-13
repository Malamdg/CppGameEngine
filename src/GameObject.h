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

	void draw();

	RigidBody* getRigidBody();
	Collider* getCollider();
	Sphere* getSphere();
};