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
 *	@example NodeMapCallback.cpp
 *
 *	@brief NodeMapCallback.cpp shows how to use nodemap callbacks. It relies
 *	on information provided in the Enumeration, Acquisition, and NodeMapInfo 
 *	examples. As callbacks are very similar to events, it may be a good idea to 
 *	explore this example prior to tackling the events examples.
 *
 *	This example focuses on creating, registering, using, and unregistering
 *	callbacks. A callback requires a function signature, which allows it to be
 *	registered to and access a node. Events, while slightly more complex,
 *	follow this same pattern.
 *
 *	Once comfortable with NodeMapCallback, we suggest checking out any of the
 *	events examples: DeviceEvents, EnumerationEvents, ImageEvents, or Logging.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// This is the first of two callback functions. Notice the function signature.
// This callback function will be registered to the height node.
void OnHeightNodeUpdate(INode* node)
{
	CIntegerPtr ptrHeight = node;
	
	cout << "Height callback message:" << endl;
	cout << "\tLook! Height changed to " << ptrHeight->GetValue() << "..." << endl << endl;
}

// This is the second of two callback functions. Notice that despite different
// names, everything else is exactly the same as the first. This callback 
// function will be registered to the gain node.
void OnGainNodeUpdate(INode* node)
{
	CFloatPtr ptrGain = node;
	
	cout << "Gain callback message:" << endl;
	cout << "\tLook now!  Gain changed to " << ptrGain->GetValue() << "..." << endl << endl;
}

