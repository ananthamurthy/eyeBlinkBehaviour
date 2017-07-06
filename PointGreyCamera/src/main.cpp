#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <error.h>
#include "Streamer.hpp"
#include <chrono>
#include <exception>
#include <opencv2/highgui/highgui.hpp>

#include "config.h"

using namespace std::chrono;
using namespace cv;


using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

int total_frames_ = 0;
int socket_ = -1;                               /* Socket descriptor */
float fps_ = 0.0;                               /* Frame per second. */

SystemPtr system_;
CameraList cam_list_;


void sig_handler( int s )
{
    cout << "Got keyboard interrupt. Removing socket" << endl;
    close( socket_ );
    remove( SOCK_PATH );
    throw runtime_error( "Ctrl+C pressed" );
}

// This function returns the camera to its default state by re-enabling automatic
// exposure.
int ResetExposure(INodeMap & nodeMap)
{
        int result = 0;
        try
        {
                // 
                // Turn automatic exposure back on
                //
                // *** NOTES ***
                // Automatic exposure is turned on in order to return the camera to its 
                // default state.
                //
                CEnumerationPtr ptrExposureAuto = nodeMap.GetNode("ExposureAuto");
                if (!IsAvailable(ptrExposureAuto) || !IsWritable(ptrExposureAuto))
                {
                        cout << "Unable to enable automatic exposure (node retrieval). Non-fatal error..." << endl << endl;
                        return -1;
                }
        
                CEnumEntryPtr ptrExposureAutoContinuous = ptrExposureAuto->GetEntryByName("Continuous");
                if (!IsAvailable(ptrExposureAutoContinuous) || !IsReadable(ptrExposureAutoContinuous))
                {
                        cout << "Unable to enable automatic exposure (enum entry retrieval). Non-fatal error..." << endl << endl;
                        return -1;
                }
                ptrExposureAuto->SetIntValue(ptrExposureAutoContinuous->GetValue());
                cout << "Automatic exposure enabled..." << endl << endl;
        }
        catch (Spinnaker::Exception &e)
        {
                cout << "Error: " << e.what() << endl;
                result = -1;
        }
        return result;
}

/**
 * @brief Write data to socket.
 *
 * @param data
 * @param size
 *
 * @return 
 */
int write_data( void* data, size_t width, size_t height )
{
    // If socket_ is not set, don't try to write.
    if( socket_ == 0 )
        return 0;

    Mat img(height, width, CV_8UC1, data );
    data = img.data;

#ifdef TEST_WITH_CV
    imshow( "MyImg", img );
    waitKey( 10 );
#else
    try 
    {
        if( write( socket_, data,  width * height ) == -1 )
            throw runtime_error( strerror( errno ) );
    } 
    catch ( exception & e )
    {
        throw runtime_error( "Error in writing" );
    }
#endif
    return 0;
}

