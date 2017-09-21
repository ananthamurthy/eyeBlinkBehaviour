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
 *	@example Logging.cpp
 *
 *	@brief Logging.cpp shows how to create a handler to access logging events. 
 *	It relies on information provided in the Enumeration, Acquisition, and 
 *	NodeMapInfo examples.
 *
 *	It can also be helpful to familiarize yourself with the NodeMapCallback
 *	example, as nodemap callbacks follow the same general procedure as
 *	events, but with a few less steps.
 *
 *	This example creates a user-defined class, LoggingEventHandler, that inherits 
 *	from the Spinnaker class, LoggingEvent. The child class allows the user to 
 *	define any properties, parameters, and the event itself while LoggingEvent
 *	allows the child class to appropriately interface with the Spinnaker SDK.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// Define callback priority threshold; please see documentation for additional
// information on logging level philosophy.
const SpinnakerLogLevel k_LoggingLevel = LOG_LEVEL_DEBUG;

// Although logging events are just as flexible and extensible as other events, 
// they are generally only used for logging purposes, which is why a number of 
// helpful functions that provide logging information have been added. Generally,
// if the purpose is not logging, one of the other event types is probably more
// appropriate.
class LoggingEventHandler : public LoggingEvent
{
	// This function displays readily available logging information.
	void OnLogEvent(LoggingEventDataPtr loggingEventDataPtr)
	{
		cout << "--------Log Event Received----------"							<< endl;
		cout << "Category: "		<< loggingEventDataPtr->GetCategoryName()	<< endl;
		cout << "Priority Value: "	<< loggingEventDataPtr->GetPriority()		<< endl;
		cout << "Priority Name: "	<< loggingEventDataPtr->GetPriorityName()	<< endl;
		cout << "Timestmap: "		<< loggingEventDataPtr->GetTimestamp()		<< endl;
		cout << "NDC: "				<< loggingEventDataPtr->GetNDC()			<< endl;
		cout << "Thread: "			<< loggingEventDataPtr->GetThreadName()		<< endl;
		cout << "Message: "			<< loggingEventDataPtr->GetLogMessage()		<< endl;
		cout << "------------------------------------"							<< endl << endl;
	}
};

// Example entry point; notice the volume of data that the logging event handler
// prints out on debug despite the fact that very little really happens in this 
// example. Because of this, it may be better to have the logger set to lower 
// level in order to provide a more concise, focussed log.
int main( int /*argc*/, char** /*argv*/ )
{
	// Print application build information
	cout << "Application build date: " << __DATE__ << " " << __TIME__ << endl << endl;

	// Retrieve singleton reference to system object
	SystemPtr system = System::GetInstance();
	
	//
	// Create and register the logging event handler
	//
	// *** NOTES ***
	// Logging events are registered to the system. Take note that a logging
	// event handler is very verbose when the logging level is set to debug.
	// 
	// *** LATER ***
	// Logging events must be unregistered manually. This must be done prior to
	// releasing the system and while the device events are still in scope.
	//
	LoggingEventHandler loggingEventHandler;
	system->RegisterLoggingEvent(loggingEventHandler);

	//
	// Set callback priority level
	//
	// *** NOTES ***
	// Please see documentation for up-to-date information on the logging
	// philosophies of the Spinnaker SDK.
	//
	system->SetLoggingEventPriorityLevel(k_LoggingLevel);

	// Retrieve list of cameras from the system
	CameraList camList = system->GetCameras();

	unsigned int numCameras = camList.GetSize();

	cout << "Number of cameras detected: " << numCameras << endl << endl;

	// Clear camera list before releasing system
	camList.Clear();

	//
	// Unregister logging event handler
	//
	// *** NOTES ***
	// It is important to unregister all logging events from the system.
	//
	system->UnregisterLoggingEvent(loggingEventHandler);

	// Release system
	system->ReleaseInstance();

	cout << endl << "Done! Press Enter to exit..." << endl;
	getchar();

	return 0;
}
