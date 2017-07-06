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

#ifndef PGR_SPINNAKER_BASE_PTR_H
#define PGR_SPINNAKER_BASE_PTR_H

#include "SpinnakerPlatform.h"


namespace Spinnaker
{
	/**
	*  @defgroup SpinnakerClasses Spinnaker Classes
	*/
	/*@{*/

	/**
	*  @defgroup BasePtr_h BasePtr Class
	*/
	/*@{*/

    /**
    * @brief The base class of the SystemPtr, CameraPtr, InterfacePtr, ImagePtr and LoggingEventDataPtr objects.
    */
	
	template<class T, class B = T >
	class SPINNAKER_API BasePtr
	{

	public:
		//! Default constructor.
		BasePtr(void) throw();

		virtual ~BasePtr(void);

		//copy constructor
		BasePtr(const BasePtr& other) throw();

		//! Assign INode Pointer
		virtual BasePtr& operator=(const BasePtr& rhs);

		virtual BasePtr& operator=(const int nMustBeNull);

		//! Dereferencing
		virtual operator T*(void) const;	

		//! Dereferencing
		virtual T* operator->(void) const;
		

		//! true if the pointer is valid
		virtual bool IsValid() const throw();
		

		//! true if the pointer is valid
		virtual operator bool(void) const throw();
		

		//! pointer equal
		virtual bool operator==(const BasePtr &rT) const;
		

		//! pointer equal
		virtual bool operator==(int nMustBeNull) const;
		


	protected:
		struct PointerData;
		//! Underlying raw pointer.
		PointerData* m_pT;
	};

    /** @}*/

    /** @}*/
}

#endif //PGR_SPINNAKER_BASE_PTR_H