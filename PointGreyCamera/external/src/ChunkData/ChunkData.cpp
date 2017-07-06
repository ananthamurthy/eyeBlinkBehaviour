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
 *	@example ChunkData.cpp
 *
 *  @brief ChunkData.cpp shows how to get chunk data on an image, either from 
 *	the nodemap or from the image itself. It relies on information provided in 
 *	the Enumeration, Acquisition, and NodeMapInfo examples.
 *
 *	It can also be helpful to familiarize yourself with the ImageFormatControl 
 *	and Exposure examples. As they are somewhat shorter and simpler, either 
 *	provides a strong introduction to camera customization.
 *
 *	Chunk data provides information on various traits of an image. This includes
 *	identifiers such as frame ID, properties such as black level, and more. This 
 *	information can be acquired from either the nodemap or the image itself. 
 *
 *	It may be preferrable to grab chunk data from each individual image, as it 
 *	can be hard to verify whether data is coming from the correct image when 
 *	using the nodemap. This is because chunk data retrieved from the nodemap is 
 *	only valid for the current image; when GetNextImage() is called, chunk data
 *	will be updated to that of the new current image.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream> 

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// Use the following enum and global constant to select whether chunk data is 
// displayed from the image or the nodemap.
enum chunkDataType
{
	IMAGE,
	NODEMAP
};

const chunkDataType chosenChunkData = IMAGE;

