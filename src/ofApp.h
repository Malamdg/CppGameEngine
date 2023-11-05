#pragma once

#include "Blob.h"
#include "cmath"
#include "Collisions/CollisionHandler.h"
#include "Collisions/BlobCollisionHandler.h"
#include "Forces/ParticleDeplacement.h"
#include "Forces/ParticleGravity.h"
#include "Forces/ParticleForceRegistry.h"
#include "iostream"
#include "ofMain.h"
#include "of3dPrimitives.h"
#include "Particle.h"
#include "Tests.h"
#include "Vector3D.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
private:
	void drawText();
	void updateForces();
	/*
	* generate floor accordingly to layout
	*/
	void generateFloor(std::list<std::pair<int*, Vector3D*>> layout);
	/*
	* get layout of floor
	*/
	std::list<std::pair<int*, Vector3D*>> getLayout();
	
	//HUD
	float fps;
	string commandText;
	string movingHud;
	Vector3D movingHudInitialPos;
	Vector3D movingHudPos;

	//Camera
	ofCamera cam;
	Vector3D cameraPosition;
	float viewWidth;
	float viewHeight;

	//**Primitives**//
	std::list<std::pair<of3dPrimitive*, int*>> primitives;
	std::list<Particle*> particles;

	ofBoxPrimitive floor;
	Blob blob;

	//Colors & Textures
	Vector3D* colors = new Vector3D[3];

	// Physics
	ParticleForceRegistry* forceRegistry;
	CollisionHandler* collisionHandler;
	BlobCollisionHandler* blobCollisionHandler;

	ParticleGravity* gravity;

	Particle* p;
	Particle* p1;
	Particle* p2;
	Particle* p3;

	Cable* cable;
	Spindle* spindle;
};