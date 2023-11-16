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
	laSpherePourTester->setRadius(10);
	laSpherePourTester->setPosition(0, 0, -100);
	primitives.push_back(std::pair<of3dPrimitive*, int>(laSpherePourTester, magenta));
	
	// Setup cam variables
	cameraPosition = Vector3D(0, 0, 500);
	// Pythagoras to get displayed width with fov and z of camera 	
	float fovRad = cam.getFov() * PI / 180;
	viewWidth = tan(fovRad / 2) * 2 * cameraPosition.z();
	viewHeight = viewWidth / cam.getAspectRatio();

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

	// move on arrow key press
	switch (key)
	{
	case 57358: // stride right
	{
		break;
	}
	case 57356: // stride left
	{
		break;
	}
	case 57357: // jump
	{
		return;
	}
	default:
		return;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

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