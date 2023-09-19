#pragma once

#include "ofMain.h"
#include "of3dPrimitives.h"
#include "Vector3D.h"
#include "Particle.h"
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


		ofCamera cam;

		std::list<of3dPrimitive*> primitives;
		std::list<Particle*> particles;

		ofSpherePrimitive sphere;
		Particle p1;
		Vector3D position;
		Vector3D speed;


private :
	void TestsVector3D();
};
