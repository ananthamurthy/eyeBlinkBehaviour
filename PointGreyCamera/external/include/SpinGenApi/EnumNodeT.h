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

#ifndef SPINNAKER_GENAPI_ENUMNODET_H
#define SPINNAKER_GENAPI_ENUMNODET_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "GCString.h"
#include "ISelector.h"
#include "INode.h"
#include "ValueNode.h"
#include "EnumNode.h"
#include "IEnumeration.h"
#include "IEnumerationT.h"
#include "IEnumEntry.h"
#include "Node.h"
#include "Exception.h"

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
		template< class EnumT >
		class SPINNAKER_API CEnumerationTRef : virtual public IEnumerationT<EnumT> , public virtual EnumNode
		{
		public:
            struct NodeImpl;
            CEnumerationTRef();

            CEnumerationTRef(std::shared_ptr<Node::NodeImpl> pEnumeration);

            virtual ~CEnumerationTRef();

			//! Set node value
			/*!
			\param Value The value to set
			\param Verify Enables AccessMode and Range verification (default = true)
			*/
            virtual void SetValue(EnumT Value, bool Verify = true);

			//! Set node value
            virtual IEnumeration& operator=(EnumT Value);

			//! Get node value
			/*!
			\param Verify Enables Range verification (default = false). The AccessMode is always checked
			\param IgnoreCache If true the value is read ignoring any caches (default = false)
			\return The value read
			*/
            virtual EnumT GetValue(bool Verify = false, bool IgnoreCache = false);

			//! Get node value
            virtual EnumT operator()();

			//! Set node value
			/*! Note : the operator= is not inherited thus the operator= versions
			from IEnumeration must be implemented again */
            virtual IEnumeration& operator=(const GenICam::gcstring& ValueStr);

			//! returns the EnumEntry object belonging to the Value
            virtual IEnumEntry* GetEntry(const EnumT Value);

			//! Get an entry node by its IntValue
			virtual IEnumEntry* GetEntry(const int64_t IntValue);

			//! Get the current entry
            virtual IEnumEntry* GetCurrentEntry(bool Verify = false, bool IgnoreCache = false);

			//! overload SetReference for EnumerationT
            virtual void SetReference(INode* pBase);
			
			//! sets the Enum value corresponding to a value
            virtual void SetEnumReference(int Index, GenICam::gcstring Name);

			//! sets the number of enum values
            virtual void SetNumEnums(int NumEnums);

		private:
			
			std::shared_ptr<Node::NodeImpl> m_pEnumerationT;

		};
	}
}

#endif // SPINNAKER_GENAPI_ENUMNODET_H