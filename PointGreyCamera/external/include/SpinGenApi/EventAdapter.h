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
\brief    Declaration of the CEventAdapter class.
\ingroup Spinnaker_GenApi_PublicUtilities
*/

#ifndef SPINNAKER_GENAPI_EVENTADAPTER_H
#define SPINNAKER_GENAPI_EVENTADAPTER_H

#include "Types.h"
#include "INodeMap.h"
#include "EventPort.h"

namespace Spinnaker
{
	namespace GenApi
	{

		/**
		\brief Delivers Events to ports
		\ingroup Spinnaker_GenApi_PublicUtilities
		*/
		class SPINNAKER_API CEventAdapter
		{

		public:
			//! Constructor
			CEventAdapter(INodeMap* pNodeMap = NULL);

			//! Destructor
			virtual ~CEventAdapter();

			//! Attaches to a node map and retrieves the chunk ports
			virtual void AttachNodeMap(INodeMap* pNodeMap);

			//! Detaches from the node emap
			virtual void DetachNodeMap();

			//! Deliver message
			virtual void DeliverMessage(const uint8_t msg[], uint32_t numBytes) = 0;

		protected:

			void* m_pEventAdapter;
		};

	}
}

#endif // SPINNAKER_GENAPI_EVENTADAPTER_H
