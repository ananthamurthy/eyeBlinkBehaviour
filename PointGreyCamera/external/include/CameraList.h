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

#ifndef PGR_SPINNAKER_CAMERALIST_H
#define PGR_SPINNAKER_CAMERALIST_H
#include "SpinnakerPlatform.h"
#include "SpinnakerDefs.h"
#include "Camera.h"
#include "CameraPtr.h"

namespace Spinnaker
{
	/**
	 *  @defgroup SpinnakerClasses Spinnaker Classes
	 */

	/*@{*/

	/**
	 *  @defgroup CameraList_h Camera List Class
	 */

	/*@{*/

    /**
    * @brief Used to hold a list of camera objects.
    */

	class SPINNAKER_API CameraList
	{
	public:

		/**
		* Default constructor.
		*/
		CameraList(void);

		/**
		* Virtual destructor.
		*/
		virtual ~CameraList(void);

		/**
		* Copy constructor
		*/
		CameraList(const CameraList & iface);

		/**
         * Assignment operator.
         */
		CameraList&	operator=( const CameraList& iface );

		/**
		 * Array subscription operators.
		 */
		CameraPtr  operator[](int index);

		/**
         * Returns the size of the camera list.  The size is the number
		 * of Camera objects stored in the list.
         *
         * @return An integer that represents the list size.
         */
		int GetSize() const;

		/**
         * Returns a pointer to a camera object at the "index".
         *
		 * @param index The index at which to retrieve the camera object
		 *
         * @return A pointer to an camera object.
         */
		CameraPtr GetByIndex(int index) const;

        /**
        * Returns a pointer to a camera object with the specified serial number.
        *
        * @param serialNumber The serial number of the camera object to retrieve 
        *
        * @return A pointer to an camera object.
        */
        CameraPtr GetBySerial(std::string serialNumber) const;

		/**
         * Clears the list of cameras and destroys their corresponding reference counted
		 * objects. This is necessary in order to clean up the parent interface.
		 * It is important that the camera list is destroyed or is cleared before calling
		 * system->ReleaseInstance() or else the call to system->ReleaseInstance() 
         * will result in an error message thrown that a reference to the camera 
         * is still held.
         *
		 * @see System:ReleaseInstance()
         */
		void Clear();

		/**
         * Removes a camera at "index" and destroys its corresponding reference counted
		 * object.
         *
		 * @param index The index at which to remove the Camera object
         */
		void RemoveByIndex(int index);

        /**
        * Removes a camera using its serial number and destroys its corresponding reference counted
        * object.
        *
        * @param serialNumber The serial number of the Camera object to remove
        */
        void RemoveBySerial(std::string serialNumber);

		/**
         * Appends a camera list to the current list.
         *
		 * @param otherList The other list to append to this list
         */
		void Append(CameraList & otherList);

	protected:
		friend class InterfaceImpl;
		friend class CameraListImpl;
		struct CameraListData; // Forward declaration
		CameraListData* m_pCameraListData;
	};

	/*@}*/

	/*@}*/
}

#endif // PGR_SPINNAKER_CAMERALIST_H