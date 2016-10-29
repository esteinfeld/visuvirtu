#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
}

//--------------------------------------------------------------
void ofApp::update(){
	swarm.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
	swarm.draw();
	ofPopMatrix();
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
	}
}