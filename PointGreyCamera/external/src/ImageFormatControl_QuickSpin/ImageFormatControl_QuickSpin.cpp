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
 *  @example ImageFormatControl_QuickSpin.cpp
 *
 *  @brief ImageFormatControl_QuickSpin.cpp shows how to apply custom image 
 *	settings to the camera using the QuickSpin API. QuickSpin is a subset of 
 *	the Spinnaker library that allows for simpler node access and control.
 *
 *	This example demonstrates customizing offsets X and Y, width and height, 
 *	and the pixel format. Ensuring custom values fall within an acceptable
 *	range is also touched on. Retrieving and setting node values using
 *	QuickSpin is the only portion of the example that differs from
 *	ImageFormatControl.
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

// This function configures a number of settings on the camera including 
// offsets X and Y, width, height, and pixel format. These settings must be 
// applied before spinCameraBeginAcquisition() is called; otherwise, those 
// nodes would be read only. Also, it is important to note that settings are 
// applied immediately. This means if you plan to reduce the width and move 
// the x offset accordingly, you need to apply such changes in the appropriate 
// order.
int ConfigureCustomImageSettings(CameraPtr pCam)
{
	int result = 0;

	cout << endl << endl << "*** CONFIGURING CUSTOM IMAGE SETTINGS ***" << endl << endl;

	try
	{
		//
		// Apply mono 8 pixel format
		//
		// *** NOTES ***
		// In QuickSpin, enumeration nodes are as easy to set as other node
		// types. This is because enum values representing each entry node
		// are added to the API.
		//
		if (pCam->PixelFormat != NULL && pCam->PixelFormat.GetAccessMode() == RW)
		{
			pCam->PixelFormat.SetValue(PixelFormat_Mono8);

			cout << "Pixel format set to " << pCam->PixelFormat.GetCurrentEntry()->GetSymbolic() << "..." << endl;
		}
		else
		{
			cout << "Pixel format not available..." << endl;
			result = -1;
		}

		// 
		// Apply minimum to offset X
		//
		// *** NOTES ***
		// Numeric nodes have both a minimum and maximum. A minimum is retrieved
		// with the method GetMin(). Sometimes it can be important to check 
		// minimums to ensure that your desired value is within range.
		//
		if (pCam->OffsetX != NULL && pCam->OffsetX.GetAccessMode() == RW) 
		{
			pCam->OffsetX.SetValue(pCam->OffsetX.GetMin());
			
			cout << "Offset X set to " << pCam->OffsetX.GetValue() << "..." << endl;
		}
		else
		{
			cout << "Offset X not available..." << endl;
			result = -1;
		}

		//
		// Apply minimum to offset Y
		// 
		// *** NOTES ***
		// It is often desirable to check the increment as well. The increment
		// is a number of which a desired value must be a multiple. Certain
		// nodes, such as those corresponding to offsets X and Y, have an
		// increment of 1, which basically means that any value within range
		// is appropriate. The increment is retrieved with the method GetInc().
		//
		if (pCam->OffsetY != NULL && pCam->OffsetY.GetAccessMode() == RW)
		{
			pCam->OffsetY.SetValue(pCam->OffsetY.GetMin());
			
			cout << "Offset Y set to " << pCam->OffsetY.GetValue() << "..." << endl;
		}
		else
		{
			cout << "Offset Y not available..." << endl;
			result = -1;
		}

		//
		// Set maximum width
		//
		// *** NOTES ***
		// Other nodes, such as those corresponding to image width and height, 
		// might have an increment other than 1. In these cases, it can be
		// important to check that the desired value is a multiple of the
		// increment. 
		//
		// This is often the case for width and height nodes. However, because
		// these nodes are being set to their maximums, there is no real reason
		// to check against the increment.
		//
		if (pCam->Width != NULL && pCam->Width.GetAccessMode() == RW && pCam->Width.GetInc() != 0 && pCam->Width.GetMax() != 0)
		{
			pCam->Width.SetValue(pCam->Width.GetMax());

			cout << "Width set to " << pCam->Width.GetValue() << "..." << endl;
		}
		else
		{
			cout << "Width not available..." << endl;
			result = -1;
		}

		//
		// Set maximum height
		//
		// *** NOTES ***
		// A maximum is retrieved with the method GetMax(). A node's minimum and
		// maximum should always be a multiple of its increment.
		//
		if (pCam->Height != NULL && pCam->Height.GetAccessMode() == RW && pCam->Height.GetInc() != 0 && pCam->Height.GetMax() != 0)
		{
			pCam->Height.SetValue(pCam->Height.GetMax());

			cout << "Height set to " << pCam->Height.GetValue() << "..." << endl;
		}
		else
		{
			cout << "Height not available..." << endl;
			result = -1;
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

					filename << "ImageFormatControlQS-";
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

		// Configure custome image settings
		result = result | ConfigureCustomImageSettings(pCam);

		// Acquire images
		result = result | AcquireImages(pCam);

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
