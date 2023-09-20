#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	primitives = std::list<of3dPrimitive*>();
	preview = std::list<Particle*>();

	sphere.setRadius(10);
	position = Vector3D();
	sphere.setPosition(position.v3());
	speed = Vector3D(1, 1);

	primitives.push_back(&sphere);

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
		/*std::cout << "particle position : ( " 
			+ to_string(particle->getPosition().x) + ", "
			+ to_string(particle->getPosition().y) + ", "
			+ to_string(particle->getPosition().z) + " )"
			<< std::endl;*/
	}

	preview.clear();
	GeneratePrevisualization(Vector3D());
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	for (of3dPrimitive* primitive : primitives)
	{
		primitive->draw();
	}
	for (Particle* particle : particles)
	{
		int r = particle->getColor()[0];
		int g = particle->getColor()[1];
		int b = particle->getColor()[2];
		ofSetColor(r, g, b);
		particle->draw();
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
			mode = 0; break;
		}
		case 'z': 
		case 'w': 
		{
			mode = 1; break;
		}
		case 'e': 
		{
			mode = 2; break;
		}
		case 'r': 
		{
			mode = 3; break;
		}
		case 't': 
		{
			mode = 4; break;
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
			switch (mode)
			{
				case 0 :
				{
					colorParticle = Vector3D(0, 255, 0);
					speedParticle = 50;
					break;
				}
				case 1 :
				{
					colorParticle = Vector3D(255, 0, 0);
					speedParticle = 75;
					break;
				}
				case 2 :
				{
					colorParticle = Vector3D(0, 0, 255);
					speedParticle = 100;
					break;
				}
				case 3 :
				{
					colorParticle = Vector3D(125, 125, 125);
					speedParticle = 125;
					break;
				}
				case 4 : 
				{
					int r = rand() % 256;
					int g = rand() % 256;
					int b = rand() % 256;
					colorParticle = Vector3D(r, g, b);
					speedParticle = (r * g * b) % 500;
					break;
				}
				default: break;
			}
			Particle* p = new Particle(10, Vector3D(), launchDirection * speedParticle, 10);
			p->setColor(colorParticle);
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