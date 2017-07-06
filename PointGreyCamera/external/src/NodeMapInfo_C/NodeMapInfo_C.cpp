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
 *	@example NodeMapInfo_C.cpp
 *
 *	@brief NodeMapInfo_C.cpp shows how to retrieve node map information. It
 *	relies on information provided in the Enumeration_C example. Following this,
 *	check out the Acquisition_C example if you haven't already. It explores
 *	acquiring images.
 *
 *	This example explores retrieving information from all major node types on the
 *	camera. This includes string, integer, float, boolean, command, enumeration,
 *	category, and value types. Looping through multiple child nodes is also
 *	covered. A few node types are not covered - base, port, and register - as
 *	they are not fundamental. The final node type - enumeration entry - is
 *	explored only in terms of its parent node type - enumeration.
 *
 *	Once comfortable with NodeMapInfo_C, we suggest checking out
 *	ImageFormatControl_C and Exposure_C. ImageFormatControl_C explores
 *	customizing image settings on a camera while Exposure_C introduces the
 *	standard structure of configuring a device, acquiring some images, and then
 *	returning the device to a default state.
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

// Use the following enum and global constant to select whether nodes are read
// as 'value' nodes or their individual types.
typedef enum _readType
{
	VALUE,
	INDIVIDUAL
} readType;

const readType chosenRead = VALUE;

// This helper function deals with output indentation, of which there is a lot.
void indent(unsigned int level)
{
	unsigned int i = 0;

	for (i = 0; i < level; i++)
	{
		printf("   ");
	}
}

// This function retrieves and prints the display name and value of all node
// types as value nodes. A value node is a general node type that allows for
// the reading and writing of any node type as a string.
spinError printValueNode(spinNodeHandle hNode, unsigned int level)
{
	spinError err = SPINNAKER_ERR_SUCCESS;
	unsigned int i = 0;

	//
	// Retrieve display name
	//
	// *** NOTES ***
	// A node's 'display name' is generally more appropriate for output and
	// user interaction whereas its 'name' is what the camera understands.
	// Generally, its name is the same as its display namebut without
	// spaces - for instance, the name of the node that houses a camera's
	// serial number is 'DeviceSerialNumber' while its display name is
	// 'Device Serial Number'.
	//
	char displayName[MAX_BUFF_LEN];
	size_t displayNameLength = MAX_BUFF_LEN;
	err = spinNodeGetDisplayName(hNode, displayName, &displayNameLength);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	//
	// Retrieve value of any node type as string
	//
	// *** NOTES ***
	// Because value nodes return any node type as a string, it can be much
	// easier to deal with nodes as value nodes rather than their actual
	// individual types.
	//
	char value[MAX_BUFF_LEN];
	size_t valueLength = MAX_BUFF_LEN;

	// Ensure allocated buffer is large enough for storing the string
	err = spinNodeToString(hNode, NULL, &valueLength);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	const unsigned int k_maxChars = MAX_CHARS;
	if (valueLength <= k_maxChars)
	{
		err = spinNodeToString(hNode, value, &valueLength);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			return err;
		}
	}

	// Print value
	indent(level);
	printf("%s: ", displayName);

	// Ensure that the value length is not excessive for printing
	if (valueLength > k_maxChars)
	{
		printf("...\n");
	}
	else
	{
		printf("%s\n", value);
	}

	return err;
}

// This function retrieves and prints the display name and value of a string
// node, limiting the number of printed characters to a maximum defined
// by MAX_CHARS macro.
spinError printStringNode(spinNodeHandle hNode, unsigned int level)
{
	spinError err = SPINNAKER_ERR_SUCCESS;
	unsigned int i = 0;

	// Retrieve display name
	char displayName[MAX_BUFF_LEN];
	size_t displayNameLength = MAX_BUFF_LEN;

	err = spinNodeGetDisplayName(hNode, displayName, &displayNameLength);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	//
	// Retrieve string node value
	//
	// *** NOTES ***
	// The Spinnaker SDK requires a character array to hold the string and
	// an integer for the number of characters. Ensure that the size of the
	// character array is large enough to hold the entire string.
	//
	// Throughout the examples in C, 256 is typically used as the size of a
	// character array. This will typically be sufficient, but not always.
	// For instance, a lookup table register node (which is not explored in
	// this example) may be much larger.
	//
	char stringValue[MAX_BUFF_LEN];
	size_t stringValueLength = MAX_BUFF_LEN;

	// Ensure allocated buffer is large enough for storing the string
	err = spinStringGetValue(hNode, NULL, &stringValueLength);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	const unsigned int k_maxChars = MAX_CHARS;
	if (stringValueLength <= k_maxChars)
	{
		err = spinNodeToString(hNode, stringValue, &stringValueLength);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			return err;
		}
	}

	// Print value
	indent(level);
	printf("%s: ", displayName);

	// Ensure that the value length is not excessive for printing
	if (stringValueLength > k_maxChars)
	{
		printf("...\n");
	}
	else
	{
		printf("%s\n", stringValue);
	}

	return err;
}

