#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// Tests
	cout << "Voulez vous effectuer les tests ? o/n  ";
	char response; 
	cin >> response;
	cout << endl << endl;

	if (response == 'o') Tests::ExecuteTests();

	// Light
	directionalLight.setDirectional();
	directionalLight.setSpecularColor(ofColor(255));
	directionalLight.setDiffuseColor(ofColor(255));
	directionalLight.setAmbientColor(ofColor(100));
	directionalLight.rotateDeg(45, glm::vec3(1, 1, 1));

	// Set command text
	commandText = "";

	// Setup lists
	primitives = list<pair<of3dPrimitive*, int>>(); // display primitive on each draw()
	centersMass = list<pair<of3dPrimitive*, int>>();
	rigidBodies = list<RigidBody*>();

	//Colors
	colors = new ofColor[10];

	colors[0] = ofColor(0, 0, 0);
	colors[1] = ofColor(255, 255, 255);
	colors[2] = ofColor(100, 100, 100);
	colors[3] = ofColor(10, 200, 250);
	colors[4] = ofColor(250, 10, 200);
	colors[5] = ofColor(255, 0, 0);

	//SkyBox
	skyboxCenter = ofVec3f(0, 0, 0);
	skybox.load();

	//Camera
	cam.setPosition(0, 0, 10);
	cam.setFarClip(15000);

	//Rigid bodies
	table = list<pair<of3dPrimitive*, Vector3D>>
	{
		{new ofBoxPrimitive(16, .5, 8), Vector3D(0, 1, 0)},
		{new ofBoxPrimitive(.5, 7, .5), Vector3D(7.75, -2.5, 3.75)},
		{new ofBoxPrimitive(.5, 7, .5), Vector3D(-7.75, -2.5, 3.75)},
		{new ofBoxPrimitive(.5, 7, .5), Vector3D(7.75, -2.5, -3.75)},
		{new ofBoxPrimitive(.5, 7, .5), Vector3D(-7.75, -2.5, -3.75)}
	};
	RigidBody* rbTable = new RigidBody(table);
	//addToList(rbTable);

	chair = list<pair<of3dPrimitive*, Vector3D>>
	{
		{new ofBoxPrimitive(4, .5, 4), Vector3D(0, 0, 0)},
		{new ofBoxPrimitive(4, 5, .5), Vector3D(0, 2.5, -1.75)},
		{new ofBoxPrimitive(.5, 4, .5), Vector3D(1.75, -2, 1.75)},
		{new ofBoxPrimitive(.5, 4, .5), Vector3D(-1.75, -2, 1.75)},
		{new ofBoxPrimitive(.5, 4, .5), Vector3D(1.75, -2, -1.75)},
		{new ofBoxPrimitive(.5, 4, .5), Vector3D(-1.75, -2, -1.75)}
	};
	RigidBody* rbChair = new RigidBody(chair);
	//addToList(rbChair);

	bottle = list<pair<of3dPrimitive*, Vector3D>>
	{
		{new ofCylinderPrimitive(.5, 2, 16, 16), Vector3D(0, -.25, 0)},
		{new ofConePrimitive(.5, -1, 16, 16), Vector3D(0, 1.25, 0)},
		{new ofCylinderPrimitive(.2, 1.5, 16, 16), Vector3D(0, 1, 0)},
	};
	RigidBody* rbBottle = new RigidBody(bottle);
	//addToList(rbBottle);

	car = list<pair<of3dPrimitive*, Vector3D>>
	{
		{new ofBoxPrimitive(8, 15, 30), Vector3D(2, 0, 0)},
		{new ofBoxPrimitive(8, 15, 15), Vector3D(10, 0, 0)},
		{new ofCylinderPrimitive(5, 3, 16, 16), Vector3D(-1, 9, 8)},
		{new ofCylinderPrimitive(5, 3, 16, 16), Vector3D(-1, 9, -8)},
		{new ofCylinderPrimitive(5, 3, 16, 16), Vector3D(-1, -9, 8)},
		{new ofCylinderPrimitive(5, 3, 16, 16), Vector3D(-1, -9, -8)},
	};
	RigidBody* rbCar = new RigidBody(car);
	//addToList(rbCar);

	guitar = list<pair<of3dPrimitive*, Vector3D>>
	{
		{new ofCylinderPrimitive(2.5, 1, 16, 16), Vector3D(0, 0, 3)},
		{new ofCylinderPrimitive(2, 1, 16, 16), Vector3D()},
		{new ofBoxPrimitive(1, .6, 5), Vector3D(0, 0, -4)},
		{new ofBoxPrimitive(1.5, 1, 2), Vector3D(0, 0, -7)},
	};
	RigidBody* rbGuitar = new RigidBody(guitar);
	//addToList(rbGuitar);

	//Setup Physics
	forceRegistry = new ForceRegistry();

	gravity = new Gravity(Vector3D(0, -9.8, 0));
	airFriction = new Friction(.1, .1);
	springZero = new Spring(new Vector3D(), 20, 3, .8);
	elasticZero = new Elastic(new Vector3D(), 40, 3, .8);
}

