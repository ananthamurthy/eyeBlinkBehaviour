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
 *	@example EnumerationEvents.cpp
 *
 *	@brief EnumerationEvents.cpp explores arrival and removal events on 
 *	interfaces and the system. It relies on information provided in the 
 *	Enumeration, Acquisition, and NodeMapInfo examples.
 *
 *	It can also be helpful to familiarize yourself with the NodeMapCallback
 *	example, as nodemap callbacks follow the same general procedure as 
 *	events, but with a few less steps.
 *
 *	This example creates two user-defined classes: InterfaceEventHandler and 
 *	SystemEventHandler. These child classes allow the user to define properties,
 *	parameters, and the event itself while the parent classes - ArrivalEvent,
 *	RemovalEvent, and InterfaceEvent - allow the child classes to interface
 *	with Spinnaker.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream> 

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// This class defines the properties and methods for device arrivals and removals
// on an interface. Take special note of the signatures of the OnDeviceArrival()
// and OnDeviceRemoval() methods. Also, enumeration events must inherit from
// ManagedInterfaceEvent whether they are to be registered to the system or an
// interface.
class InterfaceEventHandler : public InterfaceEvent
{
public:
	
	//
	// Set the constructor and destructor
	//
	// *** NOTES ***
	// Notice that the constructor sets the interface pointer and the destructor
	// clears it.
	//
	InterfaceEventHandler(InterfacePtr iface, unsigned int interfaceNum) : m_interface(iface), m_interfaceNum(interfaceNum) {};
	~InterfaceEventHandler() { m_interface = NULL; };

	// This method defines arrival events on an interface. It grabs the serial
	// number of the first device on the interface and prints it out with the
	// interface number. It is important to note that this function assumes 
	// there will only be a single camera on an interface.
	void OnDeviceArrival()
	{
		// Retrieve device serial number of newly arrived camera
		CameraPtr pCam = m_interface->GetCameras().GetByIndex(0);
		CStringPtr ptrDeviceSerialNumber = pCam->GetTLDeviceNodeMap().GetNode("DeviceSerialNumber");
		gcstring deviceSerialNumber = ptrDeviceSerialNumber->ToString();

		// Print out device serial number and interface number
		cout << "Interface event handler:" << endl;
		cout << "\tDevice " << deviceSerialNumber << " has arrived on interface " << m_interfaceNum << "." << endl << endl;

		pCam = NULL;
	}

	// This method defines removal events on an interface. It prints out the
	// device serial number of the camera being removed and the interface
	// number. The argument is the serial number of the camera that triggered
	// the removal event.
	void OnDeviceRemoval(uint64_t deviceSerialNumber)
	{
		cout << "Interface event handler:" << endl;
		cout << "\tDevice " << deviceSerialNumber << " was removed from interface " << m_interfaceNum << "." << endl << endl;
	}

private:

	int m_interfaceNum;
	InterfacePtr m_interface;
};

// In the example, InterfaceEventHandler inherits from InterfaceEvent while
// SystemEventHandler inherits from ArrivalEvent and RemovalEvent. This is
// done for demonstration purposes and is not a constraint of the SDK. All 
// three event types - ArrivalEvent, RemovalEvent, and InterfaceEvent - can be 
// registered to interfaces, the system, or both.
class SystemEventHandler : public ArrivalEvent, public RemovalEvent
{
public:

	SystemEventHandler(SystemPtr system) : m_system(system) {};
	~SystemEventHandler() {};

	// This method defines the arrival event on the system. It retrieves the
	// number of cameras currently connected and prints it out.
	void OnDeviceArrival()
	{
		int count = m_system->GetCameras().GetSize();

		cout << "System event handler:" << endl;
		cout << "\tThere " << (count == 1 ? "is " : "are ") << count << (count == 1 ? " device " : " devices ") << "on the system." << endl << endl;
	}

	// This method defines the removal event on the system. It does the same
	// as the system arrival event - it retrieves the number of cameras 
	// currently connected and prints it out.
	void OnDeviceRemoval(uint64_t deviceSerialNumber)
	{
		int count = m_system->GetCameras().GetSize();

		cout << "System event handler:" << endl;
		cout << "\tThere " << (count == 1 ? "is " : "are ") << count << (count == 1 ? " device " : " devices ") << "on the system." << endl << endl;
	}

private:

