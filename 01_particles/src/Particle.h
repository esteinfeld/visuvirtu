#pragma once

#include "ofMain.h"

#define SPEED_LIMIT					50
#define ACCELERATION_LIMIT			15
#define MAX_NUM_HISTORY				20
#define TIME_HISTORY				60

#define MA_FILTER_ACC		0.98		

class Particle{
	public:
		Particle();
		~Particle();
		
		void setupParticlesRandomPosition();
		
		void update();
		
		void addForce(ofVec3f force_)
		{
			force += force_;
		}
		
		ofVec3f getVelocity()
		{
			return velocity;
		}
		ofVec3f getPosition()
		{
			return position;
		}
		float getAverageAcceleration()
		{
			return averageAcceleration; 
		}
		void setPosition(ofVec3f pos)
		{
			position = pos;
		}
		void setVelocity(ofVec3f vel)
		{
			velocity = vel;
		}
		void setMass(float m)
		{
			mass = m;
		}
		
		void resetHistory()
		{
			for ( int i=0 ; i<MAX_NUM_HISTORY ; ++i ) {
				positionHistory.clear();
				accelerationHistory.clear();
			}
		}

		vector <ofVec3f> positionHistory;
		vector <ofVec3f> accelerationHistory;
		int tLastHistory;

	private:
		
		ofVec3f force;
		double mass;
		
		double wavelength;
		
		ofVec3f position;
		ofVec3f velocity;
		ofVec3f acceleration;

		float averageAcceleration;

		void saveHistory();
		
};