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
/**
\file
\brief    Declaration of the CEventAdapterGEV class.
*/

#ifndef SPINNAKER_GENAPI_EVENTADAPTERGENERIC_H
#define SPINNAKER_GENAPI_EVENTADAPTERGENERIC_H

#include "EventAdapter.h"

namespace Spinnaker
{
	namespace GenApi
	{
		//! Connects a generic event to a node map
		class SPINNAKER_API CEventAdapterGeneric : public  CEventAdapter
		{
		public:
			//! Constructor
			CEventAdapterGeneric(INodeMap* pNodeMap = NULL);

			//! Destructor
			virtual ~CEventAdapterGeneric();

			// Does not have implementation, use the version with EventID
			virtual void DeliverMessage(const uint8_t msg[], uint32_t numBytes);

			virtual void DeliverMessage(const uint8_t msg[], uint32_t numBytes, const GenICam::gcstring& EventID);

			virtual void DeliverMessage(const uint8_t msg[], uint32_t numBytes, uint64_t EventID);
		};
	}
}

#endif // SPINNAKER_GENAPI_EVENTADAPTERGENERIC_H
