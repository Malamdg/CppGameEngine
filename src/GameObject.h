#pragma once

#include <RigidBody.h>
#include <Box.h>
#include <Sphere.h>

class GameObject
{
private:
	RigidBody* m_rigidBody;
	Box* m_boxCollider;
	Sphere* m_encompassingSphere;

public:
	GameObject();

	GameObject(RigidBody* rigidBody, Box* boxCollider, Sphere* encompassingSphere);

	void update();

	void draw();
};