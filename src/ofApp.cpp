#include "ofApp.h"
#include "iostream"
#include "CollisionHandler.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Tests
	Tests::ExecuteTests();

	level1 = new LevelPhase1();

	levels.push_back(level1); // LevelPhase1 level1

	levelSelection.setup(levels);

	for_each(levels.begin(), levels.end(), std::mem_fn(&Level::setup));

	doLevelSelection = true;
	selectedLevel = &levelSelection;
}

//--------------------------------------------------------------
void ofApp::update() {
	(selectedLevel)->update();
	ofSetEscapeQuitsApp(doLevelSelection);
}

//--------------------------------------------------------------
void ofApp::draw(){
	(selectedLevel)->draw();
	if (doLevelSelection) {
		levelSelection.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
	case 27: // esc
		doLevelSelection = true;
		(selectedLevel)->setup();
		selectedLevel = &levelSelection;
		(selectedLevel)->setup();
		break;
	default:
		(selectedLevel)->keyPressed(key);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	(selectedLevel)->keyReleased(key);
	if (doLevelSelection) {
		int selectionKey = levelSelection.keyReleased(key);
		int index = selectionKey - 1;
		if (levels.size() > index && index >= 0) {
			doLevelSelection = false;
			list<Level*>::iterator level_it = levels.begin();
			advance(level_it, index);
			selectedLevel = *level_it;
			doLevelSelection = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	(selectedLevel)->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	(selectedLevel)->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	(selectedLevel)->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	(selectedLevel)->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	(selectedLevel)->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	(selectedLevel)->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	(selectedLevel)->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	(selectedLevel)->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	(selectedLevel)->dragEvent(dragInfo);
}