#pragma once

#include "ofMain.h"
#include "of3dPrimitives.h"
#include "Vector3D.h"
#include "Particle.h"
#include "Tests.h"
#include "Blob.h"
#include "Forces/ParticleGravity.h"
#include "Forces/ParticleForceRegistry.h"
#include "Collisions/CollisionHandler.h"
#include "iostream"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void updateForces();
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

	//HUD && Physics
	float fps;

	//Camera
	ofCamera cam;
	Vector3D cameraPosition;
	float viewWidth;

	//**Primitives**//
	std::list<std::pair<of3dPrimitive*, int*>> primitives;
	std::list<Particle*> particles;

	Vector3D m_gravity = Vector3D();
	ofBoxPrimitive floor;
	Blob blob;

	//Colors & Textures
	Vector3D* colors = new Vector3D[2];
	Vector3D visualizationColor = Vector3D(0, 255, 0);

	ParticleForceRegistry* forceRegistry;
	CollisionHandler* collisionHandler;

	ParticleGravity* gravity;

	// Texts to display
	string commandText;
};