// This function retrieves and prints the display name and value of an integer
// node.
spinError printIntegerNode(spinNodeHandle hNode, unsigned int level)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	// Retrieve display name
	char displayName[MAX_BUFF_LEN];
	size_t displayNameLength = MAX_BUFF_LEN;

	err = spinNodeGetDisplayName(hNode, displayName, &displayNameLength);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	//
	// Retrieve integer node value
	//
	// *** NOTES ***
	// Keep in mind that the data type of an integer node value is an
	// int64_t as opposed to a standard int. While it is true that the two
	// are often interchangeable, it is recommended to use the int64_t
	// to avoid the introduction of bugs into software built with the
	// Spinnaker SDK.
	//
	int64_t integerValue = 0;

	err = spinIntegerGetValue(hNode, &integerValue);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Print value
	indent(level);
	printf("%s: %d\n", displayName, (int)integerValue);

	return err;
}

// This function retrieves and prints the display name and value of a float node.
spinError printFloatNode(spinNodeHandle hNode, unsigned int level)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	// Retrieve display name
	char displayName[MAX_BUFF_LEN];
	size_t displayNameLength = MAX_BUFF_LEN;

	err = spinNodeGetDisplayName(hNode, displayName, &displayNameLength);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	//
	// Retrieve float node value
	//
	// *** NOTES ***
	// Please take note that floating point numbers in the Spinnaker SDK are
	// almost always represented by the larger data type double rather than
	// float.
	//
	double floatValue = 0.0;

	err = spinFloatGetValue(hNode, &floatValue);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Print value
	indent(level);
	printf("%s: %f\n", displayName, floatValue);

	return err;
}

// This function retrieves and prints the display name and value of a boolean,
// printing "true" for true and "false" for false rather than the corresponding
// integer value ('1' and '0', respectively).
spinError printBooleanNode(spinNodeHandle hNode, unsigned int level)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	// Retrieve display name
	char displayName[MAX_BUFF_LEN];
	size_t displayNameLength = MAX_BUFF_LEN;

	err = spinNodeGetDisplayName(hNode, displayName, &displayNameLength);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	//
	// Retrieve value as a string representation
	//
	// *** NOTES ***
	// Boolean node type values are represented by the standard bool data
	// type. The boolean ToString() method returns either a '1' or '0' as a
	// a string rather than a more descriptive word like 'true' or 'false'.
	//
	bool8_t booleanValue = False;

	err = spinBooleanGetValue(hNode, &booleanValue);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Print value
	indent(level);
	printf("%s: %s\n", displayName, (booleanValue ? "true" : "false"));

	return err;
}

// This function retrieves and prints the display name and tooltip of a command
// node, limiting the number of printed characters to a macro-defined maximum.
// The tooltip is printed below as command nodes do not have an intelligible
// value.
spinError printCommandNode(spinNodeHandle hNode, unsigned int level)
{
	spinError err = SPINNAKER_ERR_SUCCESS;
	unsigned int i = 0;

	// Retrieve display name
	char displayName[MAX_BUFF_LEN];
	size_t displayNameLength = MAX_BUFF_LEN;

	err = spinNodeGetDisplayName(hNode, displayName, &displayNameLength);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	//
	// Retrieve tooltip
	//
	// *** NOTES ***
	// All node types have a tooltip available. Tooltips provide useful
	// information about nodes. Command nodes do not have a method to
	// retrieve values as their is no intelligible value to retrieve.
	//
	char toolTip[MAX_BUFF_LEN];
	size_t toolTipLength = MAX_BUFF_LEN;

	err = spinNodeGetToolTip(hNode, toolTip, &toolTipLength);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Print tooltip
	indent(level);
	printf("%s: ", displayName);

	// Ensure that the value length is not excessive for printing
	const unsigned int k_maxChars = MAX_CHARS;

	if (toolTipLength > k_maxChars)
	{
		for (i = 0; i < k_maxChars; i++)
		{
			printf("%c", toolTip[i]);
		}
		printf("...\n");
	}
	else
	{
		printf("%s\n", toolTip);
	}

	return err;
}

