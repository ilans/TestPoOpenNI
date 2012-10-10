/*	Created by Ilan Schifter on 10/5/12.
 *	Copyright 2012 __MyCompanyName__. All rights reserved.
 */

#include "TestPoOpenNIApp.h"
#include "poApplication.h"
#include "poCamera.h"


// APP CONSTRUCTOR. Create all objects here.
TestPoOpenNIApp::TestPoOpenNIApp() {
	addModifier(new poCamera2D(poColor::black));
    
    for (int i=0; i<2; ++i) {
        rects.push_back(new poRectShape(KINECT_WIDTH,KINECT_HEIGHT));
        rects[i]->rotation = 180;
        rects[i]->position.x = KINECT_WIDTH;
        rects[i]->position.y = KINECT_HEIGHT;
        addChild(rects[i]);
    }
    
    flip_view = false;
    if(flip_view)
        rects[0]->position.x += rects[1]->getWidth();
    else
        rects[1]->position.x += rects[0]->getWidth();
    
    
    openni = new poOpenNI(rects.size());
    
    addChild(openni);
}

// APP DESTRUCTOR. Delete all objects here.
TestPoOpenNIApp::~TestPoOpenNIApp() {
	openni->updateRGBImage(rects);
}

// UPDATE. Called once per frame. Animate objects here.
void TestPoOpenNIApp::update() {
	
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
