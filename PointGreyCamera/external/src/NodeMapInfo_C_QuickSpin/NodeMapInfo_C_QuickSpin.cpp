//=============================================================================
// Copyright © 2016 Point Grey Research, Inc. All Rights Reserved.
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
 *	@example NodeMapInfo_C_QuickSpin.cpp
 *
 *	@brief NodeMapInfo_C_QuickSpin.cpp shows how to interact with nodes
 *  using the QuickSpin API. QuickSpin is a subset of the Spinnaker library 
 *  that allows for simpler node access and control.
 *
 *  This example demonstrates the retrieval of information from both the
 *  transport layer and the camera. Because the focus of this example is node
 *  access, which is where QuickSpin and regular Spinnaker differ, this 
 *  example differs from NodeMapInfo_C quite a bit.
 *
 *  A much wider range of topics is covered in the full Spinnaker examples than
 *  in the QuickSpin ones. There are only enough QuickSpin examples to
 *  demonstrate node access and to get started with the API; please see full
 *  Spinnaker examples for further or specific knowledge on a topic.
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

// This macro defines the maximum number of characters that will be printed out
// for any information retrieved from a node.
#define MAX_CHARS 35

//
spinError PrintTransportLayerDeviceInfo(spinCamera hCamera)
{
	spinError errReturn = SPINNAKER_ERR_SUCCESS;
	spinError err = SPINNAKER_ERR_SUCCESS;
	
	//
	// Pre-fetch TL device nodes
	//
	// *** NOTES ***
	// In order to use QuickSpin in C, it is required to manually pre-fetch
	// all available nodes into a QuickSpin struct, which then acts as the
	// means of accessing its nodes. In order to pre-fetch TL device nodes,
	// the quickSpinTLDeviceInit() function and its corresponding 
	// quickSpinTLDevice object are used.
	//
	// The main advantage of transport layer nodes is that they do not require
	// camera initialization. The main disadvantage is that there is much less
	// camera information and interaction that may be performed.
	//
	quickSpinTLDevice qsD;

	err = quickSpinTLDeviceInit(hCamera, &qsD);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to pre-fetch TL device nodes. Aborting with error %d...\n\n", err);
		return err;
	}

	//
	// Print device information from the transport layer
	//
	// *** NOTES ***
	// In QuickSpin, accessing device information on the transport layer is
	// accomplished via a camera's quickSpinTLDevice object. The 
	// quickSpinTLDevice object houses nodes related to general device 
	// information such as the three demonstrated below, device access status, 
	// XML and GUI paths and locations, and GEV information to name a few. The 
	// quickSpinTLDevice property allows access to nodes that would generally 
	// be retrieved through the TL device nodemap in full Spinnaker.
	//
	// Print device serial number
	char deviceSerialNumber[MAX_BUFF_LEN];
	size_t lenDeviceSerialNumber = MAX_BUFF_LEN;

	printf("Device serial number: ");

	err = spinNodeToString(qsD.DeviceSerialNumber, deviceSerialNumber, &lenDeviceSerialNumber);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(deviceSerialNumber, "unavailable");
		errReturn = err;
	}

	printf("%s\n", deviceSerialNumber);

	// Print device vendor name
	char deviceVendorName[MAX_BUFF_LEN];
	size_t lenDeviceVendorName = MAX_BUFF_LEN;

	printf("Device vendor name: ");

	err = spinNodeToString(qsD.DeviceVendorName, deviceVendorName, &lenDeviceVendorName);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(deviceVendorName, "unavailable");
		errReturn = err;
	}

	printf("%s\n", deviceVendorName);

	// Print device display name
	char deviceDisplayName[MAX_BUFF_LEN];
	size_t lenDeviceDisplayName = MAX_BUFF_LEN;

	printf("Device display name: ");

	err = spinNodeToString(qsD.DeviceDisplayName, deviceDisplayName, &lenDeviceDisplayName);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(deviceDisplayName, "unavailable");
		errReturn = err;
	}

	printf("%s\n\n", deviceDisplayName);

	return errReturn;
}

