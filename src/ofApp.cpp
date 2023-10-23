#include "ofApp.h"
#include "Collisions/CollisionHandler.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Set command text
	commandText = "Changer de mode de tir en appuyant sur 'a'/'q', 'z'/'w', 'e', 'r', et 't' !\nTirer avec 'mouse left' !";

	// Setup lists
	primitives = std::list<std::pair<of3dPrimitive*, int*>>(); // display primitive on each draw()
	preview = std::list<std::pair<ofSpherePrimitive*, int*>>(); // particles to update position on each update()

	// Setup cam and basic primitives
	particleVisualization.setRadius(10);
	particleVisualization.setPosition(Vector3D().v3());
	const float floorWidth = ofGetScreenWidth() * 100;
	const float floorHeight = 5;
	floor = ofBoxPrimitive(floorWidth, floorHeight, 0);
	floor.setPosition(Vector3D(0, -10).v3());
	
	// Colors & Text
	ofDisableArbTex();
	ofLoadImage(textures[0], "T_fireBall.png");
	ofLoadImage(textures[1], "T_canonBall.png");

	// Setup colors
	colors[0] = Vector3D(0, 255, 0);
	colors[1] = Vector3D(255, 100, 100);
	colors[2] = Vector3D(0, 0, 255);
	colors[3] = Vector3D(125, 125, 125);
	colors[4] = Vector3D(255, 255, 255);

	// add previsualization sphere to primitive list
	primitives.push_back(std::pair<of3dPrimitive*, int*>(&particleVisualization, &mode));
	
	// add floor to primitive list
	int* floorMode = new int(3);
	primitives.push_back(std::pair<of3dPrimitive*, int*>(&floor, floorMode));

	// Center cam and set origin at the bottom left corner
	cam.setPosition(Vector3D(0, 0, 1500).v3());
	cam.move(Vector3D(ofGetWidth() * .5, ofGetHeight() * .5).v3());

	// Tests
	Tests::ExecuteTests();
}

//--------------------------------------------------------------
void ofApp::update(){
	
	//Update particles
	for (Particle* particle : particles)
	{
		particle->Update();
		handleCollision(particles);
	}

	// clear screen for following draw()
	preview.clear();
	// generate shoot previsualization
	GeneratePrevisualization();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// begin camera job
	cam.begin();

	// display command text
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(ofToString(commandText), 0, ofGetScreenHeight());
	
	// display primitives with correct color
	for (std::pair<of3dPrimitive*, int*> primitive : primitives)
	{
		int r = colors[*(primitive.second)][0];
		int g = colors[*(primitive.second)][1];
		int b = colors[*(primitive.second)][2];
		ofSetColor(r, g, b);
		
		// if mode has bound texture set it
		if (*primitive.second == 1) textures[0].bind();
		if (*primitive.second == 3) textures[1].bind();
		
		// display primitive
		primitive.first->draw();
		
		// if mode had bound texture unset it
		if (*primitive.second == 1) textures[0].unbind();
		if (*primitive.second == 3) textures[1].unbind();
	}

	// display preview spheres with correct color
	for (std::pair<ofSpherePrimitive*, int*> previewPair : preview)
	{
		int r = colors[*(previewPair.second)][0];
		int g = colors[*(previewPair.second)][1];
		int b = colors[*(previewPair.second)][2];
		ofSetColor(r, g, b);

		previewPair.first->draw();
	}

	// end camera job
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// switch shooting mode given on key press
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
		// left click to launch particle
		case 0 : 
		{
			// define speed and color according to shooting mode
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
					// random speed initiated from base color - old method because no more random color but get great random speed
					int r = rand() % 256;
					int g = rand() % 256;
					int b = rand() % 256;
					particleSpeed = (r * g * b) % 500;
					break;
				}
				default: break;
			}
      
			// store particle in particles and primitives lists
			Particle* p = new Particle(10, Vector3D(), GetLaunchDirection(x, y) * particleSpeed, 10);
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
	// keep coherent display when resizing viewport
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
	// get world's (0,0,0) in screen's coordinates
	Vector3D worldZeroOnScreen = Vector3D(cam.worldToScreen(glm::uvec3(0, 0, 0)));
	worldZeroOnScreen[2] = 0; // set z at 0 => plane movement

	// position of mouse on screen
	Vector3D cursorPosition = Vector3D(x, y);

	// create a vector between 
	Vector3D launchDirection = cursorPosition - worldZeroOnScreen;
	// invert y because camera do so on display and everything is calculated this way
	launchDirection[1] *= -1;
	// offset launch direction to be exact when launching particle
	launchDirection += m_initialPosition;
	launchDirection.Normalize();

	// return normalized vector to facilitate calculs
	return launchDirection;
}

