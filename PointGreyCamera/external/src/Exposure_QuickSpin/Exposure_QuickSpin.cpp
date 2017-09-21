//=============================================================================
// Copyright © 2015 Point Grey Research, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of 
// Point Grey Research, Inc. ("Confidential Information"). You shall not
// disclose such Confidential Information and shall use it only in 
// accordance with the terms of the "License Agreement" that you 
// entered into with PGR in connection with this software.
//
// UNLESS OTHERWISE SET OUT IN THE LICENSE AGREEMENT, THIS SOFTWARE IS 
// PROVIDED ON AN “AS-IS” BASIS AND POINT GREY RESEARCH INC. MAKES NO 
// REPRESENTATIONS OR WARRANTIES ABOUT THE SOFTWARE, EITHER EXPRESS 
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO ANY IMPLIED WARRANTIES OR 
// CONDITIONS OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR 
// NON-INFRINGEMENT. POINT GREY RESEARCH INC. SHALL NOT BE LIABLE FOR ANY 
// DAMAGES, INCLUDING BUT NOT LIMITED TO ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, PUNITIVE, OR CONSEQUENTIAL DAMAGES, OR ANY LOSS OF PROFITS, 
// REVENUE, DATA OR DATA USE, ARISING OUT OF OR IN CONNECTION WITH THIS 
// SOFTWARE OR OTHERWISE SUFFERED BY YOU AS A RESULT OF USING, MODIFYING 
// OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

