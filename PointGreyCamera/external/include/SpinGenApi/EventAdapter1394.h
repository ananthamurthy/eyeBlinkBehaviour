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
\brief    Declaration of the CEventAdapter1394 class.
*/
#ifndef SPINNAKER_GENAPI_EVENTADAPTER1394_H
#define SPINNAKER_GENAPI_EVENTADAPTER1394_H


#if _MSC_VER > 1000
#pragma once
#endif

#include "EventAdapter.h"

namespace Spinnaker
{
	namespace GenApi
	{
		// the opaque event data on IEEE 1394
		struct EventData1394;

		//! Distribute the events to the node map
		class SPINNAKER_API CEventAdapter1394 : public CEventAdapter
		{
		public:
			//! constructor
			explicit CEventAdapter1394(INodeMap* pNodeMap = NULL);

			virtual ~CEventAdapter1394();
		
		public:
			virtual void DeliverMessage(const uint8_t msg[], uint32_t numBytes);
			//! distributes events to node map
			void DeliverEventMessage(EventData1394& Event, uint32_t numBytes);

		private:
			//! not implemented: copy constructor
			CEventAdapter1394(const CEventAdapter1394&);
			//! not implemented: assignment operator
			CEventAdapter1394& operator=(const CEventAdapter1394&);
		};
	}
}
#endif //SPINNAKER_GENAPI_EVENTADAPTER1394_H
