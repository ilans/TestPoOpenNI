/////////////////////////////////////////
//
// pocode application configuration
//
/////////////////////////////////////////


#include "poApplication.h"
#include "TestPoOpenNIApp.h"

poObject *createObjectForID(uint uid) {
	return new TestPoOpenNIApp();
}

void setupApplication() {
	applicationCreateWindow(0, WINDOW_TYPE_NORMAL, "TestPoOpenNI", 100, 100, 1024, 768);
}

void cleanupApplication() {
}