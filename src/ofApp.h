#pragma once

#include "ofMain.h"
#include "of3dPrimitives.h"
#include "Vector3D.h"
#include "Particle.h"
#include "Tests.h"
#include "iostream"

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

		ofCamera cam;

		std::list<std::pair<of3dPrimitive*, Vector3D*>> primitives;
		std::list<Particle*> particles;
		Vector3D colorVisualization = Vector3D(0, 255, 0);
		Vector3D* colors = new Vector3D[4];

		ofBoxPrimitive floor;

		ofSpherePrimitive particleVisualization;


		int mode = 0;

};
