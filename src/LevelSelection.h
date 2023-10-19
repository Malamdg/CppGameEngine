#pragma once
#include "Level.h";
#include "ofMain.h";

class LevelSelection : public Level
{ 
public:
	string commands;

	LevelSelection();
	~LevelSelection();

	void setup(std::list<Level*> levels);
	void update();
	void draw();

	void keyPressed(int key);
	int keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};