// This function retrieves and prints the display names of an enumeration node
// and its current entry (which is actually housed in another node unto itself).
spinError printEnumerationNodeAndCurrentEntry(spinNodeHandle hEnumerationNode, unsigned int level)
{
	spinError err = SPINNAKER_ERR_SUCCESS;
	unsigned int i = 0;

	// Retrieve display name
	char displayName[MAX_BUFF_LEN];
	size_t displayNameLength = MAX_BUFF_LEN;

	err = spinNodeGetDisplayName(hEnumerationNode, displayName, &displayNameLength);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	//
	// Retrieve current entry node
	//
	// *** NOTES ***
	// Returning the current entry of an enumeration node delivers the entry
	// node rather than the integer value or symbolic. The current entry's
	// integer and symbolic need to be retrieved from the entry node because
	// they cannot be directly accessed through the enumeration node in C.
	//
	spinNodeHandle hCurrentEntryNode = NULL;

	err = spinEnumerationGetCurrentEntry(hEnumerationNode, &hCurrentEntryNode);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	//
	// Retrieve current symbolic
	//
	// *** NOTES ***
	// Rather than retrieving the current entry node and then retrieving its
	// symbolic, this could have been taken care of in one step by using the
	// enumeration node's ToString() method.
	//
	char currentEntrySymbolic[MAX_BUFF_LEN];
	size_t currentEntrySymbolicLength = MAX_BUFF_LEN;

	err = spinEnumerationEntryGetSymbolic(hCurrentEntryNode, currentEntrySymbolic, &currentEntrySymbolicLength);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Print current entry symbolic
	indent(level);
	printf("%s: %s\n", displayName, currentEntrySymbolic);

	return err;
}

// This function retrieves and prints out the display name of a category node
// before printing all child nodes. Child nodes that are also category nodes are
// printed recursively.
spinError printCategoryNodeAndAllFeatures(spinNodeHandle hCategoryNode, unsigned int level)
{
	spinError err = SPINNAKER_ERR_SUCCESS;
	unsigned int i = 0;

	// Retrieve display name
	char displayName[MAX_BUFF_LEN];
	size_t displayNameLength = MAX_BUFF_LEN;

	err = spinNodeGetDisplayName(hCategoryNode, displayName, &displayNameLength);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Print display name
	indent(level);
	printf("%s\n", displayName);

	//
	// Retrieve number of children
	//
	// *** NOTES ***
	// The two nodes that typically have children are category nodes and
	// enumeration nodes. Throughout the examples, the children of category
	// nodes are referred to as features while the children of enumeration
	// nodes are referred to as entries. Further, it might be important to
	// note that enumeration nodes can be cast as category nodes, but
	// category nodes cannot be cast as enumeration nodes.
	//
	size_t numberOfFeatures = 0;

	err = spinCategoryGetNumFeatures(hCategoryNode, &numberOfFeatures);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	//
	// Iterate through all children
	//
	// *** NOTES ***
	// It is important to note that the children of an enumeration nodes
	// may be of any node type.
	//
	for (i = 0; i < numberOfFeatures; i++)
	{
		// Retrieve child
		spinNodeHandle hFeatureNode = NULL;

		err = spinCategoryGetFeatureByIndex(hCategoryNode, i, &hFeatureNode);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			return err;
		}

		bool8_t featureNodeIsAvailable = False;
		bool8_t featureNodeIsReadable = False;

		err = spinNodeIsAvailable(hFeatureNode, &featureNodeIsAvailable);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			return err;
		}

		err = spinNodeIsReadable(hFeatureNode, &featureNodeIsReadable);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			return err;
		}

		if (!featureNodeIsAvailable || !featureNodeIsReadable)
		{
			continue;
		}

		spinNodeType type = UnknownNode;

		err = spinNodeGetType(hFeatureNode, &type);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			return err;
		}

		// Category nodes must be dealt with separately in order to
		// retrieve subnodes recursively.
		if (type == CategoryNode)
		{
			err = printCategoryNodeAndAllFeatures(hFeatureNode, level + 1);
		}
		// Read all non-category nodes using spinNodeToString() function
		else if (chosenRead == VALUE)
		{
			err = printValueNode(hFeatureNode, level + 1);
		}
		// Read all non-category nodes using typed functions
		else if (chosenRead == INDIVIDUAL)
		{
			switch (type)
			{
			case StringNode:
				err = printStringNode(hFeatureNode, level + 1);
				break;

			case IntegerNode:
				err = printIntegerNode(hFeatureNode, level + 1);
				break;

			case FloatNode:
				err = printFloatNode(hFeatureNode, level + 1);
				break;

			case BooleanNode:
				err = printBooleanNode(hFeatureNode, level + 1);
				break;

			case CommandNode:
				err = printCommandNode(hFeatureNode, level + 1);
				break;

			case EnumerationNode:
				err = printEnumerationNodeAndCurrentEntry(hFeatureNode, level + 1);
				break;
			}
		}
	}
	printf("\n");

	return err;
}

