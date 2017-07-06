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
 *	@example Enumeration.cpp
 *
 *  @brief Enumeration.cpp shows how to enumerate interfaces and cameras. 
 *	Knowing this is mandatory for doing anything with the Spinnaker SDK, and is 
 *	therefore the best place to start learning how to use the SDK.
 *
 *	This example introduces the preparation, use, and cleanup of the system
 *	object, interface and camera lists, interfaces, and cameras. It also touches
 *	on retrieving both nodes from nodemaps and information from nodes.
 *
 *	Once comfortable with enumeration, we suggest checking out the Acquisition,
 *	ExceptionHandling, or NodeMapInfo examples. Acquisition demonstrates using 
 *	a camera to acquire images, ExceptionHandling explores the use of standard
 *	and Spinnaker exceptions, and NodeMapInfo demonstrates retrieving
 *	information from various node types.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream> 

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// This function queries an interface for its cameras and then prints out device
// information.
int QueryInterface(InterfacePtr pInterface)
{
	int result = 0;

	try
	{
		//
		// Retrieve TL nodemap from interface
		//
		// *** NOTES ***
		// Each interface has a nodemap that can be retrieved in order to
		// access information about the interface itself, any devices 
		// connected, or addressing information if applicable.
		//
		INodeMap & nodeMapInterface = pInterface->GetTLNodeMap();

		//
		// Print interface display name
		//
		// *** NOTES ***
		// Grabbing node information requires first retrieving the node and
		// then retrieving its information. There are two things to keep in
		// mind. First, a node is distinguished by type, which is related 
		// to its value's data type. Second, nodes should be checked for 
		// availability and readability/writability prior to making an 
		// attempt to read from or write to the node.
		//
		CStringPtr ptrInterfaceDisplayName = nodeMapInterface.GetNode("InterfaceDisplayName");

		if (IsAvailable(ptrInterfaceDisplayName) && IsReadable(ptrInterfaceDisplayName))
		{
			gcstring interfaceDisplayName = ptrInterfaceDisplayName->GetValue();

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
		// Updating the cameras on each interface is especially important if 
		// there has been any device arrivals or removals since the last time
		// that UpdateCameras() was called.
		//
		pInterface->UpdateCameras();

		//
		// Retrieve list of cameras from the interface
		//
		// *** NOTES ***
		// Camera lists can be retrieved from an interface or the system object.
		// Camera lists retrieved from an interface, such as this one, only
		// return cameras attached on that specific interface whereas camera
		// lists retrieved from the system will return all cameras on all 
		// interfaces.
		//
		// *** LATER ***
		// Camera lists must be cleared manually. This must be done prior to
		// releasing the system and while the camera list is still in scope.
		// 
		CameraList camList = pInterface->GetCameras();

		// Retrieve number of cameras
		unsigned int numCameras = camList.GetSize();

		// Return if no cameras detected
		if (numCameras == 0)
		{
			cout << "\tNo devices detected." << endl << endl;
			return result;
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

			// Retrieve TL device nodemap; please see NodeMapInfo example for 
			// additional comments on transport layer nodemaps
			INodeMap & nodeMapTLDevice = pCam->GetTLDeviceNodeMap();

			cout << "\tDevice " << i << " ";

			// Print device vendor name and device model name
			//
			// *** NOTES ***
			// Grabbing node information requires first retrieving the node and
			// then retrieving its information. There are two things to keep in
			// mind. First, a node is distinguished by type, which is related 
			// to its value's data type. Second, nodes should be checked for 
			// availability and readability/writability prior to making an 
			// attempt to read from or write to the node.
			//
			CStringPtr ptrDeviceVendorName = nodeMapTLDevice.GetNode("DeviceVendorName");

			if (IsAvailable(ptrDeviceVendorName) && IsReadable(ptrDeviceVendorName))
			{
				gcstring deviceVendorName = ptrDeviceVendorName->ToString();

				cout << deviceVendorName << " ";
			}

			CStringPtr ptrDeviceModelName = nodeMapTLDevice.GetNode("DeviceModelName");
			
			if (IsAvailable(ptrDeviceModelName) && IsReadable(ptrDeviceModelName))
			{
				gcstring deviceModelName = ptrDeviceModelName->ToString();

				cout << deviceModelName << endl << endl;
			}
		}

		//
		// Clear camera list before losing scope
		//
		// *** NOTES ***
		// Camera lists (and interface lists) must be cleared manually while in 
		// the same scope that the system is released. However, in cases like this
		// where scope is lost, camera lists (and interface lists) will be cleared
		// automatically.
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

// Example entry point; please see Enumeration example for more in-depth 
// comments on preparing and cleaning up the system.
int main(int /*argc*/, char** /*argv*/)
{
	int result = 0;

	// Print application build information
	cout << "Application build date: " << __DATE__ << " " << __TIME__ << endl << endl;

	// 
	// Retrieve singleton reference to system object
	//
	// *** NOTES ***
	// Everything originates with the system object. It is important to notice
	// that it has a singleton implementation, so it is impossible to have 
	// multiple system objects at the same time. Users can only get a smart
	// pointer (SystemPtr) to the system instance.
	// 
	// *** LATER ***
	// The system object should be cleared prior to program completion. If not
	// released explicitly, it will be released automatically when all SystemPtr
	// objects that point to the system go out of scope.
	//
	SystemPtr system = System::GetInstance();

	//
	// Retrieve list of interfaces from the system
	//
	// *** NOTES ***
	// Interface lists are retrieved from the system object.
	// 
	// *** LATER ***
	// Interface lists must be cleared manually. This must be done prior to
	// releasing the system and while the interface list is still in scope.
	// 
	InterfaceList interfaceList = system->GetInterfaces();

	unsigned int numInterfaces = interfaceList.GetSize();

	cout << "Number of interfaces detected: " << numInterfaces << endl << endl;

	//
	// Retrieve list of cameras from the system
	//
	// *** NOTES ***
	// Camera lists can be retrieved from an interface or the system object.
	// Camera lists retrieved from the system, such as this one, return all
	// cameras available on the system.
	//
	// *** LATER ***
	// Camera lists must be cleared manually. This must be done prior to
	// releasing the system and while the camera list is still in scope.
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
	// Create shared pointer interface
	//
	// *** NOTES ***
	// The InterfacePtr object is a smart pointer, and will generally clean 
	// itself up upon exiting its scope.
	//
	// *** LATER ***
	// However, if a smart interface pointer is created in the same scope that 
	// a system object is explicitly released (i.e. this scope), the reference to 
	// the interface must be broken by manually setting the pointer to NULL.
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
	// Release reference to the interface
	//
	// *** NOTES ***
	// Had the InterfacePtr object been created within the for-loop, it would 
	// not be necessary to manually break the reference because the smart 
	// pointer would have automatically cleaned itself up upon exiting the loop.
	//
	interfacePtr = NULL;

	//
	// Clear camera list before releasing system
	//
	// *** NOTES ***
	// Camera lists must be cleared manually prior to a system release call.
	//
	camList.Clear();

	//
	// Clear interface list before releasing system
	//
	// *** NOTES ***
	// Interface lists must be cleared manually prior to a system release call.
	//
	interfaceList.Clear();

	//
	// Release system
	//
	// *** NOTES ***
	// The system should be released, but if it is not, it will do so itself.
	// It is often at the release of the system (whether manual or automatic)
	// that unreleased resources and still registered events will throw an
	// exception.
	//
	system->ReleaseInstance();

	cout << endl << "Done! Press Enter to exit..." << endl;
	getchar();

	return result;
}
