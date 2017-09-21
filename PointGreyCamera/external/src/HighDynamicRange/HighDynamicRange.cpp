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
 *  @example HighDynamicRange.cpp
 *  @brief This example shows how to set High Dynamic Range (HDR) if it is available on the camera.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream> 

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

const unsigned int k_HDRShutter1 = 1000; //us
const unsigned int k_HDRShutter2 = 5000;
const unsigned int k_HDRShutter3 = 15000;
const unsigned int k_HDRShutter4 = 30000;

const unsigned int k_HDRGain1 = 0; //dB
const unsigned int k_HDRGain2 = 5;
const unsigned int k_HDRGain3 = 10;
const unsigned int k_HDRGain4 = 15;


// Helper for outputting build information
void PrintBuildInfo()
{
	std::ostringstream out;
	out << "Application build date: " << __DATE__ << " " << __TIME__ << endl << endl;
	cout << out.str();
}

// Helper for outputting camera information
void PrintDeviceInfo(INodeMap & nodeMap)
{
	cout << endl << "*** DEVICE INFORMATION ***" << endl;

	FeatureList_t features;
	CCategoryPtr category = nodeMap.GetNode("DeviceControl");
	category->GetFeatures( features );

	FeatureList_t::const_iterator it;
	for (it = features.begin(); it != features.end(); ++it)
	{
		CNodePtr pfeatureNode = *it;
		cout << pfeatureNode->GetName() << " : ";
		CValuePtr pValue = (CValuePtr)pfeatureNode;
		cout << (IsReadable(pValue) ? pValue->ToString() : "Node not readable");
		cout << endl;
	}

	cout << endl;
}

// Helper for checking GenICam node accessibility
bool CheckNodeAccessibility(const CNodePtr nodePtr)
{
	return (IsAvailable(nodePtr) && (IsReadable(nodePtr) || IsWritable(nodePtr)));
}

// Helper for toggling HDR mode on camera
bool ToggleHDRMode(INodeMap& nodeMap, bool hdrOn)
{
	CBooleanPtr ptrPGRHDREnabled = nodeMap.GetNode("PGR_HDRModeEnabled");
	if (CheckNodeAccessibility((CNodePtr)ptrPGRHDREnabled))
	{
		ptrPGRHDREnabled->SetValue(hdrOn);
	}
	else
	{
		return false;
	}

	cout << "HDR mode turned to " << (hdrOn ? "on " : "off ") << endl;

	return true;
}

// Helper for initializing HDR images
bool InitializeHDRImages(INodeMap& nodeMap)
{
	CEnumerationPtr ptrHDRImageSelector = nodeMap.GetNode("PGR_HDRImageSelector");
	CFloatPtr ptrHDRExposureAbs = nodeMap.GetNode("PGR_HDR_ExposureTimeAbs");
	CFloatPtr ptrHDRGainAbs = nodeMap.GetNode("PGR_HDR_GainAbs");

	if (!CheckNodeAccessibility((CNodePtr)ptrHDRImageSelector))
	{
		return false;
	}

	if (!CheckNodeAccessibility((CNodePtr)ptrHDRExposureAbs))
	{
		return false;
	}

	if (!CheckNodeAccessibility((CNodePtr)ptrHDRGainAbs))
	{
		return false;
	}

	// Configure Image1
	ptrHDRImageSelector->SetIntValue(ptrHDRImageSelector->GetEntryByName("Image1")->GetValue());
	ptrHDRExposureAbs->SetValue(k_HDRShutter1);
	ptrHDRGainAbs->SetValue(k_HDRGain1);
	cout << "Initialized HDR Image1..." << endl;

	// Configure Image2
	ptrHDRImageSelector->SetIntValue(ptrHDRImageSelector->GetEntryByName("Image2")->GetValue());
	ptrHDRExposureAbs->SetValue(k_HDRShutter2);
	ptrHDRGainAbs->SetValue(k_HDRGain2);
	cout << "Initialized HDR Image2..." << endl;

	// Configure Image3
	ptrHDRImageSelector->SetIntValue(ptrHDRImageSelector->GetEntryByName("Image3")->GetValue());
	ptrHDRExposureAbs->SetValue(k_HDRShutter3);
	ptrHDRGainAbs->SetValue(k_HDRGain3);
	cout << "Initialized HDR Image3..." << endl;

	// Configure Image4
	ptrHDRImageSelector->SetIntValue(ptrHDRImageSelector->GetEntryByName("Image4")->GetValue());
	ptrHDRExposureAbs->SetValue(k_HDRShutter4);
	ptrHDRGainAbs->SetValue(k_HDRGain4);
	cout << "Initialized HDR Image4..." << endl;

	return true;
}

