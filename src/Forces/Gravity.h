#include "ForceGenerator.h"

class Gravity : public ForceGenerator{
	
private:
	/* constant of gravity */
	Vector3D m_gravity;

public:
	/*
	class constructor

	@param gravity, the vector associated to gravity
	*/
	Gravity(Vector3D gravity);

	/*
	class destructor
	*/
	~Gravity();

	/*
	update the particle's gravity

	@param *particle, the particle to update
	@param duration, frame duration when the gravity applies
	*/
	virtual void updateForce(Particle* particle, float duration);

	/*
	update the RigidBody's gravity

	@param *rb, the RigidBody to update
	@param duration, frame duration when the gravity applies
	*/
	virtual void updateForce(RigidBody* rb, float duration);
};
