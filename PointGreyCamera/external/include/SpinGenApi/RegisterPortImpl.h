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
\brief   Definition of CRegisterPortImpl
\ingroup Spinnaker_GenApi_PublicUtilities
*/

#ifndef SPINNAKER_GENAPI_REGISTERPORTIMPL_H
#define SPINNAKER_GENAPI_REGISTERPORTIMPL_H

#include "PortImpl.h"
#include "Log.h"
#include "Compatibility.h"

namespace Spinnaker
{
	namespace GenApi
	{
		//*************************************************************
		// CRegisterPortImpl class
		//*************************************************************

		/**
		\brief Standard implementation for a port using a register based transport layer
		//! \ingroup Spinnaker_GenApi_PublicUtilities
		*/
		class CRegisterPortImpl : public CPortImpl
		{
		public:
			//! Constructor
			CRegisterPortImpl(int MaxNumQuadlets = 1, bool TransportLayerSwapsEndianess = false){};

			//! Destructor
			virtual ~CRegisterPortImpl(){};

			/*---------------------------------------------------------------*/
			// IBase ==> You need to override this method
			/*---------------------------------------------------------------*/

			//! Get the access mode of the node
			/*! Driver closed => NI, Driver open => RW, analyzing a struct, RO */
			virtual EAccessMode GetAccessMode() const = 0;

			/*---------------------------------------------------------------*/
			// IRegisterPort ==> You need to override these methods
			/*---------------------------------------------------------------*/

			//! Reads an array of quadlets from the port
			virtual void ReadRegister(uint32_t *pRegisters, int64_t Address, int64_t Length) = 0;

			//! Writes an array of quadlets to the port
			virtual void WriteRegister(const uint32_t *pRegisters, int64_t Address, int64_t Length) = 0;

			/*---------------------------------------------------------------*/
			// IPort
			/*---------------------------------------------------------------*/

			//! Reads a chunk of bytes from the port
			virtual void Read(void *pBuffer, int64_t Address, int64_t Length){};

			//! Writes a chunk of bytes to the port
			virtual void Write(const void *pBuffer, int64_t Address, int64_t Length){};

			/*---------------------------------------------------------------*/
			// IPortConstruct implementation (without IPort & IBase)
			/*---------------------------------------------------------------*/

			//! Sets pointer the real port implementation; this function may called only once
			virtual void SetPortImpl(IPort* pPort)
			{
				m_ptrPort = pPort;
				assert(m_ptrPort.IsValid());
			};
		};
	}
}

#endif // ifndef SPINNAKER_GENAPI_REGISTERPORTIMPL_H
