#include "RBCollisionHandler.h"
#include 'Sphere.h'
#include 'Box.h'

RBCollisionHandler::RBCollisionHandler()
{
	// Create and instanciate the octree

}

RBCollisionHandler::~RBCollisionHandler()
{

}

void RBCollisionHandler::wideCollision(float duration, ForceRegistry* forceRegistry)
{
	// Attention: il ne faut pas appliquer la collision 2x (rb1xrb2 et rb2xrb1)
	for (RigidBody rb1 : m_registry)
	{
		//Sphere sph1 = Sphere(rb1, rb1.getPointWorldPosition(), rb1.getRadius());

		// A MODIFIER : BALAYER POUR AVOIR TOUT SAUF LE rb1
		for (RigidBody rb2 : m_registry)
		{
			// Sphere sph2 = Sphere(rb2, rb2.getPointWorldPosition(), rb2.getRadius());
			// list<Contact*> contacts = sph1.intersect(sph2)
			
			// test intesection of encompassing sphere
			// si contacts est vide...
			if (true)
			{
				narrowCollision(duration, forceRegistry, &rb1, &rb2);
			}
		}
	}
}

void RBCollisionHandler::narrowCollision(float duration, ForceRegistry* forceRegistry, RigidBody* rb1, RigidBody* rb2)
{
	// Box box1 = Box(rb1, rb1.getPointWorldPosition(), Vector3D* axe1, Vector3D* axe2, Vector3D* axe3);
	// Box box2 = Box(rb2, rb2.getPointWorldPosition(), Vector3D* axe1, Vector3D* axe2, Vector3D* axe3);
	
	// test intesection of bounding boxes
	if (true)
	{
		// Compute the vector between both rigid bodies
		Vector3D vectorBetweenParticles = (*rb1)->getPosition() - (*rb2)->getPosition();
		float firstMass = (1 / (*rb1)->getInverseMass());
		float secondMass = (1 / (*rb2)->getInverseMass());

		// Third Newton's law
		float firstDisplacement = secondMass / (firstMass + secondMass) * displacement;
		float secondDisplacement = -1 * firstMass / (firstMass + secondMass) * displacement;

		Vector3D firstDisplacementVector = vectorBetweenParticles * firstDisplacement;
		Vector3D secondDisplacementVector = vectorBetweenParticles * secondDisplacement;

		// This separate the two particles
		(*firstParticle)->addPosition(firstDisplacementVector);
		(*secondParticle)->addPosition(secondDisplacementVector);

		// No rest contact if there is no static particle

		// Impulsions
		float firstK = (relativeVelocity * vectorBetweenParticles * ((*rb2)->getCoefficientRestitution() + 1)) / ((*rb1)->getInverseMass() + (*rb2)->getInverseMass());
		float secondK = (relativeVelocity * vectorBetweenParticles * ((*rb1)->getCoefficientRestitution() + 1)) / ((*rb1)->getInverseMass() + (*rb2)->getInverseMass());
		Vector3D firstVelocityModifier = vectorBetweenParticles * (firstK * (*rb1)->getInverseMass());
		Vector3D secondVelocityModifier = vectorBetweenParticles * (secondK * (*rb2)->getInverseMass());
		(*rb1)->addVelocity(firstVelocityModifier * -1);
		(*rb2)->addVelocity(secondVelocityModifier);
		

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

	// Penser à supprimer les octrees à la fin
}