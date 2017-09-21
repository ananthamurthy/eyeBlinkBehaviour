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
\brief   Definition of CPortImpl
\ingroup Spinnaker_GenApi_PublicUtilities
*/

#ifndef SPINNAKER_PORTIMPL_H
#define SPINNAKER_PORTIMPL_H

#include "Types.h"
#include "IPortConstruct.h"
#include "IPortRecorder.h"
#include "Pointer.h"

#pragma warning( push )
#pragma warning( disable: 4251 ) // enApi::CPortImpl::m_ptrPort' : class 'GenApi::CPointer<T>' needs to have dll-interface
#pragma warning ( disable : 4068 ) // unknown pragma; refers to BullsEyeCoverage

namespace Spinnaker
{
	namespace GenApi
	{
		//*************************************************************
		// CPortImpl class
		//*************************************************************

		/**
		\brief Standard implementation for a port
		//! \ingroup Spinnaker_GenApi_PublicUtilities
		*/
		class SPINNAKER_API CPortImpl : public IPortConstruct, public IPortReplay
		{
		public:
			//! Constructor
			CPortImpl()
			{
			}

			//! Destructor
			virtual ~CPortImpl()
			{
			}

			/*---------------------------------------------------------------*/
			// IBase ==> You need to override this method
			/*---------------------------------------------------------------*/

			//! Get the access mode of the node
			/*! Driver closed => NI, Driver open => RW, analyzing a struct, RO */
			virtual EAccessMode GetAccessMode() const = 0;

			/*---------------------------------------------------------------*/
			// IPort ==> You need to override these methods
			/*---------------------------------------------------------------*/

			//! Reads a chunk of bytes from the port
			virtual void Read(void *pBuffer, int64_t Address, int64_t Length) = 0;

			//! Writes a chunk of bytes to the port
			virtual void Write(const void *pBuffer, int64_t Address, int64_t Length) = 0;

			/*---------------------------------------------------------------*/
			// IPortConstruct implementation (without IPort & IBase)
			/*---------------------------------------------------------------*/

			//! Sets pointer the real port implementation; this function may called only once
			virtual void SetPortImpl(IPort* pPort)
			{
				m_ptrPort = pPort;
				assert(m_ptrPort.IsValid());
			}

			//! Determines if the port adapter must perform an endianness swap
			#pragma BullseyeCoverage off
			virtual EYesNo GetSwapEndianess()
			{
				return No;
			}
			#pragma BullseyeCoverage on


			//---------------------------------------------------------------
			// IPortReplay implementation
			//---------------------------------------------------------------

			//! sends the commands to the camera.
			/*! the default implementation just walks the list and issues each command
			using the WriteRegister method. Depending on the capabilities of
			the transport layer the implementation can however use a special command
			which sends all register write commands as one package.
			*/
			virtual void Replay( IPortWriteList *pPortRecorder, bool Invalidate = true )
			{
				if(pPortRecorder)
					pPortRecorder->Replay(this);

				if(Invalidate)
					InvalidateNode();
			}

			// Invalidate the node
			void InvalidateNode()
			{
				if(m_ptrPort.IsValid())
					m_ptrPort->InvalidateNode();
			}

		protected:
			//! Pointer to the node holding a reference to this implementation
			CNodePtr m_ptrPort;

		};
	}
}

#pragma warning(pop)
#endif // ifndef SPINNAKER_PORTIMPL_H