// This function acts as the body of the example. First the TL device and
// TL stream nodemaps are retrieved and their nodes printed. Following this,
// the camera is initialized and then the GenICam node is retrieved
// and its nodes printed.
spinError RunSingleCamera(spinCamera hCam)
{
	spinError err = SPINNAKER_ERR_SUCCESS;
	unsigned int level = 0;

	//
	// Retrieve TL device nodemap
	//
	// *** NOTES ***
	// The TL device nodemap is available on the transport layer. As such,
	// camera initialization is unnecessary. It provides mostly immutable
	// information fundamental to the camera such as the serial number,
	// vendor, and model.
	//
	printf("\n*** PRINTING TL DEVICE NODEMAP ***\n\n");

	spinNodeMapHandle hNodeMapTLDevice = NULL;
	spinNodeHandle hTLDeviceRoot = NULL;

	// Retrieve nodemap from camera
	err = spinCameraGetTLDeviceNodeMap(hCam, &hNodeMapTLDevice);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to print TL device nodemap (nodemap retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve root node from nodemap
	err = spinNodeMapGetNode(hNodeMapTLDevice, "Root", &hTLDeviceRoot);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to print TL device nodemap (root node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	// Print values recursively
	err = printCategoryNodeAndAllFeatures(hTLDeviceRoot, level);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

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
	printf("*** PRINTING TL STREAM NODEMAP ***\n\n");

	spinNodeMapHandle hNodeMapStream = NULL;
	spinNodeHandle hStreamRoot = NULL;

	// Retrieve nodemap from camera
	err = spinCameraGetTLStreamNodeMap(hCam, &hNodeMapStream);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to print TL stream nodemap (nodemap retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve root node from nodemap
	err = spinNodeMapGetNode(hNodeMapStream, "Root", &hStreamRoot);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to print TL stream nodemap (root node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	// Print values recursively
	err = printCategoryNodeAndAllFeatures(hStreamRoot, level);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

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
	err = spinCameraInit(hCam);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to initialize camera. Aborting with error %d...\n\n", err);
		return err;
	}

	//
	// Retrieve GenICam nodemap
	//
	// *** NOTES ***
	// The GenICam nodemap is the primary gateway to customizing and
	// configuring the camera to suit your needs. Configuration options such
	// as image height and width, trigger mode enabling and disabling, and the
	// sequencer are found on this nodemap.
	//
	printf("*** PRINTING GENICAM NODEMAP ***\n\n");

	spinNodeMapHandle hNodeMap = NULL;
	spinNodeHandle hRoot = NULL;

	// Retrieve nodemap from camera
	err = spinCameraGetNodeMap(hCam, &hNodeMap);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to print GenICam nodemap (nodemap retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve root node from nodemap
	err = spinNodeMapGetNode(hNodeMap, "Root", &hRoot);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to print GenICam nodemap (root node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	// Print values recursively
	err = printCategoryNodeAndAllFeatures(hRoot, level);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	//
	// Deinitialize camera
	//
	// *** NOTES ***
	// Camera deinitialization helps ensure that devices clean up properly
	// and do not need to be power-cycled to maintain integrity.
	//
	err = spinCameraDeInit(hCam);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to deinitialize camera. Non-fatal error %d...\n\n", err);
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
