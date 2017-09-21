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
 *	@example Enumeration_C_QuickSpin.cpp
 *
 *	@brief Enumeration_C_QuickSpin.cpp shows how to enumerate interfaces
 *  and cameras using the QuickSpin API. QuickSpin is a subset of the Spinnaker
 *  library that allows for simpler node access and control. This is a great 
 *  example to start learning about QuickSpin.
 *
 *	This example introduces the preparation, use, and cleanup of the system
 *	object, interface and camera lists, interfaces, and cameras. It also 
 *	touches on retrieving information from pre-fetched nodes using QuickSpin.
 *	Retrieving node information is the only portion of the example that
 *	differs from Enumeration_C.
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

// This function queries an interface for its cameras and then prints out 
// device information.
spinError QueryInterface(spinInterface hInterface)
{
	spinError err = SPINNAKER_ERR_SUCCESS;
	unsigned int i = 0;

	//
	// Pre-fetch TL interface nodes
	//
	// *** NOTES ***
	// In order to use QuickSpin in C, it is required to manually pre-fetch
	// all available nodes into a QuickSpin struct, which then acts as the
	// means of accessing its nodes.
	//
	quickSpinTLInterface qsI;

	err = quickSpinTLInterfaceInit(hInterface, &qsI);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to pre-fetch TL interface nodes. Aborting with error %d...\n\n", err);
		return err;
	}

	//
	// Print interface display name
	//
	// *** NOTES ***
	// QuickSpin allows for the retrieval of interface information directly
	// from an initialized quickSpinTLInterface struct. Because interface
	// information is made available on the transport layer, camera
	// initialization is not required.
	//
	bool8_t interfaceDisplayNameIsAvailable = False;
	bool8_t interfaceDisplayNameIsReadable = False;
	char interfaceDisplayName[MAX_BUFF_LEN];
	size_t lenInterfaceDisplayName = MAX_BUFF_LEN;

	// Check availability
	err = spinNodeIsAvailable(qsI.InterfaceDisplayName, &interfaceDisplayNameIsAvailable);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to check node availability (interface display name). Aborting with error %d...\n\n", err);
		return err;
	}

	// Check readability
	err = spinNodeIsReadable(qsI.InterfaceDisplayName, &interfaceDisplayNameIsReadable);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to check node readability (interface display name). Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve and print
	if (interfaceDisplayNameIsAvailable && interfaceDisplayNameIsReadable)
	{
		err = spinStringGetValue(qsI.InterfaceDisplayName, interfaceDisplayName, &lenInterfaceDisplayName);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve value (interface display name). Aborting with error %d...\n\n", err);
			return err;
		}
	}
	else
	{
		strcpy(interfaceDisplayName, "Interface display name not readable");
	}

	printf("%s\n", interfaceDisplayName);

	//
	// Retrieve list of cameras from the interface
	//
	// *** NOTES ***
	// Camera lists can be retrieved from an interface or the system object.
	// Camera lists retrieved from an interface, such as this one, only return 
	// cameras attached on that specific interface whereas camera lists 
	// retrieved from the system will return all cameras on all interfaces.
	//
	// *** LATER ***
	// Camera lists must be cleared manually. This must be done prior to 
	// releasing the system and while the camera list is still in scope.
	// 
	spinCameraList hCameraList = NULL;
	size_t numCameras = 0;

	// Create empty camera list
	err = spinCameraListCreateEmpty(&hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to create camera list. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve cameras
	err = spinInterfaceGetCameras(hInterface, hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve camera list. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve number of cameras
	err = spinCameraListGetSize(hCameraList, &numCameras);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve number of cameras. Aborting with error %d...\n\n", err);
		return err;
	}

	// Return if no cameras detected
	if (numCameras == 0)
	{
		printf("\tNo devices detected.\n\n");

		//
		// Clear and destroy camera list before losing scope
		//
		// *** NOTES ***
		// Camera lists do not automatically clean themselves up. This must be done 
		// manually. The same is true of interface lists.
		//
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
		return err;
	}

	// Print device vendor and model name for each camera on the interface
	for (i = 0; i < numCameras; i++)
	{
		//
		// Select camera
		//
		// *** NOTES ***
		// Each camera is retrieved from a camera list with an index. If the
		// index is out of range, an exception is thrown.
		// 
		// *** LATER ***
		// Each camera handle needs to be released before losing scope or the
		// system is released.
		// 
		spinCamera hCam = NULL;

		err = spinCameraListGet(hCameraList, i, &hCam);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve camera. Aborting with error %d...\n\n", err);
			return err;
		}

		// Pre-fetch TL device nodes; please see NodeMapInfo_C_QuickSpin example
		// for more in-depth comments on pre-fetching nodes
		quickSpinTLDevice qsD;

		err = quickSpinTLDeviceInit(hCam, &qsD);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to pre-fetch TL device nodes. Aborting with error %d...\n\n", err);
			return err;
		}

		//
		// Retrieve device vendor name
		//
		// *** NOTES ***
		// A node is distinguished by type, which is related to its value's
		// data type. Also, they can be checked for availability and
		// readability/writability prior to making an attempt to read
		// from or write to a node.
		//
		bool8_t deviceVendorNameIsAvailable = False;
		bool8_t deviceVendorNameIsReadable = False;

		// Check availability
		err = spinNodeIsAvailable(qsD.DeviceVendorName, &deviceVendorNameIsAvailable);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to check availability (vendor name). Aborting with error %d...\n\n", err);
			return err;
		}

		// Check readability
		err = spinNodeIsReadable(qsD.DeviceVendorName, &deviceVendorNameIsReadable);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to check readability (vendor name). Aborting with error %d...\n\n", err);
			return err;
		}

		//
		// Retrieve device model name
		//
		// *** NOTES ***
		// Because C has no try-catch blocks, each functions returns an error
		// code to suggest whether an error has occurred. Errors can be 
		// sufficiently handled with these return codes. Checking availabily
		// and readability/writability makes for safer and more complete code;
		// however, keeping in mind example conciseness and legibility, only
		// this example and NodeMapInfo_C_QuickSpin demonstrate checking node
		// availability and readability/writability while other examples
		// handle errors with error codes alone.
		//
		bool8_t deviceModelNameIsAvailable = False;
		bool8_t deviceModelNameIsReadable = False;
		
		// Check availability
		err = spinNodeIsAvailable(qsD.DeviceModelName, &deviceModelNameIsAvailable);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to check availability (model name). Aborting with error %d...\n\n", err);
			return err;
		}

		// Check readability
		err = spinNodeIsReadable(qsD.DeviceModelName, &deviceModelNameIsReadable);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to check readability (model name). Aborting with error %d...\n\n", err);
			return err;
		}

		//
		// Print device vendor and model names
		//
		// *** NOTES ***
		// Generally it is best to check readability when it is required to read
		// information from a node and writability when it is required to write
		// to a node. For most nodes, writability implies readability while
		// readability does not imply writability.
		// 
		char deviceVendorName[MAX_BUFF_LEN];
		size_t lenDeviceVendorName = MAX_BUFF_LEN;
		char deviceModelName[MAX_BUFF_LEN];
		size_t lenDeviceModelName = MAX_BUFF_LEN;

		// Print device vendor name
		if (deviceVendorNameIsAvailable && deviceVendorNameIsReadable)
		{
			err = spinStringGetValue(qsD.DeviceVendorName, deviceVendorName, &lenDeviceVendorName);
			if (err != SPINNAKER_ERR_SUCCESS)
			{
				printf("Unable to retrieve device information (vendor name value). Aborting with error %d...\n\n", err);
				return err;
			}
		}
		else
		{
			strcpy(deviceVendorName, "Not readable");
		}

		// Print device model name
		if (deviceModelNameIsAvailable && deviceModelNameIsReadable)
		{
			err = spinStringGetValue(qsD.DeviceModelName, deviceModelName, &lenDeviceModelName);
			if (err != SPINNAKER_ERR_SUCCESS)
			{
				printf("Unable to retrieve device information (model name value). Aborting with error %d...\n\n", err);
				return err;
			}
		}
		else
		{
			strcpy(deviceModelName, "Not readable");
		}

		printf("\tDevice %d %s %s\n\n", i, deviceVendorName, deviceModelName);

		// 
		// Release camera before losing scope
		//
		// *** NOTES ***
		// Every handle that is created for a camera must be released before
		// the system is released or an exception will be thrown.
		// 
		err = spinCameraRelease(hCam);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to release camera. Aborting with error %d...\n\n", err);
			return err;
		}
	}

	//
	// Clear and destroy camera list before losing scope
	//
	// *** NOTES ***
	// Camera lists do not automatically clean themselves up. This must be done 
	// manually. The same is true of interface lists.
	//
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

	return err;
}

