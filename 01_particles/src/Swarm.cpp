#include "Swarm.h"

Swarm::Swarm()
{
	numParticles = 1900;
	
	for ( int i=0 ; i<numParticles ; ++i ) {
		particles.push_back(Particle());
	}
	
	/*
	for ( int i=0 ; i<numParticles ; ++i ) {
		particles[i].setPosition(ofVec3f(ofRandomf()*100,ofRandomf()*100,0) * 3.f);
		ofVec3f vel = particles[i].getPosition().normalized().getRotated(90, ofVec3f(0,0,1)) * ofRandomf()*3.0;
		particles[i].setVelocity(vel);
	}
	*/
	
	for ( int i=0 ; i<numParticles ; ++i ) {
		particles[i].setPosition(ofVec3f(-298,0,0));
		ofVec3f vel = particles[i].getPosition().normalized().getRotated(90, ofVec3f(0,0,1));
		vel *=  ofMap(i,0,numParticles, 1.0, 10.0);
		particles[i].setVelocity(vel);
		particles[i].setMass(5.0);
	}
	
	 box = ofVec3f(500, 500, 100);
	 outerSphereRadius = 600;
	 //magneticField = ofVec3f(0,0,1);
}

Swarm::~Swarm()
{
	
}

void Swarm::update()
{
	simulateHardSphere();		//TODO: simulateHardSphere(&particles);
	simulateFriction();
	simulateLorentzForce();
	//simulateRepulsion();
	simulateGridForce();
	for ( int i=0 ; i<numParticles ; ++i ) {
		particles[i].update();
	}
}

void Swarm::draw()
{
	ofSetColor(50,50);
	// draw simple circle
	for ( int i=0 ; i<numParticles ; ++i ) {
		//ofDrawCircle(particles[i].getPosition(), 1);
	}
	
	ofSetColor(50,10);
	/*/lines
	for ( int i=1 ; i<numParticles ; ++i ) {
		ofDrawLine(particles[i-1].getPosition(),particles[i].getPosition());
	}*/
	
	//draw history

		//map average acc to alpha
	/*
	for ( int i=0 ; i<numParticles ; ++i ) {

		float alphaFactor = ofMap(particles[i].getAverageAcceleration(), 0.0, 1.0, 0.1, 1.0, true); //clamp
		for (int j=particles[i].positionHistory.size()-1 ; j>0 ; --j) {
			alphaFactor = ofMap(particles[i].accelerationHistory[j].length(),0,ACCELERATION_LIMIT,0.2,1.0,true);
			ofSetColor(50,0,100,ofMap(j,particles[i].positionHistory.size()-1,0,150,0)*alphaFactor);
			ofDrawLine(particles[i].positionHistory[j],particles[i].positionHistory[j-1]);
		}
	}
*/
		//fade out
	for ( int i=0 ; i<numParticles ; ++i ) {

		for (int j=0 ; j<particles[i].positionHistory.size()-1 ; ++j) {
			ofSetColor(50,0,100,ofMap(j, particles[i].positionHistory.size()-1,0,40,0));
			ofDrawLine(particles[i].positionHistory[j], particles[i].positionHistory[j-1]);
		}
	}
}

void Swarm::simulateHardSphere()
{
	for ( int i=0 ; i<numParticles ; ++i ) {
		float depth = particles[i].getPosition().length() - outerSphereRadius;
		if ( depth > 0.f) {
			particles[i].addForce(-particles[i].getPosition().getNormalized() * pow(depth,4) * 0.00001);
		}
	}
}

void Swarm::simulateFriction()
{
	for ( int i=0 ; i<numParticles ; ++i ) {
		ofVec3f vel = particles[i].getVelocity();
		if ( vel.length() > SPEED_LIMIT_DRAG ) {
			particles[i].addForce( -vel.normalized()*pow(vel.length()-SPEED_LIMIT_DRAG,4) * FRICTION_FACTOR );
		}
	}
}

void Swarm::simulateLorentzForce()
{
	//homogenous B field
	for ( int i=0 ; i<numParticles ; ++i ) {
		ofVec3f b;
		if (magneticField == 1) {
			b = vectorField_01(particles[i].getPosition());
		} else if (magneticField == 2) {
			b = vectorField_02(particles[i].getPosition());
		} else if (magneticField == 3) {
			b = vectorField_03(particles[i].getPosition());
		} else if (magneticField == 4) {
			b = vectorField_04(particles[i].getPosition());
		} else if (magneticField == 5) {
			b = vectorField_05(particles[i].getPosition());
		}
		particles[i].addForce( particles[i].getVelocity().cross(b) * 0.1 );
	}
}


void Swarm::simulateRepulsion()
{
	for ( int i=0 ; i<numParticles ; ++i ) {
		float depth = 100 - particles[i].getPosition().length();
		if (depth > 0.f) {
			particles[i].addForce(particles[i].getPosition().getNormalized() * pow(depth,2) * 0.0001);
		}
	}
}

void Swarm::simulateGridForce()
{
	
	float factor = 0.008;
	float scale = 10.f;
	for ( int i=0 ; i<numParticles ; ++i ) {
		float x = particles[i].getPosition().x;
		float z = ( cos(x*factor) + cos(3*x*factor)/9.0 + cos(5*x*factor)/25.0 );
		if ( z > 0.9 ) {
			particles[i].addForce(ofVec3f(0.0, 3.0, 0.0));
		} else if ( z < -0.9 ) {
			particles[i].addForce(ofVec3f(0.0, -3.0, 0.0));
		}

		float y = particles[i].getPosition().y;
		z = ( cos(y*factor) + cos(3*y*factor)/9.0 + cos(5*y*factor)/25.0 );
		if ( z > 0.9 ) {
			particles[i].addForce(ofVec3f(3.0, 0.0, 0.0));
		} else if ( z < -0.9 ) {
			particles[i].addForce(ofVec3f(-3.0, 0.0, 0.0));
		}
	}
	/*
	for ( int i=0 ; i<numParticles ; ++i ) {
		int posX = (int)particles[i].getPosition().x;
		if ( posX > 350 && posX < 400) {
			particles[i].addForce(ofVec3f(0.0,1.0,0.0));
		} else if ( posX < -350 && posX > -400) {
			particles[i].addForce(ofVec3f(0.0,1.0,0.0));
		}
	}
	*/

}