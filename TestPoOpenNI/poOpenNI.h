//
//  poOpenNI.h
//  TestMultiKinect
//
//  Created by Ilan Schifter on 10/4/12.
//
//

#ifndef __TestMultiKinect__poOpenNI__
#define __TestMultiKinect__poOpenNI__

#include "poObject.h"
#include "poShapeBasics2D.h"

// OpenNI
#include <XnOpenNI.h>
#include <XnLog.h>
#include <XnCppWrapper.h>
#include <XnFPSCalculator.h>

// OpenCV
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
using std::cout;
using std::endl;

// Defines
#define MAX_NUM_OF_SENSORS 6


#define CHECK_RC(rc, what)                                      \
if (rc != XN_STATUS_OK)                                         \
{                                                               \
printf("%s failed: %s\n", what, xnGetStatusString(rc));     \
return rc;                                                  \
}

#define CHECK_RC_CONTINUE(rc, what)                             \
if (rc != XN_STATUS_OK)                                         \
{                                                               \
printf("%s failed: %s\n", what, xnGetStatusString(rc));        \
}

#define KINECT_WIDTH    320
#define KINECT_HEIGHT   240

using namespace xn;
using namespace cv;
using namespace std;

struct xnDepthRgbSensors
{
    char name[80];
    ProductionNode device;
    DepthGenerator depth;
    DepthMetaData depthMD;
    ImageGenerator image;
    ImageMetaData imageMD;
};

class poOpenNI: public poObject {
public:
    poOpenNI(uint _max_devices = 1, bool _flip_view = false);
    
    ~poOpenNI();
    
    virtual void update();
    
    void updateRGBImage(vector<poRectShape*>& rects);
    void updateDepthImage(vector<poRectShape*>& rects);
    
    
protected:
    virtual void proccessImage();
    virtual void proccessDepth();
    
    
private:
    void initOpenNI();
    void run();
    
    float scale_w;
    float scale_h;
    bool flip_view;
    
    Context xnContext;
    XnStatus nRetVal;
    
    xnDepthRgbSensors sensors[MAX_NUM_OF_SENSORS];
    
    boost::thread openni_t;
    boost::thread opencv_t;
    
    vector<poTexture*> rgb_textures;
    vector<poTexture*> depth_textures;
    
    ubyte rgb[MAX_NUM_OF_SENSORS][KINECT_WIDTH*KINECT_HEIGHT*3];
    ubyte depth[MAX_NUM_OF_SENSORS][KINECT_WIDTH*KINECT_HEIGHT*3];
    
    uint num_of_devices;
    uint max_devices;
};


#endif /* defined(__TestMultiKinect__poOpenNI__) */
