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
 *	@example NodeMapInfo.cpp
 *	
 *	@brief NodeMapInfo.cpp shows how to retrieve node map information. It relies 
 *	on information provided in the Enumeration example. Also, check out the
 *	Acquisition and ExceptionHandling examples if you haven't already. 
 *	Acquisition demonstrates image acquisition while ExceptionHandling shows the 
 *	handling of standard and Spinnaker exceptions.
 *
 *	This example explores retrieving information from all major node types on the
 *	camera. This includes string, integer, float, boolean, command, enumeration,
 *	category, and value types. Looping through multiple child nodes is also 
 *	covered. A few node types are not covered - base, port, and register - as 
 *	they are not fundamental. The final node type - enumeration entry - is
 *	explored only in terms of its parent node type - enumeration.
 *
 *	Once comfortable with NodeMapInfo, we suggest checking out ImageFormatControl 
 *	and Exposure. ImageFormatControl explores customizing image settings on a
 *  camera while Exposure introduces the standard structure of configuring a 
 *	device, acquiring some images, and then returning the device to a default 
 *	state.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include <iostream>
#include <sstream>

// This macro defines the maximum number of characters that will be printed out
// for any information retrieved from a node.
#define MAX_CHARS 35

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// Use the following enum and global constant to select whether nodes are read
// as 'value' nodes or their individual types.
enum readType
{
	VALUE,
	INDIVIDUAL
};

const readType chosenRead = VALUE;

// This helper function deals with output indentation, of which there is a lot.
void indent(unsigned int level)
{
	for (unsigned int i = 0; i < level; i++)
	{
		cout << "   ";
	}
}