spinError PrintTransportLayerStreamInfo(spinCamera hCamera)
{
	spinError errReturn = SPINNAKER_ERR_SUCCESS;
	spinError err = SPINNAKER_ERR_SUCCESS;

	//
	// Pre-fetch TL device nodes
	//
	// *** NOTES ***
	// Separate from TL device, but still on the transport layer, the TL stream
	// nodes provide information. TL stream nodes are accessed via the
	// quickspinTLStreamInit() function and its corresponding quickSpinTLStream
	// object.
	//
	quickSpinTLStream qsS;

	err = quickSpinTLStreamInit(hCamera, &qsS);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to pre-fetch TL stream nodes. Aborting with error %d...\n\n", err);
		return err;
	}

	//
	// Print stream information from the transport layer
	//
	// *** NOTES ***
	// In QuickSpin, accessing stream information on the transport layer is
	// accomplished via a camera's quickSpinTLStream object. The 
	// quickSpinTLStream object houses nodes related to streaming such as the 
	// two demonstrated below, buffer information, and GEV packet information
	// to name a few. The quickSpinTLStream object allows access to nodes that 
	// would generally be retrieved through the TL stream nodemap in full 
	// Spinnaker.
	//
	// Print stream serial
	char streamID[MAX_BUFF_LEN];
	size_t lenStreamID = MAX_BUFF_LEN;

	printf("Stream ID: ");

	err = spinNodeToString(qsS.StreamID, streamID, &lenStreamID);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(streamID, "unavailable");
		errReturn = err;
	}

	printf("%s\n", streamID);

	// Print stream type
	char streamType[MAX_BUFF_LEN];
	size_t lenStreamType = MAX_BUFF_LEN;

	printf("Stream type: ");

	err = spinNodeToString(qsS.StreamType, streamType, &lenStreamType);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(streamType, "unavailable");
		errReturn = err;
	}

	printf("%s\n\n", streamType);

	return errReturn;
}

spinError PrintTransportLayerInterfaceInfo(spinInterface hInterface)
{
	spinError errReturn = SPINNAKER_ERR_SUCCESS;
	spinError err = SPINNAKER_ERR_SUCCESS;

	//
	// Pre-fetch TL interface nodes
	//
	// *** NOTES ***
	// The final group of nodes on the transport layer are the interface nodes. 
	// TL interface nodes are accessed via the quickspinTLInterfaceInit() 
	// function and its corresponding quickSpinTLInterface object. Of course,
	// these nodes are accessed via interfaces instead of cameras.
	//
	quickSpinTLInterface qsI;

	err = quickSpinTLInterfaceInit(hInterface, &qsI);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to pre-fetch TL interface nodes. Aborting with error %d...\n\n", err);
		return err;
	}

	//
	// Print interface information from the transport layer
	//
	// *** NOTES ***
	// In QuickSpin, accessing interface information is accomplished via an
	// interface's quickSpinTLInterface object. The quickSpinTLInterface object 
	// houses nodes that hold information about the interface such as the three
	// demonstrated below, other general interface information, and 
	// GEV addressing information. The quickSpinTLInterface object allows 
	// access to nodes that would generally be retrieved through the interface 
	// nodemap in full Spinnaker.
	//
	// Print interface display name
	char interfaceDisplayName[MAX_BUFF_LEN];
	size_t lenInterfaceDisplayName = MAX_BUFF_LEN;

	printf("Interface display name: ");

	err = spinNodeToString(qsI.InterfaceDisplayName, interfaceDisplayName, &lenInterfaceDisplayName);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(interfaceDisplayName, "unavailable");
		errReturn = err;
	}

	printf("%s\n", interfaceDisplayName);

	// Print interface ID
	char interfaceID[MAX_BUFF_LEN];
	size_t lenInterfaceID = MAX_BUFF_LEN;

	printf("Interface ID: ");
	
	err = spinNodeToString(qsI.InterfaceID, interfaceID, &lenInterfaceID);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(interfaceID, "unavailable");
		errReturn = err;
	}

	printf("%s\n", interfaceID);

	// Print interface type
	char interfaceType[MAX_BUFF_LEN];
	size_t lenInterfaceType = MAX_BUFF_LEN;

	printf("Interface type: ");

	err = spinNodeToString(qsI.InterfaceType, interfaceType, &lenInterfaceType);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(interfaceType, "unavailable");
		errReturn = err;
	}

	printf("%s\n\n", interfaceType);

	return errReturn;
}

