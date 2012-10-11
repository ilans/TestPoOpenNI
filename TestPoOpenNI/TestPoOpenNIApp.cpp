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
        rgb_rects[i]->rotation = 180;
        rgb_rects[i]->position.x = KINECT_WIDTH;
        rgb_rects[i]->position.y = KINECT_HEIGHT;
        addChild(rgb_rects[i]);

        depth_rects.push_back(new poRectShape(KINECT_WIDTH,KINECT_HEIGHT));
        depth_rects[i]->rotation = 180;
        depth_rects[i]->position.x = KINECT_WIDTH;
        depth_rects[i]->position.y = KINECT_HEIGHT*2;
        addChild(depth_rects[i]);
    }
    
    flip_view = false;
    if(rgb_rects.size() == 2){
        if(flip_view){
            rgb_rects[0]->position.x += rgb_rects[1]->getWidth();
            depth_rects[0]->position.x += depth_rects[1]->getWidth();
        }
        else{
            rgb_rects[1]->position.x += rgb_rects[0]->getWidth();
            depth_rects[1]->position.x += depth_rects[0]->getWidth();
        }
    }
    
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