// This function configures the camera to add chunk data to each image. It does 
// this by enabling each type of chunk data before enabling chunk data mode. 
// When chunk data is turned on, the data is made available in both the nodemap 
// and each image.
int ConfigureChunkData(INodeMap & nodeMap)
{
	int result = 0;

	cout << endl << endl << "*** CONFIGURING CHUNK DATA ***" << endl << endl;

	try
	{
		//
		// Activate chunk mode
		//
		// *** NOTES ***
		// Once enabled, chunk data will be available at the end of the payload
		// of every image captured until it is disabled. Chunk data can also be 
		// retrieved from the nodemap.
		//
		CBooleanPtr ptrChunkModeActive = nodeMap.GetNode("ChunkModeActive");

		if (!IsAvailable(ptrChunkModeActive) || !IsWritable(ptrChunkModeActive))
		{
			cout << "Unable to activate chunk mode. Aborting..." << endl << endl;
			return -1;
		}

		ptrChunkModeActive->SetValue(true);

		cout << "Chunk mode activated..." << endl;

		//
		// Enable all types of chunk data
		//
		// *** NOTES ***
		// Enabling chunk data requires working with nodes: "ChunkSelector"
		// is an enumeration selector node and "ChunkEnable" is a boolean. It
		// requires retrieving the selector node (which is of enumeration node 
		// type), selecting the entry of the chunk data to be enabled, retrieving 
		// the corresponding boolean, and setting it to true. 
		//
		// In this example, all chunk data is enabled, so these steps are 
		// performed in a loop. Once this is complete, chunk mode still needs to
		// be activated.
		//
		NodeList_t entries;

		// Retrieve the selector node
		CEnumerationPtr ptrChunkSelector = nodeMap.GetNode("ChunkSelector");

		if (!IsAvailable(ptrChunkSelector) || !IsReadable(ptrChunkSelector))
		{
			cout << "Unable to retrieve chunk selector. Aborting..." << endl << endl;
			return -1;
		}

		// Retrieve entries
		ptrChunkSelector->GetEntries(entries);

		cout << "Enabling entries..." << endl;

		for (int i = 0; i < entries.size(); i++)
		{
			// Select entry to be enabled
			CEnumEntryPtr ptrChunkSelectorEntry = entries.at(i);

			// Go to next node if problem occurs
			if (!IsAvailable(ptrChunkSelectorEntry) || !IsReadable(ptrChunkSelectorEntry))
			{
				continue;
			}

			ptrChunkSelector->SetIntValue(ptrChunkSelectorEntry->GetValue());

			cout << "\t" << ptrChunkSelectorEntry->GetSymbolic() << ": ";

			// Retrieve corresponding boolean
			CBooleanPtr ptrChunkEnable = nodeMap.GetNode("ChunkEnable");

			// Enable the boolean, thus enabling the corresponding chunk data
			if (!IsAvailable(ptrChunkEnable))
			{
				cout << "Node not available" << endl;
			}
			else if (ptrChunkEnable->GetValue())
			{
				cout << "Enabled" << endl;
			}
			else if (IsWritable(ptrChunkEnable))
			{
				ptrChunkEnable->SetValue(true);
				cout << "Enabled" << endl;
			}
			else
			{
				cout << "Node not writable" << endl;
			}
		}
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function displays a select amount of chunk data from the image. Unlike
// accessing chunk data via the nodemap, there is no way to loop through all 
// available data.
int DisplayChunkData(ImagePtr pImage)
{
	int result = 0;

	cout << "Printing chunk data from image..." << endl;

	try
	{
		//
		// Retrieve chunk data from image
		//
		// *** NOTES ***
		// When retrieving chunk data from an image, the data is stored in a
		// a ChunkData object and accessed with getter functions.
		//
		ChunkData chunkData = pImage->GetChunkData();
	
		//
		// Retrieve exposure time; exposure time recorded in microseconds
		//
		// *** NOTES ***
		// Floating point numbers are returned as a float64_t. This can safely
		// and easily be statically cast to a double.
		//
		double exposureTime = static_cast<double>(chunkData.GetExposureTime());
		std::cout << "\tExposure time: " << exposureTime << endl;

		//
		// Retrieve frame ID
		//
		// *** NOTES ***
		// Integers are returned as an int64_t. As this is the typical integer
		// data type used in the Spinnaker SDK, there is no need to cast it.
		//
		int64_t frameID = chunkData.GetFrameID();
		cout << "\tFrame ID: " << frameID << endl;

		// Retrieve gain; gain recorded in decibels
		double gain = chunkData.GetGain();
		cout << "\tGain: " << gain << endl;

		// Retrieve height; height recorded in pixels
		int64_t height = chunkData.GetHeight();
		cout << "\tHeight: " << height << endl;

		// Retrieve offset X; offset X recorded in pixels
		int64_t offsetX = chunkData.GetOffsetX();
		cout << "\tOffset X: " << offsetX << endl;

		// Retrieve offset Y; offset Y recorded in pixels
		int64_t offsetY = chunkData.GetOffsetY();
		cout << "\tOffset Y: " << offsetY << endl;

		// Retrieve sequencer set active
		int64_t sequencerSetActive = chunkData.GetSequencerSetActive();
		cout << "\tSequencer set active: " << sequencerSetActive << endl;

		// Retrieve timestamp
		int64_t timestamp = chunkData.GetTimestamp();
		cout << "\tTimestamp: " << timestamp << endl;

		// Retrieve width; width recorded in pixels
		int64_t width = chunkData.GetWidth();
		cout << "\tWidth: " << width << endl;
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}
	
	return result;
}

// This function displays all available chunk data by looping through the chunk 
// data category node on the nodemap.
int DisplayChunkData(INodeMap & nodeMap)
{
	int result = 0;

	cout << "Printing chunk data from nodemap..." << endl;

	try
	{
		//
		// Retrieve chunk data information nodes
		//
		// *** NOTES ***
		// As well as being written into the payload of the image, chunk data is
		// accessible on the GenICam nodemap. Insofar as chunk data is enabled,
		// it is available from both sources.
		//
		CCategoryPtr ptrChunkDataControl = nodeMap.GetNode("ChunkDataControl");
		if (!IsAvailable(ptrChunkDataControl) || !IsReadable(ptrChunkDataControl))
		{
			cout << "Unable to retrieve chunk data control. Aborting..." << endl << endl;
			return -1;
		}

		FeatureList_t features;
		ptrChunkDataControl->GetFeatures(features);

		// Iterate through children
		FeatureList_t::const_iterator it;

		for (it = features.begin(); it != features.end(); ++it)
		{
			CNodePtr pFeature = (CNodePtr)*it;

			cout << "\t" << pFeature->GetDisplayName() << ": ";

			if (!IsAvailable(pFeature) || !IsReadable(pFeature))
			{
				cout << "node not available" << endl;
				result = result | -1;
				continue;
			}
			//
			// Print boolean node type value
			//
			// *** NOTES ***
			// Boolean information is manipulated to output the more-easily
			// identifiable 'true' and 'false' as opposed to '1' and '0'.
			//
			else if (pFeature->GetPrincipalInterfaceType() == intfIBoolean)
			{
				CBooleanPtr pBool = (CBooleanPtr)pFeature;
				bool value = pBool->GetValue();
				cout << (value ? "true" : "false") << endl;
			}
			//
			// Print non-boolean node type value
			//
			// *** NOTES ***
			// All nodes can be cast as value nodes and have their information
			// retrieved as a string using the ToString() method. This is much
			// easier than dealing with each node type individually.
			//
			else
			{
				CValuePtr pValue = (CValuePtr)pFeature;
				cout << pValue->ToString() << endl;
			}
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

	cout << endl << endl << "*** IMAGE ACQUISITION ***" << endl << endl;

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

					filename << "ChunkData-";
					if (deviceSerialNumber != "")
					{
						filename << deviceSerialNumber.c_str() << "-";
					}
					filename << imageCnt << ".jpg";

					// Save image
					convertedImage->Save(filename.str().c_str());

					cout << "Image saved at " << filename.str() << endl;

					// Display chunk data
					if (chosenChunkData == IMAGE)
					{
						result = DisplayChunkData(pResultImage);
					}
					else if (chosenChunkData == NODEMAP)
					{
						result = DisplayChunkData(nodeMap);
					}
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

		// Configure chunk data
		err = ConfigureChunkData(nodeMap);
		if (err < 0)
		{
			return err;
		}

		// Acquire images and display chunk data
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