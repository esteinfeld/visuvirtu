#pragma once

#include "ofMain.h"
#include "Particle.h"

#define SPEED_LIMIT_DRAG			0.8

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
		void simulateGridForce();


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
		void resetParticlesHistory()
		{
			for ( int i=0 ; i<numParticles ; ++i ) {
				particles[i].resetHistory();
			}		
		}
		void setParticlesLine(float length)
		{
			for (int i=0 ; i<numParticles ; ++i) {
				particles[i].setPosition(ofVec3f(ofMap(i,0,numParticles,-length/2,length/2),0,0));
				particles[i].setVelocity(ofVec3f(0,2,0));
			}	
		}
		void setParticlesRandomXY()
		{
			for (int i=0 ; i<numParticles ; ++i) {
				particles[i].setPosition(ofVec3f(ofRandomf()*4000,ofRandomf()*4000,0));
				particles[i].setVelocity(ofVec3f(0,0,0));
			}			}
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
		
		double FRICTION_FACTOR = 0.00005;
		float gridForceFactor = 0.08;

	private:
		int numParticles;
		vector <Particle> particles;
		
		ofVec3f box; 	//box at (0,0,0) min = -x max = x
		float outerSphereRadius;
		
		ofVec3f vectorField_01(ofVec3f r)
		{
			return ofVec3f(0,0,sqrt(pow(r.x,2)+pow(abs(r.y),3))*0.00055);
		}
		ofVec3f vectorField_02(ofVec3f r)
		{
			return ofVec3f(pow(r.length()/1000.0,3),0,0);
		}
		ofVec3f vectorField_03(ofVec3f r)
		{
			return ofVec3f(0,0,pow(2.13,r.x/1000.0));
		}
		ofVec3f vectorField_04(ofVec3f r)
		{
			return ofVec3f(0,0,pow(sin(r.x/100.0),r.z/1000.0));
		}
		ofVec3f vectorField_05(ofVec3f r)
		{
			return ofVec3f(sin(r.z/10.0)*cos(r.z/10.0),0)*0.1;
		}
		ofVec3f vectorField_06(ofVec3f r)
		{
			return ofVec3f(sin(r.z/10.0),cos(r.z/10.0),0)*10.0;
		}
		//ofVec3f magneticField;
			
};