#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	primitives = std::list<std::pair<of3dPrimitive*, int*>>();

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
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

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
			colorVisualization = colors[0];
			break;
		}
		case 'z': 
		case 'w': 
		{
			mode = 1;
			textureVisualization = textures[0];
			colorVisualization = colors[1];
			break;
		}
		case 'e': 
		{
			mode = 2;
			colorVisualization = colors[2];
			break;
		}
		case 'r': 
		{
			mode = 3;
			textureVisualization = textures[1];
			colorVisualization = colors[3];
			break;
		}
		case 't': 
		{
			mode = 4; 
			colorVisualization = colors[4];
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
			Vector3D speedParticle;
			Vector3D* colorParticle;
			switch (mode)
			{
				case 0 :
				{
					speedParticle = Vector3D(50, 50, 0);
					break;
				}
				case 1 :
				{
					speedParticle = Vector3D(100, 50, 0);
					break;
				}
				case 2 :
				{
					speedParticle = Vector3D(50, 100, 0);
					break;
				}
				case 3 :
				{
					speedParticle = Vector3D(100, 100, 0);
					break;
				}
				case 4 : 
				{
					int r = rand() % 256;
					int g = rand() % 256;
					int b = rand() % 256;
					colorVisualization = *colorParticle;
					speedParticle = Vector3D(r, g, 0);
					break;
				}
				default: break;
			}
			
			Particle* p = new Particle(10, Vector3D(), speedParticle, 10);
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