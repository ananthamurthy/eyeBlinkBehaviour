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

#ifndef PGR_SPINNAKER_SYSTEM_H
#define PGR_SPINNAKER_SYSTEM_H

#include "SpinnakerPlatform.h"
#include "SpinnakerDefs.h"
#include "InterfaceList.h"
#include "CameraList.h"
#include "LoggingEvent.h"

namespace Spinnaker
{
	// Forward declaration of implementation class
	class SystemImpl;
	class SystemPtr;
	class LoggingEvent;

	/**
	 * @defgroup SpinnakerClasses Spinnaker Classes
	 */
	/*@{*/

	/**
	 * @defgroup System_h System Class
	 */
	/*@{*/

    /**
    * @brief The system object is used to retrieve the list of interfaces and cameras available.
    */

    class SPINNAKER_API System
    {
    public:


		/**
         * Returns a pointer to a Singleton instance of a System object.
		 * The System object may be used to get cameras or interfaces.
		 * When an application is done using the cameras it is necessary
		 * to free the System by calling ReleaseInstance().
		 *
		 * @see ReleaseInstance()
         *
         * @return A const ref to a system object.
         */
		static SystemPtr GetInstance();

        /**
        * Default destructor.
        */
        virtual ~System();

		/**
         * This call releases the instance of the System Singleton for
		 * this process.  After successfully releasing the System instance
		 * the pointer returned by GetInstance() will be invalid.  Calling
		 * ReleaseInstance while a camera reference is still held will throw
		 * an error of type SPINNAKER_ERR_RESOURCE_IN_USE.
		 *
         * @see Error
		 * @see GetInstance()
         *
         */
		void ReleaseInstance();

		/**
         * Returns a list of interfaces available on the system.  This call
		 * returns GigE and Usb2 and Usb3 interfaces.
         *
         * @param updateInterface Determines whether or not UpdateInterfaceList() is called before getting available interfaces
         *
         * @return An InterfaceList object that contains a list of all interfaces.
         */
        InterfaceList GetInterfaces(bool updateInterface = true);

		/**
         * Returns a list of cameras that are available on the system.  This call
		 * returns both GigE Vision and Usb3 Vision cameras from all interfaces.
		 * The camera list object will reference count the cameras it returns.  It
		 * is important that the camera list is destroyed or is cleared before calling
		 * system->ReleaseInstance() or else the call to system->ReleaseInstance() 
         * will result in an error message thrown that a reference to the camera 
         * is still held.
		 *
		 * @see ReleaseInstance()
		 *
		 * @see CameraList::Clear()
         *
         * @param updateInterfaces Determines whether or not updateInterfaceList() is called before getting cameras 
         *                         from available interfaces on the system
         * 
         * @param updateCameras Determines whether or not UpdateCameras() is called before getting cameras from 
         *                      available interfaces on the system
         *
         * @return An CameraList object that contains a list of all cameras.
         */
        CameraList GetCameras(bool updateInterfaces = true, bool updateCameras = true);

        /**
         * Updates the list of cameras on the system.  Note that System::GetCameras() 
         * internally calls UpdateCameras() for each interface it enumerates.  If the list
		 * changed between this call and the last time UpdateCameras was called then the return
		 * value will be true, otherwise it is false.
		 *	
		 * @see GetCameras()
         *
         * @param updateInterfaces Determines whether or not UpdateInterfaceList() is called before updating cameras
         *                         for available interfaces on the system
         *
         * @return True if cameras changed on interface and false otherwise.
         */
        bool UpdateCameras(bool updateInterfaces = true);
                
        /**
         * Registers events for all available interfaces that are found on the system 
         *
         * @param evtToRegister The event to register for the available interfaces  
         * @param updateInterface Determines whether or not UpdateInterfaceList() is called before registering event for 
         *                        available interfaces on the system
         */
        void RegisterInterfaceEvent(Event & evtToRegister, bool updateInterface = true);

        /**
        * Unregisters events for all available interfaces that are found on the system 
        *
        * @param evtToUnregister The event to unregister from the available interfaces
        */
        void UnregisterInterfaceEvent(Event & evtToUnregister);

		 /**
         * Registers a logging event.
         *
         * @param handler The logging event handler to register
         */
		void RegisterLoggingEvent(LoggingEvent & handler);

		/**
         * Unregisters all previously registered logging events.
         *
         */
		void UnregisterAllLoggingEvent();

		/**
         * Unregisters a logging event.
         *
         * @param handler The logging event handler to unregister
         */
		void UnregisterLoggingEvent(LoggingEvent & handler);

		/**
         * Sets a threshold priority level for logging event. Logging events
		 * below such level will not trigger callbacks.
		 *
		 * Spinnaker uses five levels of logging:
		 *	- Error		— failures that are non-recoverable without user intervention.
		 *	- Warning	— failures that are recoverable without user intervention.
		 *	- Notice	— information about events such as camera arrival and removal, initialization and deinitialization, starting and stopping image acquisition, and feature modification.
		 *	- Info		— information about recurring events that are generated regularly such as information on individual images.
		 *	- Debug		— information that can be used to troubleshoot the system.
		 *
         *
         * @see SpinnakerLogLevel 
         *
         * @param level The threshold level
         */
		void SetLoggingEventPriorityLevel(SpinnakerLogLevel level);

		/**
         * Retrieves the current logging event priority level.
         *
		 * Spinnaker uses five levels of logging:
		 *	- Error		— failures that are non-recoverable without user intervention.
		 *	- Warning	— failures that are recoverable without user intervention.
		 *	- Notice	— information about events such as camera arrival and removal, initialization and deinitialization, starting and stopping image acquisition, and feature modification.
		 *	- Info		— information about recurring events that are generated regularly such as information on individual images.
		 *	- Debug		— information that can be used to troubleshoot the system.
		 *
         * @see SpinnakerLogLevel 
         *
         * @return Level The threshold level
         */
		SpinnakerLogLevel GetLoggingEventPriorityLevel();

		/**
         * Checks if the system is in use by any interface or camera objects.
         *
		 * @return Returns true if the system is in use and false otherwise.
         */
		bool IsInUse();

    private:

		 /**
         * Default constructor.
         */
        System();

		/**
         * Copy constructor.
         */
		System( const System& );

		/**
         * Assignment operator.
         */
		System& operator=( const System& );
    };

	/*@}*/

	/*@}*/
}

#endif // PGR_SPINNAKER_SYSTEM_H
