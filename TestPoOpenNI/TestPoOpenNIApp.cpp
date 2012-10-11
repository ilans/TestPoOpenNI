/*	Created by Ilan Schifter on 10/5/12.
 *	Copyright 2012 __MyCompanyName__. All rights reserved.
 */

#include "TestPoOpenNIApp.h"
#include "poApplication.h"
#include "poCamera.h"


// APP CONSTRUCTOR. Create all objects here.
TestPoOpenNIApp::TestPoOpenNIApp() {
	addModifier(new poCamera2D(poColor::black));
    
    int max_num_of_devices = 2;
    
    for (int i=0; i<max_num_of_devices; ++i) {
        rgb_rects.push_back(new poRectShape(KINECT_WIDTH,KINECT_HEIGHT));
        rgb_rects[i]->rotation = i%2 ? 90 : -90 ;
        rgb_rects[i]->position.x += KINECT_HEIGHT ;
        rgb_rects[i]->position.y += i%2 ? 0 : KINECT_WIDTH ;
        addChild(rgb_rects[i]);

        depth_rects.push_back(new poRectShape(KINECT_WIDTH,KINECT_HEIGHT));
        depth_rects[i]->rotation = i%2 ? 90 : -90 ;
        depth_rects[i]->position.x += KINECT_HEIGHT ;
        depth_rects[i]->position.y += i%2 ? KINECT_WIDTH : KINECT_WIDTH*2 ;
        addChild(depth_rects[i]);
    }
    
    flip_view = false;
    openni = new poOpenNI(max_num_of_devices, flip_view);
    
    addChild(openni);
}

// APP DESTRUCTOR. Delete all objects here.
TestPoOpenNIApp::~TestPoOpenNIApp() {
}

// UPDATE. Called once per frame. Animate objects here.
void TestPoOpenNIApp::update() {
	openni->updateRGBImage(rgb_rects);
	openni->updateDepthImage(depth_rects);
}

// DRAW. Called once per frame. Draw objects here.
void TestPoOpenNIApp::draw() {
}

// EVENT HANDLER. Called when events happen. Respond to events here.
void TestPoOpenNIApp::eventHandler(poEvent *event) {
	
}

// MESSAGE HANDLER. Called from within the app. Use for message passing.
void TestPoOpenNIApp::messageHandler(const std::string &msg, const poDictionary& dict) {
	
}