//--------------------------------------------------------------
void ofApp::update() {
	fps = ofGetFrameRate();

	duration = fps == 0 ? 0 : 1/fps;

	for (RigidBody* rb : rigidBodies)
	{
		forceRegistry->add(rb, gravity);
		forceRegistry->add(rb, airFriction);
		forceRegistry->add(rb, springZero);
		//forceRegistry->add(rb, elasticZero);

	}
	forceRegistry->updateForces(duration);

	for (RigidBody* rb : rigidBodies) rb->Update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofEnableDepthTest();

	directionalLight.enable();

	// begin camera job
	cam.begin();

	// draw Skybox
	skybox.draw();
	ofEnableDepthTest();

	ofDrawGrid(10.0f, 10, true);

	// display texts on screen
	//drawText();

	// display primitives with correct color
	for (pair<of3dPrimitive*, int> primitive : primitives)
	{
		ofSetColor(colors[primitive.second]);

		// display primitive
		primitive.first->draw();
	}

	// display centers of mass above the primitives
	ofDisableDepthTest();
	for (pair<of3dPrimitive*, int> centerMass : centersMass)
	{
		ofSetColor(colors[centerMass.second]);

		// display primitive
		centerMass.first->draw();
	}
	ofEnableDepthTest();

	// end camera job
	cam.end();

	directionalLight.disable();
	
	ofDisableDepthTest();

	std::stringstream strm;
	strm << "framerate : " << fps << "    |    Masse : " << rbMasse;
	ofSetWindowTitle(strm.str());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key)
	{
	case ' ':
	{
		rbMasse += duration*4;
	}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key)
	{
	case 'f': //FullScreen
	{
		fullscreen = !fullscreen;
		ofSetFullscreen(fullscreen);
		break;
	}
	case ' ': //Lauch RigidBody
		Vector3D position = cam.getPosition();
		Vector3D lauchDirection = cam.getLookAtDir();
		Vector3D rotation = Vector3D(0, PI, 0);
		float velocity = 50;

		list<pair<of3dPrimitive*, Vector3D>> rbPrimitives = list<pair<of3dPrimitive*, Vector3D>> 
		{ 
			{new ofBoxPrimitive(2, 2, 2), Vector3D(1, 1, 1)},
			{new ofCylinderPrimitive(2, 2, 8, 8), Vector3D(-1, 0, -1)}
		};
		

		RigidBody* rb = new RigidBody(rbPrimitives,
			position, lauchDirection * velocity,
			Quaternion::Identity(), rotation,
			1/rbMasse, .1f);
		
		rigidBodies.push_back(rb);

		addToList(rb);
		
		rbMasse = 0;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	cam.toggleControl();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

//--------------------------------------------------------------
void ofApp::drawText() {
	// Command Text
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(ofToString(commandText), -viewWidth / 2, viewHeight / 2);

	// Informative HUD 
	movingHud = "Framerate : " + to_string(fps);
	float camX, camY;
	camX = Vector3D(cam.getPosition()).x();
	camY = Vector3D(cam.getPosition()).y();
	ofSetColor(	255, 125, 125);
	ofDrawBitmapString(ofToString(movingHud), -viewWidth / 2 - 50 + camX, viewHeight / 2 + 50 + camY);
}

void ofApp::addToList(RigidBody* rb)
{
	rigidBodies.push_back(rb);

	bool first = true;
	for (of3dPrimitive* primitive : rb->getPrimitives())
	{
		if (first)
		{
			centersMass.push_back(pair<of3dPrimitive*, int>(primitive, red));
			first = false;
		}
		else primitives.push_back(pair<of3dPrimitive*, int>(primitive, cyan));
	}
}