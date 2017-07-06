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
 *	@example Exposure_C.cpp
 *
 *	@brief Exposure_C.cpp shows how to set a custom exposure time on a device. 
 *	It relies on information provided in the Enumeration_C, Acquisition_C, and
 *	NodeMapInfo_C examples.
 *
 *	This example shows the processes of preparing the camera, setting a custom
 *	exposure time, and restoring the camera to a normal state (without power
 *	cycling). Ensuring custom values do not fall out of range is also touched
 *	on.
 *
 *	Following this, we suggest familiarizing yourself with the 
 *	ImageFormatControl_C example if you haven't already. ImageFormatControl_C 
 *	is another example on camera customization that is shorter and simpler than 
 *	many of the others. Once comfortable with Exposure_C and 
 *	ImageFormatControl_C, we suggest checking out any of the longer, more 
 *	complicated examples related to camera configuration: ChunkData_C, 
 *	LookupTable_C, Sequencer_C, or Trigger_C.
 */

#include "SpinnakerC.h"
#include "stdio.h"
#include "string.h"

// Compiler warning C4996 suppressed due to deprecated strcpy() and sprintf() 
// functions on Windows platform.
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64 
	#pragma warning(disable : 4996)
#endif

// This macro helps with C-strings.
#define MAX_BUFF_LEN 256

// This function configures a custom exposure time. Automatic exposure is turned 
// off in order to allow for the customization, and then the custom setting is 
// applied.
spinError ConfigureExposure(spinNodeMapHandle hNodeMap)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	printf("\n\n*** CONFIGURING EXPOSURE ***\n\n");

	//
	// Turn off automatic exposure mode
	//
	// *** NOTES ***
	// Automatic exposure prevents the manual configuration of exposure 
	// time and needs to be turned off.
	//
	// *** LATER ***
	// Exposure time can be set automatically or manually as needed. This 
	// example turns automatic exposure off to set it manually and back on
	// in order to return the camera to its default state.
	//
	spinNodeHandle hExposureAuto = NULL;
	spinNodeHandle hExposureAutoOff = NULL;
	int64_t exposureAutoOff = 0;

	// Retrieve enumeration node from nodemap
	err = spinNodeMapGetNode(hNodeMap, "ExposureAuto", &hExposureAuto);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable automatic exposure (node retrieval). Aborting with error %d...\n", err);
		return err;
	}

	// Retrieve entry node from enumeration node
	err = spinEnumerationGetEntryByName(hExposureAuto, "Off", &hExposureAutoOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable automatic exposure (enum entry retrieval). Aborting with error %d...\n", err);
		return err;
	}

	// Retrieve integer value from entry node
	err = spinEnumerationEntryGetIntValue(hExposureAutoOff, &exposureAutoOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable automatic exposure (enum entry int value retrieval). Aborting with error %d...\n", err);
		return err;
	}

	// Set integer as new value for enumeration node
	err = spinEnumerationSetIntValue(hExposureAuto, exposureAutoOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable automatic exposure (enum entry setting). Aborting with error %d...\n", err);
		return err;
	}

	printf("Automatic exposure disabled...\n");

	//
	// Set exposure time manually; exposure time recorded in microseconds
	//
	// *** NOTES ***
	// It is ensured that the desired exposure time does not exceed the maximum.
	// Exposure time is counted in microseconds - this can be found out either 
	// by retrieving the unit with the spinFloatGetUnit() methods or by 
	// checking SpinView.
	// 
	spinNodeHandle hExposureTime = NULL;
	double exposureTimeMax = 0.0;
	double exposureTimeToSet = 2000000.0;

	// Retrieve exposure time node
	err = spinNodeMapGetNode(hNodeMap, "ExposureTime", &hExposureTime);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set exposure time. Aborting with error %d...\n", err);
		return err;
	}

	// Retrieve maximum value
	err = spinFloatGetMax(hExposureTime, &exposureTimeMax);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set exposure time. Aborting with error %d...\n", err);
		return err;
	}

	// Ensure desired exposure time does not exceed maximum
	if (exposureTimeToSet > exposureTimeMax)
	{
		exposureTimeToSet = exposureTimeMax;
	}

	// Set desired exposure time as new value
	err = spinFloatSetValue(hExposureTime, exposureTimeToSet);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set exposure time. Aborting with error %d...\n", err);
		return err;
	}

	printf("Exposure time set to %f us...\n", exposureTimeToSet);

	return err;
}

