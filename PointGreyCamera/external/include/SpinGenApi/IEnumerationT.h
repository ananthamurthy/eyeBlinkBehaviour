//=============================================================================
// Copyright © 2016 Point Grey Research, Inc. All Rights Reserved.
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
/*!
\file
\brief   Definition of interface IEnumerationT
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_IENUMERATIONT_H
#define SPINNAKER_GENAPI_IENUMERATIONT_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Pointer.h"
#include "IEnumeration.h"
#include <vector>
//#include "GenApi/Compatibility.h"

namespace Spinnaker
{
	namespace GenApi
	{
		//*************************************************************
		// Enumeration template interface
		//*************************************************************

		/**
		\brief Interface for enumeration properties
		\ingroup Spinnaker_GenApi
		*/
		template< typename EnumT >
		interface SPINNAKER_API_ABSTRACT IEnumerationT : virtual public IEnumeration, virtual public IEnumReference
		{
			//! Set node value
			/*!
			\param Value The value to set
			\param Verify Enables AccessMode and Range verification (default = true)
			*/
			virtual void SetValue(EnumT Value, bool Verify = true) = 0;

			//! Set node value
			virtual IEnumeration& operator=(EnumT Value) = 0;

			//! Get node value
			/*!
			\param Verify Enables Range verification (default = false). The AccessMode is always checked
			\param IgnoreCache If true the value is read ignoring any caches (default = false)
			\return The value read
			*/
			virtual EnumT GetValue(bool Verify = false, bool IgnoreCache = false) = 0;

			//! Get node value
			virtual EnumT operator()() = 0;

			//! Set node value
			/*! Note : the operator= is not inherited thus the operator= versions
			from IEnumeration must be implemented again */
			virtual IEnumeration& operator=(const GenICam::gcstring& ValueStr) = 0;

			//! returns the EnumEntry object belonging to the Value
			virtual IEnumEntry* GetEntry(const EnumT Value) = 0;

			//! Get the current entry
			virtual IEnumEntry* GetCurrentEntry(bool Verify = false, bool IgnoreCache = false) = 0;

		};

	}
}

#endif // ifndef SPINNAKER_GENAPI_IENUMERATIONT_H
