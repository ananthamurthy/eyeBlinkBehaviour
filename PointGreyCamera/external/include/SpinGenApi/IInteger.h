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
\brief   Definition of the interface IInteger.
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_IIINTEGER_H
#define SPINNAKER_GENAPI_IIINTEGER_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "IValue.h"
#include "GCString.h"

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{
	namespace GenApi
	{
		//*************************************************************
		// IInteger interface
		//*************************************************************

		/**
		\brief Interface for integer properties
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		interface SPINNAKER_API_ABSTRACT IInteger : virtual public IValue
		{
			//! Set node value
			/*!
			\param Value The value to set
			\param Verify Enables AccessMode and Range verification (default = true)
			*/
			virtual void SetValue(int64_t Value, bool Verify = true) = 0;

			//! Set node value
			virtual IInteger& operator=(int64_t Value) = 0;

			//! Get node value
			/*!
			\param Verify Enables Range verification (default = false). The AccessMode is always checked
			\param IgnoreCache If true the value is read ignoring any caches (default = false)
			\return The value read
			*/
			virtual int64_t GetValue(bool Verify = false, bool IgnoreCache = false) = 0;

			//! Get node value
			virtual int64_t operator()() = 0;

			//! Get node value
			virtual int64_t operator*() = 0;

			//! Get minimum value allowed
			virtual int64_t GetMin() = 0;

			//! Get maximum value allowed
			virtual int64_t GetMax() = 0;

			//! Get increment mode
			virtual EIncMode GetIncMode() = 0;

			//! Get increment
			virtual int64_t GetInc() = 0;

			//! Get list of valid value
			virtual int64_autovector_t GetListOfValidValues(bool bounded = true) = 0;

			//! Get recommended representation
			virtual  ERepresentation GetRepresentation() = 0;

			//! Get the physical unit name
			virtual GenICam::gcstring GetUnit() = 0;

			//! Restrict minimum value
			virtual void ImposeMin(int64_t Value) = 0;

			//! Restrict maximum value
			virtual void ImposeMax(int64_t Value) = 0;
		};

	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_IIINTEGER_H
