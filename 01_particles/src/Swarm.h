#pragma once

#include "ofMain.h"
#include "Particle.h"

#define SPEED_LIMIT_DRAG			5
#define FRICTION_FACTOR				0.0002

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
			return ofVec3f(0,0,r.x*2-r.y)*0.001;
		}
		//ofVec3f magneticField;
		
		
};