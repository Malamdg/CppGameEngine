#pragma once

#include "ofMain.h"
#include "Tests.h"	
#include "Level.h"
#include "LevelPhase1.h"
#include "LevelSelection.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
		LevelPhase1* level1;
		LevelSelection levelSelection;
		std::list<Level*> levels;

		Level* selectedLevel;
		bool doLevelSelection;

};
