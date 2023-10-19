#include "LevelSelection.h"
#include "ofApp.h"

LevelSelection::LevelSelection() {}
LevelSelection::~LevelSelection() {}

void LevelSelection::setup(std::list<Level*> levels) {
	commands = "SELECT YOUR LEVEL:\nuse the number before to select\n";
	string buffer;
	int i = 1;
	for (Level* level : levels) {
		commands = commands + "\t ." + to_string(i) + " : " + (level)->name + "\n";
		i++;
	}
}

void LevelSelection::update() {}

void LevelSelection::draw() {
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(ofToString(commands), ((float) ofGetWindowWidth() / 2) - 100, ((float) ofGetWindowHeight() / 2));
}

void LevelSelection::keyPressed(int key) {}

int LevelSelection::keyReleased(int key) {
	std::cout << to_string(key - '0') << std::endl;
	return key - '0';
}

void LevelSelection::mouseMoved(int x, int y) {}

void LevelSelection::mouseDragged(int x, int y, int button) {}

void LevelSelection::mousePressed(int x, int y, int button) {}

void LevelSelection::mouseReleased(int x, int y, int button) {}

void LevelSelection::mouseEntered(int x, int y) {}

void LevelSelection::mouseExited(int x, int y) {}

void LevelSelection::windowResized(int w, int h) {}

void LevelSelection::dragEvent(ofDragInfo dragInfo) {}

void LevelSelection::gotMessage(ofMessage msg) {}