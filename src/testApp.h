#pragma once

#include "ofMain.h"
#include "ofxCv.h"
using namespace ofxCv;
using namespace cv;

#include "ofxFaceTrackerThreaded.h"
#include "ofxAssimpModelLoader.h"

class testApp : public ofBaseApp {
public:
	void setup();
    void exit();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTrackerThreaded tracker;
	ofVec2f position;
	float scale;
	ofVec3f orientation;
	ofMatrix4x4 rotationMatrix;
	
	Mat translation, rotation;
	ofMatrix4x4 pose;
	
	ofEasyCam easyCam;
    
    ofxAssimpModelLoader model;
    
    bool showVideo;
    
    
};
