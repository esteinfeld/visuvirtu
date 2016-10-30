#include "Swarm.h"

Swarm::Swarm()
{
	numParticles = 4000;
	
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
	simulateHardSphere();
	simulateFriction();
	simulateLorentzForce();
	for ( int i=0 ; i<numParticles ; ++i ) {
		particles[i].update();
	}
}

void Swarm::draw()
{
	ofSetColor(50,70);
	// draw simple circle
	for ( int i=0 ; i<numParticles ; ++i ) {
		ofDrawCircle(particles[i].getPosition(), 3);
	}
	
	/* lines
	for ( int i=1 ; i<numParticles ; ++i ) {
		ofDrawLine(particles[i-1].getPosition(),particles[i].getPosition());
	}
	*/
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
			particles[i].addForce( -vel.normalized()*pow(vel.length()-SPEED_LIMIT_DRAG,2) * FRICTION_FACTOR );
		}
	}
}

void Swarm::simulateLorentzForce()
{
	//homogenous B field
	for ( int i=0 ; i<numParticles ; ++i ) {
		particles[i].addForce( particles[i].getVelocity().cross(magneticField(particles[i].getPosition())) * 0.1 );
	}
}