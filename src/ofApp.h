#pragma once

#include "ofMain.h"
#include "of3dPrimitives.h"
#include "Vector3D.h"
#include "Particle.h"
#include "Tests.h"
#include "ParticleForceRegistry.h"
#include "CollisionHandler.h"
#include "Spindle.h"
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
		std::list<std::pair<ofSpherePrimitive*, int*>> preview;

		Vector3D m_initialPosition = Vector3D();
		ofBoxPrimitive floor;
		ofSpherePrimitive particleVisualization;

		//Colors & Textures
		Vector3D* colors = new Vector3D[5];
		Vector3D visualizationColor = Vector3D(0, 255, 0);

		ofTexture* textures = new ofTexture[2];
		ofTexture textureVisualization;

		ParticleForceRegistry* forceRegistry;

		Particle* p;
		Particle* p1;

		Spindle* spindle;

		// Shooting modes
		int mode = 0;

		// Constants 
		float gravity = 9.8;
		
		// Texts to display
		string commandText;

		/*
		* Function to get launch direction from mouse
		* 
		* @param float x, mouse's x on screen
		* @param float y, mouse's y on screen
		* @return Vector3D, normalized shooting direction vector
		*/
		Vector3D GetLaunchDirection(float x, float y);

		/*
		* Method to display a previsualization of current shot
		* 
		* @param Vector3D initialPosition, particle's starting point from (0, 0, 0)
		*/
		void GeneratePrevisualization(Vector3D initialPosition = Vector3D());

};
