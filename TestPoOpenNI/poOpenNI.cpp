//
//  poOpenNI.cpp
//  TestMultiKinect
//
//  Created by Ilan Schifter on 10/4/12.
//
//

#include "poOpenNI.h"

poOpenNI::poOpenNI(uint _max_devices, bool _flip_view):
max_devices(_max_devices)
{
    for(int i=0; i<max_devices; ++i){
        textures.push_back(new poTexture(KINECT_WIDTH, KINECT_HEIGHT, NULL, GL_RGB));
    }
    
    flip_view = _flip_view;
    num_of_devices = 0;
    
    initOpenNI();
    
    openni_t = boost::thread(boost::bind(&poOpenNI::run,this));
}

poOpenNI::~poOpenNI(){
    xnContext.Release();
}

void poOpenNI::update(){
    
}

void poOpenNI::updateRGBImage(vector<poRectShape*>& rects){
    for (int i=0; i<num_of_devices ; ++i) {
        if(rects.size()>i){
            textures[i]->replace(rgb[i]);
            rects[i]->placeTexture(textures[i]);
        }
    }
}

void poOpenNI::updateDepthImage(vector<poRectShape*>& rects){
    for (int i=0; i<num_of_devices ; ++i) {
        textures[i]->replace(rgb[i]);
        rects[i]->placeTexture(textures[i]);
    }
}

void poOpenNI::initOpenNI() {
    nRetVal = XN_STATUS_OK;
    nRetVal = xnContext.Init();
    NodeInfoList devicesList;
    int devicesListCount = 0;
    
    // Getting Sensors information and configure all sensors
    nRetVal = xnContext.EnumerateProductionTrees(XN_NODE_TYPE_DEVICE, NULL, devicesList);
    for (NodeInfoList::Iterator it = devicesList.Begin(); it != devicesList.End(); ++it)
    {
        devicesListCount++;
    }
    CHECK_RC(nRetVal, "Enumerate");
    
    int i=0;
    for (NodeInfoList::Iterator it = devicesList.Begin(); it != devicesList.End(); ++it, ++i)
    {
        if(i < max_devices){
            // Create the device node
            NodeInfo deviceInfo = *it;
            nRetVal = xnContext.CreateProductionTree(deviceInfo, sensors[i].device);
            CHECK_RC(nRetVal, "Create Device");
            
            // Create a query to depend on this node
            Query query;
            query.AddNeededNode(deviceInfo.GetInstanceName());
            
            // Copy the device name
            xnOSMemCopy(sensors[i].name,deviceInfo.GetInstanceName(),
                        xnOSStrLen(deviceInfo.GetInstanceName()));
            
            // Now create a depth generator over this device
            nRetVal = xnContext.CreateAnyProductionTree(XN_NODE_TYPE_DEPTH, &query, sensors[i].depth);
            CHECK_RC(nRetVal, "Create Depth");
            
            // now create a image generator over this device
            nRetVal = xnContext.CreateAnyProductionTree(XN_NODE_TYPE_IMAGE, &query, sensors[i].image);
            CHECK_RC(nRetVal, "Create Image");
            
            cout << "Device created\n";
            
            num_of_devices++;
        }
    }
    
    if(flip_view)
        xnContext.SetGlobalMirror(true);
    
    xnContext.StartGeneratingAll();
	CHECK_RC(nRetVal, "StartGenerating");

}

void poOpenNI::run(){
    while (true)
    {
        for(int i = 0 ; i < num_of_devices ; ++i)
        {
            xnDepthRgbSensors &sensor = sensors[i];
            nRetVal = XN_STATUS_OK;
            nRetVal = xnContext.WaitAnyUpdateAll();
            CHECK_RC_CONTINUE(nRetVal, "WaitAnyUpdateAll() failed");
            
            if (sensor.depth.IsValid())
            {
                sensor.depth.GetMetaData(sensor.depthMD);
                
            }
            
            if (sensor.image.IsValid())
            {
                sensor.image.GetMetaData(sensor.imageMD);
                memcpy( rgb[i], (ubyte*) sensor.imageMD.RGB24Data() , sizeof(ubyte)*KINECT_WIDTH*KINECT_HEIGHT*3 );
            }
        }
    }
}

void poOpenNI::proccessImage(){
}

void poOpenNI::proccessDepth(){
}