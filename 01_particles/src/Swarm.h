#pragma once

#include "ofMain.h"
#include "Particle.h"

#define SPEED_LIMIT_DRAG			5
#define FRICTION_FACTOR				0.00002

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
		
		void resetParticles()
		{
			for (int i=0 ; i<numParticles ; ++i) {
				particles[i].setPosition(ofVec3f(0,0,0));
				float angle = ofMap(i,0,numParticles,0,TWO_PI);
				particles[i].setVelocity(ofVec3f(cos(angle),sin(angle),0));
			}
		}

		void addCentralForce()
		{
			for ( int i=0 ; i<numParticles ; ++i ) {
				particles[i].addForce(-particles[i].getPosition().normalize()*20.0);
			}
		}

		void addForceZ(float z)
		{
			for ( int i=0 ; i<numParticles ; ++i ) {
				particles[i].addForce(ofVec3f(0.f,0.f,z));
			}
		}
		int magneticField = 0;
		
	private:
		int numParticles;
		vector <Particle> particles;
		
		ofVec3f box; 	//box at (0,0,0) min = -x max = x
		float outerSphereRadius;
		
		ofVec3f magneticField_01(ofVec3f r)
		{
			return ofVec3f(0,0,sqrt(pow(r.x,4)+pow(r.y,4))*0.00001);
		}
		ofVec3f magneticField_02(ofVec3f r)
		{
			return ofVec3f(0,0,-sqrt(pow(r.x,2)+pow(r.y,2))*0.0001);
		}
		ofVec3f magneticField_03(ofVec3f r)
		{
			return ofVec3f(0,0,pow(r.x,1)*pow(r.y,1)*0.00002);
		}
		ofVec3f magneticField_04(ofVec3f r)
		{
			return ofVec3f(0,0,sin(r.x/10.0));
		}
		ofVec3f magneticField_05(ofVec3f r)
		{
			return ofVec3f(sin(r.z/10.0),cos(r.z/10.0),0)*0.01;
		}
		ofVec3f magneticField_06(ofVec3f r)
		{
			return ofVec3f(sin(r.z/10.0),cos(r.z/10.0),0)*10.0;
		}
		//ofVec3f magneticField;
			
};