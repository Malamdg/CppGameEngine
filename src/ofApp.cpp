#include "ofApp.h"
#include "MathHelper.h"

//--------------------------------------------------------------
void ofApp::setup(){
	commandText = "Changer de mode de tir en appuyant sur 'a'/'q', 'z'/'w', 'e', 'r', et 't' !";

	primitives = std::list<std::pair<of3dPrimitive*, int*>>();
	preview = std::list<std::pair<ofSpherePrimitive*, int*>>();

	particleVisualization.setRadius(10);
	particleVisualization.setPosition(Vector3D().v3());
	const float floorWidth = ofGetScreenWidth() * 100;
	const float floorHeight = 5;
	floor = ofBoxPrimitive(floorWidth, floorHeight, 0);
	floor.setPosition(Vector3D(0, -10).v3());
	
	//Colors & Text
	ofDisableArbTex();
	ofLoadImage(textures[0], "T_fireBall.png");
	ofLoadImage(textures[1], "T_canonBall.png");

	colors[0] = Vector3D(0, 255, 0);
	colors[1] = Vector3D(255, 100, 100);
	colors[2] = Vector3D(0, 0, 255);
	colors[3] = Vector3D(125, 125, 125);
	colors[4] = Vector3D(255, 255, 255);

	primitives.push_back(std::pair<of3dPrimitive*, int*>(&particleVisualization, &mode));
	
	int* floorMode = new int(3);
	primitives.push_back(std::pair<of3dPrimitive*, int*>(&floor, floorMode));


	particleVisualization.setRadius(10);
	particleVisualization.setPosition(Vector3D().v3());

	// Center cam and set origin at the bottom left corner
	cam.setPosition(Vector3D(0, 0, 1500).v3());
	cam.move(Vector3D(ofGetWidth() * .5, ofGetHeight() * .5).v3());

	//Tests
	Tests::ExecuteTests();
}

//--------------------------------------------------------------
void ofApp::update(){

	//Update particles
	for (Particle* particle : particles)
	{
		particle->Update();
	}

	preview.clear();
	GeneratePrevisualization();
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(ofToString(commandText), 0, ofGetScreenHeight());

	for (std::pair<of3dPrimitive*, int*> primitive : primitives)
	{
		int r = colors[*(primitive.second)][0];
		int g = colors[*(primitive.second)][1];
		int b = colors[*(primitive.second)][2];
		ofSetColor(r, g, b);
		
		if (*primitive.second == 1) textures[0].bind();
		if (*primitive.second == 3) textures[1].bind();
		
		primitive.first->draw();
		
		if (*primitive.second == 1) textures[0].unbind();
		if (*primitive.second == 3) textures[0].unbind();
	}

	for (std::pair<ofSpherePrimitive*, int*> previewPair : preview)
	{
		int r = colors[*(previewPair.second)][0];
		int g = colors[*(previewPair.second)][1];
		int b = colors[*(previewPair.second)][2];
		ofSetColor(r, g, b);

		previewPair.first->draw();
	}
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
		case 'a':
		case 'q':
		{
			mode = 0;
			break;
		}
		case 'z': 
		case 'w': 
		{
			mode = 1;
			textureVisualization = textures[0];
			break;
		}
		case 'e': 
		{
			mode = 2;
			break;
		}
		case 'r': 
		{
			mode = 3;
			textureVisualization = textures[1];
			break;
		}
		case 't': 
		{
			mode = 4;
			break;
		}
		default: break;

		visualizationColor = colors[mode];
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	switch(button)
	{
		case 0 : 
		{
			float particleSpeed;
			Vector3D* particleColor;

			switch (mode)
			{
				case 0 :
				{
					particleSpeed = 50;
					break;
				}
				case 1 :
				{
					particleSpeed = 75;
					break;
				}
				case 2 :
				{
					particleSpeed = 100;
					break;
				}
				case 3 :
				{
					particleSpeed = 125;
					break;
				}
				case 4 : 
				{
					int r = rand() % 256;
					int g = rand() % 256;
					int b = rand() % 256;
					particleColor = new Vector3D(r, g, b);
					particleSpeed = (r * g * b) % 500;
					visualizationColor = *particleColor;

					break;
				}
				default: break;
			}

			Particle* p = new Particle(10, Vector3D(), GetLaunchDirection(x, y) * particleSpeed, 10, Vector3D(0, -gravity));
			int* tmpMode = new int(mode);
			primitives.push_back(std::pair<of3dPrimitive*, int*>(p, tmpMode));
			particles.push_back(p);
			break;
		}
		default: break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

	cam.setPosition(Vector3D(0, 0, 1500).v3());
	cam.move(Vector3D(ofGetWidth() * .5, ofGetHeight() * .5).v3());
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

Vector3D ofApp::GetLaunchDirection(float x, float y)
{
	Vector3D worldZeroOnScreen = Vector3D(cam.worldToScreen(glm::uvec3(0, 0, 0)));
	worldZeroOnScreen[2] = 0;

	Vector3D cursorPosition = Vector3D(x, y);

	Vector3D launchDirection = cursorPosition - worldZeroOnScreen;
	launchDirection[1] *= -1;
	launchDirection += m_initialPosition;
	launchDirection.Normalize();

	return launchDirection;
}

void ofApp::GeneratePrevisualization(Vector3D initialPosition)
{
	float particleSpeed;
	Vector3D* particleColor;
	Vector3D directionUnitVector = GetLaunchDirection(ofGetMouseX(), ofGetMouseY());

	switch (mode)
	{
		case 0:
		{
			particleSpeed = 50;
			particleColor = &colors[0];
			break;
		}
		case 1:
		{
			particleSpeed = 75;
			particleColor = &colors[1];
			break;
		}
		case 2:
		{
			particleSpeed = 100;
			particleColor = &colors[2];
			break;
		}
		case 3:
		{
			particleSpeed = 125;
			particleColor = &colors[3];
			break;
		}
		case 4:
		{
			Vector3D position;
			for (int i = 0; i < 3; i++) {
				position = directionUnitVector * 20 * (i + 1);
				ofSpherePrimitive* previewSphere = new ofSpherePrimitive();
				previewSphere->setRadius(5);
				previewSphere->setPosition(position.v3());
				preview.push_back(std::pair<ofSpherePrimitive*, int*>(previewSphere, &mode));
			}

			return;
		}
		default: break;
	}

	const Vector3D initialSpeed = directionUnitVector * particleSpeed;
	
	if (initialSpeed.y() <= 0) {
		return;
	}
	
	float g = gravity;

	// cartesian equation of y
	function <float(float)> y_x = [initialSpeed, initialPosition, g](float x) {
		return -g * x * x / (2 * initialSpeed.x() * initialSpeed.x()) + x * initialSpeed.y() / initialSpeed.x() + initialPosition.y();
		}
	;	

	float finalX = initialPosition.x() + 2 * initialSpeed.x() * initialSpeed.y() / gravity;
	float apexY = initialPosition.y() + initialSpeed.y() * initialSpeed.y() / (2 * gravity);

	int nbSphere = 10;

	float deltaX = finalX / nbSphere;

	float y;

	for (float x = initialPosition.x(); abs(x) <= abs(finalX); x += deltaX)
	{
		y = y_x(x);
		
		ofSpherePrimitive* previewSphere = new ofSpherePrimitive();
		previewSphere->setRadius(5);
		previewSphere->setPosition(Vector3D(x, y).v3());
		preview.push_back(std::pair<ofSpherePrimitive*, int*>(previewSphere, &mode));
	}
}