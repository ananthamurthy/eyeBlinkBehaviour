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
\brief    Definition of IReference and IEnumReference
\ingroup Spinnaker_GenApi_PublicImpl
*/

#ifndef SPINNAKER_GENAPI_REFERENCE_H
#define SPINNAKER_GENAPI_REFERENCE_H

#include "Types.h"
#include "SpinnakerPlatform.h"
#include "GCString.h"

namespace Spinnaker
{
	namespace GenApi
	{
		interface IBase;

		//*************************************************************
		// IReference interface
		//*************************************************************

		/**
		\brief Interface to construct a reference
		\ingroup Spinnaker_GenApi_PublicImpl
		*/
		interface SPINNAKER_API_ABSTRACT IReference
		{
			//! sets the implementation to a reference
			virtual void SetReference(INode* pBase) = 0;
		};

		//*************************************************************
		// IEnumReference interface
		//*************************************************************

		/**
		\brief Interface to construct an enum reference
		\ingroup Spinnaker_GenApi_PublicImpl
		*/
		interface SPINNAKER_API_ABSTRACT IEnumReference
		{
			//! sets the Enum value corresponding to a value
			virtual void SetEnumReference(int Index, GenICam::gcstring Name) = 0;

			//! sets the number of enum values
			virtual void SetNumEnums(int NumEnums) = 0;
		};

	}
}

#endif // ifndef SPINNAKER_GENAPI_REFERENCE_H
