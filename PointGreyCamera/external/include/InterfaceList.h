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

#ifndef PGR_SPINNAKER_INTERFACELIST_H
#define PGR_SPINNAKER_INTERFACELIST_H

#include "SpinnakerPlatform.h"
#include "SpinnakerDefs.h"
#include "Interface.h"
#include "InterfacePtr.h"

namespace Spinnaker
{
	/**
	 * @defgroup SpinnakerClasses Spinnaker Classes
	 */

	/*@{*/

	/**
	 * @defgroup InterfaceList_h InterfaceList Class
	 */

	/*@{*/

    /**
    * @brief A list of the available interfaces on the system.
    */

	class SPINNAKER_API InterfaceList
	{
	public:

		/*
		* Default Constructor
		*/
		InterfaceList(void);

		/*
		* Virtual Destructor
		*/
		virtual ~InterfaceList(void);

		/*
		* Copy Constructor
		*/
		InterfaceList(const InterfaceList & iface);

		/**
         * Assignment operator.
         */
		InterfaceList&	operator=( const InterfaceList& iface );

		/**
		 * Array subscription operators
		 */
		InterfacePtr operator[](int index);

		/**
         * Returns the size of the interface list.  The size is the number
		 * of Interface objects stored in the list.
         *
         * @return An integer that represents the list size.
         */
		int GetSize() const;

		/**
         * Returns a pointer to an Interface object at the "index".
         *
		 * @param index The index at which to retrieve the Interface object
		 *
         * @return A pointer to an Interface object.
         */
		InterfacePtr GetByIndex(int index) const;

		/**
         * Clears the list of interfaces and destroys their corresponding objects.
		 * It is important to first make sure there are no referenced cameras still
		 * in use before calling Clear().  If a camera on any of the interfaces is still
		 * in use this function will throw an exception.
         *
         */
		void Clear();


	protected:
		friend class SystemImpl;
		struct InterfaceListData; // Forward declaration
		InterfaceListData* m_pInterfaceListData;
	};

	/*@}*/

	/*@}*/
}

#endif // PGR_SPINNAKER_INTERFACELIST_H