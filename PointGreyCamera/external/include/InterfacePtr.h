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

#ifndef PGR_SPINNAKER_INTERFACE_PTR_H
#define PGR_SPINNAKER_INTERFACE_PTR_H

#include "SpinnakerPlatform.h"
#include "BasePtr.h"
#include "Interface.h"


namespace Spinnaker
{
	/**
	*  @defgroup SpinnakerClasses Spinnaker Classes
	*/

	/*@{*/

	/**
	*  @defgroup InterfacePtr_h InterfacePtr Class
	*/

	/*@{*/

	/**
	* @brief A reference tracked pointer to the interface object.
	*/

	class SPINNAKER_API InterfacePtr : public BasePtr<Interface>
	{
	public:
		/**
		* Default Constructor
		*/
		InterfacePtr() throw()
			: BasePtr<Interface>()
		{
		}

		/**
		* Default Constructor
		*/
		InterfacePtr(const int /*nMustBeNull*/) throw()
			: BasePtr<Interface>()
		{
		}

		/**
		* Virtual Destructor
		*/
		virtual ~InterfacePtr(void){};

		/**
		* Copy Constructor
		*/
		virtual InterfacePtr& operator=(const int nMustBeNull){ return dynamic_cast<InterfacePtr&>(BasePtr<Interface>::operator=(nMustBeNull)); };
		
	};

	/*@}*/

	/*@}*/
}

#endif //PGR_SPINNAKER_INTERFACE_PTR_H