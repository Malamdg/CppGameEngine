#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	primitives = std::list<of3dPrimitive*>();

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
			Vector3D speedParticle;
			Vector3D colorParticle;
			switch (mode)
			{
				case 0 :
				{
					colorParticle = Vector3D(0, 255, 0);
					speedParticle = Vector3D(50, 50, 0);
					break;
				}
				case 1 :
				{
					colorParticle = Vector3D(255, 0, 0);
					speedParticle = Vector3D(100, 50, 0);
					break;
				}
				case 2 :
				{
					colorParticle = Vector3D(0, 0, 255);
					speedParticle = Vector3D(50, 100, 0);
					break;
				}
				case 3 :
				{
					colorParticle = Vector3D(125, 125, 125);
					speedParticle = Vector3D(100, 100, 0);
					break;
				}
				case 4 : 
				{
					int r = rand() % 256;
					int g = rand() % 256;
					int b = rand() % 256;
					colorParticle = Vector3D(r, g, b);
					speedParticle = Vector3D(r, g, 0);
					break;
				}
				default: break;
			}
			Particle* p = new Particle(10, Vector3D(), speedParticle, 10);
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