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
\brief    Declaration of the CChunkAdapterGEV class.
\ingroup  Spinnaker_GenApi_PublicUtilities
*/

#ifndef SPINNAKER_GENAPI_CHUNKADAPTERGEV_H
#define SPINNAKER_GENAPI_CHUNKADAPTERGEV_H

#include "ChunkAdapter.h"

namespace Spinnaker
{
	namespace GenApi
	{
		/* ------------------------------------------- */
		// Declaration of GigE Vision Chunk message trailer

		// make sure everything is properly packed
#   pragma pack(push, 1)

		//! header of a GVCP request packet
		typedef struct GVCP_CHUNK_TRAILER
		{
			uint32_t ChunkID;
			uint32_t ChunkLength;
		} GVCP_CHUNK_TRAILER;

		// restore the previous packing
#   pragma pack(pop)
		/* ------------------------------------------- */

		//! Connects a chunked DCAM buffer to a node map
		class SPINNAKER_API CChunkAdapterGEV : public  CChunkAdapter
		{

		public:
			//! Constructor
			CChunkAdapterGEV(INodeMap* pNodeMap = NULL, int64_t MaxChunkCacheSize = -1);

			//! Destructor
			virtual ~CChunkAdapterGEV();

			//! Checks if a buffer contains chunks in a known format
			virtual bool CheckBufferLayout(uint8_t *pBuffer, int64_t BufferLength);

			//! Attaches a buffer to the matching ChunkPort
			virtual void AttachBuffer(uint8_t *pBuffer, int64_t BufferLength, AttachStatistics_t *pAttachStatistics = NULL);
		};

	}
}

#endif // SPINNAKER_GENAPI_CHUNKADAPTERGEV_H
