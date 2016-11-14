#pragma once

#include "ofMain.h"
#include "Swarm.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void touchMoved(ofTouchEventArgs &touch);
		Swarm swarm;
		
		ofEasyCam camera;
};
