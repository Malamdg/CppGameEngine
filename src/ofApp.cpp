#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	primitives = std::list<of3dPrimitive>();

	sphere.setRadius(50);
	position = Vector3D();
	sphere.setPosition(position.v3());
	speed = Vector3D(1, 1);

	primitives.push_back(sphere);
}

//--------------------------------------------------------------
void ofApp::update(){
	position += speed;
	sphere.setPosition(position.v3());
	std::cout << position.toString() << std::endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
	sphere.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	for(of3dPrimitive primitive : primitives)
	{
		primitive.draw();
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

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
