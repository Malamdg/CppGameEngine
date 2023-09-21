#include "ofApp.h"
#include "MathHelper.h"

//--------------------------------------------------------------
void ofApp::setup(){

	primitives = std::list<std::pair<of3dPrimitive*, Vector3D*>>();
	particles = std::list<Particle*>();
	preview = std::list<std::pair<ofSpherePrimitive*, Vector3D*>>();

	particleVisualization.setRadius(10);
	particleVisualization.setPosition(Vector3D().v3());
	const float floorWidth = ofGetScreenWidth() * 100;
	const float floorHeight = 5;
	floor = ofBoxPrimitive(floorWidth, floorHeight, 0);
	floor.setPosition(Vector3D(0, -10).v3());

	//Colors
	colors[0] = Vector3D(0, 255, 0);
	colors[1] = Vector3D(255, 0, 0);
	colors[2] = Vector3D(0, 0, 255);
	colors[3] = Vector3D(125, 125, 125);

	primitives.push_back(std::pair<of3dPrimitive*, Vector3D*>(&particleVisualization, &visualizationColor));
	primitives.push_back(std::pair<of3dPrimitive*, Vector3D*>(&floor, new Vector3D(120, 120, 120)));

	particleVisualization.setRadius(10);
	particleVisualization.setPosition(Vector3D().v3());

	// Center cam and set origin at the bottom left corner
	cam.setPosition(Vector3D(0, 0, 1500).v3());
	cam.move(Vector3D(ofGetWidth() * .5, ofGetHeight() * .5).v3());

	std::cout << "Change de mode de tir en appuyant sur 'a'/'q', 'z'/'w', 'e', 'r', et 't' !" << std::endl;

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

	for (std::pair<of3dPrimitive*, Vector3D*> primitive : primitives)
	{
		int r = primitive.second->x();
		int g = primitive.second->y();
		int b = primitive.second->z();
		ofSetColor(r, g, b);
		primitive.first->draw();
	}
	for (std::pair<ofSpherePrimitive*, Vector3D*> previewPair : preview)
	{
		int r = previewPair.second->x();
		int g = previewPair.second->y();
		int b = previewPair.second->z();
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
			visualizationColor = Vector3D(0, 255, 0);
			break;
		}
		case 'z': 
		case 'w': 
		{
			mode = 1;
			visualizationColor = Vector3D(255, 0, 0);
			break;
		}
		case 'e': 
		{
			mode = 2;
			visualizationColor = Vector3D(0, 0, 255);
			break;
		}
		case 'r': 
		{
			mode = 3;
			visualizationColor = Vector3D(125, 125, 125);
			break;
		}
		case 't': 
		{
			mode = 4; 
			visualizationColor = Vector3D(255, 255, 255);
			break;
		}
		default: break;
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
					particleColor = &colors[0];
					break;
				}
				case 1 :
				{
					particleSpeed = 75;
					particleColor = &colors[1];
					break;
				}
				case 2 :
				{
					particleSpeed = 100;
					particleColor = &colors[2];
					break;
				}
				case 3 :
				{
					particleSpeed = 125;
					particleColor = &colors[3];
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

			Particle* p = new Particle(10, Vector3D(), GetLaunchDirection(x, y) * particleSpeed, 10);
			primitives.push_back(std::pair<of3dPrimitive*, Vector3D*>(p, particleColor));
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
				preview.push_back(std::pair<ofSpherePrimitive*, Vector3D*>(previewSphere, &visualizationColor));
			}

			return;
		}
		default: break;
	}

	const Vector3D initialSpeed = directionUnitVector * particleSpeed;

	// parametric equation of y
	function <float(float)> y_t = [initialSpeed, initialPosition](float t) {
			return -9.8 * t * t / 2 + t * initialSpeed.y() + initialPosition.y();
		}
	;
	
	// cartesian equation of time
	function <float(float)> t_x = [initialSpeed, initialPosition](float x) {
			return (x - initialPosition.x()) / initialSpeed.x();
		}
	;	
	
	// cartesian equation of y, avoid developping expressions with x - x0
	function <float(float)> y_x = [y_t, t_x](float x) {
			return y_t(t_x(x));
		}
	;	
	
	// cartesian equation of dy / dx
	function <float(float)> dy_x = [initialSpeed, initialPosition](float x) {
		return (-9.8 * x * x / (initialSpeed.x() * initialSpeed.x())) + x * (initialSpeed.y() / initialSpeed.x() - initialPosition.x());
		}
	;	
	
	// differential of length to integrate to get y(x)'s curve length
	function <float(float)> dl = [dy_x](float x) {
			return sqrt(1 + dy_x(x) * dy_x(x));
		}
	;

	
	float finalX = initialPosition.x() + 2 * initialSpeed.x() * initialSpeed.y() / 9.8;



	Vector3D i;
	i[0] = finalX > initialPosition.x() ? initialPosition.x() : finalX;
	i[1] = finalX > initialPosition.x() ? finalX : initialPosition.x();
	
	float interval[2] = { i.x(), i.y() };
	float l = abs(integrate(dy_x, interval)); // dunno why I've got negative values

	int nbDots = l > 200 ? 10 : (l >= 20 ? round(l / 10) : 1);

	float deltaX = finalX / nbDots;

	float y;

	for (float x = initialPosition.x(); abs(x) <= abs(finalX); x += deltaX)
	{
		y = y_x(x);

		ofSpherePrimitive* previewSphere = new ofSpherePrimitive();
		previewSphere->setRadius(5);
		previewSphere->setPosition(Vector3D(x, y).v3());
		preview.push_back(std::pair<ofSpherePrimitive*, Vector3D*>(previewSphere, &visualizationColor));
	}
}