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

#ifndef PGR_SPINNAKER_EVENT_H
#define PGR_SPINNAKER_EVENT_H

#include "SpinnakerDefs.h"
#include "SpinnakerPlatform.h"
#include "SpinGenApi/GCString.h"

namespace Spinnaker
{
	/**
	 *  @defgroup SpinnakerEventClasses Spinnaker Event Classes
	 */
	/*@{*/

	/**
	 *  @defgroup Event_h Event Class
	 */
	 /*@{*/

    /**
    * @brief The base class for all event types.
    */

	class SPINNAKER_API Event
	{
	public:

		/**
		* Virtual Destructor
		*/
		virtual ~Event();

		/**
		* Sets the event type
		*
		* @param eventType The event type
		*
		*/
		void SetEventType(EventType eventType);

		/**
		* Gets the event type
		*
		* @return The event type
		*
		*/
		EventType GetEventType();

		/**
		* Gets the event payload data
		*
		* @return The event payload data
		*/
		const uint8_t* GetEventPayloadData();

		/**
		* Gets the event payload data size
		*
		* @return The event payload data size
		*/
		const size_t GetEventPayloadDataSize();

	protected:
		Event();
		Event(const Event&);
		Event& operator=( const Event& );
		friend class EventProcessor;
		friend class IDataStream;
		friend class Stream;
		struct EventData;
		EventData* m_pEventData;
		void SetEventPayload(uint8_t* offset, size_t length);
	};

	/*@}*/

	/*@}*/
}

#endif // PGR_SPINNAKER_EVENT_H