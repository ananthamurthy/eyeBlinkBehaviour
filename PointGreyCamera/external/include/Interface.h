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

#ifndef PGR_SPINNAKER_INTERFACE_H
#define PGR_SPINNAKER_INTERFACE_H

#include "SpinnakerPlatform.h"
#include "SpinnakerDefs.h"
#include "CameraList.h"
#include "Event.h"
#include "TransportLayerInterface.h"


namespace Spinnaker
{
	/**
	 * @defgroup SpinnakerClasses Spinnaker Classes
	 */

	/*@{*/

	/**
	 * @defgroup Interface_h Interface Class
	 */

	/*@{*/

    /**
    * @brief An interface object which holds a list of cameras.
    */

	class SPINNAKER_API Interface
	{
	public:

		/**
		* Virtual Destructor
		*/
		virtual ~Interface(void);


		/**
         * Returns a list of cameras available on this interface.  This call
		 * returns either usb3 vision  or gige vision cameras depending on the
		 * underlying transport layer of this interface.  The camera list object
		 * will reference count the cameras that it holds.  It is important that
		 * the CameraList is destroyed or is cleared before System::ReleaseInstance()
		 * can be called or an InterfaceList that holds this interface can be cleared.
		 *
		 * @see System::ReleaseInstance()
		 *
		 * @see InterfaceList::Clear()
		 *
		 * @see CameraList::Clear()
         *
         * @param updateCameras A flag used to issue an updateCameras() call internally 
         *        before getting the camera list
         *
         * @return An CameraList object that contains a list of cameras on this interface.
         */
		CameraList GetCameras(bool updateCameras = true) const;

		/**
         * Updates the list of cameras on this interface.  This function needs to be called
		 * before any cameras can be discovered using GetCameras().  System::GetCameras() will
		 * automatically call this function for each interface it enumerates.  If the list 
         * changed after the last time System::GetCameras() or UpdateCameras() was called 
         * then the return value will be true, otherwise it is false.
		 *
		 * @see System::GetCameras()
		 *
		 * @see GetCameras()
         *
         * @return true if cameras changed on interface and false otherwise.
         */
		bool UpdateCameras();

		/**
		 * Gets a nodeMap that is generated from a GenICam
		 * XML file for the GenTL interface Module.
		 *
		 * @return  A reference to a INodeMap object.
		 */
		GenApi::INodeMap & GetTLNodeMap() const;

		/**
		* Registers an event for the interface
        *
        * @param evtToRegister The event to register for the interface        
        *
		*/
        void RegisterEvent(Event & evtToRegister);

		/**
		* Unregisters an event for the interface
        *
        * @param evtToUnregister The event to unregister from the interface
        *
		*/
		void UnregisterEvent(Event & evtToUnregister);

		/**
		* Checks if the interface is in use by any camera objects
		*
        * @return Returns true if the interface is in use and false otherwise.
		*/
		bool IsInUse() const;

	public:

		/*
		* Gets vital interface information without connecting to the XML through
		* transport layer specific bootstrap registers.
		*/
		TransportLayerInterface TLInterface;
        
	protected:
		friend class InterfaceInternal;
		friend class SystemImpl;
		struct InterfaceData; // Forward declaration
		InterfaceData* m_pInterfaceData;

	private:
		/*
		* Default Constructor
		*/
		Interface(void);

		/*
		* Copy Constructor
		*/
		Interface(const Interface & /*iface*/);

		/**
		* Assignment operator.
		*/
		Interface&	operator=(const Interface&  /*iface*/);
	};

	/*@}*/

	/*@}*/
}

#endif // PGR_SPINNAKER_INTERFACE_H