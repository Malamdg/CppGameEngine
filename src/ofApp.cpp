#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	primitives = std::list<std::pair<of3dPrimitive*, Vector3D*>>();
	preview = std::list<Particle*>();

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

	primitives.push_back(std::pair<of3dPrimitive*, Vector3D*>(&particleVisualization, &colorVisualization));
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
	//Update Sphere
	position += speed;
	sphere.setPosition(position.v3());

	
	//Update particles
	for (Particle* particle : particles)
	{
		particle->Update();
	}

	preview.clear();
	GeneratePrevisualization(Vector3D());
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
	for (Particle* particle : preview)
	{
		particle->draw();
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
			colorVisualization = Vector3D(0, 255, 0);
			break;
		}
		case 'z': 
		case 'w': 
		{
			mode = 1;
			colorVisualization = Vector3D(255, 0, 0);
			break;
		}
		case 'e': 
		{
			mode = 2;
			colorVisualization = Vector3D(0, 0, 255);
			break;
		}
		case 'r': 
		{
			mode = 3;
			colorVisualization = Vector3D(125, 125, 125);
			break;
		}
		case 't': 
		{
			mode = 4; 
			colorVisualization = Vector3D(255, 255, 255);
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
			Vector3D launchDirection = GetLaunchDirection(x, y);

			float speedParticle;
			Vector3D colorParticle;
			Vector3D speedParticle;
			Vector3D* colorParticle;
			switch (mode)
			{
				case 0 :
				{
					colorParticle = Vector3D(0, 255, 0);
					speedParticle = 50;
					speedParticle = Vector3D(50, 50, 0);
					colorParticle = &colors[0];
					break;
				}
				case 1 :
				{
					colorParticle = Vector3D(255, 0, 0);
					speedParticle = 75;
					speedParticle = Vector3D(100, 50, 0);
					colorParticle = &colors[1];
					break;
				}
				case 2 :
				{
					colorParticle = Vector3D(0, 0, 255);
					speedParticle = 100;
					speedParticle = Vector3D(50, 100, 0);
					colorParticle = &colors[2];
					break;
				}
				case 3 :
				{
					colorParticle = Vector3D(125, 125, 125);
					speedParticle = 125;
					speedParticle = Vector3D(100, 100, 0);
					colorParticle = &colors[3];
					break;
				}
				case 4 : 
				{
					int r = rand() % 256;
					int g = rand() % 256;
					int b = rand() % 256;
					colorParticle = Vector3D(r, g, b);
					speedParticle = (r * g * b) % 500;
					colorParticle = new Vector3D(r, g, b);
					colorVisualization = *colorParticle;
					speedParticle = Vector3D(r, g, 0);
					break;
				}
				default: break;
			}
			Particle* p = new Particle(10, Vector3D(), launchDirection * speedParticle, 10);
			p->setColor(colorParticle);
			
			Particle* p = new Particle(10, Vector3D(), speedParticle, 10);
			primitives.push_back(std::pair<of3dPrimitive*, Vector3D*>(p, colorParticle));
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
	launchDirection.Normalize();

	return launchDirection;
}

void ofApp::GeneratePrevisualization(Vector3D initialPosition)
{
	std::list<float> timestamp;
	for (int i = 0; i < 5; i++)
	{
		timestamp.push_back(i);
	}

	float speedParticle = 0;
	switch (mode)
	{
		case 0:
		{
			speedParticle = 50;
			break;
		}
		case 1:
		{
			speedParticle = 75;
			break;
		}
		case 2:
		{
			speedParticle = 100;
			break;
		}
		case 3:
		{
			speedParticle = 125;
			break;
		}
		default: break;
	}

	Vector3D initialSpeed = GetLaunchDirection(ofGetMouseX(), ofGetMouseY()) * speedParticle;
	Vector3D acceleration = Vector3D(0, -9.8, 0);

	Vector3D position = initialPosition;

	for (float time : timestamp)
	{
		position += acceleration * .5 * time * time + initialSpeed * time;
		
		Particle* previewParticle = new Particle(10, position, Vector3D(), 0, Vector3D());
		preview.push_back(previewParticle);
	}
}