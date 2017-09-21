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
\brief   Definition of interface IEnumeration
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_IENUMERATION_H
#define SPINNAKER_GENAPI_IENUMERATION_H

//#include "GCStringVector.h"
#include "SpinnakerPlatform.h"
#include "IEnumEntry.h"
#include "Types.h"
#include "IValue.h"

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{
	namespace GenApi
	{
		//*************************************************************
		// Enumeration interface
		//*************************************************************

		/**
		\brief Interface for enumeration properties
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		interface SPINNAKER_API_ABSTRACT IEnumeration : virtual public IValue
		{

			//! Get list of symbolic Values
			virtual void GetSymbolics(StringList_t & Symbolics) = 0;

			//! Get list of entry nodes
			virtual void GetEntries(NodeList_t & Entries) = 0;

			//! Set string node value
			virtual IEnumeration& operator=(const GenICam::gcstring& ValueStr) = 0;

			//! Set integer node value
			/*!
			\param Value The value to set
			\param Verify Enables AccessMode and Range verification (default = true)
			*/
			virtual void SetIntValue(int64_t Value, bool Verify = true) = 0;

			//! Get string node value
			virtual GenICam::gcstring operator*() = 0;

			//! Get integer node value
			/*!
			\param Verify Enables Range verification (default = false). The AccessMode is always checked
			\param IgnoreCache If true the value is read ignoring any caches (default = false)
			\return The value read
			*/
			virtual int64_t GetIntValue(bool Verify = false, bool IgnoreCache = false) = 0;

			//! Get an entry node by name
			virtual IEnumEntry* GetEntryByName(const GenICam::gcstring& Symbolic) = 0;

			//! Get an entry node by its IntValue
			virtual IEnumEntry* GetEntry(const int64_t IntValue) = 0;

			//! Get the current entry
			virtual IEnumEntry* GetCurrentEntry(bool Verify = false, bool IgnoreCache = false) = 0;

		};

	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_IENUMERATION_H
