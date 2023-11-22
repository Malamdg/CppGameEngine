#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// Tests
	cout << "Voulez vous effectuer les tests ? o/n  ";
	char response; 
	cin >> response;
	cout << endl << endl;

	if (response == 'o') Tests::ExecuteTests();

	//HUD
	gui.setup();
	gui.add(text1.setup("Mouvement camera", "ZQSD + AE | WASD + QE"));
	gui.add(text8.setup("Pause", "P"));
	gui.add(text2.setup("Change RigidBody", "C"));
	gui.add(text3.setup("Change Force", "V"));
	gui.add(text4.setup("Lauch RigidBody", "Space"));
	gui.add(text5.setup("Toggle Grid", "G"));
	gui.add(text9.setup("Toggle Impulse", "B"));
	gui.add(text6.setup("Toggle FullScreen", "F"));
	gui.add(text7.setup("Toggle Focus", "Clic gauche"));

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
	colors[4] = ofColor(0, 255, 0);
	colors[5] = ofColor(255, 0, 0);

	//SkyBox
	skyboxCenter = ofVec3f(0, 0, 0);
	skybox.load();

	//Camera
	cam.setPosition(0, 0, 10);
	cam.setFarClip(15000);

	//Rigid bodies
	rigidObjects = new RigidBody[5];

	list<pair<of3dPrimitive*, Vector3D>> tablePrimitives = list<pair<of3dPrimitive*, Vector3D>>
	{
		{new ofBoxPrimitive(16, .5, 8), Vector3D(0, 1, 0)},
		{new ofBoxPrimitive(.5, 7, .5), Vector3D(7.75, -2.5, 3.75)},
		{new ofBoxPrimitive(.5, 7, .5), Vector3D(-7.75, -2.5, 3.75)},
		{new ofBoxPrimitive(.5, 7, .5), Vector3D(7.75, -2.5, -3.75)},
		{new ofBoxPrimitive(.5, 7, .5), Vector3D(-7.75, -2.5, -3.75)}
	};
	RigidBody table = RigidBody(tablePrimitives, Vector3D(), Vector3D(), Quaternion::Identity(), Vector3D(), 1 / 6.f, 8.f);
	rigidObjects[0] = table;

	list <pair<of3dPrimitive*, Vector3D>> chairPrimitives = list<pair<of3dPrimitive*, Vector3D>>
	{
		{new ofBoxPrimitive(4, .5, 4), Vector3D(0, 0, 0)},
		{new ofBoxPrimitive(4, 5, .5), Vector3D(0, 2.5, -1.75)},
		{new ofBoxPrimitive(.5, 4, .5), Vector3D(1.75, -2, 1.75)},
		{new ofBoxPrimitive(.5, 4, .5), Vector3D(-1.75, -2, 1.75)},
		{new ofBoxPrimitive(.5, 4, .5), Vector3D(1.75, -2, -1.75)},
		{new ofBoxPrimitive(.5, 4, .5), Vector3D(-1.75, -2, -1.75)}
	};
	RigidBody chair = RigidBody(chairPrimitives, Vector3D(), Vector3D(), Quaternion::Identity(), Vector3D(), 1 / 2.5, 4.5f);
	rigidObjects[1] = chair;

	list <pair<of3dPrimitive*, Vector3D>> bottlePrimitives = list<pair<of3dPrimitive*, Vector3D>>
	{
		{new ofCylinderPrimitive(.5, 2, 16, 16), Vector3D(0, -.25, 0)},
		{new ofConePrimitive(.5, -1, 16, 16), Vector3D(0, 1.25, 0)},
		{new ofCylinderPrimitive(.2, 1.5, 16, 16), Vector3D(0, 1, 0)},
	};
	RigidBody bottle = RigidBody(bottlePrimitives, Vector3D(), Vector3D(), Quaternion::Identity(), Vector3D(), 1, 1.75f);
	rigidObjects[2] = bottle;

	list <pair<of3dPrimitive*, Vector3D>> carPrimitives = list<pair<of3dPrimitive*, Vector3D>>
	{
		{new ofBoxPrimitive(8, 15, 30), Vector3D(2, 0, 0)},
		{new ofBoxPrimitive(8, 15, 15), Vector3D(10, 0, 0)},
		{new ofCylinderPrimitive(5, 3, 16, 16), Vector3D(-1, 9, 8)},
		{new ofCylinderPrimitive(5, 3, 16, 16), Vector3D(-1, 9, -8)},
		{new ofCylinderPrimitive(5, 3, 16, 16), Vector3D(-1, -9, 8)},
		{new ofCylinderPrimitive(5, 3, 16, 16), Vector3D(-1, -9, -8)},
	};
	RigidBody car = RigidBody(carPrimitives, Vector3D(), Vector3D(), Quaternion::Identity(), Vector3D(), 1 / 1200.f, 10.5f);
	rigidObjects[3] = car;

	list <pair<of3dPrimitive*, Vector3D>> guitarPrimitives = list<pair<of3dPrimitive*, Vector3D>>
	{
		{new ofCylinderPrimitive(2.5, 1, 16, 16), Vector3D(0, 0, 3)},
		{new ofCylinderPrimitive(2, 1, 16, 16), Vector3D()},
		{new ofBoxPrimitive(1, .6, 5), Vector3D(0, 0, -4)},
		{new ofBoxPrimitive(1.5, 1, 2), Vector3D(0, 0, -7)},
	};
	RigidBody guitar = RigidBody(guitarPrimitives, Vector3D(), Vector3D(), Quaternion::Identity(), Vector3D(), .5, 4.f);
	rigidObjects[4] = guitar;


	//Setup Physics
	forceRegistry = new ForceRegistry();

	gravity = new Gravity(Vector3D(0, -9.8, 0));
	airFriction = new Friction(.1, .1);
	springZero = new Spring(new Vector3D(), 20, 32, .8);
	elasticZero = new Elastic(new Vector3D(), 60, 10, .8);
}