// This function retrieves and prints the display name and value of all node
// types as value nodes. A value node is a general node type that allows for
// the reading and writing of any node type as a string.
int printValueNode(CNodePtr node, unsigned int level)
{
	int result = 0;

	try
	{
		// Cast as value node
		CValuePtr ptrValueNode = static_cast<CValuePtr>(node);

		//
		// Retrieve display name
		//
		// *** NOTES ***
		// A node's 'display name' is generally more appropriate for output and
		// user interaction whereas its 'name' is what the camera understands.
		// Generally, its name is the same as its display name but without
		// spaces - for instance, the name of the node that houses a camera's
		// serial number is 'DeviceSerialNumber' while its display name is
		// 'Device Serial Number'.
		//
		gcstring displayName = ptrValueNode->GetDisplayName();

		//
		// Retrieve value of any node type as string
		//
		// *** NOTES ***
		// Because value nodes return any node type as a string, it can be much 
		// easier to deal with nodes as value nodes rather than their actual
		// individual types.
		//
		gcstring value = ptrValueNode->ToString();

		// Ensure that the value length is not excessive for printing
		if (value.size() > MAX_CHARS)
		{
			value = value.substr(0, MAX_CHARS) + "...";
		}

		// Print value
		indent(level);
		cout << displayName << ": " << value << endl;
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function retrieves and prints the display name and value of a string 
// node, limiting the number of printed characters to a maximum defined by
// MAX_CHARS macro. Level parameter determines the indentation level for the
// output.
int printStringNode(CNodePtr node, unsigned int level)
{
	int result = 0;

	try
	{
		// Cast as string node
		CStringPtr ptrStringNode = static_cast<CStringPtr>(node);

		// Retrieve display name
		gcstring displayName = ptrStringNode->GetDisplayName();

		//
		// Retrieve string node value
		//
		// *** NOTES ***
		// The Spinnaker SDK includes its own wrapped string class, gcstring. As 
		// such, there is no need to import the 'string' library when using the
		// SDK. If a standard string object is preferred, simply use a c-style
		// or static cast on the gcstring object.
		//
		gcstring value = ptrStringNode->GetValue();

		// Ensure that the value length is not excessive for printing
		if (value.size() > MAX_CHARS)
		{
			value = value.substr(0, MAX_CHARS) + "...";
		}
		
		// Print value; 'level' determines the indentation level of output
		indent(level);
		cout << displayName << ": " << value << endl;
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function retrieves and prints the display name and value of an integer 
// node.
int printIntegerNode(CNodePtr node, unsigned int level)
{
	int result = 0;

	try
	{
		// Cast node as integer node
		CIntegerPtr ptrIntegerNode = static_cast<CIntegerPtr>(node);

		// Retrieve display name
		gcstring displayName = ptrIntegerNode->GetDisplayName();

		//
		// Retrieve integer node value
		//
		// *** NOTES ***
		// Keep in mind that the data type of an integer node value is an 
		// int64_t as opposed to a standard int. While it is true that the two
		// are often interchangeable, it is recommended to use the int64_t 
		// to avoid the introduction of bugs.
		//
		// All node types except for base and port nodes include a handy 
		// ToString() method which returns a value as a gcstring. 
		//
		int64_t value = ptrIntegerNode->GetValue();

		// Print value
		indent(level);
		cout << displayName << ": " << value << endl;
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function retrieves and prints the display name and value of a float 
// node.
int printFloatNode(CNodePtr node, unsigned int level)
{
	int result = 0;

	try
	{
		// Cast as float node
		CFloatPtr ptrFloatNode = static_cast<CFloatPtr>(node);

		// Retrieve display name
		gcstring displayName = ptrFloatNode->GetDisplayName();

		//
		// Retrieve float node value
		//
		// *** NOTES ***
		// Please take note that floating point numbers in the Spinnaker SDK are
		// almost always represented by the larger data type double rather than 
		// float.
		//
		double value = ptrFloatNode->GetValue();

		// Print value
		indent(level);
		cout << displayName << ": " << value << endl;
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function retrieves and prints the display name and value of a boolean,
// printing "true" for true and "false" for false rather than the corresponding
// integer value ('1' and '0', respectively).
int printBooleanNode(CNodePtr node, unsigned int level)
{
	int result = 0;

	try
	{
		// Cast as boolean node
		CBooleanPtr ptrBooleanNode = static_cast<CBooleanPtr>(node);

		// Retrieve display name
		gcstring displayName = ptrBooleanNode->GetDisplayName();

		// 
		// Retrieve value as a string representation
		//
		// *** NOTES ***
		// Boolean node type values are represented by the standard bool data
		// type. The boolean ToString() method returns either a '1' or '0' as
		// a string rather than a more descriptive word like 'true' or 'false'.
		//
		gcstring value = (ptrBooleanNode->GetValue() ? "true" : "false");

		// Print value
		indent(level);
		cout << displayName << ": " << value << endl;
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function retrieves and prints the display name and tooltip of a command 
// node, limiting the number of printed characters to a macro-defined maximum.
// The tooltip is printed below because command nodes do not have an intelligible 
// value.
int printCommandNode(CNodePtr node, unsigned int level)
{
	int result = 0;

	try
	{
		// Cast as command node
		CCommandPtr ptrCommandNode = static_cast<CCommandPtr>(node);

		// Retrieve display name
		gcstring displayName = ptrCommandNode->GetDisplayName();

		//
		// Retrieve tooltip
		//
		// *** NOTES ***
		// All node types have a tooltip available. Tooltips provide useful
		// information about nodes. Command nodes do not have a method to
		// retrieve values as their is no intelligible value to retrieve.
		//
		gcstring tooltip = ptrCommandNode->GetToolTip();

		// Ensure that the value length is not excessive for printing
		if (tooltip.size() > MAX_CHARS)
		{
			tooltip = tooltip.substr(0, MAX_CHARS) + "...";
		}

		// Print tooltip
		indent(level);
		cout << displayName << ": " << tooltip << endl;
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function retrieves and prints the display names of an enumeration node
// and its current entry (which is actually housed in another node unto itself).
int printEnumerationNodeAndCurrentEntry(CNodePtr node, unsigned int level)
{
	int result = 0;

	try
	{
		// Cast as enumeration node
		CEnumerationPtr ptrEnumerationNode = static_cast<CEnumerationPtr>(node);

		//
		// Retrieve current entry as enumeration node
		//
		// *** NOTES ***
		// Enumeration nodes have three methods to differentiate between: first, 
		// GetIntValue() returns the integer value of the current entry node;
		// second, GetCurrentEntry() returns the entry node itself; and third, 
		// ToString() returns the symbolic of the current entry.
		//
		CEnumEntryPtr ptrEnumEntryNode = ptrEnumerationNode->GetCurrentEntry();

		// Retrieve display name
		gcstring displayName = ptrEnumerationNode->GetDisplayName();

		//
		// Retrieve current symbolic
		//
		// *** NOTES ***
		// Rather than retrieving the current entry node and then retrieving its
		// symbolic, this could have been taken care of in one step by using the
		// enumeration node's ToString() method.
		//
		gcstring currentEntrySymbolic = ptrEnumEntryNode->GetSymbolic();

		// Print current entry symbolic
		indent(level);
		cout << displayName << ": " << currentEntrySymbolic << endl;
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function retrieves and prints out the display name of a category node 
// before printing all child nodes. Child nodes that are also category nodes are
// printed recursively.
int printCategoryNodeAndAllFeatures(CNodePtr node, unsigned int level)
{
	int result = 0;

	try
	{
		// Cast as category node
		CCategoryPtr ptrCategoryNode = static_cast<CCategoryPtr>(node);

		// Retrieve display name
		gcstring displayName = ptrCategoryNode->GetDisplayName();

		// Print display name
		indent(level);
		cout << displayName << endl;

		//
		// Retrieve children
		//
		// *** NOTES ***
		// The two nodes that typically have children are category nodes and
		// enumeration nodes. Throughout the examples, the children of category
		// nodes are referred to as features while the children of enumeration
		// nodes are referred to as entries. Keep in mind that enumeration
		// nodes can be cast as category nodes, but category nodes cannot be 
		// cast as enumerations.
		//
		FeatureList_t features;
		ptrCategoryNode->GetFeatures(features);

		//
		// Iterate through all children
		// 
		// *** NOTES ***
		// If dealing with a variety of node types and their values, it may be
		// simpler to cast them as value nodes rather than as their individual
		// types. However, with this increased ease-of-use, functionality is
		// sacrificed.
		//
		FeatureList_t::const_iterator it;
		for (it = features.begin(); it != features.end(); ++it)
		{
			CNodePtr ptrFeatureNode = *it;

			// Ensure node is available and readable
			if (!IsAvailable(ptrFeatureNode) || !IsReadable(ptrFeatureNode))
			{
				continue;
			}

			// Category nodes must be dealt with separately in order to
			// retrieve subnodes recursively.
			if (ptrFeatureNode->GetPrincipalInterfaceType() == intfICategory)
			{
				result = result | printCategoryNodeAndAllFeatures(ptrFeatureNode, level + 1);
			}
			// Cast all non-category nodes as value nodes
			else if (chosenRead == VALUE)
			{
				result = result | printValueNode(ptrFeatureNode, level + 1);
			}
			// Cast all non-category nodes as actual types
			else if (chosenRead == INDIVIDUAL)
			{
				switch (ptrFeatureNode->GetPrincipalInterfaceType())
				{
				case intfIString:
					result = result | printStringNode(ptrFeatureNode, level + 1);
					break;

				case  intfIInteger:
					result = result | printIntegerNode(ptrFeatureNode, level + 1);
					break;

				case intfIFloat:
					result = result | printFloatNode(ptrFeatureNode, level + 1);
					break;

				case intfIBoolean:
					result = result | printBooleanNode(ptrFeatureNode, level + 1);
					break;

				case intfICommand:
					result = result | printCommandNode(ptrFeatureNode, level + 1);
					break;

				case intfIEnumeration:
					result = result | printEnumerationNodeAndCurrentEntry(ptrFeatureNode, level + 1);
					break;
				}
			}
		}
		cout << endl;
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function acts as the body of the example. First nodes from the TL 
// device and TL stream nodemaps are retrieved and printed. Following this, 
// the camera is initialized and then nodes from the GenICam nodemap are
// retrieved and printed.
int RunSingleCamera(CameraPtr cam)
{
	int result = 0;
	unsigned int level = 0;

	try
	{
		//
		// Retrieve TL device nodemap
		//
		// *** NOTES ***
		// The TL device nodemap is available on the transport layer. As such, 
		// camera initialization is unnecessary. It provides mostly immutable
		// information fundamental to the camera such as the serial number,
		// vendor, and model.
		//
		cout << endl << "*** PRINTING TRANSPORT LAYER DEVICE NODEMAP ***" << endl << endl;

		INodeMap & genTLNodeMap = cam->GetTLDeviceNodeMap();
		
		result = printCategoryNodeAndAllFeatures(genTLNodeMap.GetNode("Root"), level);

		//
		// Retrieve TL stream nodemap
		//
		// *** NOTES ***
		// The TL stream nodemap is also available on the transport layer. Camera
		// initialization is again unnecessary. As you can probably guess, it
		// provides information on the camera's streaming performance at any
		// given moment. Having this information available on the transport
		// layer allows the information to be retrieved without affecting camera
		// performance.
		//
		cout << "*** PRINTING TL STREAM NODEMAP ***" << endl << endl;

		INodeMap & nodeMapTLStream = cam->GetTLStreamNodeMap();
		
		result = result | printCategoryNodeAndAllFeatures(nodeMapTLStream.GetNode("Root"), level);

		//
		// Initialize camera
		//
		// *** NOTES ***
		// The camera becomes connected upon initialization. This provides
		// access to configurable options and additional information, accessible
		// through the GenICam nodemap.
		//
		// *** LATER ***
		// Cameras should be deinitialized when no longer needed.
		//
		cout << "*** PRINTING GENICAM NODEMAP ***" << endl << endl;

		cam->Init();

		// 
		// Retrieve GenICam nodemap
		//
		// *** NOTES ***
		// The GenICam nodemap is the primary gateway to customizing
		// and configuring the camera to suit your needs. Configuration options 
		// such as image height and width, trigger mode enabling and disabling,
		// and the sequencer are found on this nodemap.
		//
		INodeMap & appLayerNodeMap = cam->GetNodeMap();
		
		result = result | printCategoryNodeAndAllFeatures(appLayerNodeMap.GetNode("Root"), level);

		//
		// Deinitialize camera
		//
		// *** NOTES ***
		// Camera deinitialization helps ensure that devices clean up properly
		// and do not need to be power-cycled to maintain integrity.
		//
		cam->DeInit();
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

	//
	// Create shared pointer for camera
	//
	// *** NOTES ***
	// The CameraPtr object is a shared pointer, and will generally clean itself
	// up upon exiting its scope.
	//
	// *** LATER ***
	// However, if a shared camera pointer is created in the same scope that a 
	// system object is explicitly released (i.e. this scope), the reference to 
	// the camera must be broken by manually setting the pointer to NULL.
	//
	CameraPtr pCam = NULL;

	// Run example on each camera
	for (unsigned int i = 0; i < numCameras; i++)
	{
		// Select camera
		pCam = camList.GetByIndex(i);

		cout << endl << "Running example for camera " << i << "..." << endl;

		// Run example
		result = result | RunSingleCamera(pCam);

		cout << "Camera " << i << " example complete..." << endl << endl;
	}

	//
	// Release shared pointer reference to camera before releasing system
	//
	// *** NOTES ***
	// Had the CameraPtr object been created within the for-loop, it would not
	// be necessary to manually break its reference because the shared pointer
	// would have automatically cleaned itself up upon exiting the loop.
	//
	pCam = NULL;

	// Clear camera list before releasing system
	camList.Clear();

	// Release system
	system->ReleaseInstance();

	cout << endl << "Done! Press Enter to exit..." << endl;
	getchar();

	return result;
}