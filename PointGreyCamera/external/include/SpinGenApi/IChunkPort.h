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
\brief   Definition of interface IChunkPort
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_ICHUNKPORT_H
#define SPINNAKER_GENAPI_ICHUNKPORT_H

#include "GCString.h"
#include "SpinnakerPlatform.h"
#include "Types.h"
#include "IPort.h"

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{
	namespace GenApi
	{
		//*************************************************************
		// IChunkPort interface
		//*************************************************************

		//! Address of a int64_t pseudo register containing the base address of the chunk (MAX_INT64)
#   define CHUNK_BASE_ADDRESS_REGISTER     GC_INT64_MAX

		//! Lenght of the CHUNK_BASE_ADDRESS_REGISTER pseudo register
#   define CHUNK_BASE_ADDRESS_REGISTER_LEN 8

		//! Address of a int64_t pseudo register containing the length of the chunk
#   define CHUNK_LENGTH_REGISTER     (GC_INT64_MAX-15)

		//! Lenght of the CHUNK_LENGTH_REGISTER pseudo register
#   define CHUNK_LENGTH_REGISTER_LEN 8

		/**
		\brief Interface for ports attached to a chunk
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		interface SPINNAKER_API_ABSTRACT IChunkPort : virtual public IPort
		{
			//! Get the Id of the chunk the port should be attached to
			virtual GenICam::gcstring GetChunkID() const = 0;

			//! Indicates if the chunk a adapter must hold a cached version of the chunk data
			virtual EYesNo CacheChunkData() const = 0;
		};
	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_ICHUNKPORT_H
