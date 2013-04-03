//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <XnOpenNI.h>
#include <XnLog.h>
#include <XnCppWrapper.h>
#include <XnFPSCalculator.h>

using namespace xn;

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define NUM_OF_SENSORS 2
//#define USE_RGB_IMAGE_STREAMS
//---------------------------------------------------------------------------
// Macros
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
// Code
//---------------------------------------------------------------------------

xn::Context g_Context;

struct DepthRgbSensors
{
    char name[80];
    ProductionNode device;
    DepthGenerator depth;
    DepthMetaData depthMD;
#if defined(USE_RGB_IMAGE_STREAMS)
    ImageGenerator image;
    ImageMetaData imageMD;
#endif
};

void CloseDevice()
{
    //Do additional cleanup if needed
    g_Context.Release();
}

void UpdateCommon(DepthRgbSensors &sensor)
{
    XnStatus rc = XN_STATUS_OK;
    rc = g_Context.WaitAnyUpdateAll();
    //This function will wait until all nodes will have new data:
    //rc = g_Context.WaitAndUpdateAll();
    CHECK_RC_CONTINUE(rc, "WaitAnyUpdateAll() failed");
    
    if (sensor.depth.IsValid())
    {
        sensor.depth.GetMetaData(sensor.depthMD);
    }
#if defined(USE_RGB_IMAGE_STREAMS)
    if (sensor.image.IsValid())
    {
        sensor.image.GetMetaData(sensor.imageMD);
    }
#endif
}

int main()
{
    XnStatus nRetVal = XN_STATUS_OK;
    // Getting Sensors information and configure all sensors
    DepthRgbSensors sensors[NUM_OF_SENSORS];
    nRetVal = g_Context.Init();
    NodeInfoList devicesList;
    int devicesListCount = 0;
    nRetVal = g_Context.EnumerateProductionTrees(XN_NODE_TYPE_DEVICE, NULL, devicesList);
    for (NodeInfoList::Iterator it = devicesList.Begin(); it != devicesList.End(); ++it)
    {
        devicesListCount++;
    }
    CHECK_RC(nRetVal, "Enumerate");
    int i=0;
    for (NodeInfoList::Iterator it = devicesList.Begin(); it != devicesList.End(); ++it, ++i)
    {
        // Create the device node
        NodeInfo deviceInfo = *it;
        nRetVal = g_Context.CreateProductionTree(deviceInfo, sensors[i].device);
        CHECK_RC(nRetVal, "Create Device");
        // Create a query to depend on this node
        Query query;
        query.AddNeededNode(deviceInfo.GetInstanceName());
        // Copy the device name
        xnOSMemCopy(sensors[i].name,deviceInfo.GetInstanceName(),
                    xnOSStrLen(deviceInfo.GetInstanceName()));
        // Now create a depth generator over this device
        nRetVal = g_Context.CreateAnyProductionTree(XN_NODE_TYPE_DEPTH, &query, sensors[i].depth);
        CHECK_RC(nRetVal, "Create Depth");
#if defined(USE_RGB_IMAGE_STREAMS)
        // now create a image generator over this device
        nRetVal = g_Context.CreateAnyProductionTree(XN_NODE_TYPE_IMAGE, &query, sensors[i].image);
        CHECK_RC(nRetVal, "Create Image");
#endif
    }
    g_Context.StartGeneratingAll();
    
    XnFPSData xnFPS;
    nRetVal = xnFPSInit(&xnFPS, 180);
    CHECK_RC(nRetVal, "FPS Init");
    while (!xnOSWasKeyboardHit())
    {
        for(i = 0 ; i < NUM_OF_SENSORS ; ++i)
        {
            printf("Sensor [%d] output:\n",i);
            UpdateCommon(sensors[i]);
            xnFPSMarkFrame(&xnFPS);
            // Print Depth central pixel
            const DepthMetaData *dmd = &sensors[i].depthMD;
            const XnDepthPixel* pDepthMap = sensors[i].depthMD.Data();
            printf("Depth frame [%d] Middle point is: %u. FPS: %f\n",
                   dmd->FrameID(), sensors[i].depthMD(dmd->XRes() / 2, dmd->YRes() / 2),
                   xnFPSCalc(&xnFPS));
#if defined(USE_RGB_IMAGE_STREAMS)
            // Print Image first pixel
            const ImageMetaData *imd = &sensors[i].imageMD;
            const XnUInt8 *imageMap = sensors[i].imageMD.Data();
            printf("Image frame [%d] first pixel is: R[%u],G[%u],B[%u]. FPS: %f\n",
                   imd->FrameID(), imageMap[0], imageMap[1], imageMap[2], xnFPSCalc(&xnFPS));
#endif
        }
    }
    CloseDevice();
    
    return 0;
}

