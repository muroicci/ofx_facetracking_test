#include "testApp.h"

using namespace ofxCv;

void testApp::setup() {
    
    ofEnableSmoothing();
    
	ofSetVerticalSync(true);
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    cam.initGrabber(640, 480);
	
	tracker.setup();
    
    // load model
    model.loadModel("horse_head_r.obj");
    model.setScale(0.4, 0.4, 0.4);
    model.setPosition(0, -10, 40);
    model.setRotation(0, 180, 0, 1, 0);
    
    showVideo = false;
    
}

void testApp::exit() {
    tracker.waitForThread();
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
		position = tracker.getPosition();
		scale = tracker.getScale();
		orientation = tracker.getOrientation();
		rotationMatrix = tracker.getRotationMatrix();
	}
}


void testApp::draw() {
    
    ofColor centerColor = ofColor(0, 0, 0);
    ofColor edgeColor = ofColor(0,0,0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    if (showVideo) {
        ofSetColor(255);
        cam.draw(0,0);
        ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    }
	
	if(tracker.getFound()) {
		ofSetLineWidth(1);
        ofSetColor(0, 255, 0);
//		tracker.draw();
		
		//easyCam.begin();
		ofSetupScreenOrtho(640, 480, -1000, 1000);
//		ofTranslate(640 / 2, 480 / 2);
        ofTranslate(position.x, position.y);
		applyMatrix(rotationMatrix);
        
        ofScale(scale, scale, scale);
		//ofDrawAxis(scale*10);
//        model.drawWireframe();
        
        ofMesh mesh = tracker.getObjectMesh();
		mesh.drawWireframe();
		//easyCam.end();
	}
}

void testApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
    
    if (key=='v') {
        showVideo = !showVideo;
    }
    
    
}