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
 *	@example Enumeration_QuickSpin.cpp
 *
 *  @brief Enumeration_QuickSpin.cpp shows how to enumerate interfaces
 *  and cameras using the QuickSpin API. QuickSpin is a subset of the Spinnaker
 *  library that allows for simpler node access and control. This is a great 
 *  example to start learning about QuickSpin.
 *
 *	This example introduces the preparation, use, and cleanup of the system
 *	object, interface and camera lists, interfaces, and cameras. It also
 *	touches on retrieving information from pre-fetched nodes using QuickSpin.
 *	Retrieving node information is the only portion of the example that
 *	differs from Enumeration.
 *
 *  A much wider range of topics is covered in the full Spinnaker examples than
 *  in the QuickSpin ones. There are only enough QuickSpin examples to
 *  demonstrate node access and to get started with the API; please see full
 *  Spinnaker examples for further or specific knowledge on a topic.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// This function queries an interface for its cameras and then prints out some 
// device information.
int QueryInterface(InterfacePtr pInterface)
{
	int result = 0;

	try
	{
		//
		// Print interface display name
		//
		// *** NOTES ***
		// QuickSpin allows for the retrieval of interface information directly
		// from an interface. Because interface information is made available 
		// on the transport layer, camera initialization is not required.
		//
		if (IsAvailable(pInterface->TLInterface.InterfaceDisplayName) && IsReadable(pInterface->TLInterface.InterfaceDisplayName))
		{
			gcstring interfaceDisplayName = pInterface->TLInterface.InterfaceDisplayName.GetValue();

			cout << interfaceDisplayName << endl;
		}
		else
		{
			cout << "Interface display name not readable" << endl;
		}

		//
		// Update list of cameras on the interface
		//
		// *** NOTES ***
		// Updating the camera list on each interface is especially important 
		// if there have been any device arrivals or removals since accessing 
		// the camera list.
		//
		pInterface->UpdateCameras();

		//
		// Retrieve list of cameras from the interface
		//
		// *** NOTES ***
		// Camera lists are retrieved from interfaces or the system object. 
		// Camera lists received from the system are constituted of all available 
		// cameras. Iterating through the cameras can be accomplished with a 
		// foreach loop, which will dispose of each camera appropriately. 
		// Individual cameras can be accessed using an index.
		// 
		// *** LATER ***
		// Camera lists must be disposed of manually. This must be done prior 
		// to releasing the system and while still in scope.
		// 
		CameraList camList = pInterface->GetCameras();

		unsigned int numCameras = camList.GetSize();

		// Return if no cameras detected
		if (numCameras == 0)
		{
			cout << "\tNo devices detected." << endl << endl;
			return 0;
		}

		// Print device vendor and model name for each camera on the interface
		for (unsigned int i = 0; i < numCameras; i++)
		{
			//
			// Select camera
			//
			// *** NOTES ***
			// Each camera is retrieved from a camera list with an index. If 
			// the index is out of range, an exception is thrown.
			// 
			CameraPtr pCam = camList.GetByIndex(i);

			cout << "\tDevice " << i << " ";

			//
			// Print device vendor name and device model name
			//
			// *** NOTES ***
			// In QuickSpin, accessing nodes does not require first retrieving a
			// nodemap. Instead, GenICam nodes are made available 
			// directly through the camera, and transport layer nodes are made 
			// available through the camera's TLDevice and TLStream properties.
			//
			// Most camera interaction happens through the GenICam nodemap, which 
			// requires the device to be initialized. Simpler reads, like the 
			// ones below, can often be accomplished at the transport layer, 
			// which does not require initialization; please see 
			// NodeMapInfo_QuickSpin for additional information on this topic.
			//
			// Availability and readability/writability should be checked 
			// prior to interacting with nodes. Availability is ensured by 
			// checking for null. Readability and writability are ensured 
			// either by checking the access mode or by using the methods 
			// demonstrated in the full Spinnaker examples.
			//
			if (pCam->TLDevice.DeviceVendorName != NULL && pCam->TLDevice.DeviceVendorName.GetAccessMode() == RO)
			{
				gcstring deviceVendorName = pCam->TLDevice.DeviceVendorName.GetValue();

				cout << deviceVendorName << " ";
			}

			if (pCam->TLDevice.DeviceModelName != NULL && pCam->TLDevice.DeviceModelName.GetAccessMode() == RO)
			{
				gcstring deviceModelName = pCam->TLDevice.DeviceModelName.GetValue();

				cout << deviceModelName << " " << endl << endl;
			}
		}

		//
		// Clear camera list before losing scope
		//
		// *** NOTES ***
		// Camera lists must be cleared before losing scope in order to ensure 
		// that references are appropriately broken before releasing the system 
		// object.
		//
		camList.Clear();
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// Example entry points; this function sets up the system and retrieves 
// interfaces to feed into the example.
int main(int /*argc*/, char** /*argv*/)
{
	int result = 0;

	// Print application build information
	cout << "Application build date: " << __DATE__ << " " << __TIME__ << endl << endl;

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
	SystemPtr system = System::GetInstance();

	//
	// Retrieve list of interfaces from the system
	//
	// *** NOTES ***
	// Interface lists are retrieved from the system object. Iterating through 
	// all interfaces can be accomplished with a foreach loop, which will 
	// dispose of each interface appropriately. Individual interfaces can be 
	// accessed using an index.
	// 
	// *** LATER ***
	// Interface lists must be disposed of manually. This must be done prior to 
	// releasing the system and while still in scope.
	// 
	InterfaceList interfaceList = system->GetInterfaces();
	
	unsigned int numInterfaces = interfaceList.GetSize();

	cout << "Number of interfaces detected: " << numInterfaces << endl << endl;

	
	//
	// Retrieve list of cameras from the system
	//
	// *** NOTES ***
	// Camera lists are retrieved from interfaces or the system object. Camera 
	// lists received from an interface are constituted of only the cameras 
	// connected to that interface. Iterating through the cameras can be 
	// accomplished with a foreach loop, which will dispose of each camera 
	// appropriately. Individual cameras can be accessed using an index.
	// 
	// *** LATER ***
	// Camera lists must be disposed of manually. This must be done prior to 
	// releasing the system and while still in scope.
	// 
	CameraList camList = system->GetCameras();

	unsigned int numCameras = camList.GetSize();

	cout << "Number of cameras detected: " << numCameras << endl << endl; 

	// Finish if there are no cameras
	if (numCameras == 0 || numInterfaces == 0)
	{
		// Clear camera list before releasing system
		camList.Clear();

		// Clear interface list before releasing system
		interfaceList.Clear();

		// Release system
		system->ReleaseInstance();

		cout << "Not enough cameras!" << endl;
		cout << "Done! Press Enter to exit..." << endl;
		getchar();
		
		return -1;
	}

	cout << endl << "*** QUERYING INTERFACES ***" << endl << endl;

	//
	// Create interface pointer
	//
	// *** NOTES ***
	// Interface pointers are smart pointers, and will generally clean 
	// themselves up upon losing scope.
	//
	// *** LATER ***
	// If an interface pointer is created in the same scope that a system object 
	// is explicitly released (i.e. this scope), the reference to the interface 
	// must be broken by manually setting the pointer to NULL.
	//
	InterfacePtr interfacePtr = NULL;

	for (unsigned int i = 0; i < numInterfaces; i++)
	{
		// Select interface
		interfacePtr = interfaceList.GetByIndex(i);

		// Query interface
		result = result | QueryInterface(interfacePtr);
	}

	//
	// Release reference to interface pointer
	//
	// *** NOTES ***
	// Had the interface pointer been created within the for loop, the reference
	// would have been appropriately broken and cleaned up automatically at
	// the change of scope. However, because it is created in the same scope of
	// the system release, the reference must be broken manually.
	//
	interfacePtr = NULL;

	//
	// Clear camera list before releasing system
	//
	// *** NOTES ***
	// Camera lists are not smart pointers and do not automatically clean 
	// themselves up and break their own references. Therefore, this must be
	// done manually. The same is true of interface lists.
	// 
	camList.Clear();

	//
	// Clear interface list before releasing system
	//
	// *** NOTES ***
	// Interface lists are not smart pointers and do not automatically clean 
	// themselves up and break their own references. Therefore, this must be
	// done manually. The same is true of camera lists.
	// 
	interfaceList.Clear();

	//
	// Release system
	//
	// *** NOTES ***
	// The system should be released, but if it is not, it will do so by 
	// itself. It is often at the release of the system (whether manual or 
	// automatic) that unbroken references and events that are still 
	// registered will throw an exception.
	//
	system->ReleaseInstance();

	cout << endl << "Done! Press Enter to exit..." << endl;
	getchar();

	return result;
}