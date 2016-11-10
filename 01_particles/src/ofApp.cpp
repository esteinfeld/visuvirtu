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
	ofSetColor(10);
	ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()),10,10);
	ofDrawBitmapString("magnetic field: " + ofToString(swarm.magneticField),10,40);
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
	} else if ( key == '#' ) {
		swarm.addCentralForce();
	} else if ( key == 'z') {
		swarm.addForceZ(20.0);
	} else if ( key == 'Z') {
		swarm.addForceZ(-20.0);
	} else if ( key == 'r' ) {
		swarm.resetParticles();
	} else if ( key == 'R' ) {
		swarm.resetParticlesHistory();
	} else if ( key == '1' ) {
		//animate 1
		// increase history length smoothly to max back to default
		// alpha factor > 1 for all drawings related to history elements
		// aim: save a picture for a longer period
	} else if ( key == '2' ) {
		//save frame, background exlcuded
	}
	if ('0' <= key && key <='7') {
		swarm.magneticField = key - '1' + 1;
	}

	//camera animation
}