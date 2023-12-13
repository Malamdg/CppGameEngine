#include "RBCollisionHandler.h"

RBCollisionHandler::RBCollisionHandler()
{
	m_registry = Registry();
	m_collisionregistry = RegistryCollision();
	m_pairs = list<pair<GameObject*, GameObject*>>();
}

RBCollisionHandler::~RBCollisionHandler()
{

}

void RBCollisionHandler::broadPhase(float duration, ForceRegistry* forceRegistry)
{

	for (auto i = m_registry.begin(); i != m_registry.end(); i++)
	{
		GameObject* go1 = *i;
		Sphere* sph1 = go1->getSphere();

		for (auto j = i; j != m_registry.end(); j++)
		{
			if (j == i) continue;

			GameObject* go2 = *j;

			pair<GameObject*, GameObject*> m_pair1 = pair<GameObject*, GameObject*>(go1, go2);
			pair<GameObject*, GameObject*> m_pair2 = pair<GameObject*, GameObject*>(go2, go1);

			auto f1 = find(m_pairs.begin(), m_pairs.end(), m_pair1);
			auto f2 = find(m_pairs.begin(), m_pairs.end(), m_pair2);

			if (!(f1 == m_pairs.end() && f2 == m_pairs.end())) continue;

			m_pairs.push_back(m_pair1);

			Sphere* sph2 = go2->getSphere();
			list<Contact*> contacts = sph1->intersect(sph2);

			// test intesection of encompassing sphere
			if (!contacts.empty())
			{
				narrowPhase(duration, forceRegistry, go1, go2);
			}
		}
	}
}

void RBCollisionHandler::narrowPhase(float duration, ForceRegistry* forceRegistry, GameObject* go1, GameObject* go2)
{
	Collider* collider1 = go1->getCollider();
	Collider* collider2 = go2->getCollider();
	list<Contact*> contacts = collider1->intersect(collider2);

	// test intesection of bounding boxes
	for (Contact* contact : contacts)
	{
		addcollision(contact);
	}
}


void RBCollisionHandler::addcollision(Contact* contact)
{
	CollisionRegistration collisionRegistration;
	collisionRegistration.contact = contact;
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
			Vider le registre
*/
void RBCollisionHandler::handleCollision(float duration, ForceRegistry* forceRegistry, Octree* tree)
{
	m_pairs.clear();

	// Apply Octree
	list<OctreeNode*> leaves = tree->getLeaves();
	for (OctreeNode* leave : leaves)
	{
		m_registry = leave->gameObjects;

		broadPhase(duration, forceRegistry);
	}

	computeCollision(duration, forceRegistry);
}

void RBCollisionHandler::computeCollision(float duration, ForceRegistry* forceRegistry)
{
	for (CollisionRegistration collision : m_collisionregistry)
	{
		Contact* contact = collision.contact;

		RigidBody* rb1 = contact->getBody(0);
		RigidBody* rb2 = contact->getBody(1);

		Vector3D normal = *contact->getNormal();
		Vector3D point = *contact->getContactPoint();
		float penetration = contact->getPenetration();
		float restitution = contact->getRestitution();
		float friction = contact->getFriction();

		//Compute the 2 normals
		Vector3D n1 = normal.Normalized();
		Vector3D n2 = normal.Normalized();

		Vector3D direction = point - rb1->getPosition();
		if (direction * normal > 0) n1 = n1 * -1;
		else n2 = n2 * -1;

		float accelerationProj1 = rb1->getAcceleration() * normal;
		float accelerationProj2 = rb2->getAcceleration() * normal;

		float velocityProj1 = rb1->getVelocity() * normal;
		float velocityProj2 = rb2->getVelocity() * normal;

		if (rb1->getInverseMass() == 0 && rb2->getInverseMass() == 0) continue;
		else if (rb1->getInverseMass() == 0) rb2->addPosition(n2 * penetration);
		else if (rb2->getInverseMass() == 0) rb1->addPosition(n1 * penetration);
		else
		{
			float mass1 = 1 / rb1->getInverseMass();
			float mass2 = 1 / rb2->getInverseMass();

			float firstDisplacement = mass2 / (mass1 + mass2) * penetration;
			float secondDisplacement = mass1 / (mass1 + mass2) * penetration;

			Vector3D firstDisplacementVector = n1 * firstDisplacement;
			Vector3D secondDisplacementVector = n2 * secondDisplacement;

			rb1->addPosition(firstDisplacementVector);
			rb2->addPosition(secondDisplacementVector);
		}

		Vector3D relativeVelocity = rb1->getVelocity() - rb2->getVelocity();

		//compute of impulse's amplitude
		float amp = relativeVelocity.Norm()* restitution * 100;

		//Friction
		Friction* f = new Friction(friction, friction);

		Vector3D imp1 = n1 * amp;
		Vector3D imp2 = n2 * amp;

		//Adding impulsion if not a resting contact
		if (!(abs(accelerationProj1 * duration) > abs(velocityProj1))) rb1->addForce(imp1, point);
		else forceRegistry->add(rb1, f);

		if (!(abs(accelerationProj2 * duration) > abs(velocityProj2))) rb2->addForce(imp2, point);
		else forceRegistry->add(rb2, f);
	}

	m_collisionregistry.clear();
}
