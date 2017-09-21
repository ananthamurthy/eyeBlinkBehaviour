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
\brief   Definition of CNodeMapRef
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_NODEMAP_H
#define SPINNAKER_GENAPI_NODEMAP_H

#include "GCString.h"
#include "GCStringVector.h"

#include "Types.h"
#include "INodeMap.h"
#include "IDeviceInfo.h"
#include "Node.h"
#include "Container.h"
#include "Node.h"
#include "Synch.h"
#include "ValueNode.h"
#include "EnumNodeT.h"
#include "EnumNode.h"
#include "EnumEntryNode.h"
#include "PortNode.h"
#include "IntegerNode.h"
#include "FloatNode.h"
#include "StringNode.h"
#include "BooleanNode.h"
#include "Pointer.h"

#include <map>
namespace Spinnaker
{
	namespace GenApi
	{
		class PortAdapter;

# 		/**
		\brief Smart pointer template for NodeMaps with create function
		\ingroup Spinnaker_GenApi_PublicInterface
		\tparam TCameraParams  The camera specific parameter class (auto generated from camera xml file)
		*/
		class SPINNAKER_API NodeMap : public virtual INodeMap, public virtual IDeviceInfo
		{
		public:
			//! Constructor
			NodeMap(GenICam::gcstring DeviceName = "Device");

			//! Destructor
			virtual ~NodeMap();

			//! Destroys the node map
			void Destroy();

			//! Creates the object from the default DLL
			/*! \note Can only be used if the class TCameraParams was auto generated from a specific camera xml file */
			/*void LoadDLL(void);

			//! Creates the object from a DLL whose name is deduced from vendor and model name
			void LoadDLL(GenICam::gcstring VendorName, GenICam::gcstring ModelName);

			//! Creates the object from a DLL with given file name
			void LoadDLL(GenICam::gcstring FileName);*/
			
			//! Creates the object from a XML file with given file name
			void LoadXMLFromFile(GenICam::gcstring FileName);

			//! Creates the object from a ZIP'd XML file with given file name
			void LoadXMLFromZIPFile(GenICam::gcstring ZipFileName);

			//! Creates the object from a ZIP'd XML file given in a string
			void LoadXMLFromZIPData(const void* zipData, size_t zipSize);

			//! Creates the object from a XML target and an inject file with given file name
			void LoadXMLFromFileInject(GenICam::gcstring TargetFileName, GenICam::gcstring InjectFileName);

			//! Creates the object from XML data given in a string
			void LoadXMLFromString(const GenICam::gcstring& XMLData);

			//! Creates the object from XML data given in a string with injection
			void LoadXMLFromStringInject(const GenICam::gcstring& TargetXMLDataconst, const GenICam::gcstring& InjectXMLData);

			//! Loads an XML, checks it for correctness, applies a style-sheet and outputs it
			/*void PreprocessXMLFromFile(const GenICam::gcstring& XMLFileName,
				const GenICam::gcstring& StyleSheetFileName,
				const GenICam::gcstring& OutputFileName,
				const uint32_t XMLValidation = xvDefault);

			//! Loads a Zipped XML, checks it for correctness, applies a style-sheet and outputs it
			void PreprocessXMLFromZIPFile(const GenICam::gcstring& ZIPFileName,
				const GenICam::gcstring& StyleSheetFileName,
				const GenICam::gcstring& OutputFileName,
				const uint32_t XMLValidation = xvDefault);

			//! Injects an XML file into a target file
			virtual void MergeXMLFiles(
				const GenICam::gcstring& TargetFileName,      //!< Name of the target XML file to process
				const GenICam::gcstring& InjectedFileName,    //!< Name of the Injected XML file to process
				const GenICam::gcstring& OutputFileName       //!< Name of the output file
				);

			//! Extract independent subtree
			virtual void ExtractIndependentSubtree(
				const GenICam::gcstring& XMLData,            //!< The XML data the subtree is extracted from.
				const GenICam::gcstring& InjectXMLData,      //!< Optional XML data that is injected before extracting the subtree. No effect if an empty string is passed.
				const GenICam::gcstring& SubTreeRootNodeName,//!< The name of the node that represents the root of the subtree that shall be extracted.
				GenICam::gcstring& ExtractedSubtree          //!< The returned extracted subtree as string.
				);*/

			//! Gets a list of supported schema versions
			/*! Each list entry is a string with the format "{Major}.{Minor}" were {Major} and {Minor} are integers
			Example: {"1.1", "1.2"} indicates that the schema v1.1 and v1.2 are supported.
			The SubMinor version number is not given since it is for fully compatible bug fixes only
			*/
			virtual void GetSupportedSchemaVersions(GenICam::gcstring_vector &SchemaVersions);

			//! Get device name
			virtual GenICam::gcstring GetDeviceName();

			//! Fires nodes which have a polling time
			virtual void Poll(int64_t ElapsedTime);

			//! Clears the cache of the camera description files
			static bool ClearXMLCache();

			//----------------------------------------------------------------
			// INodeMap
			//----------------------------------------------------------------

			//! Retrieves all nodes in the node map
			virtual void GetNodes(NodeList_t &Nodes) const;

			//! Retrieves the node from the central map by name
			virtual INode* GetNode(const GenICam::gcstring& key) const;

			//! Invalidates all nodes
			virtual void InvalidateNodes() const;

			//! Connects a port to a port node with given name
			virtual bool Connect(IPort* pPort, const GenICam::gcstring& PortName) const;

			//! Connects a port to the standard port "Device"
			virtual bool Connect(IPort* pPort) const;

			//! Returns the lock which guards the node map
			virtual CLock& GetLock() const;

			//! Get the number of nodes in the map
			virtual uint64_t GetNumNodes() const;

			//static std::shared_ptr<INode> CreateINode(::GenApi::INode* pNode);

			//! Pointer to the NodeMap
			INodeMap* _Ptr;

			void* GetNodeMapHandle() const;

			//implementation of IDeviceInfo
			//! Get the model name
			virtual GenICam::gcstring GetModelName();

			//! Get the vendor name
			virtual GenICam::gcstring GetVendorName();

			//! Get tool tip
			virtual GenICam::gcstring GetToolTip();

			//! Get the standard name space
			virtual GenICam::gcstring GetStandardNameSpace();

			//! Get the version of the DLL's GenApi implementation
			virtual void GetGenApiVersion(GenICam::Version_t &Version, uint16_t &Build);

			//! Get the schema version number
			virtual void GetSchemaVersion(GenICam::Version_t &Version);

			//! Get the version of the device description file
			virtual void GetDeviceVersion(GenICam::Version_t &Version);

			//! Get the GUID describing the product
			virtual GenICam::gcstring GetProductGuid();

			//! Get the GUID describing the product version
			virtual GenICam::gcstring GetVersionGuid();


		private:

			NodeMap(const NodeMap&);
			NodeMap& operator=(const NodeMap&);

			void PopulateNodeMap(void* pNodeMap, std::map< GenICam::gcstring, std::shared_ptr<INode> >& outMap);

			void* m_nodeMapRef;

			mutable CLock* m_pLock;

			mutable std::vector< std::shared_ptr<PortAdapter> > m_portAdapters;

			mutable std::map < GenICam::gcstring, std::shared_ptr<INode> > m_nodeMap;
		};

		typedef NodeMap CNodeMapRef;
	}
}

#endif // ifndef SPINNAKER_GENAPI_NODEMAP_H
