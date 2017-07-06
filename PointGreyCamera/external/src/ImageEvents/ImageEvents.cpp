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
 *	@example ImageEvents.cpp
 *
 *	@brief ImageEvents.cpp shows how to acquire images using the image event 
 *	handler. It relies on information provided in the Enumeration, Acquisition, 
 *	and NodeMapInfo examples. 
 *	
 *	It can also be helpful to familiarize yourself with the NodeMapCallback
 *	example, as nodemap callbacks follow the same general procedure as
 *	events, but with a few less steps.
 *
 *	This example creates a user-defined class, ImageEventHandler, that inherits 
 *	from the Spinnaker class, ImageEvent. ImageEventHandler allows the user to 
 *	define any properties, parameters, and the event itself while ImageEvent
 *	allows the child class to appropriately interface with Spinnaker.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// Libraries windows.h or unistd.h included for Sleep()/usleep().
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64
	#include "windows.h"
#else
	#include "unistd.h"
#endif

// This helper function allows the example to sleep in both Windows and Linux 
// systems.
void SleepyWrapper(int milliseconds)
{
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64 
	Sleep(milliseconds);
#else
	usleep(milliseconds);
#endif
}

// This class defines the properties, parameters, and the event itself. Take a 
// moment to notice what parts of the class are mandatory, and what have been 
// added for demonstration purposes. First, any class used to define image events 
// must inherit from ImageEvent. Second, the method signature of OnImageEvent() 
// must also be consistent. Everything else - including the constructor, 
// deconstructor, properties, body of OnImageEvent(), and other functions - 
// is particular to the example. 
class ImageEventHandler : public ImageEvent
{
public:
	
	// The constructor retrieves the serial number and initializes the image 
	// counter to 0.
	ImageEventHandler(CameraPtr pCam) 
	{ 
		// Retrieve device serial number
		INodeMap & nodeMap = pCam->GetTLDeviceNodeMap();

		m_deviceSerialNumber = "";
		CStringPtr ptrDeviceSerialNumber = nodeMap.GetNode("m_deviceSerialNumber");
		if (IsAvailable(ptrDeviceSerialNumber) && IsReadable(ptrDeviceSerialNumber))
		{
			m_deviceSerialNumber = ptrDeviceSerialNumber->GetValue();
		}

		// Initialize image counter to 0
		m_imageCnt = 0;

		// Release reference to camera
		pCam = NULL;
	}
	~ImageEventHandler() {}

	// This method defines an image event. In it, the image that triggered the 
	// event is converted and saved before incrementing the count. Please see 
	// Acquisition_CSharp example for more in-depth comments on the acquisition 
	// of images.
	void OnImageEvent(ImagePtr image)
	{
		// Save a maximum of 10 images
		if (m_imageCnt < mk_numImages)
		{
			cout << "Image event occurred..." << endl;

			// Check image retrieval status
			if (image->IsIncomplete())
			{
				cout << "Image incomplete with image status " << image->GetImageStatus() << "..." << endl << endl;
			}
			else
			{
				// Print image information
				cout << "Grabbed image " << m_imageCnt << ", width = " << image->GetWidth() << ", height = " << image->GetHeight() << endl;

				// Convert image to mono 8
				ImagePtr convertedImage = image->Convert(PixelFormat_Mono8, HQ_LINEAR);

				// Create a unique filename and save image
				ostringstream filename;

				filename << "ImageEvents-";
				if (m_deviceSerialNumber != "")
				{
					filename << m_deviceSerialNumber.c_str() << "-";
				}
				filename << m_imageCnt << ".jpg";

				convertedImage->Save(filename.str().c_str());

				cout << "Image saved at " << filename.str() << endl << endl;

				// Increment image counter
				m_imageCnt++;
			}
		}
	}

	// Getter for image counter
	int getImageCount()
	{
		return m_imageCnt;
	}

	// Getter for maximum images
	int getMaxImages()
	{
		return mk_numImages;
	}

private:

	static const unsigned int mk_numImages = 10;
	unsigned int m_imageCnt;
	string m_deviceSerialNumber;
};

// This function configures the example to execute image events by preparing and
// registering an image event. 
int ConfigureImageEvents(CameraPtr pCam, ImageEventHandler*& imageEventHandler)
{
	int result = 0;

	try
	{
		//
		// Create image event
		//
		// *** NOTES ***
		// The class has been constructed to accept a camera pointer in order
		// to allow the saving of images with the device serial number.
		//
		imageEventHandler = new ImageEventHandler(pCam);
		
		// 
		// Register image event handler
		//
		// *** NOTES ***
		// Image events are registered to cameras. If there are multiple 
		// cameras, each camera must have the image events registered to it
		// separately. Also, multiple image events may be registered to a
		// single camera.
		//
		// *** LATER ***
		// Image events must be unregistered manually. This must be done prior
		// to releasing the system and while the image events are still in
		// scope.
		//
		pCam->RegisterEvent(*imageEventHandler);
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function waits for the appropriate amount of images.  Notice that 
// whereas most examples actively retrieve images, the acquisition of images is 
// handled passively in this example.
int WaitForImages(ImageEventHandler*& imageEventHandler)
{
	int result = 0;

	try
	{
		//
		// Wait for images
		//
		// *** NOTES ***
		// In order to passively capture images using image events and
		// automatic polling, the main thread sleeps in increments of 200 ms
		// until 10 images have been acquired and saved.
		//
		const int sleepDuration = 200; // in milliseconds
		
		while (imageEventHandler->getImageCount() < imageEventHandler->getMaxImages())
		{
			cout << "\t//" << endl;
			cout << "\t// Sleeping for " << sleepDuration << " ms. Grabbing images..." << endl;
			cout << "\t//" << endl;

			SleepyWrapper(sleepDuration);
		}
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This functions resets the example by unregistering the image event.
int ResetImageEvents(CameraPtr pCam, ImageEventHandler*& imageEventHandler)
{
	int result = 0;

	try
	{
		//
		// Unregister image event handler
		//
		// *** NOTES ***
		// It is important to unregister all image events from all cameras
		// they are registered to.
		//
		pCam->UnregisterEvent(*imageEventHandler);

		// Delete image event (because it is a pointer)
		delete imageEventHandler;
		
		cout << "Image events unregistered..." << endl << endl;
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

// This function passively waits for images by calling WaitForImages(). Notice that 
// this function is much shorter than the AcquireImages() function of other examples.
// This is because most of the code has been moved to the image event's OnImageEvent()
// method. 
int AcquireImages(CameraPtr pCam, INodeMap & nodeMap, INodeMap & nodeMapTLDevice, ImageEventHandler*& imageEventHandler)
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
			cout << "Unable to set acquisition mode to continuous (enum entry retrieval). Aborting..." << endl << endl;
			return -1;
		}

		int64_t acquisitionModeContinuous = ptrAcquisitionModeContinuous->GetValue();

		ptrAcquisitionMode->SetIntValue(acquisitionModeContinuous);

		cout << "Acquisition mode set to continuous..." << endl;

		// Begin acquiring images
		pCam->BeginAcquisition();

		cout << "Acquiring images..." << endl;

		// Retrieve images using image event handler
		WaitForImages(imageEventHandler);
		
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

		// Configure image events
		ImageEventHandler* imageEventHandler;

		err = ConfigureImageEvents(pCam, imageEventHandler);
		if (err < 0)
		{
			return err;
		}

		// Acquire images using the image event handler
		result = result | AcquireImages(pCam, nodeMap, nodeMapTLDevice, imageEventHandler);

		// Reset image events
		result = result | ResetImageEvents(pCam, imageEventHandler);

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