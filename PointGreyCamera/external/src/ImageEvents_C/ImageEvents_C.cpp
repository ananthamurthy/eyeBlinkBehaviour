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
 *	@example ImageEvents_C.cpp
 *
 *	@brief ImageEvents_C.cpp shows how to acquire images using the image event
 *	handler. It relies on information provided in the Enumeration_C, 
 *	Acquisition_C, and NodeMapInfo_C examples.
 *
 *	It can also be helpful to familiarize yourself with the NodeMapCallback_C
 *	example, as nodemap callbacks follow the same general procedure as
 *	events, but with a few less steps.
 *
 *	Events generally require a class to be defined as an event handler; however,
 *	because C is not an object-oriented language, an event context is created
 *	using a function and a struct whereby the function acts as the event
 *	method and the struct acts as its properties.
 */

#include "SpinnakerC.h"
#include "stdio.h"
#include "string.h"

// Libraries windows.h or unistd.h included for Sleep()/usleep(); compiler
// warning C4996 suppressed due to deprecated strcpy() and sprintf() functions 
// on Windows platform.
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64 
	#include "windows.h"
	#pragma warning(disable : 4996)
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

// This macro helps with C-strings.
#define MAX_BUFF_LEN 256

// This struct represents the properties of what would be an image event handler
// were we working in an object-oriented programming language. The struct is 
// created with a pointer and passed into the function, which creates persistent 
// data, mimicking the properties of a class.
typedef struct _userData
{
	unsigned int numImages;
	unsigned int imageCnt;

	size_t lenDeviceSerialNumber;
	char deviceSerialNumber[MAX_BUFF_LEN];
} userData;

// This function represents what would be the method of an image event handler.
// Together with the struct above, this makes up the image event context.
// Notice that the function signature must match this exactly for the function 
// to be accepted when creating the event.
void onImageEvent(spinImage hImage, void* pUserData)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	// Convert void pointer back to struct	
	userData* imageEventInfo = (userData*)pUserData;

	// Only retrieve, convert, and save images if number of expected images has
	// not been exceeded
	if (imageEventInfo->imageCnt < imageEventInfo->numImages)
	{
		printf("Image event occurred...\n");

		// Ensure image completion
		bool8_t isIncomplete = False;
		bool8_t hasFailed = False;

		err = spinImageIsIncomplete(hImage, &isIncomplete);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to determine image completion. Non-fatal error %d...\n\n", err);
			return;
		}

		if (isIncomplete)
		{
			spinImageStatus imageStatus = IMAGE_NO_ERROR;

			err = spinImageGetStatus(hImage, &imageStatus);
			if (err != SPINNAKER_ERR_SUCCESS)
			{
				printf("Unable to retrieve image status. Non-fatal error %d...\n\n", err);
			}
			else
			{
				printf("Image incomplete with image status %d...\n", imageStatus);
			}

			return;
		}

		// Print image information
		size_t width = 0;
		size_t height = 0;

		err = spinImageGetWidth(hImage, &width);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve image width. Non-fatal error %d...\n", err);
		}

		err = spinImageGetHeight(hImage, &height);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve image height. Non-fatal error %d...\n", err);
		}

		printf("Grabbed image %u, width = %u, height = %u\n", imageEventInfo->imageCnt, (unsigned int)width, (unsigned int)height);

		// Convert image to mono 8
		spinImage hConvertedImage = NULL;

		err = spinImageCreateEmpty(&hConvertedImage);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to create image. Non-fatal error %d...\n\n", err);
			hasFailed = True;
		}

		err = spinImageConvert(hImage, PixelFormat_Mono8, hConvertedImage);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to convert image. Non-fatal error %d...\n\n", err);
			return;
		}

		// Create unique file name
		char filename[MAX_BUFF_LEN];

		if (imageEventInfo->lenDeviceSerialNumber == 0)
		{
			sprintf(filename, "ImageEvents-C-%d.jpg", imageEventInfo->imageCnt);
		}
		else
		{
			sprintf(filename, "ImageEvents-C-%s-%d.jpg", imageEventInfo->deviceSerialNumber, imageEventInfo->imageCnt);
		}

		// Save image
		err = spinImageSave(hConvertedImage, filename, JPEG);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to save image. Non-fatal error %d...\n", err);
		}
		else
		{
			printf("Image saved at %s\n\n", filename);
		}

		// Destroy converted image
		err = spinImageDestroy(hConvertedImage);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to destroy image. Non-fatal error %d...\n\n", err);
		}

		// Increment number of saved images
		imageEventInfo->imageCnt++;
	}
}