	SystemPtr m_system;
};

// Example entry point; this function sets up the example to act appropriately 
// upon arrival and removal events; please see Enumeration example for more 
// in-depth comments on preparing and cleaning up the system.
int main(int /*argc*/, char** /*argv*/)
{
	// Print application build information
	cout << "Application build date: " << __DATE__ << " " << __TIME__ << endl << endl;

	// Retrieve singleton reference to system object
	SystemPtr system = System::GetInstance();

	// Retrieve list of cameras from the system
	CameraList camList = system->GetCameras();

	unsigned int numCameras = camList.GetSize();

	cout << "Number of cameras detected: " << numCameras << endl << endl;

	// Retrieve list of interfaces from the system
	InterfaceList interfaceList = system->GetInterfaces();

	unsigned int numInterfaces = interfaceList.GetSize();

	cout << "Number of interfaces detected: " << numInterfaces << endl << endl;

	cout << endl << "*** CONFIGURING ENUMERATION EVENTS ***" << endl << endl;

	//
	// Create interface event for the system
	//
	// *** NOTES ***
	// The SystemEventHandler has been constructed to accept a system object in 
	// order to print the number of cameras on the system.
	//
	SystemEventHandler systemEventHandler(system);
	
	//
	// Register interface event for the system
	//
	// *** NOTES ***
	// Arrival, removal, and interface events can all be registered to 
	// interfaces or the system. Do not think that interface events can only be
	// registered to an interface. An interface event is merely a combination
	// of an arrival and a removal event.
	//
	// *** LATER ***
	// Arrival, removal, and interface events must all be unregistered manually.
	// This must be done prior to releasing the system and while they are still
	// in scope.
	//
	system->RegisterInterfaceEvent(systemEventHandler);

	//
	// Create and register interface event to each interface
	//
	// *** NOTES ***
	// The process of event creation and registration on interfaces is similar
	// to the process of event creation and registration on the system. The 
	// class for interfaces has been constructed to accept an interface and an
	// interface number (this is just to separate the interfaces).
	// 
	// *** LATER ***
	// Arrival, removal, and interface events must all be unregistered manually.
	// This must be done prior to releasing the system and while they are still
	// in scope.
	//
	vector<InterfaceEventHandler*> interfaceEvents;

	for (unsigned int i = 0; i < numInterfaces; i++)
	{
		// Select interface
		InterfacePtr pInterface = interfaceList.GetByIndex(i);

		// Create interface event
		InterfaceEventHandler* interfaceEventHandler = new InterfaceEventHandler(pInterface, i);
		interfaceEvents.push_back(interfaceEventHandler);

		// Register interface event
		pInterface->RegisterEvent(*interfaceEvents[i]);

		cout << "Event handler registered to interface " << i << "..." << endl;
	}

	// Wait for user to plug in and/or remove camera devices
	cout << endl << "Ready! Remove/Plug in cameras to test or press Enter to exit..." << endl << endl;
	getchar();

	//
	// Unregister interface event from each interface
	//
	// *** NOTES ***
	// It is important to unregister all arrival, removal, and interface events
	// from all interfaces that they may be registered to. 
	//
	for (unsigned int i = 0; i < numInterfaces; i++)
	{
		interfaceList.GetByIndex(i)->UnregisterEvent(*interfaceEvents[i]);

		// Delete interface event (because it is a pointer)
		delete interfaceEvents[i];
	}

	cout << "Event handler unregistered from interfaces..." << endl;

	//
	// Unregister system event from system object
	//
	// *** NOTES ***
	// It is important to unregister all arrival, removal, and interface events
	// registered to the system.
	//
	system->UnregisterInterfaceEvent(systemEventHandler);

	cout << "Event handler unregistered from system..." << endl;
	
	// Clear camera list before releasing system
	camList.Clear();

	// Clear interface list before releasing system
	interfaceList.Clear();

	// Release system
	system->ReleaseInstance();

	cout << endl << "Done! Press Enter to exit..." << endl;
	getchar();
	
	return 0;
}
