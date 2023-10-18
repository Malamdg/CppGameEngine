#include "ofApp.h"
#include "CollisionHandler.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Tests
	Tests::ExecuteTests();

	levelSelection.setup(levels);

	for (Level level : levels) {
		level.setup();
	}

	doLevelSelection = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	selectedLevel.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	selectedLevel.draw();
	if (doLevelSelection) {
		levelSelection.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	selectedLevel.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	selectedLevel.keyReleased(key);
	if (doLevelSelection) {
		int selectionKey = levelSelection.keyReleased(key);
		if (levels.size() > selectionKey && selectionKey >= 0) {
			doLevelSelection = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	selectedLevel.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	selectedLevel.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	selectedLevel.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	selectedLevel.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	selectedLevel.mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	selectedLevel.mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	selectedLevel.windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	selectedLevel.gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	selectedLevel.dragEvent(dragInfo);
}