/**
 *	@example Exposure_QuickSpin.cpp
 *
 *	@brief Exposure_QuickSpin.cpp shows how to customize image exposure time 
 *	using the QuickSpin API. QuickSpin is a subset of the Spinnaker library
 *	that allows for simpler node access and control. 
 *
 *  This example prepares the camera, sets a new exposure time, and restores
 *  the camera to its default state. Ensure custom values fall within an
 *  acceptable range is also touched on. Retrieving and setting information
 *  is the only portion of hte example that differs from Exposure.
 *
 *  A much wider range of topics is covered in the full Spinnaker examples than
 *  in the QuickSpin ones. There are only enough QuickSpin examples to 
 *  demonstrate node access and to get started with the API; please see full
 *  Spinnaker examples for further or specific knowledge on a topic.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// This function configures a custom exposure time. Automatic exposure is turned 
// off in order to allow for the customization, and then the custom setting is 
// applied.
int ConfigureExposure(CameraPtr pCam)
{
	int result = 0;

	cout << endl << endl << "*** CONFIGURING EXPOSURE ***" << endl << endl;

	try
	{
		//
		// Turn off automatic exposure mode
		//
		// *** NOTES ***
		// Automatic exposure prevents the manual configuration of exposure 
		// times and needs to be turned off for this example. Enumerations
		// representing entry nodes have been added to QuickSpin. This allows
		// for the much easier setting of enumeration nodes to new values.
		// 
		// In C++, the naming convention of QuickSpin enums is the name of the
		// enumeration node followed by an underscore and the symbolic of
		// the entry node. Selecting "Off" on the "ExposureAuto" node is
		// thus named "ExposureAuto_Off".
		//
		// *** LATER ***
		// Exposure time can be set automatically or manually as needed. This
		// example turns automatic exposure off to set it manually and back
		// on to return the camera to its default state.
		//
		if (pCam->ExposureAuto == NULL || pCam->ExposureAuto.GetAccessMode() != RW)
		{
			cout << "Unable to disable automatic exposure. Aborting..." << endl << endl;
			return -1;
		}

		pCam->ExposureAuto.SetValue(ExposureAuto_Off);

		cout << "Automatic exposure disabled..." << endl;

		//
		// Set exposure time manually; exposure time recorded in microseconds
		//
		// *** NOTES ***
		// Notice that the node is checked for availability and writability
		// prior to the setting of the node. In QuickSpin, availability is
		// ensured by checking for null while writability is ensured by checking
		// the access mode. 
		//
		// Further, it is ensured that the desired exposure time does not exceed 
		// the maximum. Exposure time is counted in microseconds - this can be 
		// found out either by retrieving the unit with the GetUnit() method or 
		// by checking SpinView.
		// 
		if (pCam->ExposureTime == NULL || pCam->ExposureTime.GetAccessMode() != RW)
		{
			cout << "Unable to set exposure time. Aborting..." << endl << endl;
			return -1;
		}

		// Ensure desired exposure time does not exceed the maximum
		const double exposureTimeMax = pCam->ExposureTime.GetMax();
		double exposureTimeToSet = 2000000.0;

		if (exposureTimeToSet > exposureTimeMax)
		{
			exposureTimeToSet = exposureTimeMax;
		}

		pCam->ExposureTime.SetValue(exposureTimeToSet);

		cout << "Shutter time set to " << exposureTimeToSet << " us..." << endl << endl;
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function returns the camera to a normal state by re-enabling automatic
// exposure.
int ResetExposure(CameraPtr pCam)
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
		if (pCam->ExposureAuto == NULL || pCam->ExposureAuto.GetAccessMode() != RW)
		{
			cout << "Unable to enable automatic exposure (node retrieval). Non-fatal error..." << endl << endl;
			return -1;
		}

		pCam->ExposureAuto.SetValue(ExposureAuto_Continuous);

		cout << "Automatic exposure enabled..." << endl << endl;
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
int PrintDeviceInfo(CameraPtr pCam)
{
	int result = 0;

	cout << endl << "*** DEVICE INFORMATION ***" << endl << endl;

	try
	{
		INodeMap & nodeMap = pCam->GetTLDeviceNodeMap();

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

// This function acquires and saves 10 images from a device; please see
// Acquisition example for more in-depth comments on the acquisition of images.
int AcquireImages(CameraPtr pCam)
{
	int result = 0;

	cout << endl << "*** IMAGE ACQUISITION ***" << endl << endl;

	try
	{
		// Set acquisition mode to continuous
		if (pCam->AcquisitionMode == NULL || pCam->AcquisitionMode.GetAccessMode() != RW)
		{
			cout << "Unable to set acquisition mode to continuous. Aborting..." << endl << endl;
			return -1;
		}

		pCam->AcquisitionMode.SetValue(AcquisitionMode_Continuous);

		cout << "Acquisition mode set to continuous..." << endl;
	
		// Begin acquiring images
		pCam->BeginAcquisition();

		cout << "Acquiring images..." << endl;

		// Get device serial number for filename
		gcstring deviceSerialNumber("");
		
		if (pCam->TLDevice.DeviceSerialNumber != NULL && pCam->TLDevice.DeviceSerialNumber.GetAccessMode() == RO)
		{
			deviceSerialNumber = pCam->TLDevice.DeviceSerialNumber.GetValue();

			cout << "Device serial number retrieved as " << deviceSerialNumber << "..." << endl;
		}
		cout << endl;
		
		// Retrieve, convert, and save images
		const int k_numImages = 5;

		for (unsigned int imageCnt = 0; imageCnt < k_numImages; imageCnt++)
		{
			try
			{
				// Retrieve next received image and ensure image completion
				ImagePtr pResultImage = pCam->GetNextImage();

				if (pResultImage->IsIncomplete())
				{
					cout << "Image incomplete with image status " << pResultImage->GetImageStatus() << "..." << endl << endl;
				}
				else
				{
					// Print image information
					cout << "Grabbed image " << imageCnt << ", width = " << pResultImage->GetWidth() << ", height = " << pResultImage->GetHeight() << endl;

					// Convert image to mono 8
					ImagePtr convertedImage = pResultImage->Convert(PixelFormat_Mono8);

					// Create a unique filename
					ostringstream filename;

					filename << "ExposureQS-";
					if (deviceSerialNumber != "")
					{
						filename << deviceSerialNumber.c_str() << "-";
					}
					filename << imageCnt << ".jpg";

					// Save image
					convertedImage->Save(filename.str().c_str());

					cout << "Image saved at " << filename.str() << endl;
				}

				// Release image
				pResultImage->Release();

				cout << endl;
			}
			catch (Spinnaker::Exception &e)
			{
				cout << "Error: " << e.what() << endl;
				result = -1;
			}
		}

		// End acquisition
		pCam->EndAcquisition();
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function acts as the body of the example; please see 
// NodeMapInfo_QuickSpin example for more in-depth comments on setting 
// up cameras.
int RunSingleCamera(CameraPtr pCam)
{
	int result = 0;
	int err = 0;

	try
	{
		// Initialize camera
		pCam->Init();

		// Print device info
		result = PrintDeviceInfo(pCam);

		// Configure exposure
		err = ConfigureExposure(pCam);
		if (err < 0)
		{
			return err;
		}

		// Acquire images
		result = result | AcquireImages(pCam);

		// Reset exposure
		result = result | ResetExposure(pCam);

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

// Example entry point; please see Enumeration_QuickSpin example for more 
// in-depth comments on preparing and cleaning up the system.
int main(int /*argc*/, char** /*argv*/)
{
	int result = 0;

	// Print application build information
	cout << "Application build date: " << __DATE__ << " " << __TIME__ << endl << endl;

	// Retrieve singleton reference to system object
	SystemPtr system = System::GetInstance();

	// Retrieve list of cameras from the system
	CameraList camList = system->GetCameras();

	unsigned int numCameras = camList.GetSize();

	cout << "Number of cameras detected: " << numCameras << endl << endl;

	// Finish if there are no cameras
	if (numCameras == 0)
	{
		// Clear camera list before releasing system
		camList.Clear();

		// Release system
		system->ReleaseInstance();

		cout << "Not enough cameras!" << endl;
		cout << "Done! Press Enter to exit..." << endl;
		getchar();

		return -1;
	}

	// Run example on each camera
	for (unsigned int i = 0; i < numCameras; i++)
	{
		cout << endl << "Running example for camera " << i << "..." << endl;

		result = result | RunSingleCamera(camList.GetByIndex(i));

		cout << "Camera " << i << " example complete..." << endl << endl;
	}

	// Clear camera list before releasing system
	camList.Clear();

	// Release system
	system->ReleaseInstance();

	cout << endl << "Done! Press Enter to exit..." << endl;
	getchar();

	return result;
}
