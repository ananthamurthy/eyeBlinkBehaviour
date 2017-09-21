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
\brief   Definition of interface INodeMap
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_INODEMAP_H
#define SPINNAKER_GENAPI_INODEMAP_H

#include "GCString.h"
#include "INode.h"
#include "IPort.h"
#include "Synch.h"
#include "Container.h"


#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{
	namespace GenApi
	{

		//*************************************************************
		// INodeMap interface
		//*************************************************************

		/**
		\brief Interface to access the node map
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		interface SPINNAKER_API_ABSTRACT INodeMap
		{
			//! Retrieves all nodes in the node map
			virtual void GetNodes(NodeList_t &Nodes) const = 0;

			//! Retrieves the node from the central map by Name
			virtual INode* GetNode(const GenICam::gcstring& Name) const = 0;

			//! Invalidates all nodes
			virtual void InvalidateNodes() const = 0;

			//! Connects a port to a port node with given name
			virtual bool Connect(IPort* pPort, const GenICam::gcstring& PortName) const = 0;

			//! Connects a port to the standard port "Device"
			virtual bool Connect(IPort* pPort) const = 0;

			//! Get device name
			/*! The device name identifies a device instance, e.g. for debugging purposes.
			The default ist "Device". */
			virtual GenICam::gcstring GetDeviceName() = 0;

			//! Fires nodes which have a polling time
			virtual void Poll(int64_t ElapsedTime) = 0;

			//! Returns the lock which guards the node map
			virtual CLock& GetLock() const = 0;

			//! Get the number of nodes in the map
			virtual uint64_t GetNumNodes() const = 0;
		};
	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_INODEMAP_H
