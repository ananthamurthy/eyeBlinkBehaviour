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
 *	@example SaveToAvi_C.cpp
 *
 *	@brief SaveToAvi_C.cpp shows how to create an AVI video from a vector of
 *	images. It relies on information provided in the Enumeration_C, 
 *	Acquisition_C, and NodeMapInfo_C examples.
 *
 *	This example introduces the AVIRecorder class, which is used to quickly 
 *	and easily create various types of AVI videos. It demonstrates the 
 *	creation of three types: uncompressed, MJPG, and H264.
 */

#include "SpinnakerC.h"
#include "stdio.h"
#include "string.h"

// Compiler warning C4996 suppressed due to deprecated strcpy() and sprintf() 
// functions on Windows platform.
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64 
	#pragma warning(disable : 4996)
#endif

// These macros helps with C-strings and number of frames in a video.
#define MAX_BUFF_LEN 256
#define NUM_IMAGES 10

// Use the following enum and global constant to select the type of AVI video
// file to be created and saved.
typedef enum _fileType
{
	UNCOMPRESSED,
	MJPG,
	H264
} fileType;

const fileType chosenFileType = UNCOMPRESSED;

// This function prepares, saves, and cleans up an AVI video from a vector of 
// images.
spinError SaveArrayToAVI(spinNodeMapHandle hNodeMap, spinNodeMapHandle hNodeMapTLDevice, spinImage hImages[])
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	printf("\n\n*** CREATING VIDEO ***\n\n");

	//
	// Get the current frame rate; acquisition frame rate recorded in hertz
	//
	// *** NOTES ***
	// The video frame rate can be set to anything; however, in order to 
	// have videos play in real-time, the acquisition frame rate can be
	// retrieved from the camera.
	//
	spinNodeHandle hAcquisitionFrameRate = NULL;
	double acquisitionFrameRate = 0.0;
	float frameRateToSet = 0.0;

	err = spinNodeMapGetNode(hNodeMap, "AcquisitionFrameRate", &hAcquisitionFrameRate);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve frame rate (node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinFloatGetValue(hAcquisitionFrameRate, &acquisitionFrameRate);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve frame rate (value retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	frameRateToSet = (float)acquisitionFrameRate;

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

	//
	// Create a unique filename
	//
	// *** NOTES ***
	// This example creates filenames according to the type of AVI video 
	// being created. Notice that '.avi' does not need to be appended to the 
	// name of the file. This is because the AVI recorder object takes care
	// of the file extension automatically.
	//
	char filename[MAX_BUFF_LEN];
	size_t lenFilename = MAX_BUFF_LEN;

	if (chosenFileType == UNCOMPRESSED)
	{
		if (lenDeviceSerialNumber == 0)
		{
			sprintf(filename, "SaveToAvi-C-Uncompressed");
		}
		else
		{
			sprintf(filename, "SaveToAvi-C-%s-Uncompressed", deviceSerialNumber);
		}
	}
	else if (chosenFileType == MJPG)
	{
		if (lenDeviceSerialNumber == 0)
		{
			sprintf(filename, "SaveToAvi-C-MJPG");
		}
		else
		{
			sprintf(filename, "SaveToAvi-C-%s-MJPG", deviceSerialNumber);
		}
	}
	else if (chosenFileType == H264)
	{
		if (lenDeviceSerialNumber == 0)
		{
			sprintf(filename, "SaveToAvi-C-H264");
		}
		else
		{
			sprintf(filename, "SaveToAvi-C-%s-H264", deviceSerialNumber);
		}
	}

	//
	// Select option and open AVI filetype
	//
	// *** NOTES ***
	// Depending on the filetype, a number of settings need to be set in
	// an object called an option. An uncompressed option only needs to
	// have the video frame rate set whereas videos with MJPG or H264
	// compressions need to have more values set.
	//
	// Once the desired option object is configured, open the AVI file
	// with the option in order to create the image file.
	//
	// *** LATER ***
	// Once all images have been added, it is important to close the file -
	// this is similar to many other standard file streams.
	//
	spinAVIRecorder aviRecorder = NULL;

	if (chosenFileType == UNCOMPRESSED)
	{
		spinAVIOption option;

		option.frameRate = frameRateToSet;

		err = spinAVIRecorderOpenUncompressed(&aviRecorder, filename, option);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to open uncompressed AVI file. Aborting with error %d...\n\n", err);
			return err;
		}
	}
	else if (chosenFileType == MJPG)
	{
		spinMJPGOption option;

		option.frameRate = frameRateToSet;
		option.quality = 75;

		err = spinAVIRecorderOpenMJPG(&aviRecorder, filename, option);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to open MJPG AVI file. Aborting with error %d...\n\n", err);
			return err;
		}
	}
	else if (chosenFileType == H264)
	{
		spinH264Option option;

		option.frameRate = frameRateToSet;
		option.bitrate = 1000000;

		spinNodeHandle hWidth = NULL;
		int64_t width = 0;

		err = spinNodeMapGetNode(hNodeMap, "Width", &hWidth);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve width (node retrieval). Aborting with error %d...\n\n", err);
			return err;
		}

		err = spinIntegerGetValue(hWidth, &width);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve width (value retrieval). Aborting with error %d...\n\n", err);
			return err;
		}

		option.width = (unsigned int)width;

		spinNodeHandle hHeight = NULL;
		int64_t height = 0;

		err = spinNodeMapGetNode(hNodeMap, "Height", &hHeight);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve height (node retrieval). Aborting with error %d...\n\n", err);
			return err;
		}

		err = spinIntegerGetValue(hHeight, &height);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve height (value retrieval). Aborting with error %d...\n\n", err);
			return err;
		}

		option.height = (unsigned int)height;

		err = spinAVIRecorderOpenH264(&aviRecorder, filename, option);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to open H264 AVI file. Aborting with error %d...\n\n", err);
			return err;
		}
	}

	//
	// Construct and save AVI video
	//
	// *** NOTES ***
	// Although the video file has been opened, images must be individually
	// appended in order to construct the video. 
	//
	unsigned int imageCnt = 0;

	printf("Appending %d images to AVI file: %s.avi...\n\n", NUM_IMAGES, filename);

	for (imageCnt = 0; imageCnt < NUM_IMAGES; imageCnt++)
	{
		err = spinAVIRecorderAppend(aviRecorder, hImages[imageCnt]);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to append image. Aborting with error %d...\n\n", err);
			return err;
		}

		printf("\tAppended image %d...\n", imageCnt);
	}

	printf("\nVideo saved at %s.avi\n\n", filename);

	//
	// Close AVI file
	//
	// *** NOTES ***
	// Once all images have been appended, it is important to close the
	// AVI file. Notice that once an AVI file has been closed, no more
	// images can be added.
	//
	err = spinAVIRecorderClose(aviRecorder);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to close AVI file. Aborting with error %d...\n\n", err);
		return err;
	}

	// Destroy images
	for (imageCnt = 0; imageCnt < NUM_IMAGES; imageCnt++)
	{
		err = spinImageDestroy(hImages[imageCnt]);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to destroy image %d. Non-fatal error %d...\n\n", imageCnt, err);
		}
	}

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
	printf("\n");

	return err;
}

