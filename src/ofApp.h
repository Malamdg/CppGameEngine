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

		//Camera
		ofCamera cam;

		//**Primitives**//
		std::list<std::pair<of3dPrimitive*, int*>> primitives;
		std::list<Particle*> particles;

		ofBoxPrimitive floor;
		ofSpherePrimitive particleVisualization;

		//Colors & Textures
		Vector3D* colors = new Vector3D[5];
		Vector3D colorVisualization = Vector3D(0, 255, 0);

		ofTexture* textures = new ofTexture[1];
		ofTexture textureVisualization;
		ofTexture canonText;

		//Shot modes
		int mode = 0;

};