// Example entry point; this function sets up the system and retrieves 
// interfaces for the example.
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
	// Everything originates with the system object. It is important to notice
	// that it has a singleton implementation, so it is impossible to have 
	// multiple system objects at the same time.
	// 
	// *** LATER ***
	// The system object should be cleared prior to program completion.  If not
	// released explicitly, it will be released automatically.
	//
	spinSystem hSystem = NULL;
	
	err = spinSystemGetInstance(&hSystem);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve system instance. Aborting with error %d...\n\n", err);
		return err;
	}

	//
	// Retrieve list of interfaces from the system
	//
	// *** NOTES ***
	// Interface lists are retrieved from the system object.
	// 
	// *** LATER ***
	// Interface lists must be cleared and destroyed manually. This must be 
	// done prior to releasing the system and while the interface list is still 
	// in scope.
	// 
	spinInterfaceList hInterfaceList = NULL;
	size_t numInterfaces = 0;

	// Create empty interface list
	err = spinInterfaceListCreateEmpty(&hInterfaceList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to create empty interface list. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve interfaces from system
	err = spinSystemGetInterfaces(hSystem, hInterfaceList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve interface list. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve number of interfaces
	err = spinInterfaceListGetSize(hInterfaceList, &numInterfaces);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve number of interfaces. Aborting with err %d...\n\n", err);
		return err;
	}

	printf("Number of interfaces detected: %u\n\n", (unsigned int)numInterfaces);

	//
	// Retrieve list of cameras from the system
	//
	// *** NOTES ***
	// Camera lists can be retrieved from an interface or the system object.
	// Camera lists retrieved from the system, such as this one, return all
	// cameras available on the system.
	//
	// *** LATER ***
	// Camera lists must be cleared and destroyed manually. This must be done 
	// prior to releasing the system and while the camera list is still in 
	// scope.
	// 
	spinCameraList hCameraList = NULL;
	size_t numCameras = 0;

	// Create empty camera list
	err = spinCameraListCreateEmpty(&hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to create camera list. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve cameras from system
	err = spinSystemGetCameras(hSystem, hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve camera list. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve number of cameras
	err = spinCameraListGetSize(hCameraList, &numCameras);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve number of cameras. Aborting with  error %d...\n\n", err);
		return err;
	}

	printf("Number of cameras detected: %u\n\n", (unsigned int)numCameras);

	// Finish if there are no cameras
	if (numCameras == 0 || numInterfaces == 0)
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
		
		// Clear and destroy interface list before releasing system
		err = spinInterfaceListClear(hInterfaceList);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to clear interface list. Aborting with error %d...\n\n", err);
			return err;
		}

		err = spinInterfaceListDestroy(hInterfaceList);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to destroy interface list. Aborting with error %d...\n\n", err);
			return err;
		}
		
		// Release system
		err = spinSystemReleaseInstance(hSystem);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to release system instance. Aborting with  error %d...\n\n", err);
			return err;
		}

		printf("\nNot enough cameras/interfaces!\n");
		printf("Done! Press Enter to exit...\n");
		getchar();
		
		return -1;
	}

	printf("\n*** QUERYING INTERFACES ***\n\n");

	//
	// Run example on each interface
	//
	// *** NOTES ***
	// In order to run all interfaces in a loop, each interface needs to 
	// retrieved using its index.
	//
	for (i = 0; i < numInterfaces; i++)
	{
		// Select interface
		spinInterface hInterface = NULL;
		
		err = spinInterfaceListGet(hInterfaceList, i, &hInterface);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve interface from list (error %d)...\n", err);
			errReturn = err;
			continue;
		}

		// Run example
		err = QueryInterface(hInterface);
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
	// Clear and destroy camera list before releasing system
	//
	// *** NOTES ***
	// Camera lists are not shared pointers and do not automatically clean 
	// themselves up and break their own references. Therefore, this must be
	// done manually. The same is true of interface lists.
	//
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

	//
	// Clear and destroy interface list before releasing system
	//
	// *** NOTES ***
	// Interface lists are not shared pointers and do not automatically clean 
	// themselves up and break their own references. Therefore, this must be
	// done manually. The same is true of camera lists.
	//
	err = spinInterfaceListClear(hInterfaceList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to clear interface list. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinInterfaceListDestroy(hInterfaceList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to destroy interface list. Aborting with error %d...\n\n", err);
		return err;
	}

	//
	// Release system
	//
	// *** NOTES ***
	// The system should be released, but if it is not, it will do so itself.
	// It is often at the release of the system (whether manual or automatic)
	// that unbroken references and still registered events will throw an
	// exception.
	//
	err = spinSystemReleaseInstance(hSystem);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to release system instance. Aborting with  error %d...\n\n", err);
		return err;
	}

	printf("\nDone! Press Enter to exit...\n");
	getchar();

	return errReturn;
}
