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
 *  @example NodeMapInfo_QuickSpin.cpp
 *
 *  @brief NodeMapInfo_QuickSpin.cpp shows how to interact with nodes
 *  using the QuickSpin API. QuickSpin is a subset of the Spinnaker library 
 *  that allows for simpler node access and control.
 *
 *  This example demonstrates the retrieval of information from both the
 *  transport layer and the camera. Because the focus of this example is node
 *  access, which is where QuickSpin and regular Spinnaker differ, this 
 *  example differs from NodeMapInfo quite a bit.
 *
 *  A much wider range of topics is covered in the full Spinnaker examples than
 *  in the QuickSpin ones. There are only enough QuickSpin examples to
 *  demonstrate node access and to get started with the API; please see full
 *  Spinnaker examples for further or specific knowledge on a topic.
 */

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// This function prints device information from the transport layer.
int PrintTransportLayerDeviceInfo(CameraPtr pCamera)
{
	int result = 0;

	try
	{
		//
		// Print device information from the transport layer
		//
		// *** NOTES ***
		// In QuickSpin, accessing device information on the transport layer is
		// accomplished via a camera's TLDevice property. The TLDevice property
		// houses nodes related to general device information such as the three 
		// demonstrated below, device access status, XML and GUI paths and 
		// locations, and GEV information to name a few. The TLDevice property
		// allows access to nodes that would generally be retrieved through the 
		// TL device nodemap in full Spinnaker.
		//
		// Notice that each node is checked for availability and readability
		// prior to value retrieval. Checking for availability and readability 
		// (or writability when applicable) whenever a node is accessed is
		// important in terms of error handling. If a node retrieval error
		// occurs but remains unhandled, an exception is thrown.
		//
		// Print device serial number
		cout << "Device serial number: ";

		if (pCamera->TLDevice.DeviceSerialNumber != NULL && pCamera->TLDevice.DeviceSerialNumber.GetAccessMode() == RO)
		{
			cout << pCamera->TLDevice.DeviceSerialNumber.ToString() << endl;
		}
		else
		{
			cout << "unavailable" << endl;
			result = -1;
		}

		// Print device vendor name
		cout << "Device vendor name: ";

		if (pCamera->TLDevice.DeviceVendorName != NULL && pCamera->TLDevice.DeviceVendorName.GetAccessMode() == RO)
		{
			cout << pCamera->TLDevice.DeviceVendorName.ToString() << endl;
		}
		else
		{
			cout << "unavailable" << endl;
			result = -1;
		}

		// Print device display name
		cout << "Device display name: ";

		if (pCamera->TLDevice.DeviceDisplayName != NULL && pCamera->TLDevice.DeviceDisplayName.GetAccessMode() == RO)
		{
			cout << pCamera->TLDevice.DeviceDisplayName.ToString() << endl << endl;
		}
		else
		{
			cout << "unavailable" << endl << endl;
			result = -1;
		}
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function prints stream information from the transport layer.
int PrintTransportLayerStreamInfo(CameraPtr pCamera)
{
	int result = 0;

	try
	{
		//
		// Print stream information from the transport layer
		//
		// *** NOTES ***
		// In QuickSpin, accessing stream information on the transport layer is
		// accomplished via a camera's TLStream property. The TLStream property
		// houses nodes related to streaming such as the two demonstrated below,
		// buffer information, and GEV packet information to name a few. The 
		// TLStream property allows access to nodes that would generally be 
		// retrieved through the TL stream nodemap in full Spinnaker.
		//
		// Print stream ID
		cout << "Stream ID: ";

		if (pCamera->TLStream.StreamID != NULL && pCamera->TLStream.StreamID.GetAccessMode() == RO)
		{
			cout << pCamera->TLStream.StreamID.ToString() << endl;
		}
		else
		{
			cout << "unavailable" << endl;
			result = -1;
		}

		// Print stream type
		cout << "Stream type: ";

		if (pCamera->TLStream.StreamType != NULL && pCamera->TLStream.StreamType.GetAccessMode() == RO)
		{
			cout << pCamera->TLStream.StreamType.ToString() << endl << endl;
		}
		else
		{
			cout << "unavailable" << endl << endl;
			result = -1;
		}
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function prints information about the interface.
int PrintTransportLayerInterfaceInfo(InterfacePtr pInterface)
{
	int result = 0;

	try
	{
		//
		// Print stream information from the transport layer
		//
		// *** NOTES ***
		// In QuickSpin, accessing interface information is accomplished via an
		// interface's TLInterface property. The TLInterface property houses 
		// nodes that hold information about the interface such as the three
		// demonstrated below, other general interface information, and 
		// GEV addressing information. The TLInterface property allows access to
		// nodes that would generally be retrieved through the interface nodemap 
		// in full Spinnaker.
		//
		// Interface nodes should also always be checked for availability and
		// readability (or writability when applicable). If a node retrieval 
		// error occurs but remains unhandled, an exception is thrown.
		//
		// Print interface display name
		cout << "Interface display name: ";
		if (pInterface->TLInterface.InterfaceDisplayName != NULL && pInterface->TLInterface.InterfaceDisplayName.GetAccessMode() == RO)
		{
			cout << pInterface->TLInterface.InterfaceDisplayName.ToString() << endl;
		}
		else
		{
			cout << "Unavailable" << endl;
			result = -1;
		}

		// Print interface ID
		cout << "Interface ID: ";
		if (pInterface->TLInterface.InterfaceID != NULL && pInterface->TLInterface.InterfaceID.GetAccessMode() == RO)
		{
			cout << pInterface->TLInterface.InterfaceID.ToString() << endl;
		}
		else
		{
			cout << "Unavailable" << endl;
			result = -1;
		}

		// Print interface type
		cout << "Interface type: ";
		if (pInterface->TLInterface.InterfaceType != NULL && pInterface->TLInterface.InterfaceType.GetAccessMode() == RO)
		{
			cout << pInterface->TLInterface.InterfaceType.ToString() << endl << endl;
		}
		else
		{
			cout << "Unavailable" << endl << endl;
			result = -1;
		}
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// This function prints device information from the GenICam nodemap.
int PrintGenICamDeviceInfo(CameraPtr pCamera)
{
	int result = 0;

	try
	{
		//
		// Print device information from the camera
		//
		// *** NOTES ***
		// Most camera interaction happens through GenICam nodes. The 
		// advantages of these nodes is that there is a lot more of them, they
		// allow for a much deeper level of interaction with a camera, and no 
		// intermediate property (i.e. TLDevice or TLStream) is required. The 
		// disadvantage is that they require initialization.
		// 
		// Print exposure time
		cout << "Exposure time: ";

		if (pCamera->ExposureTime != NULL && (pCamera->ExposureTime.GetAccessMode() == RO || pCamera->ExposureTime.GetAccessMode() == RW))
		{
			cout << pCamera->ExposureTime.ToString() << endl;
		}
		else
		{
			cout << "unavailable" << endl;
			result = -1;
		}

		// Print black level
		cout << "Black level: ";

		if (pCamera->BlackLevel != NULL && (pCamera->BlackLevel.GetAccessMode() == RO || pCamera->BlackLevel.GetAccessMode() == RW))
		{
			cout << pCamera->BlackLevel.ToString() << endl;
		}
		else
		{
			cout << "unavailable" << endl;
			result = -1;
		}

		// Print height
		cout << "Height: ";

		if (pCamera->Height != NULL && pCamera->Height.GetAccessMode() == RW)
		{
			cout << pCamera->Height.ToString() << endl << endl;
		}
		else
		{
			cout << "unavailable" << endl << endl;
			result = -1;
		}
	}
	catch (Spinnaker::Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		result = -1;
	}

	return result;
}

// Example entry point; this function prints transport layer information from
// each interface and transport and GenICam information from each
// camera.
int main(int /*argc*/, char** /*argv*/)
{
	int result = 0;

	// Print application build information
	cout << "Application build date: " << __DATE__ << " " << __TIME__ << endl << endl;

	// Retrieve singleton reference to system object
	SystemPtr system = System::GetInstance();

	// Retrieve list of interfaces from the system 
	CameraList camList = system->GetCameras();

	unsigned int numCameras = camList.GetSize();

	cout << "Number of cameras detected: " << numCameras << endl << endl;

	// Retrieve list of cameras from the system
	InterfaceList interfaceList = system->GetInterfaces();

	unsigned int numInterfaces = interfaceList.GetSize();

	cout << "Number of interfaces detected: " << numInterfaces << endl << endl;

	//
	// Print information on each interface
	//
	// *** NOTES ***
	// All USB 3 Vision and GigE Vision interfaces should enumerate for
	// Spinnaker.
	//
	cout << endl << "*** PRINTING INTERFACE INFORMATION ***" << endl << endl;
	
	for (unsigned int i = 0; i < numInterfaces; i++)
    {
		result = result | PrintTransportLayerInterfaceInfo(interfaceList.GetByIndex(i));
    }
	
	//
	// Print general device information on each camera from transport layer
	//
	// *** NOTES ***
	// Transport layer nodes do not require initialization in order to interact
	// with them.
	//
	cout << endl << "*** PRINTING TRANSPORT LAYER DEVICE INFORMATION ***" << endl << endl;

	for (unsigned int i = 0; i < numCameras; i++)
    {
		result = result | PrintTransportLayerDeviceInfo(camList.GetByIndex(i));
    }

	//
	// Print streaming information on each camera from transport layer
	//
	// *** NOTES ***
	// Again, initialization is not required to print information from the 
	// transport layer; this is equally true of streaming information.
	//
	cout << endl << "*** PRINTING TRANSPORT LAYER STREAMING INFORMATION ***" << endl << endl;
	
	for (unsigned int i = 0; i < numCameras; i++)
	{
		result = result | PrintTransportLayerStreamInfo(camList.GetByIndex(i));
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
	cout << endl << "*** PRINTING GENICAM INFORMATION ***" << endl << endl;

	for (unsigned int i = 0; i < numCameras; i++)
	{
		// Initialize camera
		camList.GetByIndex(i)->Init();

		// Print information
		result = result | PrintGenICamDeviceInfo(camList.GetByIndex(i));

		// Deinitialize camera
		camList.GetByIndex(i)->DeInit();
	}

	// Clear camera list before releasing system
	camList.Clear();

	// Clear interface list before releasing system
	interfaceList.Clear();

	// Release system
	system->ReleaseInstance();

	cout << endl << "Done! Press Enter to exit..." << endl;
	getchar();

	return result;
}

