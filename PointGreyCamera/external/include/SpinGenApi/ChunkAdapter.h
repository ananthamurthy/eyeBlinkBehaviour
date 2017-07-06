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
\brief   Declaration of the CChunkAdapter class.
\ingroup Spinnaker_GenApi_PublicUtilities
*/

#ifndef SPINNAKER_GENAPI_CHUNKADAPTER_H
#define SPINNAKER_GENAPI_CHUNKADAPTER_H

#include "Types.h"
#include "INodeMap.h"

namespace Spinnaker
{
	namespace GenApi
	{
		//! Delivers information about the attached chunks and nodes
		//! \ingroup Spinnaker_GenApi_PublicUtilities
		typedef struct AttachStatistics_t
		{
			int NumChunkPorts;        //!< Number of chunk ports found in the node map
			int NumChunks;            //!< Number of chunks found in the buffer
			int NumAttachedChunks;    //!< Number of chunks from the buffer attached to a chunk port
		} AttachStatistics_t;


		/**
		\brief Connects a chunked buffer to a node map
		\ingroup Spinnaker_GenApi_PublicUtilities
		*/
		class SPINNAKER_API CChunkAdapter
		{

		public:
			//! Destructor
			virtual ~CChunkAdapter();

			//! Attaches to a node map and retrieves the chunk ports
			void AttachNodeMap(INodeMap* pNodeMap);

			//! Detaches from the node map
			void DetachNodeMap();

			//! Checks if a buffer contains chunks in a known format
			/*! Implement that for a specific buffer layout */
			virtual bool CheckBufferLayout(uint8_t *pBuffer, int64_t BufferLength) = 0;

			//! Attaches a buffer to the matching ChunkPort
			/*! Implement that for a specific buffer layout */
			virtual void AttachBuffer(uint8_t *pBuffer, int64_t BufferLength, AttachStatistics_t *pAttachStatistics = NULL) = 0;

			//! Detaches a buffer
			void DetachBuffer();

			//! Updates the base address of the buffer
			void UpdateBuffer(uint8_t *pBaseAddress);

			//! Clears the chunk caches
			void ClearCaches();

		protected:

			//! Serves as default constructor
			CChunkAdapter(INodeMap* pNodeMap = NULL, int64_t MaxChunkCacheSize = -1);

			void* m_pChunkAdapter;
		};
	}
}

#endif // SPINNAKER_GENAPI_CHUNKADAPTER_H
