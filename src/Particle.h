#pragma once
#include "Vector.h"
#include "ofMain.h"

class Particle
{
private: 
	Vector position, initSpeed, speed, acceleration;
	float mass;
	of3dPrimitive shape;
	
public: 
	Particle::Particle(glm::vec3 position, glm::vec3 initSpeed, float mass);
	void Particle::draw();
	void Particle::incrementPosition();
};

