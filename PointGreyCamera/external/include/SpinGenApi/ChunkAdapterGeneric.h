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
\brief    Declaration of the CChunkAdapterGeneric class.
\ingroup  Spinnaker_GenApi_PublicUtilities
*/

#ifndef SPINNAKER_GENAPI_CHUNKADAPTERGENERIC_H
#define SPINNAKER_GENAPI_CHUNKADAPTERGENERIC_H

#include "ChunkAdapter.h"
#include "GCString.h"

namespace Spinnaker
{
	namespace GenApi
	{
		/* ------------------------------------------- */
		// Single chunk info

		// make sure everything is properly packed
#pragma pack(push, 1)

		typedef struct SingleChunkData_t
		{
			uint64_t ChunkID;
			ptrdiff_t ChunkOffset;
			size_t ChunkLength;
		} SingleChunkData_t;

		// the extended version holding ChunkID as string should be used only in special cases
		// when the ChunkID does not fit into a 64-bit integer
		typedef struct SingleChunkDataStr_t
		{
			GenICam::gcstring ChunkID;
			ptrdiff_t ChunkOffset;
			size_t ChunkLength;
		} SingleChunkDataStr_t;

		// restore the previous packing
#pragma pack(pop)
		/* ------------------------------------------- */


		//! Connects a generic chunked buffer to a node map
		class SPINNAKER_API CChunkAdapterGeneric : public CChunkAdapter
		{

		public:
			//! Constructor
			
			CChunkAdapterGeneric(INodeMap* pNodeMap = NULL, int64_t MaxChunkCacheSize = -1);

			//! Destructor
			virtual ~CChunkAdapterGeneric();

			// Does not have implementation, use the version with EventID
			virtual bool CheckBufferLayout(uint8_t *pBuffer, int64_t BufferLength);

			// Does not have implementation, use the generic version
			virtual void AttachBuffer(uint8_t *pBuffer, int64_t BufferLength, AttachStatistics_t *pAttachStatistics = NULL);

			virtual void AttachBuffer(uint8_t *pBuffer, SingleChunkData_t *ChunkData, int64_t NumChunks, AttachStatistics_t *pAttachStatistics = NULL);

			virtual void AttachBuffer(uint8_t *pBuffer, SingleChunkDataStr_t *ChunkData, int64_t NumChunks, AttachStatistics_t *pAttachStatistics = NULL);
		};
	}
}

#endif // SPINNAKER_GENAPI_CHUNKADAPTERGENERIC_H
