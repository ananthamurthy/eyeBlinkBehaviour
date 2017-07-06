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
\brief   Definition of the interface ISelectorDigit
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_ISELECTORDIGIT_H
#define SPINNAKER_GENAPI_ISELECTORDIGIT_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Container.h"

namespace Spinnaker
{
	namespace GenApi
	{

		//! Interface of a "digit" of the "counter" formed by the selector set
		interface SPINNAKER_API_ABSTRACT ISelectorDigit
		{
			/*! \brief Sets digit to start value
				\return true if the resulting value is valid */
			virtual bool SetFirst() = 0;

			/*! \brief Sets digit to next value
				\param Tick if false the counter does not tick (but realize it could have)
				\return true if the resulting value is valid */
			virtual bool SetNext(bool Tick = true) = 0;

			//! Restores the selectors' values found at creation
			virtual void Restore() = 0;

			//! Returns a string representation of the digit
			virtual GenICam::gcstring ToString() = 0;

			//! Retrieves an ordered list of selectors
			virtual void GetSelectorList( 
				FeatureList_t &SelectorList, //!> List to contain the selector pointer
				bool Incremental = false  //!> if true only seletor changed since the last GetNext are contained 
				) = 0;
		};

	}
}

#endif

