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
 *	@example LookupTable_C.cpp
 *
 *	@brief LookupTable_C.cpp shows how to configure lookup tables on the 
 *	camera. It relies on information provided in the Enumeration_C, 
 *	Acquisition_C, and NodeMapInfo_C examples.
 *
 *	It can also be helpful to familiarize yourself with the
 *	ImageFormatControl_C and Exposure_C examples as these provide a strong
 *	introduction to camera customization.
 *
 *	Lookup tables allow for the customization and control of individual pixels.
 *	This can be a very powerful and deeply useful tool; however, because use
 *	cases are context dependent, this example only explores lookup table
 *	configuration.
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

// This function configures lookup tables linearly. This involves selecting 
// the type of lookup table, finding the appropriate increment calculated from 
// the maximum value, and enabling lookup tables on the camera.
spinError ConfigureLookupTables(spinNodeMapHandle hNodeMap)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	printf("\n\n*** LOOKUP TABLE CONFIGURATION ***\n\n");

	//
	// Select lookup table type
	//
	// *** NOTES ***
	// Setting the lookup table selector. It is important to note that this
	// does not enable lookup tables.
	//
	spinNodeHandle hLUTSelector = NULL;
	spinNodeHandle hLUTSelectorLUT1 = NULL;
	int64_t lutSelectorLUT1 = 0;

	err = spinNodeMapGetNode(hNodeMap, "LUTSelector", &hLUTSelector);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set lookup table type (node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hLUTSelector, "LUT1", &hLUTSelectorLUT1);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set lookup table type (enum entry retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hLUTSelectorLUT1, &lutSelectorLUT1);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set lookup table type (enum entry int value retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationSetIntValue(hLUTSelector, lutSelectorLUT1);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set lookup table type (enum entry setting). Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Lookup table type set to LUT1...\n");

	//
	// Determine pixel increment and set indexes and values as desired
	//
	// *** NOTES ***
	// To get the pixel increment, the maximum range of the value node must
	// first be retrieved. The value node represents an index, so its value
	// should be one less than a power of 2 (e.g. 511, 1023, etc.). Add 1 to
	// this index to get the maximum range. Divide the maximum range by 512
	// to calculate the pixel increment.
	//
	// Finally, all values (in the value node) and their corresponding 
	// indexes (in the index node) need to be set. The goal of this example
	// is to set the lookup table linearly. As such, the slope of the values
	// should be set according to the increment, but the slope of the 
	// indexes is inconsequential.
	//
	spinNodeHandle hLUTValue = NULL;
	spinNodeHandle hLUTIndex = NULL;
	int64_t maximumRange = 0;
	int64_t increment = 0;
	int64_t i = 0;

	// Retrieve value node
	err = spinNodeMapGetNode(hNodeMap, "LUTValue", &hLUTValue);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to configure lookup table. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve maximum index
	err = spinIntegerGetMax(hLUTValue, &maximumRange);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to configure lookup table. Aborting with error %d...\n\n", err);
		return err;
	}

	// Convert maximum index to maximum range
	maximumRange++;
	printf("\tMaximum range: %d\n", (int)maximumRange);

	// Calculate increment
	increment = maximumRange / 512;
	printf("\tIncrement: %d\n", (int)increment);

	// Retrieve index node
	err = spinNodeMapGetNode(hNodeMap, "LUTIndex", &hLUTIndex);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to configure lookup table. Aborting with error %d...\n\n", err);
		return err;
	}

	// Set values and indexes
	for (i = 0; i < maximumRange; i += increment)
	{
		err = spinIntegerSetValue(hLUTIndex, i);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to configure lookup table. Aborting with error %d...\n\n", err);
			return err;
		}

		err = spinIntegerSetValue(hLUTValue, i);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to configure lookup table. Aborting with error %d...\n\n", err);
			return err;
		}
	}

	printf("All lookup table values set...\n");

	//
	// Enable lookup tables
	//
	// *** NOTES ***
	// Once lookup tables have been configured, don't forget to enable them
	// with the appropriate node.
	//
	// *** LATER ***
	// Once the images with lookup tables have been collected, turn the
	// feature off with the same node.
	//
	spinNodeHandle hLUTEnable = NULL;

	err = spinNodeMapGetNode(hNodeMap, "LUTEnable", &hLUTEnable);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable lookup table. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinBooleanSetValue(hLUTEnable, True);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable lookup table. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Lookup table enabled...\n\n");

	return err;
}

// This function resets the camera by disabling lookup tables.
spinError ResetLookupTables(spinNodeMapHandle hNodeMap)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	//
	// Disable lookup tables
	//
	// *** NOTES ***
	// It is recommended to keep lookup tables off when they are not 
	// explicitly required.
	//
	spinNodeHandle hLUTEnable = NULL;

	err = spinNodeMapGetNode(hNodeMap, "LUTEnable", &hLUTEnable);

	err = spinBooleanSetValue(hLUTEnable, False);

	printf("Lookup tables disabled...\n\n");

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
// Acquisition_C example for additional information on the steps in this 
// function.
spinError AcquireImages(spinCamera hCam, spinNodeMapHandle hNodeMap, spinNodeMapHandle hNodeMapTLDevice)
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
	const unsigned int k_numImages = 10;
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

		// Create unique file name and save image
		char filename[MAX_BUFF_LEN];

		if (lenDeviceSerialNumber == 0)
		{
			sprintf(filename, "LookupTable-C-%d.jpg", imageCnt);
		}
		else
		{
			sprintf(filename, "LookupTable-C-%s-%d.jpg", deviceSerialNumber, imageCnt);
		}

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

	// Configure lookup tables
	err = ConfigureLookupTables(hNodeMap);
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

	// Reset lookup tables
	err = ResetLookupTables(hNodeMap);
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
