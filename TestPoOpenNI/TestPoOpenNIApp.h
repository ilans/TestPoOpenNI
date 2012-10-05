/*	Created by Ilan Schifter on 10/5/12.
 *	Copyright 2012 __MyCompanyName__. All rights reserved.
 */

#include "poObject.h"

class TestPoOpenNIApp : public poObject {
public:
	TestPoOpenNIApp();
	virtual ~TestPoOpenNIApp();
	
    virtual void update();
    
    virtual void draw();
	
    virtual void eventHandler(poEvent *event);
	
    virtual void messageHandler(const std::string &msg, const poDictionary& dict=poDictionary());
};

