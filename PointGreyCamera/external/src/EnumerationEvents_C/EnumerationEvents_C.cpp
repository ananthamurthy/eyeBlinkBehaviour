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
 *	@example EnumerationEvents_C.cpp
 *
 *	@brief EnumerationEvents_C.cpp explores arrival and removal events on
 *	interfaces and the system. It relies on information provided in the
 *	Enumeration_C, Acquisition_C, and NodeMapInfo_C examples.
 *
 *	It can also be helpful to familiarize yourself with the NodeMapCallback_C
 *	example, as a callback can be thought of as a simpler, easier-to-use event.
 *	Although events are more cumbersome, they are also much more flexible and
 *	extensible.
 *
 *	Events generally require a class to be defined as an event handler; however, 
 *	because C is not an object-oriented language, a pseudo-class is created 
 *	using a function (or two) and a struct whereby the function(s) acts as the 
 *	event handler method and the struct acts as its properties.
 */

#include "SpinnakerC.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

// Compiler warning C4996 suppressed due to deprecated strcpy() and sprintf() 
// functions on Windows platform.
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64 
	#pragma warning(disable : 4996)
#endif

// This macro helps with C-strings.
#define MAX_BUFF_LEN 256

// This struct represents what would be the properties of a interface event 
// handler were we working in an object-oriented programming language. The 
// struct is created with a pointer and passed into the function, which creates 
// persistent data, mimicking the properties of a class. Notice that there is
// no struct to represent the system object passed into the system event
// handler. This is because the system pseudo-handler only requires a single
// object to be passed in. The system pointer can be passed in as a void
// pointer in the same way that this struct is passed in. Further, NULL can
// be passed in if no object is required.
typedef struct _userData
{
	spinInterface hInterface;
	int interfaceNum;
} userData;

// This function represents what would be the arrival event method of the
// interface event handler. Together with the struct above and the function
// below, this makes up a sort of event handler pseudo-class. Notice that the
// function signatures must match exactly for the function to be accepted when
// creating the event.
void onDeviceArrivalInterface(void* pUserData)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	// Cast void pointer back to struct
	userData* interfaceInfo = (userData*)pUserData;

	// Retrieve device serial number from interface
	spinCameraList hCameraList = NULL;

	err = spinCameraListCreateEmpty(&hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to create camera list (interface %d). Non-fatal error %d...\n\n", interfaceInfo->interfaceNum, err);
		return;
	}

	err = spinInterfaceGetCameras(interfaceInfo->hInterface, hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve camera list (interface %d). Non-fatal error %d...\n\n", interfaceInfo->interfaceNum, err);
		return;
	}

	spinCamera hCamera = NULL;

	err = spinCameraListGet(hCameraList, 0, &hCamera);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve camera (interface %d). Non-fatal error %d...\n\n", interfaceInfo->interfaceNum, err);
		return;
	}

	spinNodeMapHandle hNodeMapTLDevice = NULL;

	err = spinCameraGetTLDeviceNodeMap(hCamera, &hNodeMapTLDevice);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve nodemap (interface %d). Non-fatal error %d...\n\n", interfaceInfo->interfaceNum, err);
		return;
	}

	spinNodeHandle hDeviceSerialNumber = NULL;

	err = spinNodeMapGetNode(hNodeMapTLDevice, "DeviceSerialNumber", &hDeviceSerialNumber);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve node (interface %d). Non-fatal error %d...\n\n", interfaceInfo->interfaceNum, err);
		return;
	}

	char deviceSerialNumber[MAX_BUFF_LEN];
	size_t lenDeviceSerialNumber = MAX_BUFF_LEN;

	err = spinStringGetValue(hDeviceSerialNumber, deviceSerialNumber, &lenDeviceSerialNumber);
	if (err != SPINNAKER_ERR_SUCCESS) 
	{
		printf("Unable to retrieve device serial number (interface %d). Non-fatal error %d...\n\n", interfaceInfo->interfaceNum, err);
		return;
	}

	// Print arrival information
	printf("Interface event handler:\n");
	printf("\tDevice %s has arrived on interface %d.\n\n", deviceSerialNumber, interfaceInfo->interfaceNum);

	// Release camera
	err = spinCameraRelease(hCamera);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to release camera (interface %d). Non-fatal error %d...\n\n", interfaceInfo->interfaceNum, err);
		return;
	}

	// Clear and destroy camera list while still in scope
	err = spinCameraListClear(hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to clear camera list (interface %d). Non-fatal error %d...\n\n", interfaceInfo->interfaceNum, err);
		return;
	}

	err = spinCameraListDestroy(hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to destroy camera list (interface %d). Non-fatal error %d...\n\n", interfaceInfo->interfaceNum, err);
		return;
	}
}

