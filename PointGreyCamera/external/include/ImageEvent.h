//=============================================================================
// Copyright � 2015 Point Grey Research, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of 
// Point Grey Research, Inc. ("Confidential Information"). You shall not
// disclose such Confidential Information and shall use it only in 
// accordance with the terms of the "License Agreement" that you 
// entered into with PGR in connection with this software.
//
// UNLESS OTHERWISE SET OUT IN THE LICENSE AGREEMENT, THIS SOFTWARE IS 
// PROVIDED ON AN �AS-IS� BASIS AND POINT GREY RESEARCH INC. MAKES NO 
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

#ifndef PGR_SPINNAKER_IMAGEEVENT_H
#define PGR_SPINNAKER_IMAGEEVENT_H

#include "Event.h"
#include "SpinnakerPlatform.h"
#include "Image.h"

namespace Spinnaker
{
	/**
	 *  @defgroup SpinnakerEventClasses Spinnaker Event Classes
	 */

	/*@{*/

	/**
	 *  @defgroup ImageEvent_h ImageEvent Class
	 */

	/*@{*/

    /**
    * @brief A handler for capturing image arrival events.
    */

	class SPINNAKER_API ImageEvent : public virtual Event
	{
	public:
		/**
		* Default Constructor
		*/
		ImageEvent();

		/**
		* Virtual Destructor
		*/
		virtual ~ImageEvent();

		/**
		* Image event callback
		*
		* @param image The ImagePtr object
		*/
		virtual void OnImageEvent(ImagePtr image) = 0;

	protected:
		/**
		* Copy Constructor
		*/
		ImageEvent( const ImageEvent& );

		/**
		* Assignment operator.
		*/
		ImageEvent& operator=( const ImageEvent& );
	};

	/*@}*/

	/*@}*/
}

#endif // PGR_SPINNAKER_IMAGEEVENT_H