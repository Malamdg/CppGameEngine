#include "ofApp.h"
#include "Forces/ParticleForceRegistry.h"
#include "Collisions/CollisionHandler.h"
#include "Forces/ParticleImpulse.cpp"

//--------------------------------------------------------------
void ofApp::setup(){
	// Tests
	Tests::ExecuteTests();

	// Set command text
	commandText = "Bouger le blob avec les fleches directionnelles de droite et de gauche!";

	// Setup lists
	primitives = std::list<std::pair<of3dPrimitive*, int*>>(); // display primitive on each draw()

	// Setup cam and basic primitives
	const float floorWidth = ofGetScreenWidth() * 100;
	const float floorHeight = 5;
	floor = ofBoxPrimitive(floorWidth, floorHeight, 0);
	floor.setPosition(Vector3D(0, -10).v3());
	
	// Colors & Text

	// Setup colors
	colors[0] = Vector3D(0, 0, 0);
	colors[1] = Vector3D(255, 255, 255);
	
	// add floor to primitive list
	int* floorMode = new int(0);
	primitives.push_back(std::pair<of3dPrimitive*, int*>(&floor, floorMode));

	// Center cam and set origin at the bottom left corner
	cam.setPosition(Vector3D(0, 0, 500).v3());
	//cam.move(Vector3D(ofGetWidth() * .5, ofGetHeight() * .5).v3());
	
	// Setup Physics
	forceRegistry = new ParticleForceRegistry();
	m_gravity = Vector3D(0, -9.8, 0);

	// setup blob
	Particle* blobCore = new Particle(10, Vector3D(0, 200), Vector3D(), .01);
	blob = Blob(blobCore);

	int i = 0;
	int* colorMode;
	for (Particle* particle : blob.m_particles) {
		colorMode = new int(1);
		if (i == 0) {
			colorMode = new int(0);
		}

		primitives.push_back(std::pair<of3dPrimitive*, int*>(particle, colorMode));
		particles.push_back(particle);
		i++;
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	float duration = ofGetFrameRate() == 0. ? 0. : 1 / ofGetFrameRate();

	blob.linkParticles(forceRegistry);

	//Update particles
	for (Particle* particle : particles)
	{
		//forceRegistry->add(particle, gravity);
	}

	forceRegistry->updateForces(duration);

	for (Particle* particle : particles)
	{
		// ParticleGravity* gravity = new ParticleGravity(m_gravity);
		// forceRegistry->add(particle, gravity);
	}

	cam.move((blob.getCore()->getPosition() - Vector3D(cam.getPosition())).v3());

	blob.linkParticles(forceRegistry);
	handleCollision(particles);
}

//--------------------------------------------------------------
void ofApp::draw(){
	// begin camera job
	cam.begin();

	// display command text
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(ofToString(commandText), 0, ofGetScreenHeight());
	
	int* colorMode;

	// display primitives with correct color
	for (std::pair<of3dPrimitive*, int*> primitive : primitives)
	{
		colorMode = primitive.second;
		ofSetColor(colors[(*colorMode)].x(), colors[(*colorMode)].y(), colors[(*colorMode)].z());

		// display primitive
		primitive.first->draw();

	}

	// end camera job
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// Default direction +x
	Vector3D impulse = Vector3D();
	Vector3D impulseX = Vector3D(1000);
	Vector3D impulseY = Vector3D(0, 100000);
	std::cout << key << std::endl;
	// move on arrow key press
	switch (key)
	{
		case 57358: // stride right
			impulse = impulseX;
			break; 
		case 57356: // stride left
			impulse = impulseX * -1;
			break;		
		case 57357: // jump
			impulse = impulseY;
			break;	
		/* case 57359: // crouch
			impulse = impulseY * -1;
			break;*/
		default: 
			return;
	}
	
	ParticleImpulse* moveImpulse = new ParticleImpulse(impulse);
	forceRegistry->add(blob.getCore(), moveImpulse);
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