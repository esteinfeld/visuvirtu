#pragma once

#include "ofMain.h"
#include "Particle.h"

#define SPEED_LIMIT_DRAG			5
#define FRICTION_FACTOR				0.002

class Swarm{
	public:
		Swarm();
		~Swarm();
		void update();
		void draw();
		
		void simulateSoftBox(); // particles can enter outer area, finite potential
		void simulateHardBox(); //	inf potential in area out of box, particles will be reflected
		void simulateHardSphere();
		void simulateFriction();
		void simulateLorentzForce();
		void simulateRepulsion();
		
		void decrementOuterSphereRadius(float dec)
		{
			outerSphereRadius -= dec;
		}
		void incrementOuterSphereRadius(float inc)
		{
			outerSphereRadius += inc;
		}
				
	private:
		int numParticles;
		vector <Particle> particles;
		
		ofVec3f box; 	//box at (0,0,0) min = -x max = x
		float outerSphereRadius;
		
		ofVec3f magneticField(ofVec3f r)
		{
			return ofVec3f(0,0,sqrt(pow(r.x,4)+pow(r.y,4))*0.00001);
		}
		//ofVec3f magneticField;
		
		
};