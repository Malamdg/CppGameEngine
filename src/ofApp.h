#pragma once

#include "iostream"
#include "ofMain.h"
#include "cmath"
#include "ofxGui.h"

#include "Blob.h"
#include "Collisions/CollisionHandler.h"
#include "Collisions/BlobCollisionHandler.h"
#include "Forces/Deplacement.h"
#include "Forces/Spring.h"
#include "Forces/Elastic.h"
#include "Forces/Gravity.h"
#include "Forces/ForceRegistry.h"
#include "of3dPrimitives.h"
#include "DataStructures/Vector3D.h"
#include "DataStructures/Quaternion.h"
#include "Particle.h"
#include "GameObject.h"
#include "Tests/Tests.h"
#include "Octree.h"
#include "Collisions/RBCollisionHandler.h"

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
	void addToList(RigidBody* rb, int mode);
	void displayWindowTitle();
	float getImpulse();

	//HUD
	float fps;
	float duration;
	string commandText;
	string movingHud;
	Vector3D movingHudInitialPos;
	Vector3D movingHudPos;

	ofxPanel gui;
	ofxTextField text1;
	ofxTextField text2;
	ofxTextField text3;
	ofxTextField text4;
	ofxTextField text5;
	ofxTextField text6;
	ofxTextField text7;
	ofxTextField text8;
	ofxTextField text9;
	ofxTextField text10;
	ofxTextField text11;

	//Lights
	ofLight directionalLight;

	//Camera
	ofxFirstPersonCamera cam;
	Vector3D cameraPosition;
	float viewWidth;
	float viewHeight;

	//Primitives
	list<pair<of3dPrimitive*, int>> primitives;
	list<pair<of3dPrimitive*, int>> centersMass;
	list<pair<of3dPrimitive*, int>> impulses;

	//RigidBodies
	list<RigidBody*> rigidBodies;
	int objectIndex = 0;
	float keyHold = 1;

	RigidBody* rigidObjects;

	//Colors
	ofColor* colors;
	int black = 0;
	int white = 1;
	int grey = 2;
	int cyan = 3;
	int magenta = 4;
	int red = 5;

	//SkyBox
	ofxSkyBox skybox;
	ofVec3f skyboxCenter;

	//Fullscreen
	bool fullscreen = false;

	//Physics
	ForceRegistry* forceRegistry;

	Gravity* gravity;
	Friction* airFriction;
	Spring* springZero;
	Elastic* elasticZero;

	list<RigidBody*> rbWithSpring = list<RigidBody*>();
	list<RigidBody*> rbWithElastic = list<RigidBody*>();
	int forceMode = 0;

	// System boolean
	bool pause = false;
	bool drawGrid = true;
	bool toggleImpulse = true;
	bool drawOctree = false;

	// GameObjects
	list<GameObject*> gameObjects;
	bool drawCollider = false;

	Vector3D* boxCollidersDimensions;
	float* encompassingSpheresRadius;

	// Octree
	Octree octree;

	// Collision
	RBCollisionHandler collisionsHandler;
};