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
 *  @example Trigger_QuickSpin.cpp
 *
 *	@brief Trigger_QuickSpin.cpp shows how to capture images with the 
 *  trigger using the QuickSpin API. QuickSpin is a subset of the Spinnaker
 *  library that allows for simpler node access and control.
 *
 *  This example demonstrates how to prepare, execute, and clean up the camera
 *  in regards to using both software and hardware triggers. Retrieving and
 *  setting node values using QuickSpin is the only portion of the example
 *  that differs from Trigger.
 *
 *	A much wider range of topics is covered in the full Spinnaker examples than
 *	in the QuickSpin ones. There are only enough QuickSpin examples to
 *	demonstrate node access and to get started with the API; please see full
 *	Spinnaker examples for further or specific knowledge on a topic.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// Use the following enum and global static variable to select whether a 
// software or hardware trigger is used.
enum triggerType
{
	SOFTWARE,
	HARDWARE
};

const triggerType chosenTrigger = SOFTWARE;

// This function configures the camera to use a trigger. First, trigger mode is 
// ensured to be off in order to select the trigger source. Trigger mode is 
// then enabled, which has the camera capture only a single image upon the 
// execution of the chosen trigger.
int ConfigureTrigger(CameraPtr pCam)
{
	int result = 0;

	cout << endl << endl << "*** CONFIGURING TRIGGER ***" << endl << endl;

	try
	{
		if (chosenTrigger == SOFTWARE)
		{
			cout << "Software trigger chosen..." << endl;
		}
		else
		{
			cout << "Hardware trigger chosen..." << endl;
		}

		//
		// Ensure trigger mode off
		//
		// *** NOTES ***
		// The trigger must be disabled in order to configure whether the source
		// is software or hardware.
		//
		if (pCam->TriggerMode == NULL || pCam->TriggerMode.GetAccessMode() != RW)
		{
			cout << "Unable to disable trigger mode. Aborting..." << endl;
			return -1;
		}

		pCam->TriggerMode.SetValue(TriggerMode_Off);

		cout << "Trigger mode disabled..." << endl;

		//
		// Select trigger source
		//
		// *** NOTES ***
		// The trigger source must be set to hardware or software while trigger 
		// mode is off.
		//
		if (chosenTrigger == SOFTWARE)
		{
			// Set the trigger source to software
			if (pCam->TriggerSource == NULL || pCam->TriggerSource.GetAccessMode() != RW)
			{
				cout << "Unable to set trigger mode (node retrieval). Aborting..." << endl;
				return -1;
			}

			pCam->TriggerSource.SetValue(TriggerSource_Software);

			cout << "Trigger source set to software..." << endl;
		}
		else
		{
			// Set the trigger source to hardware (using 'Line0')
			if (pCam->TriggerSource == NULL || pCam->TriggerSource.GetAccessMode() != RW)
			{
				cout << "Unable to set trigger mode (node retrieval). Aborting..." << endl;
				return -1;
			}

			pCam->TriggerSource.SetValue(TriggerSource_Line0);

			cout << "Trigger source set to hardware..." << endl;
		}

		//
		// Turn trigger mode on
		//
		// *** LATER ***
		// Once the appropriate trigger source has been set, turn trigger mode 
		// back on in order to retrieve images using the trigger.
		//
		if (pCam->TriggerMode == NULL || pCam->TriggerMode.GetAccessMode() != RW)
		{
			cout << "Unable to disable trigger mode. Aborting..." << endl;
			return -1;
		}

		pCam->TriggerMode.SetValue(TriggerMode_On);

		cout << "Trigger mode turned back on..." << endl << endl;
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function retrieves a single image using the trigger. In this example, 
// only a single image is captured and made available for acquisition - as such,
// attempting to acquire two images for a single trigger execution would cause 
// the example to hang. This is different from other examples, whereby a 
// constant stream of images are being captured and made available for image
// acquisition.
int GrabNextImageByTrigger(CameraPtr pCam, ImagePtr & pResultImage)
{
	int result = 0;

	try
	{
		// 
		// Use trigger to capture image
		//
		// *** NOTES ***
		// The software trigger only feigns being executed by the Enter key;
		// what might not be immediately apparent is that there is no 
		// continuous stream of images being captured; in other examples that 
		// acquire images, the camera captures a continuous stream of images. 
		// When an image is then retrieved, it is plucked from the stream; 
		// there are many more images captured than retrieved. However, while 
		// trigger mode is activated, there is only a single image captured at 
		// the time that the trigger is activated. 
		//
		if (chosenTrigger == SOFTWARE)
		{
			// Get user input
			cout << "Press the Enter key to initiate software trigger." << endl;
			getchar();

			// Execute software trigger
			if (pCam->TriggerSoftware == NULL || pCam->TriggerSoftware.GetAccessMode() != WO)
			{
				cout << "Unable to execute trigger..." << endl;
				return -1;
			}

			pCam->TriggerSoftware.Execute();
		}
		else
		{
			cout << "Use the hardware to trigger image acquisition." << endl;
		}

		// Retrieve the next received image
		pResultImage = pCam->GetNextImage();
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function returns the camera to a normal state by turning off trigger 
// mode.
int ResetTrigger(CameraPtr pCam)
{
	int result = 0;

	try
	{
		//
		// Turn trigger mode back off
		//
		// *** NOTES ***
		// Once all images have been captured, it is important to turn trigger
		// mode back off to restore the camera to a clean state.
		//
		if (pCam->TriggerMode == NULL || pCam->TriggerMode.GetAccessMode() != RW)
		{
			cout << "Unable to disable trigger mode. Aborting..." << endl;
			return -1;
		}

		pCam->TriggerMode.SetValue(TriggerMode_Off);

		cout << "Trigger mode disabled..." << endl << endl;
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

		if (pCam->DeviceSerialNumber != NULL && pCam->DeviceSerialNumber.GetAccessMode() == RO)
		{
			deviceSerialNumber = pCam->DeviceSerialNumber.GetValue();

			cout << "Device serial number retrieved as " << deviceSerialNumber << "..." << endl;
		}
		cout << endl;

		// Retrieve, convert, and save images
		const int k_numImages = 10;

		for (unsigned int imageCnt = 0; imageCnt < k_numImages; imageCnt++)
		{
			try
			{
				// Retrieve next image by trigger
				ImagePtr pResultImage = NULL;

				result = result | GrabNextImageByTrigger(pCam, pResultImage);

				// Ensure image completion
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

					filename << "TriggerQS-";
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

	try
	{
		// Initialize camera
		pCam->Init();

		// Print device info
		result = PrintDeviceInfo(pCam);

		// Configure trigger
		result = result | ConfigureTrigger(pCam);

		// Acquire images
		result = result | AcquireImages(pCam);

		// Reset trigger
		result = result | ResetTrigger(pCam);

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