// This function configures image events by creating and registering them
// to a camera.
spinError ConfigureImageEvents(spinCamera hCam, spinNodeMapHandle hNodeMapTLDevice, spinImageEvent* imageEvent, userData* imageEventInfo)
{
	spinError err = SPINNAKER_ERR_SUCCESS;
	
	printf("\n\n*** IMAGE EVENTS CONFIGURATION ***\n\n");
		
	//
	// Prepare user data
	//
	// *** NOTES ***
	// It is important to ensure that all requisite variables are initialized
	// appropriately before creating the image event context.
	//
	// *** LATER ***
	// It is a good idea to keep this data in scope in order to avoid memory
	// leaks. 
	//
	// Initialize image count to zero and number of images to 10
	imageEventInfo->imageCnt = 0;
	imageEventInfo->numImages = 10;

	// Initialize device serial number for filename
	spinNodeHandle hDeviceSerialNumber = NULL;
	imageEventInfo->lenDeviceSerialNumber = MAX_BUFF_LEN;

	err = spinNodeMapGetNode(hNodeMapTLDevice, "DeviceSerialNumber", &hDeviceSerialNumber);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(imageEventInfo->deviceSerialNumber, "");
		imageEventInfo->lenDeviceSerialNumber = 0;
	}
	else
	{
		err = spinStringGetValue(hDeviceSerialNumber, imageEventInfo->deviceSerialNumber, &imageEventInfo->lenDeviceSerialNumber);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			strcpy(imageEventInfo->deviceSerialNumber, "");
			imageEventInfo->lenDeviceSerialNumber = 0;
		}

		printf("Device serial number retrieved as %s...\n", imageEventInfo->deviceSerialNumber);
	}

	//
	// Create image event
	//
	// *** NOTES ***
	// The image event function has been written to only print convert and save
	// images. This demonstrates an alternative method of acquiring images.
	//
	// *** LATER ***
	// In Spinnaker C, every event that is created must be destroyed to avoid
	// memory leaks.
	//
	err = spinImageEventCreate(imageEvent, onImageEvent, (void*)imageEventInfo);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to create event. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Image event created...\n");

	//
	// Register image event
	//
	// *** NOTES ***
	// Image events are registered to cameras. If there are multiple cameras, 
	// each camera must have the image events registered to it separately. 
	// Also, multiple image events may be registered to a single camera.
	//
	// *** LATER ***
	// Image events must be unregistered manually. This must be done prior to 
	// releasing the system and while the image events are still in scope.
	//
	err = spinCameraRegisterImageEvent(hCam, *imageEvent);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to register event. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Image event registered...\n\n");

	return err;
}

void WaitForImages(userData* imageEventInfo)
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

	while (imageEventInfo->imageCnt < imageEventInfo->numImages)
	{
		printf("\t//\n");
		printf("\t// Sleeping for %d ms. Grabbing images...\n", sleepDuration);
		printf("\t//\n");

		SleepyWrapper(sleepDuration);
	}
}

// This function resets the example by unregistering the image event.
spinError ResetImageEvents(spinCamera hCam, spinImageEvent imageEvent)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	//
	// Unregister device event
	//
	// *** NOTES ***
	// It is important to unregister all image events from all cameras that
	// they are registered to.
	//
	err = spinCameraUnregisterImageEvent(hCam, imageEvent);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to unregister event. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Image event unregistered...\n");

	//
	// Destroy events
	//
	// *** NOTES ***
	// Events must be destroyed in order to avoid memory leaks.
	//
	err = spinImageEventDestroy(imageEvent);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to destroy event. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Image event destroyed...\n\n");

	return err;
}

