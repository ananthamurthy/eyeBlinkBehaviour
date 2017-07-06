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

#ifndef PGR_SPINNAKER_CAMERABASE_H
#define PGR_SPINNAKER_CAMERABASE_H

#include "TransportLayerStream.h"
#include "TransportLayerDevice.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include "SpinnakerPlatform.h"

#include "Event.h"
#include "SpinnakerDefs.h"

namespace Spinnaker
{
	class ImagePtr;

	/**
	*  @defgroup SpinnakerClasses Spinnaker Classes
	*/
	/*@{*/

	/**
	*  @defgroup CameraBase_h Camera Base Class
	*/
	/*@{*/

	/**
	* @brief The base class for the camera object.
	*/

	class SPINNAKER_API CameraBase
	{
	public:

		/**
		* Virtual Destructor
		*/
		virtual ~CameraBase(void);

		/**
		* Connect to camera, retrieve XML and generate node map.
		* This function needs to be called before any camera related
		* API calls such as BeginAcquisition(), EndAcquisition(),
		* GetNodeMap(), GetNextImage(), FlushImages().
		*
		* @see BeginAcquisition()
		* @see EndAcquisition()
		* @see GetNodeMap()
		* @see GetNextImage()
		* @see FlushImages()
		*/
		void Init();

		/**
		* Disconnect camera port and free GenICam node map and
		* GUI XML. Do not call more functions that access the remote
		* device such as WritePort/ReadPort after calling DeInit();
		* Events should also be unregistered before calling camera DeInit().
		* Otherwise an exception will be thrown in the DeInit() call and require
		* the user to unregister events before the camera can be re-initialized again.
		*
		* @see Init()
		* @see UnregisterEvent(Event & evtToUnregister)
		*/
		void DeInit();

		/**
		* Checks if camera is initialized. This function needs to return
		* true in order to retrieve a valid NodeMap from the GetNodeMap()
		* call.
		*
		* @see GetNodeMap()
		*
		* @return If camera is initialized or not
		*/
		bool IsInitialized();

		/**
		* Checks a flag to determine if camera is still valid for use.
		*
		* @return If camera is valid or not
		*/
		bool IsValid();

		/**
		* Gets a reference to the node map that is generated from a GenICam
		* XML file.  The camera must be initialized by a call to Init() first
		* before a node map reference can be successfully acquired.
		*
		* @see Init()
		*
		* @return  A reference to the INodeMap.
		*/
		GenApi::INodeMap & GetNodeMap() const;


		/**
		* Gets a reference to the node map that is generated from a GenICam
		* XML file for the GenTL Device module.  The camera does not need to be
		* initialized before acquiring this node map.
		*
		* @return  A reference to the INodeMap.
		*/
		GenApi::INodeMap & GetTLDeviceNodeMap() const;

		/**
		* Gets a reference to the node map that is generated from a GenICam
		* XML file for the GenTL Stream module.  The camera does not need to be
		* initialized before acquiring this node map.
		*
		* @return  A reference to the INodeMap.
		*/
		GenApi::INodeMap & GetTLStreamNodeMap() const;

		/**
		* Returns the access mode that the software has on the Camera.
		* The camera does not need to be initialized before calling this function.
		*
		* @see Init()
		*
		* @return An enumeration value indicating the access mode
		*/
		GenApi::EAccessMode GetAccessMode() const;

		/**
		* Starts the image acquisition engine. The camera must be initialized via
		* a call to Init() before starting an acquisition.
		*
		* @see Init()
		*/
		void BeginAcquisition();

		/**
		* Stops the image acquisition engine.  If EndAcquisition() is called
		* without a prior call to BeginAcquisition() an error message
		* "Camera is not started" will be thrown. All Images that were
		* acquired using GetNextImage() need to be released first using image->Release()
		* before calling EndAcquisition().  All buffers in the input pool and
		* output queue will be discarded when EndAcquisition() is called.
		*
		*
		* @see Init()
		* @see BeginAcquisition()
		* @see GetNextImage( grabTimeout )
		* @see Image::Release()
		* @see FlushImages()
		*
		*/
		void EndAcquisition();

		/**
		* Gets the next image that was received by the transport layer.  This function
		* will block indefinitely until an image arrives.
		*
		* @see Init()
		* @see BeginAcquisition()
		* @see EndAcquisition()
		*
		* @param grabTimeout a 64bit value that represents a timeout in milliseconds
		*
		* @return pointer to an Image object
		*
		*/
		ImagePtr GetNextImage(uint64_t grabTimeout = EVENT_TIMEOUT_INFINITE);

		/**
		* This returns a unique id string that identifies the camera.  This is the
		* camera serial number.
		*
		* @return string that uniquely identifies the camera (serial number)
		*/
		GenICam::gcstring GetUniqueID();

		/**
		* Returns true if the camera is currently streaming or false if it
		* is not.
		*
		* @see Init()
		*
		* @return returns true if camera is streaming and false otherwise.
		*/
		bool IsStreaming() const;

		/**
		* Returns the GUI XML that can be passed into the Spinnaker GUI framework
		*
		* @return GenICam::gcstring that represents the uncompressed GUI XML file
		*/
		GenICam::gcstring GetGuiXml() const;

		/**
		* Registers a specific event for the camera.  The camera has to be initialized first
		* with a call to Init() before registering for events.
		*
		* @see Init()
		*
		* @param evtToRegister The event to register for the camera
		*
		*/
		void RegisterEvent(Event & evtToRegister);


		/**
		* Registers a specific event for the camera
		*
		* @see Init()
		*
		* @param evtToRegister The event to register for the camera
		* @param eventName The event name to register
		*
		*/
		void RegisterEvent(Event & evtToRegister, GenICam::gcstring eventName);

		/**
		* Unregisters an event for the camera
		* Events should be unregistered first before calling camera DeInit().
		* Otherwise an exception will be thrown in the DeInit() call and require
		* the user to unregister events before the camera can be re-initialized again.
		*
		* @see DeInit()
		*
		* @param evtToUnregister The event to unregister from the camera
		*
		*/
		void UnregisterEvent(Event & evtToUnregister);

		/**
		* Returns the number of images that are currently in use.  Each of
		* the images that are currently in use must be cleaned up with
		* a call to image->Release() before calling system->ReleaseInstance().
		*
		* @return The number of images that needs to be cleaned up.
		*
		*/
		unsigned int GetNumImagesInUse();

	public:
		/**
		* Gets vital camera information by connecting to the camera's
		* bootstrap registers. These nodes also access host software
		* modules and the nodes can be used without having to call
		* Init() on the camera.
		*/
		TransportLayerDevice TLDevice;

		/**
		* Gets information about the stream data by connecting to
		* the camera's bootstrap registers.  These nodes also access
		* host software modules and the nodes can be used without
		* having to call Init() on the camera.
		*/
		TransportLayerStream TLStream;

	protected:

		/**
		* Default constructor.
		*/
		CameraBase(void);

		/**
		* Copy constructor.
		*/
		CameraBase(const CameraBase & /*cam*/);

		/**
		* Assignment operator.
		*/
		CameraBase&	operator=(const CameraBase& /*cam*/);

		friend class CameraInternal;
		friend class InterfaceImpl;
		struct CameraBaseData; // Forward declaration
		CameraBaseData* m_pCameraBaseData;


	private:
	};

	/*@}*/

	/*@}*/
}

#endif // PGR_SPINNAKER_CAMERABASE_H