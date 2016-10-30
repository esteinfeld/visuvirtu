#include "Particle.h"

Particle::Particle()
{
	mass = 1.f;
}

Particle::~Particle()
{
	
}



void Particle::update()
{
	
	if ( ofGetElapsedTimeMillis() - tLastHistory > TIME_HISTORY ) {
		saveHistory();
		tLastHistory = ofGetElapsedTimeMillis();
	}
	ofVec3f acc = force / mass;
	velocity += acc;
	velocity.limit(SPEED_LIMIT);
	position += velocity;
	force = ofVec3f(0,0,0);
}

void Particle::saveHistory()
{
	positionHistory.push_back(position);
	if (positionHistory.size() > MAX_NUM_HISTORY) {
		positionHistory.erase(positionHistory.begin());
	}
}