// This function prints the device information of the camera from the transport
// layer; please see NodeMapInfo_C example for more in-depth comments on
// printing device information from the nodemap.
spinError PrintDeviceInfo(spinNodeMapHandle hNodeMap)
{
	spinError err = SPINNAKER_ERR_SUCCESS;
	unsigned int i = 0;

	printf("\n*** DEVICE INFORMATION ***\n\n");

	// Retrieve device information category node
	spinNodeHandle hDeviceInformation = NULL;

	err = spinNodeMapGetNode(hNodeMap, "DeviceInformation", &hDeviceInformation);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve node. Non-fatal error %d...\n\n", err);
		return err;
	}

	// Retrieve number of nodes within device information node
	size_t numFeatures = 0;

	err = spinCategoryGetNumFeatures(hDeviceInformation, &numFeatures);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve number of nodes. Non-fatal error %d...\n\n", err);
		return err;
	}

	// Iterate through nodes and print information
	for (i = 0; i < numFeatures; i++)
	{
		spinNodeHandle hFeatureNode = NULL;

		err = spinCategoryGetFeatureByIndex(hDeviceInformation, i, &hFeatureNode);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve node. Non-fatal error %d...\n\n", err);
			continue;
		}

		spinNodeType featureType = UnknownNode;

		err = spinNodeGetType(hFeatureNode, &featureType);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve node type. Non-fatal error %d...\n\n", err);
			continue;
		}

		char featureName[MAX_BUFF_LEN];
		size_t lenFeatureName = MAX_BUFF_LEN;
		char featureValue[MAX_BUFF_LEN];
		size_t lenFeatureValue = MAX_BUFF_LEN;

		err = spinNodeGetName(hFeatureNode, featureName, &lenFeatureName);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			strcpy(featureName, "Unknown name");
		}

		err = spinNodeToString(hFeatureNode, featureValue, &lenFeatureValue);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			strcpy(featureValue, "Unknown value");
		}

		printf("%s: %s\n", featureName, featureValue);
	}

	return err;
}

// This function acquires and saves 10 images from a device; please see
// Acquisition_C example for more in-depth comments on the acquisition of
// images.
spinError AcquireImages(spinCamera hCam, spinNodeMapHandle hNodeMap, userData* imageEventInfo)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	printf("\n*** IMAGE ACQUISITION ***\n\n");

	// Set acquisition mode to continuous
	spinNodeHandle hAcquisitionMode = NULL;
	spinNodeHandle hAcquisitionModeContinuous = NULL;
	int64_t acquisitionModeContinuous = 0;

	err = spinNodeMapGetNode(hNodeMap, "AcquisitionMode", &hAcquisitionMode);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set acquisition mode to continuous (node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hAcquisitionMode, "Continuous", &hAcquisitionModeContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set acquisition mode to continuous (entry 'continuous' retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hAcquisitionModeContinuous, &acquisitionModeContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set acquisition mode to continuous (entry int value retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationSetIntValue(hAcquisitionMode, acquisitionModeContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set acquisition mode to continuous (entry int value setting). Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Acquisition mode set to continuous...\n");

	// Begin acquiring images
	err = spinCameraBeginAcquisition(hCam);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to begin image acquisition. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Acquiring images...\n");

	// Wait for 10 images to be captured by image events
	WaitForImages(imageEventInfo);

	// End acquisition
	err = spinCameraEndAcquisition(hCam);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to end acquisition. Non-fatal error %d...\n\n", err);
	}

	return err;
}

// This function acts as the body of the example; please see NodeMapInfo_C 
// example for more in-depth comments on setting up cameras.
spinError RunSingleCamera(spinCamera hCam)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	// Retrieve TL device nodemap and print device information
	spinNodeMapHandle hNodeMapTLDevice = NULL;

	err = spinCameraGetTLDeviceNodeMap(hCam, &hNodeMapTLDevice);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve TL device nodemap. Non-fatal error %d...\n\n", err);
	}
	else
	{
		err = PrintDeviceInfo(hNodeMapTLDevice);
	}

	// Initialize camera
	err = spinCameraInit(hCam);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to initialize camera. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve GenICam nodemap
	spinNodeMapHandle hNodeMap = NULL;

	err = spinCameraGetNodeMap(hCam, &hNodeMap);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve GenICam nodemap. Aborting with error %d...\n\n", err);
		return err;
	}

	// Configure device events
	spinImageEvent imageEvent = NULL;
	userData imageEventInfo;

	err = ConfigureImageEvents(hCam, hNodeMapTLDevice, &imageEvent, &imageEventInfo);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Acquire images
	err = AcquireImages(hCam, hNodeMap, &imageEventInfo);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Reset device events
	err = ResetImageEvents(hCam, imageEvent);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Deinitialize camera
	err = spinCameraDeInit(hCam);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to deinitialize camera. Non-fatal error %d...\n\n", err);
	}

	return err;
}

