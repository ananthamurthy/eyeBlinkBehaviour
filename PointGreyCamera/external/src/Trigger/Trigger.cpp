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
 *  @example Trigger.cpp
 *
 *  @brief Trigger.cpp shows how to trigger the camera. It relies on information 
 *	provided in the Enumeration, Acquisition, and NodeMapInfo examples.
 *
 *	It can also be helpful to familiarize yourself with the ImageFormatControl 
 *	and Exposure examples. As they are somewhat shorter and simpler, either 
 *	provides a strong introduction to camera customization.
 *
 *	This example shows the process of configuring, using, and cleaning up a 
 *	camera for use with both a software and a hardware trigger. 
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// Use the following enum and global constant to select whether a software or
// hardware trigger is used.
enum triggerType
{
	SOFTWARE,
	HARDWARE
};

const triggerType chosenTrigger = SOFTWARE;

// This function configures the camera to use a trigger. First, trigger mode is 
// set to off in order to select the trigger source. Once the trigger source
// has been selected, trigger mode is then enabled, which has the camera 
// capture only a single image upon the execution of the chosen trigger.
int ConfigureTrigger(INodeMap & nodeMap)
{
	int result = 0;

	cout << endl << endl << "*** CONFIGURING TRIGGER ***" << endl << endl;

	if (chosenTrigger == SOFTWARE)
	{
		cout << "Software trigger chosen..." << endl;
	}
	else if (chosenTrigger == HARDWARE)
	{
		cout << "Hardware trigger chosen..." << endl;
	}

	try
	{
		//
		// Ensure trigger mode off
		//
		// *** NOTES ***
		// The trigger must be disabled in order to configure whether the source
		// is software or hardware.
		//
		CEnumerationPtr ptrTriggerMode = nodeMap.GetNode("TriggerMode");
		if (!IsAvailable(ptrTriggerMode) || !IsReadable(ptrTriggerMode))
		{
			cout << "Unable to disable trigger mode (node retrieval). Aborting..." << endl;
			return -1;
		}
		
		CEnumEntryPtr ptrTriggerModeOff = ptrTriggerMode->GetEntryByName("Off");
		if (!IsAvailable(ptrTriggerModeOff) || !IsReadable(ptrTriggerModeOff))
		{
			cout << "Unable to disable trigger mode (enum entry retrieval). Aborting..." << endl;
			return -1;
		}
		
		ptrTriggerMode->SetIntValue(ptrTriggerModeOff->GetValue());
		
		cout << "Trigger mode disabled..." << endl;

		//
		// Select trigger source
		//
		// *** NOTES ***
		// The trigger source must be set to hardware or software while trigger 
		// mode is off.
		//
		CEnumerationPtr ptrTriggerSource = nodeMap.GetNode("TriggerSource");
		if (!IsAvailable(ptrTriggerSource) || !IsWritable(ptrTriggerSource))
		{
			cout << "Unable to set trigger mode (node retrieval). Aborting..." << endl;
			return -1;
		}

		if (chosenTrigger == SOFTWARE)
		{
			// Set trigger mode to software
			CEnumEntryPtr ptrTriggerSourceSoftware = ptrTriggerSource->GetEntryByName("Software");
			if (!IsAvailable(ptrTriggerSourceSoftware) || !IsReadable(ptrTriggerSourceSoftware))
			{
				cout << "Unable to set trigger mode (enum entry retrieval). Aborting..." << endl;
				return -1;
			}
			
			ptrTriggerSource->SetIntValue(ptrTriggerSourceSoftware->GetValue());
			
			cout << "Trigger source set to software..." << endl;
		}
		else if (chosenTrigger == HARDWARE)
		{
			// Set trigger mode to hardware ('Line0')
			CEnumEntryPtr ptrTriggerSourceHardware = ptrTriggerSource->GetEntryByName("Line0");
			if (!IsAvailable(ptrTriggerSourceHardware) || !IsReadable(ptrTriggerSourceHardware))
			{
				cout << "Unable to set trigger mode (enum entry retrieval). Aborting..." << endl;
				return -1;
			}
			
			ptrTriggerSource->SetIntValue(ptrTriggerSourceHardware->GetValue());
			
			cout << "Trigger source set to hardware..." << endl;
		}

		//
		// Turn trigger mode on
		//
		// *** LATER ***
		// Once the appropriate trigger source has been set, turn trigger mode 
		// on in order to retrieve images using the trigger.
		//
		CEnumEntryPtr ptrTriggerModeOn = ptrTriggerMode->GetEntryByName("On");
		if (!IsAvailable(ptrTriggerModeOn) || !IsReadable(ptrTriggerModeOn))
		{
			cout << "Unable to enable trigger mode (enum entry retrieval). Aborting..." << endl;
			return -1;
		}
		
		ptrTriggerMode->SetIntValue(ptrTriggerModeOn->GetValue());
		
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
int GrabNextImageByTrigger(INodeMap & nodeMap, CameraPtr pCam)
{
	int result = 0;

	try
	{
		// 
		// Use trigger to capture image
		//
		// *** NOTES ***
		// The software trigger only feigns being executed by the Enter key;
		// what might not be immediately apparent is that there is not a
		// continuous stream of images being captured; in other examples that 
		// acquire images, the camera captures a continuous stream of images. 
		// When an image is retrieved, it is plucked from the stream.
		//
		if (chosenTrigger == SOFTWARE)
		{
			// Get user input
			cout << "Press the Enter key to initiate software trigger." << endl;
			getchar();

			// Execute software trigger
			CCommandPtr ptrSoftwareTriggerCommand = nodeMap.GetNode("TriggerSoftware");
			if (!IsAvailable(ptrSoftwareTriggerCommand) || !IsWritable(ptrSoftwareTriggerCommand))
			{
				cout << "Unable to execute trigger. Aborting..." << endl;
				return -1;
			}

			ptrSoftwareTriggerCommand->Execute();
		}
		else if (chosenTrigger == HARDWARE)
		{
			// Execute hardware trigger
			cout << "Use the hardware to trigger image acquisition." << endl;
		}
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
int ResetTrigger(INodeMap & nodeMap)
{
	int result = 0;

	try
	{
		//
		// Turn trigger mode back off
		//
		// *** NOTES ***
		// Once all images have been captured, turn trigger mode back off to
		// restore the camera to a clean state.
		//
		CEnumerationPtr ptrTriggerMode = nodeMap.GetNode("TriggerMode");
		if (!IsAvailable(ptrTriggerMode) || !IsReadable(ptrTriggerMode))
		{
			cout << "Unable to disable trigger mode (node retrieval). Non-fatal error..." << endl;
			return -1;
		}

		CEnumEntryPtr ptrTriggerModeOff = ptrTriggerMode->GetEntryByName("Off");
		if (!IsAvailable(ptrTriggerModeOff) || !IsReadable(ptrTriggerModeOff))
		{
			cout << "Unable to disable trigger mode (enum entry retrieval). Non-fatal error..." << endl;
			return -1;
		}

		ptrTriggerMode->SetIntValue(ptrTriggerModeOff->GetValue());

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

// This function acquires and saves 10 images from a device; please see
// Acquisition example for more in-depth comments on acquiring images.
int AcquireImages(CameraPtr pCam, INodeMap & nodeMap, INodeMap & nodeMapTLDevice)
{
	int result = 0;

	cout << endl << "*** IMAGE ACQUISITION ***" << endl << endl;

	try
	{
		// Set acquisition mode to continuous
		CEnumerationPtr ptrAcquisitionMode = nodeMap.GetNode("AcquisitionMode");
		if (!IsAvailable(ptrAcquisitionMode) || !IsWritable(ptrAcquisitionMode))
		{
			cout << "Unable to set acquisition mode to continuous (node retrieval). Aborting..." << endl << endl;
			return -1;
		}

		CEnumEntryPtr ptrAcquisitionModeContinuous = ptrAcquisitionMode->GetEntryByName("Continuous");
		if (!IsAvailable(ptrAcquisitionModeContinuous) || !IsReadable(ptrAcquisitionModeContinuous))
		{
			cout << "Unable to set acquisition mode to continuous (entry 'continuous' retrieval). Aborting..." << endl << endl;
			return -1;
		}

		int64_t acquisitionModeContinuous = ptrAcquisitionModeContinuous->GetValue();

		ptrAcquisitionMode->SetIntValue(acquisitionModeContinuous);

		cout << "Acquisition mode set to continuous..." << endl;

		// Begin acquiring images
		pCam->BeginAcquisition();

		cout << "Acquiring images..." << endl;

		// Retrieve device serial number for filename
		gcstring deviceSerialNumber("");

		CStringPtr ptrStringSerial = nodeMapTLDevice.GetNode("DeviceSerialNumber");
		if (IsAvailable(ptrStringSerial) && IsReadable(ptrStringSerial))
		{
			deviceSerialNumber = ptrStringSerial->GetValue();

			cout << "Device serial number retrieved as " << deviceSerialNumber << "..." << endl;
		}
		cout << endl;

		// Retrieve, convert, and save images
		const int unsigned k_numImages = 10;

		for (unsigned int imageCnt = 0; imageCnt < k_numImages; imageCnt++)
		{
			try
			{
				// Retrieve the next image from the trigger
				result = result | GrabNextImageByTrigger(nodeMap, pCam);

				// Retrieve the next received image
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
					ImagePtr convertedImage = pResultImage->Convert(PixelFormat_Mono8, HQ_LINEAR);

					// Create a unique filename
					ostringstream filename;

					filename << "Trigger-";
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

// This function acts as the body of the example; please see NodeMapInfo example 
// for more in-depth comments on setting up cameras.
int RunSingleCamera(CameraPtr pCam)
{
	int result = 0;
	int err = 0;

	try
	{
		// Retrieve TL device nodemap and print device information
		INodeMap & nodeMapTLDevice = pCam->GetTLDeviceNodeMap();

		result = PrintDeviceInfo(nodeMapTLDevice);
		
		// Initialize camera
		pCam->Init();

		// Retrieve GenICam nodemap
		INodeMap & nodeMap = pCam->GetNodeMap();

		// Configure trigger
		err = ConfigureTrigger(nodeMap);
		if (err < 0)
		{
			return err;
		}

		// Acquire images
		result = result | AcquireImages(pCam, nodeMap, nodeMapTLDevice);

		// Reset trigger
		result = result | ResetTrigger(nodeMap);

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