// This function acquires and saves 10 images from a device; please see
// Acquisition_C example for more in-depth comments on the acquisition of
// images.
spinError AcquireImages(spinCamera hCam, spinNodeMapHandle hNodeMap, spinNodeMapHandle hNodeMapTLDevice, spinImage hImages[])
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
	unsigned int imageCnt = 0;

	for (imageCnt = 0; imageCnt < NUM_IMAGES; imageCnt++)
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

		printf("Grabbed image %d, ", imageCnt);

		err = spinImageGetWidth(hResultImage, &width);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("width = unknown, ");
		}
		else
		{
			printf("width = %u, ", (unsigned int)width);
		}

		err = spinImageGetHeight(hResultImage, &height);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("height = unknown\n");
		}
		else
		{
			printf("height = %u\n", (unsigned int)height);
		}

		// Convert image to mono 8
		hImages[imageCnt] = NULL;
		
		err = spinImageCreateEmpty(&hImages[imageCnt]);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to create image. Non-fatal error %d...\n\n", err);
			hasFailed = True;
		}

		err = spinImageConvert(hResultImage, PixelFormat_Mono8, hImages[imageCnt]);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to convert image. Non-fatal error %d...\n\n", err);
			hasFailed = True;
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

	// Acquire images
	spinImage hImages[NUM_IMAGES];

	err = AcquireImages(hCam, hNodeMap, hNodeMapTLDevice, hImages);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	err = SaveArrayToAVI(hNodeMap, hNodeMapTLDevice, hImages);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Deinitialize camera
	err = spinCameraDeInit(hCam);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to deinitialize camera. Aborting with error %d...\n\n", err);
		return err;
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