// This function represent what would be the removal event. Notice how persistent 
// data is cast from the void pointer and manipulated. 
void onDeviceRemovalInterface(uint64_t deviceSerialNumber, void* pUserData)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	// Cast void pointer back to struct
	userData* interfaceInfo = (userData*)pUserData;

	// Print removal information
	printf("Interface event handler:\n");
	printf("\tDevice %u was removed from interface %d.\n\n", (unsigned int)deviceSerialNumber, interfaceInfo->interfaceNum);
}

// This function is similar to the arrival event function above except that it
// represents an arrival event on the system rather than just a single interface.
// Notice how the system object is cast back to a system object.
void onDeviceArrivalSystem(void* pUserData)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	// Cast void pointer back to system object
	spinSystem hSystem = (spinSystem*)pUserData;

	// Retrieve count
	spinCameraList hCameraList = NULL;

	err = spinCameraListCreateEmpty(&hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to create camera list (system arrival). Non-fatal error %d...\n\n", err);
		return;
	}

	err = spinSystemGetCameras(hSystem, hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve camera list (system arrival). Non-fatal error %d...\n\n", err);
		return;
	}

	size_t numCameras = 0;

	err = spinCameraListGetSize(hCameraList, &numCameras);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve camera list size (system arrival). Non-fatal error %d...\n\n", err);
		return;
	}

	// Print count
	printf("System event handler:\n");
	printf("\tThere %s %u %s on the system.\n\n", (numCameras == 1 ? "is" : "are"), (unsigned int)numCameras, (numCameras == 1 ? "device" : "devices"));

	// Clear and destroy camera list while still in scope
	err = spinCameraListClear(hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to clear camera list (system arrival). Non-fatal error %d...\n\n", err);
		return;
	}

	err = spinCameraListDestroy(hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to destroy camera list (system arrival). Non-fatal error %d...\n\n", err);
		return;
	}
}

// This function represents a removal event on the system. The code inside is 
// exactly the same as the arrival event. This repeated code could be extracted
// out into a separate function for improved code.
void onDeviceRemovalSystem(uint64_t deviceSerialNumber, void* pUserData)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	// Cast void pointer back to system object
	spinSystem hSystem = (spinSystem*)pUserData;

	// Retrieve count
	spinCameraList hCameraList = NULL;

	err = spinCameraListCreateEmpty(&hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to create camera list (system removal). Non-fatal error %d...\n\n", err);
		return;
	}

	err = spinSystemGetCameras(hSystem, hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve camera list (system removal). Non-fatal error %d...\n\n", err);
		return;
	}

	size_t numCameras = 0;

	err = spinCameraListGetSize(hCameraList, &numCameras);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve camera list size (system removal). Non-fatal error %d...\n\n", err);
		return;
	}

	// Print count
	printf("System event handler:\n");
	printf("\tThere %s %u %s on the system.\n\n", (numCameras == 1 ? "is" : "are"), (unsigned int)numCameras, (numCameras == 1 ? "device" : "devices"));

	// Clear camera list while still in scope
	err = spinCameraListClear(hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to clear camera list (system removal). Non-fatal error %d...\n\n", err);
		return;
	}

	err = spinCameraListDestroy(hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to destroy camera list (system removal). Non-fatal error %d...\n\n", err);
		return;
	}
}