// Helper for running example on single camera
int RunSingleCamera(CameraPtr cam)
{
	const int k_numImages = 4;
	int result = 0;

	try
	{
		// Connect to a camera
		cam->Init();

		// Get GenICam NodeMap info from camera
		INodeMap&  nodeMap = cam->GetNodeMap();

		// Get camera information through NodeMap
		PrintDeviceInfo(nodeMap);

		// Verify whether HDR is supported on this device
		CBooleanPtr ptrPGRHDREnabled = nodeMap.GetNode("PGR_HDRModeEnabled");
		if (!IsAvailable(ptrPGRHDREnabled))
		{
			cout << "HDR is not supported! Exiting..." << endl;
			return 0;
		}

		// HDR needs to be enabled prior to configure
		// individual HDR images
		ToggleHDRMode(nodeMap, true);

		if (!InitializeHDRImages(nodeMap))
		{
			cout << "Error configuring HDR image! Exiting..." << endl;
			return -1;
		}

		// Retrieve Device ID
		CStringPtr ptrStringSerial = cam->GetTLDeviceNodeMap().GetNode("DeviceID");

		// Begin capturing images
		cout << endl << "Starting grabbing images..." << endl;
		cam->BeginAcquisition();

		ImagePtr convertedImage;
		for (int imageCnt = 0; imageCnt < k_numImages; imageCnt++)
		{
			try
			{
				// Retrieve the next received image
				ImagePtr rawImage = cam->GetNextImage();
				cout << "Grabbed image " << imageCnt << ", width = " << rawImage->GetWidth() << ", height = " << rawImage->GetHeight() << endl;

				// Convert image to Mono8
				convertedImage = rawImage->Convert(PixelFormat_Mono8);

				// Create a unique filename
				std::ostringstream filename;
				filename << "HighDynamicRange-" << ptrStringSerial->GetValue().c_str() << "-" << imageCnt << ".jpg";

				// Save image
				convertedImage->Save(filename.str().c_str());

				// Image need to be released after use
				rawImage->Release();
			}
			catch (std::exception &e)
			{
				cout << "Error Retrieving Image:" << e.what() << endl;
				result = -1;
				continue;
			}
		}

		// End capturing of images
		cam->EndAcquisition();
	}
	catch (std::exception &e)
	{
		cout << "Error " << e.what() << endl;
		result = -1;
	}

	cout << endl;

	return result;
}

// Example entry point
int main(int /*argc*/, char** /*argv*/)
{
	// Print Application Build Information
	PrintBuildInfo();

	// Get singleton reference to system object
	// Make sure to call system->ReleaseInstance() before program terminates
	SystemPtr system = System::GetInstance();

	// Get a list of cameras available on the system
	CameraList camList = system->GetCameras();

	// Iterate through list of discovered cameras and run example
	unsigned int numCameras = camList.GetSize();
	cout << "Number of cameras detected: " << numCameras << endl;

	if (numCameras == 0)
	{
		// CameraList needs to be cleared before system is cleaned up
		camList.Clear();
		system->ReleaseInstance();

		cout << "Not enough cameras!" << endl;
		cout << "Done! Press Enter to exit..." << endl;
		getchar();
		return -1;
	}

	int result = 0;

	for (unsigned int i = 0; i < numCameras; i++)
	{
		result = result | RunSingleCamera(camList.GetByIndex(i));
	}

	// CameraList needs to be cleared before system is cleaned up
	camList.Clear();
	system->ReleaseInstance();

	cout << "Done! Press Enter to exit..." << endl;
	getchar();

	return result;
}
