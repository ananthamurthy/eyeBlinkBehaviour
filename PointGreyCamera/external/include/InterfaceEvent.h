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

#ifndef PGR_SPINNAKER_INTERFACEEVENT_H
#define PGR_SPINNAKER_INTERFACEEVENT_H

#include "Event.h"
#include "ArrivalEvent.h"
#include "RemovalEvent.h"
#include "SpinnakerPlatform.h"

namespace Spinnaker
{
	/**
	 * @defgroup SpinnakerEventClasses Spinnaker Event Classes
	 */
	/*@{*/

	/**
	 *  @defgroup InterfaceEvent_h InterfaceEvent Class
	 */
	/*@{*/

    /**
    * @brief A handler to device arrival and removal events on all interfaces.
    */

	class SPINNAKER_API InterfaceEvent : public virtual ArrivalEvent, public virtual RemovalEvent
	{
	public:
		/**
		* Default constructor.
		*/
		InterfaceEvent();

		/**
		* Virtual destructor.
		*/
		virtual ~InterfaceEvent();

		/**
		* Device arrival event callback.
		*/
		virtual void OnDeviceArrival() = 0;

		/**
		* Callback to the device removal event.
		*
		* @param serialNumber The serial number of the removed device
		*/
		virtual void OnDeviceRemoval(uint64_t serialNumber) = 0;

	protected:
		/**
		* Copy constructor.
		*/
		InterfaceEvent( const InterfaceEvent& );

		/**
		* Assignment operator.
		*/
		InterfaceEvent& operator=( const InterfaceEvent& );
	};
	/*@}*/

	/*@}*/
}

#endif // PGR_SPINNAKER_INTERFACEEVENT_H