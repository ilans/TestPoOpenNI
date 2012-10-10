/*	Created by Ilan Schifter on 10/5/12.
 *	Copyright 2012 __MyCompanyName__. All rights reserved.
 */

#include "TestPoOpenNIApp.h"
#include "poApplication.h"
#include "poCamera.h"


// APP CONSTRUCTOR. Create all objects here.
TestPoOpenNIApp::TestPoOpenNIApp() {
	addModifier(new poCamera2D(poColor::black));
    
    openni = new poOpenNI(2);
}

// APP DESTRUCTOR. Delete all objects here.
TestPoOpenNIApp::~TestPoOpenNIApp() {
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
