#pragma once
#include "ofMain.h"

class Timer{
public:
	Timer()
	{
	}
	void pause()
	{
		paused = true;
		timeLastPause = ofGetElapsedTimef();
	}
	void play()
	{
		if (paused) {
			timeLastPlay = ofGetElapsedTimef();
			pausingTime += timeLastPlay - timeLastPause;
			paused = false;
		}
	}
	void run()
	{
		if (!paused) {
			time = ofGetElapsedTimef() - timeLastReset - pausingTime;
		}
	}
	void reset()
	{
		pausingTime = 0;
		timeLastReset = ofGetElapsedTimef();
		timeLastPlay = timeLastReset;
	}
	
	float time;
	
private:
	float pausingTime;
	float timeLastReset;
	float timeLastPlay;
	
	bool paused;
	
};