spinError ResetExposure(spinNodeHandle hNodeMap)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	// 
	// Turn automatic exposure back on
	//
	// *** NOTES ***
	// It is recommended to have automatic exposure enabled whenever manual 
	// exposure settings are not required.
	//
	spinNodeHandle hExposureAuto = NULL;
	spinNodeHandle hExposureAutoContinuous = NULL;
	int64_t exposureAutoContinuous = 0;

	// Retrieve enumeration node from nodemap
	err = spinNodeMapGetNode(hNodeMap, "ExposureAuto", &hExposureAuto);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable automatic exposure (node retrieval). Aborting with error %d...\n", err);
		return err;
	}

	// Retrieve entry node from enumeration node
	err = spinEnumerationGetEntryByName(hExposureAuto, "Continuous", &hExposureAutoContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable automatic exposure (enum entry retrieval). Aborting with error %d...\n", err);
		return err;
	}

	// Retrieve integer value from entry node
	err = spinEnumerationEntryGetIntValue(hExposureAutoContinuous, &exposureAutoContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable automatic exposure (enum entry int value retrieval). Aborting with error %d...\n", err);
		return err;
	}

	// Set integer as new value for enumeration node
	err = spinEnumerationSetIntValue(hExposureAuto, exposureAutoContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable automatic exposure (enum entry setting). Aborting with error %d...\n", err);
		return err;
	}

	printf("Automatic exposure enabled...\n\n");

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
spinError AcquireImages(spinCamera hCam, spinNodeMapHandle hNodeMap, spinNodeMapHandle hNodeMapTLDevice)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	printf("\n\n*** IMAGE ACQUISITION ***\n\n");

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

	// Retrieve device serial number for filename
	spinNodeHandle hDeviceSerialNumber = NULL;
	char deviceSerialNumber[MAX_BUFF_LEN];
	size_t lenDeviceSerialNumber = MAX_BUFF_LEN;

	err = spinNodeMapGetNode(hNodeMapTLDevice, "DeviceSerialNumber", &hDeviceSerialNumber);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(deviceSerialNumber, "");
		lenDeviceSerialNumber = 0;
	}
	else
	{
		err = spinStringGetValue(hDeviceSerialNumber, deviceSerialNumber, &lenDeviceSerialNumber);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			strcpy(deviceSerialNumber, "");
			lenDeviceSerialNumber = 0;
		}

		printf("Device serial number retrieved as %s...\n", deviceSerialNumber);
	}
	printf("\n");

	// Retrieve, convert, and save images
	const unsigned int k_numImages = 5;
	unsigned int imageCnt = 0;

	for (imageCnt = 0; imageCnt < k_numImages; imageCnt++)
	{
		// Retrieve next received image
		spinImage hResultImage = NULL;
		
		err = spinCameraGetNextImage(hCam, &hResultImage);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to get next image. Non-fatal error %d...\n\n", err);
			continue;
		}

		// Ensure image completion
		bool8_t isIncomplete = False;
		bool8_t hasFailed = False;
		
		err = spinImageIsIncomplete(hResultImage, &isIncomplete);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to determine image completion. Non-fatal error %d...\n\n", err);
			hasFailed = True;
		}

		if (isIncomplete)
		{
			spinImageStatus imageStatus = IMAGE_NO_ERROR;

			err = spinImageGetStatus(hResultImage, &imageStatus);
			if (err != SPINNAKER_ERR_SUCCESS)
			{
				printf("Unable to retrieve image status. Non-fatal error %d...\n\n", err);
			}
			else
			{
				printf("Image incomplete with image status %d...\n", imageStatus);
			}

			hasFailed = True;
		}

		// Release incomplete or failed image
		if (hasFailed)
		{
			err = spinImageRelease(hResultImage);
			if (err != SPINNAKER_ERR_SUCCESS)
			{
				printf("Unable to release image. Non-fatal error %d...\n\n", err);
			}

			continue;
		}

		// Print image information
		size_t width = 0;
		size_t height = 0;

		err = spinImageGetWidth(hResultImage, &width);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve image width. Non-fatal error %d...\n", err);
		}

		err = spinImageGetHeight(hResultImage, &height);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve image height. Non-fatal error %d...\n", err);
		}

		printf("Grabbed image %u, width = %u, height = %u\n", imageCnt, (unsigned int)width, (unsigned int)height);

		// Convert image to mono 8
		spinImage hConvertedImage = NULL;

		err = spinImageCreateEmpty(&hConvertedImage);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to create image. Non-fatal error %d...\n\n", err);
			hasFailed = True;
		}

		err = spinImageConvert(hResultImage, PixelFormat_Mono8, hConvertedImage);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to convert image. Non-fatal error %d...\n\n", err);
			hasFailed = True;
		}

		// Create unique file name
		char filename[MAX_BUFF_LEN];

		if (lenDeviceSerialNumber == 0)
		{
			sprintf(filename, "Exposure-C-%d.jpg", imageCnt);
		}
		else
		{
			sprintf(filename, "Exposure-C-%s-%d.jpg", deviceSerialNumber, imageCnt);
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

		// Release image
		err = spinImageRelease(hResultImage);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to release image. Non-fatal error %d...\n\n", err);
		}
	}

	// End Acquisition
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

	// Configure exposure
	err = ConfigureExposure(hNodeMap);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Acquire images
	err = AcquireImages(hCam, hNodeMap, hNodeMapTLDevice);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Reset exposure
	err = ResetExposure(hNodeMap);
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
