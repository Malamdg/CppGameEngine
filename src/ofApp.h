#pragma once

#include "ofMain.h"
#include "of3dPrimitives.h"
#include "Vector.h"

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

		Vector positionVect = Vector();
		Vector speedVect = Vector(0.5, 0.5, 0.1);
		ofBoxPrimitive box = ofBoxPrimitive();
};