// This function prepares the example by disabling automatic gain, creating the 
// callbacks, and registering them to their respective nodes.
int ConfigureCallbacks(INodeMap & nodeMap, int64_t & callbackHeight, int64_t & callbackGain)
{
	int result = 0;

	cout << endl << endl << "*** CONFIGURING CALLBACKS ***" << endl << endl;

	try
	{
		//
		// Turn off automatic gain
		//
		// *** NOTES ***
		// Automatic gain prevents the manual configuration of gain and needs to
		// be turned off for this example.
		//
		// *** LATER ***
		// Automatic exposure is turned off at the end of the example in order
		// to restore the camera to its default state.
		//
		CEnumerationPtr ptrGainAuto = nodeMap.GetNode("GainAuto");
		if (!IsAvailable(ptrGainAuto) || !IsWritable(ptrGainAuto))
		{
			cout << "Unable to disable automatic gain (node retrieval). Aborting..." << endl << endl;
			return -1;
		}

		CEnumEntryPtr ptrGainAutoOff = ptrGainAuto->GetEntryByName("Off");
		if (!IsAvailable(ptrGainAutoOff) && !IsReadable(ptrGainAutoOff))
		{
			cout << "Unable to disable automatic gain (enum entry retrieval). Aborting..." << endl << endl;
			return -1; 
		}

		ptrGainAuto->SetIntValue(ptrGainAutoOff->GetValue());

		cout << "Automatic gain disabled..." << endl;
		
		//
		// Register callback to height node
		//
		// *** NOTES ***
		// Callbacks need to be registered to nodes, which should be writable 
		// if the callback is to ever be triggered. Notice that callback 
		// registration returns an integer - this integer is important at the 
		// end of the example for deregistration.
		//
		// *** LATER ***
		// Each callback needs to be unregistered individually before releasing
		// the system or an exception will be thrown.
		//
		CIntegerPtr ptrHeight = nodeMap.GetNode("Height");
		if (!IsAvailable(ptrHeight) || !IsWritable(ptrHeight))
		{
			cout << "Unable to retrieve height. Aborting..." << endl << endl;
			return -1;
		}
		
		cout << "Height ready..." << endl;

		callbackHeight = Register(ptrHeight, &OnHeightNodeUpdate);

		cout << "Height callback registered..." << endl;

		//
		// Register callback to gain node
		//
		// *** NOTES ***
		// Depending on the specific goal of the function, it can be important
		// to notice the node type that a callback is registered to. Notice in
		// the callback functions above that the callback registered to height 
		// casts its node as an integer whereas the callback registered to gain
		// casts as a float.
		//
		// *** LATER ***
		// Each callback needs to be unregistered individually before releasing
		// the system or an exception will be thrown.
		//
		CFloatPtr ptrGain = nodeMap.GetNode("Gain");
		if (!IsAvailable(ptrGain) || !IsWritable(ptrGain))
		{
			cout << "Unable to retrieve gain. Aborting..." << endl << endl;
			return -1;
		}
		
		cout << "Gain ready..." << endl;
		
		callbackGain = Register(ptrGain, &OnGainNodeUpdate);
		
		cout << "Gain callback registered..." << endl << endl;
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function demonstrates the triggering of the nodemap callbacks. First it 
// changes height, which executes the callback registered to the height node, and
// then it changes gain, which executes the callback registered to the gain node.
int ChangeHeightAndGain(INodeMap & nodeMap)
{
	int result = 0;

	cout << endl << "*** CHANGE HEIGHT & GAIN ***" << endl << endl;

	try
	{
		//
		// Change height to trigger height callback
		//
		// *** NOTES ***
		// Notice that changing the height only triggers the callback function
		// registered to the height node.
		//
		CIntegerPtr ptrHeight = nodeMap.GetNode("Height");
		if (!IsAvailable(ptrHeight) || !IsWritable(ptrHeight) || ptrHeight->GetInc() == 0 || ptrHeight->GetMax() == 0)
		{
			cout << "Unable to retrieve height. Aborting..." << endl << endl;
			return -1;
		}
		
		int64_t heightToSet = ptrHeight->GetMax();

		cout << "Regular function message:" << endl;
		cout << "\tHeight about to be changed to " << heightToSet << "..." << endl << endl;

		ptrHeight->SetValue(heightToSet);

		//
		// Change gain to trigger gain callback
		//
		// *** NOTES ***
		// The same is true of changing the gain node; changing a node will 
		// only ever trigger the callback function (or functions) currently
		// registered to it.
		//
		CFloatPtr ptrGain = nodeMap.GetNode("Gain");
		if (!IsAvailable(ptrGain) || !IsWritable(ptrGain) || ptrGain->GetMax() == 0)
		{
			cout << "Unable to retrieve gain..." << endl;
			return -1;
		}
		
		double gainToSet = ptrGain->GetMax() / 2.0;

		cout << "Regular function message:" << endl;
		cout << "\tGain about to be changed to " << gainToSet << "..." << endl << endl;

		ptrGain->SetValue(gainToSet);
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function cleans up the example by deregistering the callbacks and 
// turning automatic gain back on.
int ResetCallbacks(INodeMap & nodeMap, int64_t & callbackHeight, int64_t & callbackGain)
{
	int result = 0;

	try
	{
		//
		// Deregister callbacks
		//
		// *** NOTES ***
		// It is important to deregister each callback function from each node 
		// that it is registered to.
		//
		Deregister(callbackHeight);
		
		Deregister(callbackGain);
		
		cout << "Callbacks deregistered..." << endl;

		//
		// Turn automatic gain back on
		//
		// *** NOTES ***
		// Automatic gain is turned back on in order to restore the camera to 
		// its default state.
		//
		CEnumerationPtr ptrGainAuto = nodeMap.GetNode("GainAuto");
		if (!IsAvailable(ptrGainAuto) || !IsWritable(ptrGainAuto))
		{
			cout << "Unable to enable automatic gain (node retrieval). Non-fatal error..." << endl << endl;
			return -1;
		}

		CEnumEntryPtr ptrGainAutoContinuous = ptrGainAuto->GetEntryByName("Continuous");
		if (!IsAvailable(ptrGainAutoContinuous) && !IsReadable(ptrGainAutoContinuous))
		{
			cout << "Unable to enable automatic gain (enum entry retrieval). Non-fatal error..." << endl << endl;
			return -1;
		}

		ptrGainAuto->SetIntValue(ptrGainAutoContinuous->GetValue());

		cout << "Automatic gain enabled..." << endl << endl;
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function prints the device information of the camera from the transport
// layer; please see NodeMapInfo example for more in-depth comments on printing
// device information from the nodemap.
int PrintDeviceInfo(INodeMap & nodeMap)
{
	int result = 0;

	cout << endl << "*** DEVICE INFORMATION ***" << endl << endl;

	try
	{
		FeatureList_t features;
		CCategoryPtr category = nodeMap.GetNode("DeviceInformation");
		if (IsAvailable(category) && IsReadable(category))
		{
			category->GetFeatures(features);

			FeatureList_t::const_iterator it;
			for (it = features.begin(); it != features.end(); ++it)
			{
				CNodePtr pfeatureNode = *it;
				cout << pfeatureNode->GetName() << " : ";
				CValuePtr pValue = (CValuePtr)pfeatureNode;
				cout << (IsReadable(pValue) ? pValue->ToString() : "Node not readable");
				cout << endl;
			}
		}
		else
		{
			cout << "Device control information not available." << endl;
		}
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function acts as the body of the example; please see NodeMapInfo example 
// for more in-depth comments on setting up cameras.
int RunSingleCamera(CameraPtr pCam)
{
	int result = 0;
	int err = 0;

	try
	{
		// Retrieve TL device nodemap and print device information
		INodeMap & nodeMapTLDevice = pCam->GetTLDeviceNodeMap();

		result = PrintDeviceInfo(nodeMapTLDevice);

		// Initialize camera
		pCam->Init();

		// Retrieve GenICam nodemap
		INodeMap & nodeMap = pCam->GetNodeMap();

		// Configure callbacks
		int64_t callbackHeight;
		int64_t callbackGain;

		err = ConfigureCallbacks(nodeMap, callbackHeight, callbackGain);
		if (err < 0)
		{
			return err;
		}

		// Change height and gain to trigger callbacks
		result = result | ChangeHeightAndGain(nodeMap);

		// Reset callbacks
		result = result | ResetCallbacks(nodeMap, callbackHeight, callbackGain);

		// Deinitialize camera
		pCam->DeInit();
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

	// Retrieve singleton reference to system object
	SystemPtr system = System::GetInstance();

	// Retrieve list of cameras from the system
	CameraList camList = system->GetCameras();

	unsigned int numCameras = camList.GetSize();

	cout << "Number of cameras detected: " << numCameras << endl << endl;

	// Finish if there are no cameras
	if (numCameras == 0)
	{
		// Clear camera list before releasing system
		camList.Clear();

		// Release system
		system->ReleaseInstance();

		cout << "Not enough cameras!" << endl;
		cout << "Done! Press Enter to exit..." << endl;
		getchar();

		return -1;
	}

	// Run example on each camera
	for (unsigned int i = 0; i < numCameras; i++)
	{
		cout << endl << "Running example for camera " << i << "..." << endl;

		result = result | RunSingleCamera(camList.GetByIndex(i));

		cout << "Camera " << i << " example complete..." << endl << endl;
	}

	// Clear camera list before releasing system
	camList.Clear();

	// Release system
	system->ReleaseInstance();

	cout << endl << "Done! Press Enter to exit..." << endl;
	getchar();

	return result;
}
