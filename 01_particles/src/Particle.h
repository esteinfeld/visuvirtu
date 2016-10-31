#pragma once

#include "ofMain.h"

#define SPEED_LIMIT					15
#define MAX_NUM_HISTORY				20
#define TIME_HISTORY				25


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
		
		vector <ofVec3f> positionHistory;
		int tLastHistory;

	private:
		
		ofVec3f force;
		double mass;
		
		double wavelength;
		
		ofVec3f position;
		ofVec3f velocity;
		
		void saveHistory();
		
};