spinError PrintGenICamInfo(spinCamera hCamera)
{
	spinError errReturn = SPINNAKER_ERR_SUCCESS;
	spinError err = SPINNAKER_ERR_SUCCESS;

	//
	// Pre-fetch GenICam nodes
	//
	// *** NOTES ***
	// Unlike other nodes, GenICam nodes are not on the transport layer. 
	// These nodes are accessed via the quickSpinInit() function and its
	// corresponding quickSpin object.
	//
	// The main advantages of GenICam nodes is that there are a lot more of
	// them and that they provide a much deeper level of interaction with a
	// camera. The main disadvantage is that they require camera
	// initialization.
	//
	quickSpin qs;

	err = quickSpinInit(hCamera, &qs);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to pre-fetch TL device nodes. Aborting with error %d...\n\n", err);
		return err;
	}

	//
	// Print device information from the camera
	//
	// *** NOTES ***
	// In QuickSpin, accessing most camera information and customizing most
	// settings requires access to GenICam nodes, which requires camera
	// initialization. Note that QuickSpin initialization and camera 
	// initialization are two different processes, both of which are required
	// to access GenICam nodes through QuickSpin.
	//
	// Print exposure time
	char exposureTime[MAX_BUFF_LEN];
	size_t lenExposureTime = MAX_BUFF_LEN;

	printf("Exposure time: ");

	err = spinNodeToString(qs.ExposureTime, exposureTime, &lenExposureTime);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(exposureTime, "unavailable");
		errReturn = err;
	}

	printf("%s\n", exposureTime);

	// Print black level
	char blackLevel[MAX_BUFF_LEN];
	size_t lenBlackLevel = MAX_BUFF_LEN;

	printf("Black level: ");

	err = spinNodeToString(qs.BlackLevel, blackLevel, &lenBlackLevel);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(blackLevel, "unavailable");
		errReturn = err;
	}

	printf("%s\n", blackLevel);

	// Print height
	char height[MAX_BUFF_LEN];
	size_t lenHeight = MAX_BUFF_LEN;

	printf("Device display name: ");

	err = spinNodeToString(qs.Height, height, &lenHeight);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(height, "unavailable");
		errReturn = err;
	}

	printf("%s\n\n", height);

	return errReturn;
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

	// 
	// Retrieve singleton reference to system object
	//
	// *** NOTES ***
	// Everything originates from the system. Notice that it is implemented as 
	// a singleton object, making it impossible to have more than one system.
	// 
	// *** LATER ***
	// The system object should be cleared prior to program completion. If not 
	// released explicitly, it will release itself automatically.
	//
	spinSystem hSystem = NULL;

	err = spinSystemGetInstance(&hSystem);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve system instance. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve list of interfaces from the system
	spinInterfaceList hInterfaceList = NULL;

	err = spinInterfaceListCreateEmpty(&hInterfaceList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to create interface list. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinSystemGetInterfaces(hSystem, hInterfaceList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve interface list. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve number of interfaces
	size_t numInterfaces = 0;

	err = spinInterfaceListGetSize(hInterfaceList, &numInterfaces);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve number of interfaces. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Number of interfaces detected: %u\n\n", (unsigned int)numInterfaces);
	
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

	//
	// Print information on each interface
	//
	// *** NOTES ***
	// All USB 3 Vision and GigE Vision interfaces should enumerate for
	// Spinnaker.
	//
	printf("\n*** PRINTING INTERFACE INFORMATION ***\n\n");

	for (i = 0; i < numInterfaces; i++)
	{
		// Retrieve interface
		spinInterface hInterface = NULL;

		err = spinInterfaceListGet(hInterfaceList, i, &hInterface);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}

		// Print TL information
		err = PrintTransportLayerInterfaceInfo(hInterface);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}

		// Release interface
		err = spinInterfaceRelease(hInterface);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}
	}

	//
	// Print general device information on each camera from transport layer
	//
	// *** NOTES ***
	// Transport layer nodes do not require initialization in order to interact
	// with them.
	//
	printf("\n*** PRINTING TRANSPORT LAYER DEVICE INFORMATION ***\n\n");

	for (i = 0; i < numCameras; i++)
	{
		// Retrieve camera
		spinCamera hCamera = NULL;

		err = spinCameraListGet(hCameraList, i, &hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}

		// Print TL device information
		err = PrintTransportLayerDeviceInfo(hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}

		// Release camera
		err = spinCameraRelease(hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}
	}

	//
	// Print streaming information on each camera from transport layer
	//
	// *** NOTES ***
	// Again, initialization is not required to print information from the 
	// transport layer; this is equally true of streaming information.
	//
	printf("\n*** PRINTING TRANSPORT LAYER STREAM INFORMATION ***\n\n");

	for (i = 0; i < numCameras; i++)
	{
		// Select camera
		spinCamera hCamera = NULL;

		err = spinCameraListGet(hCameraList, i, &hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}

		// Print TL stream information
		err = PrintTransportLayerStreamInfo(hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}

		// Release camera
		err = spinCameraRelease(hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}
	}

	//
	// Print device information on each camera from GenICam nodemap
	//
	// *** NOTES ***
	// GenICam nodes require initialization in order to interact with
	// them; as such, this loop initializes the camera, prints some information
	// from the GenICam nodemap, and then deinitializes it. If the camera were
	// not initialized, node availability would fail.
	//
	printf("\n*** PRINTING GENICAM INFORMATION ***\n\n");

	for (i = 0; i < numCameras; i++)
	{
		// Select camera
		spinCamera hCamera = NULL;

		err = spinCameraListGet(hCameraList, i, &hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}

		// Initialize camera
		err = spinCameraInit(hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}

		// Print GenICam information
		err = PrintGenICamInfo(hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}

		// Deinitialize information
		err = spinCameraDeInit(hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}

		// Release camera
		err = spinCameraRelease(hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}
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

	// Clear interface list before releasing system
	err = spinInterfaceListClear(hInterfaceList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to clean interface list. Aborting with error %d...\n\n", err);
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
