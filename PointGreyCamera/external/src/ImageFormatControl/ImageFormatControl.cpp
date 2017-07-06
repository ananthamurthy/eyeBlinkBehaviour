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
 *  @example ImageFormatControl.cpp
 *
 *  @brief ImageFormatControl.cpp shows how to apply custom image settings to 
 *	the camera. It relies on information provided in the Enumeration, 
 *	Acquisition, and NodeMapInfo examples.
 *
 *	This example demonstrates setting minimums to offsets, X and Y, and maximums 
 *	to width and height. It also shows the setting of a new pixel format, which 
 *	is an enumeration type node.
 *
 *	Following this, we suggest familiarizing yourself with the Exposure example 
 *	if you haven't already. Exposure is another example on camera customization 
 *	that is shorter and simpler than many of the others. Once comfortable with 
 *	Exposure and ImageFormatControl, we suggest checking out any of the longer, 
 *	more complicated examples related to camera configuration: ChunkData, 
 *	LookupTable, Sequencer, or Trigger.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// This function configures a number of settings on the camera including offsets 
// X and Y, width, height, and pixel format. These settings must be applied before
// BeginAcquisition() is called; otherwise, they will be read only. Also, it is
// important to note that settings are applied immediately. This means if you plan
// to reduce the width and move the x offset accordingly, you need to apply such
// changes in the appropriate order.
int ConfigureCustomImageSettings(INodeMap & nodeMap)
{
	int result = 0;

	cout << endl << endl << "*** CONFIGURING CUSTOM IMAGE SETTINGS ***" << endl << endl;

	try
	{
		//
		// Apply mono 8 pixel format
		//
		// *** NOTES ***
		// Enumeration nodes are slightly more complicated to set than other
		// nodes. This is because setting an enumeration node requires working
		// with two nodes instead of the usual one. 
		//
		// As such, there are a number of steps to setting an enumeration node: 
		// retrieve the enumeration node from the nodemap, retrieve the desired 
		// entry node from the enumeration node, retrieve the integer value from 
		// the entry node, and set the new value of the enumeration node with
		// the integer value from the entry node.
		//
		// Retrieve the enumeration node from the nodemap
		CEnumerationPtr ptrPixelFormat = nodeMap.GetNode("PixelFormat");
		if (IsAvailable(ptrPixelFormat) && IsWritable(ptrPixelFormat))
		{
			// Retrieve the desired entry node from the enumeration node
			CEnumEntryPtr ptrPixelFormatMono8 = ptrPixelFormat->GetEntryByName("Mono8");
			if (IsAvailable(ptrPixelFormatMono8) && IsReadable(ptrPixelFormatMono8))
			{
				// Retrieve the integer value from the entry node
				int64_t pixelFormatMono8 = ptrPixelFormatMono8->GetValue();

				// Set integer as new value for enumeration node
				ptrPixelFormat->SetIntValue(pixelFormatMono8);

				cout << "Pixel format set to " << ptrPixelFormat->GetCurrentEntry()->GetSymbolic() << "..." << endl;
			}
			else
			{
				cout << "Pixel format mono 8 not available..." << endl;
			}
		}
		else
		{
			cout << "Pixel format not available..." << endl;
		}

		// 
		// Apply minimum to offset X
		//
		// *** NOTES ***
		// Numeric nodes have both a minimum and maximum. A minimum is retrieved
		// with the method GetMin(). Sometimes it can be important to check 
		// minimums to ensure that your desired value is within range.
		//
		CIntegerPtr ptrOffsetX = nodeMap.GetNode("OffsetX");
		if (IsAvailable(ptrOffsetX) && IsWritable(ptrOffsetX))
		{
			ptrOffsetX->SetValue(ptrOffsetX->GetMin());
			cout << "Offset X set to " << ptrOffsetX->GetMin() << "..." << endl;
		}
		else
		{
			cout << "Offset X not available..." << endl;
		}

		//
		// Apply minimum to offset Y
		// 
		// *** NOTES ***
		// It is often desirable to check the increment as well. The increment
		// is a number of which a desired value must be a multiple of. Certain
		// nodes, such as those corresponding to offsets X and Y, have an
		// increment of 1, which basically means that any value within range
		// is appropriate. The increment is retrieved with the method GetInc().
		//
		CIntegerPtr ptrOffsetY = nodeMap.GetNode("OffsetY");
		if (IsAvailable(ptrOffsetY) && IsWritable(ptrOffsetY))
		{
			ptrOffsetY->SetValue(ptrOffsetY->GetMin());
			cout << "Offset Y set to " << ptrOffsetY->GetValue() << "..." << endl;
		}
		else
		{
			cout << "Offset Y not available..." << endl;
		}

		//
		// Set maximum width
		//
		// *** NOTES ***
		// Other nodes, such as those corresponding to image width and height, 
		// might have an increment other than 1. In these cases, it can be
		// important to check that the desired value is a multiple of the
		// increment. However, as these values are being set to the maximum,
		// there is no reason to check against the increment.
		//
		CIntegerPtr ptrWidth = nodeMap.GetNode("Width");
		if (IsAvailable(ptrWidth) && IsWritable(ptrWidth))
		{
			int64_t widthToSet = ptrWidth->GetMax();

			ptrWidth->SetValue(widthToSet);

			cout << "Width set to " << ptrWidth->GetValue() << "..." << endl;
		}
		else
		{
			cout << "Width not available..." << endl;
		}

		//
		// Set maximum height
		//
		// *** NOTES ***
		// A maximum is retrieved with the method GetMax(). A node's minimum and
		// maximum should always be a multiple of its increment.
		//
		CIntegerPtr ptrHeight = nodeMap.GetNode("Height");
		if (IsAvailable(ptrHeight) && IsWritable(ptrHeight))
		{
			int64_t heightToSet = ptrHeight->GetMax();

			ptrHeight->SetValue(heightToSet);

			cout << "Height set to " << ptrHeight->GetValue() << "..." << endl << endl;
		}
		else
		{
			cout << "Height not available..." << endl << endl;
		}
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
		const unsigned int k_numImages = 10;

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
					ImagePtr convertedImage = pResultImage->Convert(PixelFormat_Mono8, HQ_LINEAR);

					// Create a unique filename
					ostringstream filename;

					filename << "ImageFormatControl-";
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

		// Configure custom image settings
		err = ConfigureCustomImageSettings(nodeMap);
		if (err < 0)
		{
			return err;
		}

		// Acquire images
		result = result | AcquireImages(pCam, nodeMap, nodeMapTLDevice);

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

// Example entry point; please see Enumeration example for additional 
// comments on the steps in this function.
int main(int /*argc*/, char** /*argv*/)
{
	int result = 0;

	// Print Application Build Information
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
		// Release camera list before releasing system
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

	// Release camera list before releasing system
	camList.Clear();

	// Release system
	system->ReleaseInstance();

	cout << endl << "Done! Press Enter to exit..." << endl;
	getchar();

	return result;
}
