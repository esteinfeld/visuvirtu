#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);

	camera.setDistance(300);
	
}

//--------------------------------------------------------------
void ofApp::update(){
	swarm.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	camera.begin();
	swarm.draw();
	camera.end();
	ofColor(10);
	ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()),10,10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == '+') {
		swarm.incrementOuterSphereRadius(100);
	} else if ( key == '-' ) {
		swarm.decrementOuterSphereRadius(100);
	} else if ( key == '.' ) {
		swarm.incrementOuterSphereRadius(5);
	} else if ( key == ',' ) {
		swarm.decrementOuterSphereRadius(5);
	} else if ( key == 'm' ) {
		swarm.magneticField ++;
		if (swarm.magneticField > 2) {
			swarm.magneticField = 0;
		}
	} else if ( key == 'r' ) {
		swarm.resetParticles();
	}
}