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
\brief   Definition of CSelectorSet
\ingroup Spinnaker_GenApi_PublicUtilities
*/

#ifndef SPINNAKER_GENAPI_SELECTORSET_H
#define SPINNAKER_GENAPI_SELECTORSET_H

#include "INode.h"
#include "Node.h"
#include "Base.h"
#include "Pointer.h"

namespace Spinnaker
{
	namespace GenApi
	{

		//! The set of selectors selecting a given node
		class SPINNAKER_API CSelectorSet : virtual public Node 
		{
		public:
						
			//! Constructor
			CSelectorSet ( 
				IBase *pBase //!> Feature selected by the selector set 
				);

			//! Destructor
			~CSelectorSet();

			//! returns true if no selectors are present
			bool IsEmpty();
			
			// Implementation of ISelectorDigit
		public:
			virtual bool SetFirst();
			virtual bool SetNext(bool Tick = true);
			virtual void Restore();
			virtual GenICam::gcstring ToString();
			virtual void GetSelectorList( FeatureList_t &SelectorList, bool Incremental = false );

		private:

			INode* m_pNode;
			void* m_pSelectorSet;
		};
	}
}
#endif