// Example entry point; this function sets up the example to act appropriately 
// upon arrival and removal events; please see Enumeration example for more 
// in-depth comments on preparing and cleaning up the system.
int main(/*int argc, char** argv*/)
{
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
	size_t numCameras = 0;

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

	err = spinCameraListGetSize(hCameraList, &numCameras);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve number of cameras. Aborting with  error %d...\n\n", err);
		return err;
	}

	printf("Number of cameras detected: %u\n\n", (unsigned int)numCameras);

	// Retrieve list of interfaces from the system
	spinInterfaceList hInterfaceList = NULL;
	size_t numInterfaces = 0;

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

	err = spinInterfaceListGetSize(hInterfaceList, &numInterfaces);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve number of interfaces. Aborting with err %d...\n\n", err);
		return err;
	}

	printf("Number of interfaces detected: %u\n\n", (unsigned int)numInterfaces);

	printf("\n*** CONFIGURE ENUMERATION EVENTS ***\n\n");

	//
	// Create interface event for the system
	//
	// *** NOTES ***
	// The function for the system has been constructed to accept a system in 
	// order to print the number of cameras on the system. Notice that there
	// are 3 types of events that can be created: arrival events, removal events,
	// and interface events, which are a combination of arrival and removal
	// events. Here, the an interface event is created, which requires both
	// an arrival event and a removal event object.
	//
	// *** LATER ***
	// In Spinnaker C, every event that is created must be destroyed to avoid
	// memory leaks.
	//
	spinInterfaceEvent interfaceEventSystem = NULL;

	err = spinInterfaceEventCreate(&interfaceEventSystem, onDeviceArrivalSystem, onDeviceRemovalSystem, (void*)hSystem);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to create interface event for system. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Interface event for system created...\n");

	//
	// Register interface event for the system
	//
	// *** NOTES ***
	// Arrival, removal, and interface events can all be registered to 
	// interfaces or the system. Do not think that interface events can only be
	// registered to an interface.
	//
	// *** LATER ***
	// Arrival, removal, and interface events must all be unregistered manually.
	// This must be done prior to releasing the system and while they are still
	// in scope.
	//
	err = spinSystemRegisterInterfaceEvent(hSystem, interfaceEventSystem);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to register interface event on system. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Interface event registered to system...\n");

	//
	// Prepare user data
	//
	// *** NOTES ***
	// It is important to ensure that all requisite variables are initialized
	// appropriately before creating the device event. Notice that a different
	// user data struct is required for each interface. This is because each
	// struct will house a different interface reference. Because memory is
	// being allocated for a variable length, free() must be called at the end
	// of the example.
	//
	// *** LATER ***
	// It is a good idea to keep this data in scope in order to avoid memory
	// leaks. 
	//
	userData *interfaceInfos;

	interfaceInfos = (userData*)malloc(numInterfaces * sizeof(userData));

	//
	// Create and register arrival and removal events to each interface
	//
	// *** NOTES ***
	// Separate arrival and event objects have been created for each interface.
	// This is for demonstration purposes as an interface event object (which is 
	// simply a combination of an arrival and removal event object) is more
	// appropriate in this instance.
	//
	// *** LATER ***
	// Arrival, removal, and interface events must all be unregistered manually.
	// This must be done prior to releasing the system and while they are still
	// in scope. Also, every event that is created must be destroyed to avoid
	// memory leaks. Because memory is being allocated for a variable length,
	// free() must be called at the end of the example.
	//
	spinArrivalEvent* arrivalEvents;
	spinRemovalEvent* removalEvents;

	arrivalEvents = (spinArrivalEvent*)malloc(numInterfaces * sizeof(spinArrivalEvent));
	removalEvents = (spinRemovalEvent*)malloc(numInterfaces * sizeof(spinRemovalEvent));

	for (i = 0; i < numInterfaces; i++)
	{
		// Initialize user data for selected interface
		interfaceInfos[i].interfaceNum = i;
		
		err = spinInterfaceListGet(hInterfaceList, i, &interfaceInfos[i].hInterface);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve interface %d. Aborting with error %d...\n\n", i, err);
			return err;
		}

		// Create arrival event for selected interface
		arrivalEvents[i] = NULL;

		err = spinArrivalEventCreate(&arrivalEvents[i], onDeviceArrivalInterface, (void*)&interfaceInfos[i]);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to create arrival event for interface %d. Aborting with error %d...\n\n", i, err);
			return err;
		}

		// Create removal event for selected interface
		removalEvents[i] = NULL;

		err = spinRemovalEventCreate(&removalEvents[i], onDeviceRemovalInterface, (void*)&interfaceInfos[i]);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to create removal event for interface %d. Aborting with error %d...\n\n", i, err);
			return err;
		}

		// Register arrival event to selected interface
		err = spinInterfaceRegisterArrivalEvent(interfaceInfos[i].hInterface, arrivalEvents[i]);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to create arrival event for interface %d. Aborting with error %d...\n\n", i, err);
			return err;
		}

		// Register removal event to selected interface
		err = spinInterfaceRegisterRemovalEvent(interfaceInfos[i].hInterface, removalEvents[i]);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to create removal event for interface %d. Aborting with error %d...\n\n", i, err);
			return err;
		}
	}

	printf("Arrival and removal events created and registered to all interfaces...\n\n");

	// Wait for user to plug in and/or remove camera devices
	printf("Ready! Remove/Plug in cameras to test or press Enter to exit...\n");
	getchar();

	//
	// Unregister arrival and removal events from each interface
	//
	// *** NOTES ***
	// It is important to unregister all arrival, removal, and interface events
	// from all interfaces that they may be registered to. 
	//
	for (i = 0; i < numInterfaces; i++)
	{
		err = spinInterfaceUnregisterArrivalEvent(interfaceInfos[i].hInterface, arrivalEvents[i]);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to unregister arrival event from interface %d. Aborting with error %d...\n\n", i, err);
			return err;
		}

		err = spinInterfaceUnregisterRemovalEvent(interfaceInfos[i].hInterface, removalEvents[i]);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to unregister removal event from interface %d. Aborting with error %d...\n\n", i, err);
			return err;
		}

		// Release interface
		err = spinInterfaceRelease(interfaceInfos[i].hInterface);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to release interface %d. Aborting with error %d...\n\n", i, err);
			return err;
		}
	}

	printf("Event handlers unregistered from interfaces...\n");

	//
	// Destroy arrival and removal events and release interfaces
	//
	// *** NOTES ***
	// Events must be destroyed in order to avoid memory leaks.
	//
	for (i = 0; i < numInterfaces; i++)
	{
		err = spinArrivalEventDestroy(arrivalEvents[i]);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to destroy arrival event %d. Aborting with error %d...\n\n", i, err);
			return err;
		}

		err = spinRemovalEventDestroy(removalEvents[i]);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to destroy removal event %d. Aborting with error %d...\n\n", i, err);
			return err;
		}
	}

	//
	// Free memory
	//
	// *** NOTES ***
	// It is important to free any allocated memory to avoid memory leaks.
	//
	free(arrivalEvents);
	free(removalEvents);
	free(interfaceInfos);

	printf("Interface event handlers destroyed...\n");

	//
	// Unregister system event from system object
	//
	// *** NOTES ***
	// It is important to unregister all arrival, removal, and interface events
	// registered to the system.
	//
	err = spinSystemUnregisterInterfaceEvent(hSystem, interfaceEventSystem);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to unregister interface event from system. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Event handlers unregistered from system...\n");

	//
	// Destroy interface events
	//
	// *** NOTES ***
	// Events must be destroyed in order to avoid memory leaks.
	//
	err = spinInterfaceEventDestroy(interfaceEventSystem);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to destroy interface event. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("System event handler destroyed...\n");

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

	printf("\nDone! Press Enter to exit...\n");
	getchar();

	return err;
}
