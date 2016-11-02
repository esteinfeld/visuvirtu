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
	acceleration = force / mass;
	acceleration.limit(ACCELERATION_LIMIT);
	averageAcceleration = MA_FILTER_ACC * averageAcceleration + (1.f - MA_FILTER_ACC) * acceleration.length();
	velocity += acceleration;
	//cout << acc.length() << endl;

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
	accelerationHistory.push_back(acceleration);
	if (accelerationHistory.size() > MAX_NUM_HISTORY) {
		accelerationHistory.erase(accelerationHistory.begin());
	}
}