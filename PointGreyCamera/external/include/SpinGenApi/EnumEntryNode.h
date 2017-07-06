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

#ifndef SPINNAKER_GENAPI_ENUMENTRYNODE_H
#define SPINNAKER_GENAPI_ENUMENTRYNODE_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "GCString.h"
#include "ISelector.h"
#include "INode.h"
#include "ValueNode.h"
#include "IEnumEntry.h"

#pragma warning ( push )
#pragma warning( disable : 4250 ) // C4250 - 'class1' : inherits 'class2::member' via dominance
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY
#pragma warning( disable: 4275 ) // non dll-interface structXXX used as base

namespace Spinnaker
{
	namespace GenApi
	{
		/**
		\brief Interface for string properties
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
        class SPINNAKER_API EnumEntryNode : virtual public IEnumEntry, virtual public ValueNode
		{
		public:
            struct NodeImpl;
            EnumEntryNode();

            EnumEntryNode(std::shared_ptr<Node::NodeImpl> pEnumEntry);

            virtual ~EnumEntryNode();

			//! Get numeric enum value
			virtual int64_t GetValue();

			//! Get symbolic enum value
			virtual GenICam::gcstring GetSymbolic()const;

			//! Get double number associated with the entry
			virtual double GetNumericValue();

			//! Indicates if the corresponding EnumEntry is self clearing
			virtual bool IsSelfClearing();

			//! overload SetReference for EnumEntry
			virtual void SetReference(INode* pBase);


		private:

			std::shared_ptr<Node::NodeImpl> m_pEnumEntry;

		};

		typedef EnumEntryNode CEnumEntryRef;
	}
}

#endif // SPINNAKER_GENAPI_ENUMENTRYNODE_H