int create_socket( bool waitfor_client = true )
{
    int s, s2, len;
    struct sockaddr_un local, remote;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    cout << "[INFO] Creating socket " << SOCK_PATH << endl;
    strcpy(local.sun_path, SOCK_PATH);
    
    remove(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }


    // There is no point continuing if there is not one to read the data.
    while( true )
    {
        if( ! waitfor_client )
            return 0;
        int done, n;
        cout << "Waiting for a connection..." << endl;
        socklen_t t = sizeof(remote);
        if( (s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1 )
        {
            perror("accept");
            exit(1);
        }

        cout << "Connected." << endl;
        break;
    }

    // Assign to global value.
    socket_ = s2;
    return s2;
}

#if 0
void configure_camera( CameraPtr pCam )
{
    cout << "Max width: " << pCam->Width << endl;
    //cout << "Max height: " << pCam->Height.GetValue( ) << endl;
}
#endif


int AcquireImages(CameraPtr pCam, INodeMap & nodeMap , INodeMap & nodeMapTLDevice , int socket )
{
    signal( SIGINT, sig_handler );
    int result = 0;
    try
    {

        auto startTime = system_clock::now();

#if 1
        CEnumerationPtr ptrAcquisitionMode = nodeMap.GetNode("AcquisitionMode");
        if (!IsAvailable(ptrAcquisitionMode) || !IsWritable(ptrAcquisitionMode))
        {
            cout << "Unable to set acquisition mode to continuous " 
                << " (enum retrieval). Aborting..." << endl << endl;
            return -1;
        }

        // Retrieve entry node from enumeration node
        CEnumEntryPtr ptrAcquisitionModeContinuous = ptrAcquisitionMode->GetEntryByName("Continuous");
        if (!IsAvailable(ptrAcquisitionModeContinuous) || !IsReadable(ptrAcquisitionModeContinuous))
        {
            cout << "Unable to set acquisition mode to continuous " << 
                " (entry retrieval). Aborting..." << endl << endl;
            return -1;
        }

        // Retrieve integer value from entry node
        int64_t acquisitionModeContinuous = ptrAcquisitionModeContinuous->GetValue();

        // Set integer value from entry node as new value of enumeration node
        ptrAcquisitionMode->SetIntValue(acquisitionModeContinuous);
        cout << "Acquisition mode set to continuous..." << endl;

        // Change the acquition frame rate.

#else
        // This section does not work.
        CEnumerationPtr pAcquisitionMode = nodeMap.GetNode( "AcquisitionMode" );
        pAcquisitionMode->SetIntValue( AcquisitionMode_MultiFrame );
        CIntegerPtr pAcquitionFrameCount = nodeMap.GetNode( "AcquisitionBurstFrameCount" );
        pAcquitionFrameCount->SetValue( 3 );
        cout << "Frame per fetch " << pAcquitionFrameCount->GetValue( ) << endl;
#endif

        pCam->BeginAcquisition();

        gcstring deviceSerialNumber("");
        CStringPtr ptrStringSerial = nodeMapTLDevice.GetNode("DeviceSerialNumber");
        if (IsAvailable(ptrStringSerial) && IsReadable(ptrStringSerial))
        {
            deviceSerialNumber = ptrStringSerial->GetValue();
            cout << "Device serial number retrieved " << deviceSerialNumber 
                << endl;
        }


        char notification[100] = "running ..";
        while( true )
        {
            try
            {
                ImagePtr pResultImage = pCam->GetNextImage();
                //cout << "Pixal format: " << pResultImage->GetPixelFormatName( ) << endl;

                if ( pResultImage->IsIncomplete() ) /* Image is incomplete. */
                {
                    cout << "[WARN] Image incomplete with image status " << 
                        pResultImage->GetImageStatus() << " ..." << endl;
                }
                else
                {
                    size_t width = pResultImage->GetWidth();
                    size_t height = pResultImage->GetHeight();
                    size_t size = pResultImage->GetBufferSize( );
                    total_frames_ += 1;
                    //cout << "H: "<< height << " W: " << width << " S: " << size << endl;
                    // Convert the image to Monochorme, 8 bits (1 byte) and send
                    // the output.
                    //auto img = pResultImage->Convert( PixelFormat_Mono8 );
                    write_data( pResultImage->GetData( ), width, height );
                    if( total_frames_ % 100 == 0 )
                    {
                        duration<double> elapsedSecs = system_clock::now( ) - startTime;
                        fps_ = ( float ) total_frames_ / elapsedSecs.count( );
                        cout << "Running FPS : " << fps_ << endl;
                    }
                }
            }
            catch( runtime_error& e )
            {
                cout << "User pressed Ctrl+c" << endl;
                break;
            }
            catch (Spinnaker::Exception &e)
            {
                cout << "Error: " << e.what() << endl;
                result = -1;
            }
        }
        pCam->EndAcquisition();
    }
    catch (Spinnaker::Exception &e)
    {
        cout << "Error: " << e.what() << endl;
        result = -1;
    }

    return result;
}

// This function prints the device information of the camera from the transport
// layer; please see NodeMapInfo example for more in-depth comments on printing
// device information from the nodemap.
int PrintDeviceInfo(INodeMap & nodeMap)
{
    int result = 0;

    cout << endl << "*** DEVICE INFORMATION ***" << endl << endl;

    try
    {
        FeatureList_t features;
        CCategoryPtr category = nodeMap.GetNode("DeviceInformation");
        if (IsAvailable(category) && IsReadable(category))
        {
            category->GetFeatures(features);

            FeatureList_t::const_iterator it;
            for (it = features.begin(); it != features.end(); ++it)
            {
                CNodePtr pfeatureNode = *it;
                cout << pfeatureNode->GetName() << " : ";
                CValuePtr pValue = (CValuePtr)pfeatureNode;
                cout << (IsReadable(pValue) ? pValue->ToString() : "Node not readable");
                cout << endl;
            }

        }
        else
        {
            cout << "Device control information not available." << endl;
        }
    }
    catch (Spinnaker::Exception &e)
    {
        cout << "Error: " << e.what() << endl;
        result = -1;
    }

    return result;
}

// This function acts as the body of the example; please see NodeMapInfo example
// for more in-depth comments on setting up cameras.
int RunSingleCamera(CameraPtr pCam, int socket)
{
    int result = 0;

    try
    {
        // Retrieve TL device nodemap and print device information
        INodeMap & nodeMapTLDevice = pCam->GetTLDeviceNodeMap();

        result = PrintDeviceInfo(nodeMapTLDevice);

        // Initialize camera
        pCam->Init();

        // Retrieve GenICam nodemap
        INodeMap & nodeMap = pCam->GetNodeMap();

        // Set width, height
        CIntegerPtr width = nodeMap.GetNode("Width");
        width->SetValue( FRAME_WIDTH );

        CIntegerPtr height = nodeMap.GetNode("Height");
        height->SetValue( FRAME_HEIGHT );

        // Set frame rate manually.
        CBooleanPtr pAcquisitionManualFrameRate = nodeMap.GetNode( "AcquisitionFrameRateEnable" );
        pAcquisitionManualFrameRate->SetValue( true );

        CFloatPtr ptrAcquisitionFrameRate = nodeMap.GetNode("AcquisitionFrameRate");

        try {
            cout << "Trying to set frame rate to " << EXPECTED_FPS << endl;
            ptrAcquisitionFrameRate->SetValue( EXPECTED_FPS );
        }
        catch ( std::exception & e )
        {
            cout << "Failed to set frame rate. Using default ... " << endl;
            cout << "\tError was " << e.what( ) << endl;
        }

        if (!IsAvailable(ptrAcquisitionFrameRate) || !IsReadable(ptrAcquisitionFrameRate)) 
            cout << "Unable to retrieve frame rate. " << endl << endl;
        else
        {
            fps_ = static_cast<float>(ptrAcquisitionFrameRate->GetValue());
            cout << "[INFO] Expected frame set to " << fps_ << endl;
        }

        // Switch off auto-exposure and set it manually.
        CEnumerationPtr ptrExposureAuto = nodeMap.GetNode("ExposureAuto");
        if (!IsAvailable(ptrExposureAuto) || !IsWritable(ptrExposureAuto))
        {
            cout << "Unable to disable automatic exposure (node retrieval). Aborting..." << endl << endl;
            return -1;
        }

        CEnumEntryPtr ptrExposureAutoOff = ptrExposureAuto->GetEntryByName("Off");
        if (!IsAvailable(ptrExposureAutoOff) || !IsReadable(ptrExposureAutoOff))
        {
            cout << "Unable to disable automatic exposure (enum entry retrieval). Aborting..." << endl << endl;
            return -1;
        }

        ptrExposureAuto->SetIntValue(ptrExposureAutoOff->GetValue());
        cout << "Automatic exposure disabled..." << endl;
        CFloatPtr ptrExposureTime = nodeMap.GetNode("ExposureTime");
        if (!IsAvailable(ptrExposureTime) || !IsWritable(ptrExposureTime))
        {
            cout << "Unable to set exposure time. Aborting..." << endl << endl;
            return -1;
        }

        // Ensure desired exposure time does not exceed the maximum
        const double exposureTimeMax = ptrExposureTime->GetMax();

        ptrExposureTime->SetValue( EXPOSURE_TIME_IN_US );
        cout << "Exposure time set to " << ptrExposureTime->GetValue( ) << " us..." << endl << endl;

#if 1
        // Turn of automatic gain
        CEnumerationPtr ptrGainAuto = nodeMap.GetNode("GainAuto");
        if (!IsAvailable(ptrGainAuto) || !IsWritable(ptrGainAuto))
        {
            cout << "Unable to disable automatic gain (node retrieval). Aborting..." << endl << endl;
            return -1;
        }
        CEnumEntryPtr ptrGainAutoOff = ptrGainAuto->GetEntryByName("Off");
        if (!IsAvailable(ptrGainAutoOff) || !IsReadable(ptrGainAutoOff))
        {
            cout << "Unable to disable automatic gain (enum entry retrieval). Aborting..." << endl << endl;
            return -1;
        }

        // Set gain; gain recorded in decibels
        CFloatPtr ptrGain = nodeMap.GetNode("Gain");
        if (!IsAvailable(ptrGain) || !IsWritable(ptrGain))
        {
            cout << "[WARN] Unable to set gain (node retrieval). Using default ..." << endl;
        }
        else
        {
            double gainMax = ptrGain->GetMax();
            double gainToSet = ptrGain->GetMin( );
            ptrGain->SetValue(gainToSet);
        }

#endif

        /*-----------------------------------------------------------------------------
         *  IMAGE ACQUISITION
         *-----------------------------------------------------------------------------*/
        result = AcquireImages(pCam, nodeMap, nodeMapTLDevice, socket );

        // Reset settings.
        ResetExposure( nodeMap );

        // Deinitialize camera
        pCam->DeInit();
    }
    catch (Spinnaker::Exception &e)
    {
        cout << "Error: " << e.what() << endl;
        result = -1;
    }

    return result;
}

// Example entry point; please see Enumeration example for more in-depth
// comments on preparing and cleaning up the system.
int main(int /*argc*/, char** /*argv*/)
{
    int result = 0;

    // Print application build information
    cout << "Application build date: " << __DATE__ << " " << __TIME__ << endl << endl;

    // Retrieve singleton reference to system object
    system_ = System::GetInstance();
    if( system_->IsInUse( ) )
    {
        cout << "Warn: Camera is already in use. Reattach and continue";
        exit( -1 );
    }

    // Retrieve list of cameras from the system
    cam_list_ = system_->GetCameras();

    unsigned int numCameras = cam_list_.GetSize();

    cout << "Number of cameras detected: " << numCameras << endl << endl;

    // Finish if there are no cameras
    if (numCameras == 0)
    {
        // Clear camera list before releasing system_
        cam_list_.Clear();

        // Release system_
        system_->ReleaseInstance();
        cout << "Not enough cameras! Existing ..." << endl;
        return -1;
    }

    CameraPtr pCam = NULL;

    // Since there are enough camera lets initialize socket to write acquired
    // frames.

    socket_ = create_socket( true );

    pCam = cam_list_.GetByIndex( 0 );

    // Configure camera here.
    // configure_camera( pCam );
    result = RunSingleCamera(pCam, socket_);


    pCam = NULL;
    // Clear camera list before releasing system_
    cam_list_.Clear();

    // Release system_
    system_->ReleaseInstance();
    std::cout << "All done" << std::endl;

    if( socket_ > 0 )
        close( socket_ );

    return 0;
}