//--------------------------------------------------------------
void ofApp::update() {
	if (!pause)
	{
		fps = ofGetFrameRate();

		duration = fps == 0 ? 0 : 1 / fps;

		for (RigidBody* rb : rigidBodies)
		{
			forceRegistry->add(rb, gravity);
			forceRegistry->add(rb, airFriction);
		}

		Vector3D* attachPoint = new Vector3D(0, 0, 16);

		for (RigidBody* rb : rbWithSpring) forceRegistry->add(rb, springZero, attachPoint);
		for (RigidBody* rb : rbWithElastic) forceRegistry->add(rb, elasticZero, attachPoint);

		forceRegistry->updateForces(duration);

		for (RigidBody* rb : rigidBodies) rb->Update();
	}
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

	if (drawGrid) ofDrawGrid(10.0f, 10, true);

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
	for (pair<of3dPrimitive*, int> impulse : impulses)
	{
		ofSetColor(colors[impulse.second]);

		// display primitive
		impulse.first->draw();
	}
	ofEnableDepthTest();

	// end camera job
	cam.end();

	directionalLight.disable();
	
	ofDisableDepthTest();

	displayWindowTitle();

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key)
	{
		case ' ':
			keyHold += duration * 4;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key)
	{
		case 'f': //FullScreen
			fullscreen = !fullscreen;
			ofSetFullscreen(fullscreen);
			break;

		case 'c':
			objectIndex = (objectIndex + 1) % 6;
			break;

		case'v':
			forceMode = (forceMode + 1) % 3;
			break;

		case 'g':
			drawGrid = !drawGrid;
			break;

		case 'b':
			toggleImpulse = !toggleImpulse;
			break;

		case 'p':
			pause = !pause;
			break;

		case ' ': //Lauch RigidBody
			Vector3D position = cam.getPosition();
			Vector3D lauchDirection = cam.getLookAtDir();
			float impulse = getImpulse();

			RigidBody* rb;
			if (objectIndex < 5) rb = new RigidBody(rigidObjects[objectIndex]);
			else
			{
				list <pair<of3dPrimitive*, Vector3D>> weightedLadderPrimitives = list<pair<of3dPrimitive*, Vector3D>>
				{
					{new ofBoxPrimitive(1.5, 16, 1.5), Vector3D(2, 8, 0)},
					{new ofBoxPrimitive(1.5, 16, 1.5), Vector3D(-2, 8, 0)},
					{new ofBoxPrimitive(8, 1, 1), Vector3D(0, 4, 0)},
					{new ofBoxPrimitive(8, 1, 1), Vector3D(0, 8, 0)},
					{new ofBoxPrimitive(8, 1, 1), Vector3D(0, 12, 0)},
				};
				rb = new RigidBody(weightedLadderPrimitives, Vector3D(), Vector3D(), Quaternion::Identity(), Vector3D(), 1 / keyHold, 8.f);
			}
			rb->setPosition(position);

			Vector3D spawnImpulse = lauchDirection * impulse;

			Vector3D impulsePoint = Vector3D((float)rand() * 10.f / (float)RAND_MAX, (float)rand() * 10.f / (float)RAND_MAX, (float)rand() * 10.f / (float)RAND_MAX);

			if (toggleImpulse)
			{
				rb->addForce(spawnImpulse, impulsePoint);

				ofSpherePrimitive* impulsePrimitive = new ofSpherePrimitive(.25f, 16);
				rb->addPrimitive(impulsePrimitive, impulsePoint);
				impulses.push_back({ impulsePrimitive, magenta });
			}
			addToList(rb, forceMode);
		
			lastLaunched = rb;

			keyHold = 1;
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
	if (button == 0) cam.toggleControl();
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

void ofApp::addToList(RigidBody* rb, int mode)
{
	rigidBodies.push_back(rb);
	if (mode == 1) rbWithSpring.push_back(rb);
	if (mode == 2) rbWithElastic.push_back(rb);

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

void ofApp::displayWindowTitle()
{
	string objectType = "";
	string forceType = "";

	switch (objectIndex)
	{
	case 0:
		objectType = "Table";
		break;
	case 1:
		objectType = "Chair";
		break;
	case 2:
		objectType = "Bottle";
		break;
	case 3:
		objectType = "Car";
		break;
	case 4:
		objectType = "Guitar";
		break;
	case 5:
		objectType = "Ladder - controlable mass     |     Mass : " + to_string(keyHold);
		break;
	};

	switch (forceMode)
	{
	case 0:
		forceType = "None";
		break;
	case 1:
		forceType = "Spring";
		break;
	case 2:
		forceType = "Elastic";
		break;
	}

	std::stringstream strm;
	strm << " Objet : " << objectType << "     |     Initial Impulse : " << to_string(toggleImpulse) << "     |     Additional Force : " << forceType;
	strm << "     |     framerate : " << fps;
	ofSetWindowTitle(strm.str());
}

float ofApp::getImpulse()
{
	float impulse = 0;

	switch (objectIndex)
	{
	case 0:
		impulse = 30000;
		break;
	case 1:
		impulse = 10000;
		break;
	case 2:
		impulse = 2000;
		break;
	case 3:
		impulse = 3000000;
		break;
	case 4:
		impulse = 10000;
		break;
	case 5:
		impulse = 50000;
		break;
	};

	return impulse;
}