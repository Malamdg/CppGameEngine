#include "RBCollisionHandler.h"

RBCollisionHandler::RBCollisionHandler()
{

}

RBCollisionHandler::~RBCollisionHandler()
{

}

void RBCollisionHandler::wideCollision(float duration, ForceRegistry* forceRegistry)
{
	// Attention: il ne faut pas appliquer la collision 2x (rb1xrb2 et rb2xrb1)
	for (RigidBody rb1 : m_registry)
	{
		// A MODIFIER : BALAYER POUR AVOIR TOUT SAUF LE rb1
		for (RigidBody rb2 : m_registry)
		{
			// test intesection of encompassing sphere
			if (true)
			{
				narrowCollision(duration, forceRegistry, &rb1, &rb2);
			}
		}
	}
}

void RBCollisionHandler::narrowCollision(float duration, ForceRegistry* forceRegistry, RigidBody* rb1, RigidBody* rb2)
{
	// test intesection of bounding boxes
	if (true)
	{
		// Impulsions

		// Ajouter les deux particules dans m_collisionregistry
		addcollision(rb1, rb2);
	}
}


void RBCollisionHandler::generateRegistry()
{
	// parcourir la box conisérée dans l'octree et collecter les RigidBody dedans
}


void RBCollisionHandler::addcollision(RigidBody* rb1, RigidBody* rb2)
{
	CollisionRegistration collisionRegistration;
	collisionRegistration.rb1 = rb1;
	collisionRegistration.rb2 = rb2;
	m_collisionregistry.push_back(collisionRegistration);
}


/*
DESCRIPTION DES ETAPES :
1 - Génération de l'Octree
2 - Lancer l'Octree
Pour chaque box de l'octree, on créé un registry (generateRegistry) puis on y effectue :
	3 - Détection de collisions (phase élargie)
	si collision
		4 - Génération de collisions (phase restreinte) boîte-plan
		si collision
			5 - Résolution des Collisions
*/
void RBCollisionHandler::handleCollision(float duration, ForceRegistry* forceRegistry)
{
	// Create the Octree

	// Apply Octree

	// Loop for each box in the octree

	// 
}