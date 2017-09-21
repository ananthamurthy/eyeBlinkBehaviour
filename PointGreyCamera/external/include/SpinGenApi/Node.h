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

#ifndef SPINNAKER_GENAPI_NODE_H
#define SPINNAKER_GENAPI_NODE_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "GCString.h"
#include "Container.h"
#include "ISelector.h"
#include "INode.h"
#include "GCStringVector.h"
#include <list>

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY
#pragma warning( disable: 4275 ) // non dll-interface structXXX used as base

namespace Spinnaker
{
	namespace GenApi
	{
		interface INodeMap;
		struct CallbackHandleType_t;

		//*************************************************************
		// Node implementation
		//*************************************************************

		/**
		\brief class common to all nodes
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		class SPINNAKER_API Node : virtual public INode
		{
		public:

			struct NodeImpl; // forward declaration

			//! Constructor
			Node();

			//! Constructor
			Node(std::shared_ptr<Node::NodeImpl> pNodeHandle);

			//! Destructor
			~Node();

			//! Get node name
			virtual GenICam::gcstring GetName(bool FullQualified = false) const;

			//! Get name space
			virtual GenApi::ENameSpace GetNameSpace() const;

			//! Get the recommended visibility of the node
			virtual EVisibility GetVisibility() const;

			//! Indicates that the node's value may have changed.
			/*! Fires the callback on this and all dependent nodes */
			virtual void InvalidateNode();

			//! Is the node value cacheable
			virtual bool IsCachable() const;

			//! True if the AccessMode can be cached
			virtual EYesNo IsAccessModeCacheable() const;

			//! Get Caching Mode
			virtual ECachingMode GetCachingMode() const;

			//! recommended polling time (for not cacheable nodes)
			virtual int64_t GetPollingTime() const;

			//! Get a short description of the node
			virtual GenICam::gcstring GetToolTip() const;

			//! Get a long description of the node
			virtual GenICam::gcstring GetDescription() const;

			//! Get a name string for display
			virtual GenICam::gcstring GetDisplayName() const;

			//! Get a name of the device
			virtual GenICam::gcstring GetDeviceName() const;

			/*!
			\brief Get all nodes this node directly depends on.
			\param[out] Children List of children nodes
			\param LinkType The link type
			*/
			virtual void GetChildren(GenApi::NodeList_t &Children, ELinkType LinkType = ctReadingChildren) const;

			/*!
			\brief Gets all nodes this node is directly depending on
			\param[out] Parents List of parent nodes
			*/
			virtual void GetParents(GenApi::NodeList_t &Parents) const;

			//! Register change callback
			/*! Takes ownership of the CNodeCallback object */
			virtual CallbackHandleType RegisterCallback(CNodeCallback *pCallback);

			//! De register change callback
			/*! Destroys CNodeCallback object
			\return true if the callback handle was valid
			*/
			virtual bool DeregisterCallback(CallbackHandleType hCallback);

			//! Retrieves the central node map
			virtual INodeMap* GetNodeMap() const;

			//! Get the EventId of the node
			virtual GenICam::gcstring GetEventID() const;

			//! True if the node is streamable
			virtual bool IsStreamable() const;

			//! Returns a list of the names all properties set during initialization
			virtual void GetPropertyNames(GenICam::gcstring_vector &PropertyNames) const;

			//! Retrieves a property plus an additional attribute by name
			/*! If a property has multiple values/attribute they come with Tabs as delimiters */
			virtual bool GetProperty(const GenICam::gcstring& PropertyName, GenICam::gcstring& ValueStr, GenICam::gcstring& AttributeStr);

			//! Imposes an access mode to the natural access mode of the node
			virtual void ImposeAccessMode(EAccessMode ImposedAccessMode);

			//! Imposes a visibility  to the natural visibility of the node
			virtual void ImposeVisibility(EVisibility ImposedVisibility);

			//! Retrieves the a node which describes the same feature in a different way
			virtual INode* GetAlias() const;

			//! Retrieves the a node which describes the same feature so that it can be casted
			virtual INode* GetCastAlias() const;

			//! Gets a URL pointing to the documentation of that feature
			virtual GenICam::gcstring GetDocuURL() const;

			//! True if the node should not be used any more
			virtual bool IsDeprecated() const;

			//! Get the type of the main interface of a node
			virtual EInterfaceType GetPrincipalInterfaceType() const;

			//! True if the node can be reached via category nodes from a category node named "Root"
			virtual bool IsFeature() const;

			//! Set Node handle
			void SetNodeHandle(std::shared_ptr<Node::NodeImpl> pNodeHandle);

			//! Get Node handle
			std::shared_ptr<Node::NodeImpl> GetNodeHandle() const;

			/**
			\brief Base interface overrides
			\ingroup Spinnaker_GenApi_PublicInterface
			*/

			//! Get the access mode of the node
			virtual EAccessMode GetAccessMode() const;

			/**
			\brief Selector interface overrides
			\ingroup Spinnaker_GenApi_PublicImpl
			*/

			//! true if this feature selects a group of features
			virtual bool IsSelector() const;

			//! retrieve the group of selected features
			virtual void GetSelectedFeatures(FeatureList_t&) const;

			//! retrieve the group of features selecting this node
			virtual void GetSelectingFeatures(FeatureList_t&) const;

			/** 
			\brief Reference interface overrides
			\\ingroup Spinnaker_GenApi_PublicImpl
			*/
			virtual void SetReference(INode* pBase);

			virtual void SetReference(ISelector* pBase);

			void SetNodeMap(INodeMap* pNodeMap);

			//helpers
			virtual bool operator==(int nullPtr) const;

			virtual bool operator!=(int nullPtr) const;

		protected:
			std::shared_ptr<Node::NodeImpl> m_pNodeData;

			//! List of callbacks
            std::list<CallbackHandleType_t*> m_Callbacks;

			INodeMap* m_pNodeMap;

		};

		typedef Node CNodeRef;

		typedef Node CSelectorRef;

	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_NODE_H