void ofApp::GeneratePrevisualization(Vector3D initialPosition)
{
	float particleSpeed;
	Vector3D directionUnitVector = GetLaunchDirection(ofGetMouseX(), ofGetMouseY());

	// get speed from mode and differentiate treatment for random speed particle
	switch (mode)
	{
		case 0:
		{
			particleSpeed = 50;
			break;
		}
		case 1:
		{
			particleSpeed = 75;
			break;
		}
		case 2:
		{
			particleSpeed = 100;
			break;
		}
		case 3:
		{
			particleSpeed = 125;
			break;
		}
		case 4:
		{
			// store postion in a variable Vector3D
			Vector3D position;
			// Place 3 spheres every 20 pixels from previsualizationSphere in shot direction
			for (int i = 0; i < 3; i++) {
				// update position on each iteration
				position = directionUnitVector * 20 * (i + 1);
				// create a new sphere to push at the end of preview list
				ofSpherePrimitive* previewSphere = new ofSpherePrimitive(); 
				previewSphere->setRadius(5); // half of a particule to distinguish between each
				previewSphere->setPosition(position.v3());// set position calculated one
				// push particle preview list paired with shooting mode to display correct color
				preview.push_back(std::pair<ofSpherePrimitive*, int*>(previewSphere, &mode));
			}
			// no further treatment because speed is unknown
			return;
		}
		default: break;
	}

	// get initial speed of particle from shooting mode
	const Vector3D initialSpeed = directionUnitVector * particleSpeed;
	
	// no previsualization if shot on or under the floor
	if (initialSpeed.y() <= 0) {
		return;
	}
	
	// to get it into capture clause of lambda fumction
	float g = gravity;

	// cartesian equation of y
	function <float(float)> y_x = [initialSpeed, initialPosition, g](float x) {
		return -g * x * x / (2 * initialSpeed.x() * initialSpeed.x()) + x * initialSpeed.y() / initialSpeed.x() + initialPosition.y();
		}
	;	

	// number of spheres
	int nbSphere = 3;
	
	// troublesome case
	if (initialSpeed.x() == 0) {
		Vector3D position;
		for (int i = 0; i < nbSphere; i++) {
			// update position on each iteration
			position = directionUnitVector * 10 * (i + 1);
			// create a new sphere to push at the end of preview list
			ofSpherePrimitive* previewSphere = new ofSpherePrimitive();
			previewSphere->setRadius(5); // half of a particule to distinguish between each
			previewSphere->setPosition(position.v3());// set position calculated one
			// push particle preview list paired with shooting mode to display correct color
			preview.push_back(std::pair<ofSpherePrimitive*, int*>(previewSphere, &mode));
		}
		return;
	}

	// step between balls
	int direction = initialSpeed.x() < 0 ? -1 :  1;
	float deltaX = direction * 10;

	// finalX to get a stop point 
	float finalX = initialPosition.x() + nbSphere * deltaX;
	
	// variable to store the value of y in
	float y;
	
	///////////////////////////////////
	/// Build previsualization list ///
	///////////////////////////////////
	
	// iterate on x for easiness 
	for (float x = initialPosition.x(); abs(x) <= abs(finalX); x += deltaX)
	{
		// calculate current x corresponding y
		y = y_x(x - initialPosition.x());
		
		// use sphere primitives because it is lighter
		ofSpherePrimitive* previewSphere = new ofSpherePrimitive();
		previewSphere->setRadius(5); // half of a particule to distinguish between each
		previewSphere->setPosition(Vector3D(x, y).v3()); // set position to (x, y(x), 0)		
		// push particle preview list paired with shooting mode to display correct color
		preview.push_back(std::pair<ofSpherePrimitive*, int*>(previewSphere, &mode)); 
	}
}