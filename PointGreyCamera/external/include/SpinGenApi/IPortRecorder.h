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

#ifndef SPINNAKER_GENAPI_IPORTRECORDER_H
#define SPINNAKER_GENAPI_IPORTRECORDER_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "IPort.h"

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{
	namespace GenApi
	{

		interface SPINNAKER_API_ABSTRACT IPortWriteList
		{
			//! Writes a chunk of bytes to the port
			virtual void Write(const void *pBuffer, int64_t Address, int64_t Length) = 0;

			//! Replays the write command to the given port interface
			virtual void Replay(IPort* pPort) = 0;

			//! Sets a cookie in case the port implementation want to cache a command list
			// Default = -1
			virtual void SetCookie(const int64_t Value) = 0;

			//! Gets the cookie a port implementation may have set for caching a command list
			virtual int64_t GetCookie() = 0;
		};

		/**
		\brief Interface for replaying write commands on a port
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		interface SPINNAKER_API_ABSTRACT IPortReplay : virtual public IPort
		{
			//! sends the commands to the camera.
			/*! the default implementation just walks the list and issues each command
				using the WriteRegister method. Depending on the capabilities of
				the transport layer the implementation can however use a special command
				which sends all register write commands as one package.
				*/
			virtual void Replay(IPortWriteList *pPortRecorder, bool Invalidate = true) = 0;
		};

		/**
		\brief Interface for recording write commands on a port
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		interface SPINNAKER_API_ABSTRACT IPortRecorder : virtual public IPortReplay
		{
			//! starts logging all WriteRegister commands to a list
			virtual void StartRecording(IPortWriteList *pPortRecorder) = 0;

			//! stops recording
			virtual void StopRecording() = 0;
		};
	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_IPORTRECORDER_H
