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
	primitives = std::list<std::pair<of3dPrimitive*, int>>(); // display primitive on each draw()

	//Colors
	colors = new ofColor[10];

	colors[0] = ofColor(0, 0, 0);
	colors[1] = ofColor(255, 255, 255);
	colors[2] = ofColor(100, 100, 100);
	colors[3] = ofColor(10, 200, 250);
	colors[4] = ofColor(250, 10, 200);

	ofSpherePrimitive* laSpherePourTester = new ofSpherePrimitive();
	laSpherePourTester->setRadius(6);
	laSpherePourTester->setPosition(0, 0, -10);
	primitives.push_back(std::pair<of3dPrimitive*, int>(laSpherePourTester, magenta));

	//SkyBox
	skyboxCenter = ofVec3f(0, 0, 0);
	skybox.load();

	//Camera
	//cam = ofxFirstPersonCamera();
	//cam.enableControl();
	//cam.movespeed = .001;
	cam.setPosition(0, 0, 0);
	cam.setFarClip(15000);

}

//--------------------------------------------------------------
void ofApp::update() {
	fps = ofGetFrameRate();

	float duration = fps == 0 ? 0 : 1/fps;

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofEnableDepthTest();

	directionalLight.enable();

	// begin camera job
	cam.begin();

	// draw Skybox
	skybox.draw();

	ofDrawGrid(10.0f, 10, true);

	// display texts on screen
	drawText();
	
	// display primitives with correct color
	for (std::pair<of3dPrimitive*, int> primitive : primitives)
	{
		ofSetColor(colors[primitive.second]);

		// display primitive
		primitive.first->draw();

	}

	// end camera job
	cam.end();

	directionalLight.disable();
	
	ofDisableDepthTest();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key)
	{
	case 'f': //FullScreen
	{
		fullscreen = !fullscreen;
		ofSetFullscreen(fullscreen);
	}
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