#include "RBCollisionHandler.h"

RBCollisionHandler::RBCollisionHandler()
{

}

RBCollisionHandler::~RBCollisionHandler()
{

}

void RBCollisionHandler::wideCollision(float duration, ForceRegistry* forceRegistry)
{
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
	}
}


void RBCollisionHandler::generateRegistry()
{
	// parcourir la box conis�r�e dans l'octree et collecter les RigidBody dedans
}



/*
DESCRIPTION DES ETAPES :
1 - G�n�ration de l'Octree
2 - Lancer l'Octree
Pour chaque box de l'octree, on cr�� un registry (generateRegistry) puis on y effectue :
	3 - D�tection de collisions (phase �largie)
	si collision
		4 - G�n�ration de collisions (phase restreinte) bo�te-plan
		si collision
			5 - R�solution des Collisions
Attention : il ne faut pas appliquer la collsion 2x
*/
void RBCollisionHandler::handleCollision(float duration, ForceRegistry* forceRegistry)
{
	// Create the Octree

	// Apply Octree

	// Loop for each box in the octree

	// 
}