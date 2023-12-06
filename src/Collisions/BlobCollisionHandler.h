#pragma once
#include "Collision.h"
#include "../Forces/ForceRegistry.h"
#include "../Forces/Friction.cpp"
#include "../Particle.h"
#include "../Blob.h"

class Collision;

class BlobCollisionHandler : public CollisionHandler
{
public:
	/*
	Constructor
	*/
	BlobCollisionHandler(Blob* blob);

	/*
	Destructor
	*/
	~BlobCollisionHandler();

	/*
 	To manage the collision of blob with particles

   	@param particles, the particles consider
	@param duration, frame duration
 	*/
	void handleCollision(std::list<Particle*> particles, ForceRegistry* forceRegistry, CollisionHandler* collisionHandler);

private:
	Blob* m_blob;
};
