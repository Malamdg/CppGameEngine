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
#include "DataStructures/Vector3D.h"
#include "DataStructures/Quaternion.h"
#include "Particle.h"
#include "Tests.h"

#include "Addons/ofSkyBox/ofxSkyBox.h"
#include "Addons/ofFirstPersonCamera/ofxFirstPersonCamera.h"

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

	//HUD
	float fps;
	string commandText;
	string movingHud;
	Vector3D movingHudInitialPos;
	Vector3D movingHudPos;

	//Lights
	ofLight directionalLight;

	//Camera
	ofxFirstPersonCamera cam;
	Vector3D cameraPosition;
	float viewWidth;
	float viewHeight;

	//Primitives
	list<std::pair<of3dPrimitive*, int>> primitives;

	//Colors
	ofColor* colors;
	int noir = 0;
	int blanc = 1;
	int gris = 2;
	int cyan = 3;
	int magenta = 4;

	//SkyBox
	ofxSkyBox skybox;
	ofVec3f skyboxCenter;

	//Fullscreen
	bool fullscreen = false;

};