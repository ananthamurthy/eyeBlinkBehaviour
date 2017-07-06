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
\brief   Definition of interface IPort
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_IPORT_H
#define SPINNAKER_GENAPI_IPORT_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{
	namespace GenApi
	{
		//*************************************************************
		// IPort interface
		//*************************************************************

		/**
		\brief Interface for ports
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		interface SPINNAKER_API_ABSTRACT IPort : virtual public IBase
		{
			//! Reads a chunk of bytes from the port
			virtual void Read(void *pBuffer, int64_t Address, int64_t Length) = 0;

			//! Writes a chunk of bytes to the port
			virtual void Write(const void *pBuffer, int64_t Address, int64_t Length) = 0;
		};

	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_IPORT_H
