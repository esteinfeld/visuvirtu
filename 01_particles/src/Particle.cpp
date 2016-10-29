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
	ofVec3f acc = force / mass;
	velocity += acc;
	velocity.limit(SPEED_LIMIT);
	position += velocity;
	force = ofVec3f(0,0,0);
}
