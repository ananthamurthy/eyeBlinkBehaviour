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
\brief   Definition of CTestPortStruct
\ingroup Spinnaker_GenApi_PublicUtilities
*/

#ifndef SPINNAKER_GENAPI_STRUCTPORT_H
#define SPINNAKER_GENAPI_STRUCTPORT_H

#include "SpinGenApi/PortImpl.h"


namespace Spinnaker
{
	namespace GenApi
	{
		//! Implements a register spaces based on a C++ struct
		template <class CDataStruct>
		class CTestPortStruct : public CDataStruct, public CPortImpl
		{
		public:
			CTestPortStruct(int64_t BaseAddress = 0)
				: m_BaseAddress(BaseAddress)
			{
				MemSet(0);
				ResetStatistics();
			}

			//-------------------------------------------------------------
			// IBase implementation
			//-------------------------------------------------------------

			//! Get the access mode of the node
			virtual EAccessMode GetAccessMode() const
			{
				return RW;
			}

			//! Get the type of the main interface of a node
			virtual EInterfaceType GetPrincipalInterfaceType() const
			{
				return intfIPort;
			}

			//---------------------------------------------------------------
			// IPort implementation
			//---------------------------------------------------------------

			//! Reads a chunk of bytes from the port
			virtual void Read(void *pBuffer, int64_t Address, int64_t Length)
			{
				int64_t InternalAddress = Address - m_BaseAddress;

				CDataStruct *pDataStruct = static_cast<CDataStruct*>(this);
				if (InternalAddress < 0 || Length < 0 || InternalAddress + Length > sizeof(CDataStruct))
				{
					//throw RUNTIME_EXCEPTION("CTestPortStruct::Read - Invalid address and/or length");
				}
				memcpy(pBuffer, (uint8_t*)pDataStruct + InternalAddress, (size_t)Length);
				m_NumReads++;
			}

			//! Writes a chunk of bytes to the port
			virtual void Write(const void *pBuffer, int64_t Address, int64_t Length)
			{
				int64_t InternalAddress = Address - m_BaseAddress;

				CDataStruct *pDataStruct = static_cast<CDataStruct*>(this);
				if (InternalAddress < 0 || Length < 0 || InternalAddress + Length > sizeof(CDataStruct))
				{
					//throw RUNTIME_EXCEPTION("CTestPortStruct::Write - Invalid address and/or length");
				}
				memcpy((uint8_t*)pDataStruct + InternalAddress, pBuffer, (size_t)Length);
				m_NumWrites++;
			}

			//-------------------------------------------------------------
			// Utility functions
			//-------------------------------------------------------------

			void MemSet(const char FillValue)
			{
				memset(static_cast<CDataStruct*>(this), FillValue, sizeof(CDataStruct));
			}

			//-------------------------------------------------------------
			// Statistics functions
			//-------------------------------------------------------------

			//! Resets the read/write statistics
			void ResetStatistics()
			{
				m_NumReads = 0;
				m_NumWrites = 0;
			}

			//! Returns the number of reads since lastReset Statistics
			int64_t GetNumReads()
			{
				return m_NumReads;
			}

			//! Returns the number of writes since lastReset Statistics
			int64_t GetNumWrites()
			{
				return m_NumWrites;
			}

		protected:
			//! Number of reads since last reset
			int64_t m_NumReads;

			//! Number of writes since last reset
			int64_t m_NumWrites;

			//! the base address used for the struct
			int64_t m_BaseAddress;
		};
	}
}

#endif // SPINNAKER_GENAPI_STRUCTPORT_H