// Example entry point; please see Enumeration_C example for more in-depth
// comments on preparing and cleaning up the system.
int main(/*int argc, char** argv*/)
{
	spinError errReturn = SPINNAKER_ERR_SUCCESS;
	spinError err = SPINNAKER_ERR_SUCCESS;
	unsigned int i = 0;

	// Print application build information
	printf("Application build date: %s %s \n\n", __DATE__, __TIME__);

	// Retrieve singleton reference to system object
	spinSystem hSystem = NULL;

	err = spinSystemGetInstance(&hSystem);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve system instance. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve list of cameras from the system
	spinCameraList hCameraList = NULL;

	err = spinCameraListCreateEmpty(&hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to create camera list. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinSystemGetCameras(hSystem, hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve camera list. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve number of cameras
	size_t numCameras = 0;

	err = spinCameraListGetSize(hCameraList, &numCameras);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve number of cameras. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Number of cameras detected: %u\n\n", (unsigned int)numCameras);

	// Finish if there are no cameras
	if (numCameras == 0)
	{
		// Clear and destroy camera list before releasing system
		err = spinCameraListClear(hCameraList);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to clear camera list. Aborting with error %d...\n\n", err);
			return err;
		}

		err = spinCameraListDestroy(hCameraList);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to destroy camera list. Aborting with error %d...\n\n", err);
			return err;
		}

		// Release system
		err = spinSystemReleaseInstance(hSystem);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to release system instance. Aborting with error %d...\n\n", err);
			return err;
		}

		printf("Not enough cameras!\n");
		printf("Done! Press Enter to exit...\n");
		getchar();

		return -1;
	}

	// Run example on each camera
	for (i = 0; i < numCameras; i++)
	{
		printf("\nRunning example for camera %d...\n", i);

		// Select camera
		spinCamera hCamera = NULL;

		err = spinCameraListGet(hCameraList, i, &hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve camera from list. Aborting with error %d...\n\n", err);
			errReturn = err;
		}
		else
		{
			// Run example
			err = RunSingleCamera(hCamera);
			if (err != SPINNAKER_ERR_SUCCESS)
			{
				errReturn = err;
			}
		}

		// Release camera
		err = spinCameraRelease(hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}

		printf("Camera %d example complete...\n\n", i);
	}

	// Clear and destroy camera list before releasing system
	err = spinCameraListClear(hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to clear camera list. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinCameraListDestroy(hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to destroy camera list. Aborting with error %d...\n\n", err);
		return err;
	}

	// Release system
	err = spinSystemReleaseInstance(hSystem);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to release system instance. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("\nDone! Press Enter to exit...\n");
	getchar();

	return errReturn;
}
