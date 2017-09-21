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
\brief    Definition of ValueNode
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_VALUENODE_H
#define SPINNAKER_GENAPI_VALUENODE_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "INode.h"
#include "IValue.h"
#include "GCString.h"
#include "Node.h"

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY
#pragma warning( disable : 4250 ) // C4250 - 'class1' : inherits 'class2::member' via dominance
#pragma warning (disable : 4275 ) // warning C4275: non dll-interface struct 'Spinnaker::GenApi::IValue' used as base for dll-interface class 'Spinnaker::GenApi::Value'

namespace Spinnaker
{
	namespace GenApi
	{

		//*************************************************************
		// IValue interface
		//*************************************************************

		/**
		\brief Interface for value properties
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		class SPINNAKER_API ValueNode : virtual public IValue, virtual public Node
		{
		public:
			struct NodeImpl;
			//! Constructor
            ValueNode();

			//! constructor with GenICam IValue
            ValueNode(std::shared_ptr<Node::NodeImpl> pValue);

			//! Destructor
            ~ValueNode();

			virtual INode* GetNode();

			//! Get content of the node as string
			/*!
			\param Verify Enables Range verification (default = false). The AccessMode is always checked
			\param IgnoreCache If true the value is read ignoring any caches (default = false)
			\return The value read
			*/
			virtual GenICam::gcstring ToString(bool Verify = false, bool IgnoreCache = false);

			//! Set content of the node as string
			/*!
			\param ValueStr The value to set
			\param Verify Enables AccessMode and Range verification (default = true)
			*/
			virtual void FromString(const GenICam::gcstring& ValueStr, bool Verify = true);

			//! Checks if the value comes from cache or is requested from another node
			virtual bool IsValueCacheValid() const;

			//! overload SetReference for Value
			virtual void SetReference(INode* pBase);

		private:
			std::shared_ptr<Node::NodeImpl> m_pIValue;
		};

        typedef ValueNode CValueRef;
	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_VALUENODE_H