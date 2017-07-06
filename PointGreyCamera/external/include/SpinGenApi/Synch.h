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
\brief   Definition of Lock classes
\ingroup Spinnaker_GenApi_PublicImpl
*/

#ifndef SPINNAKER_GENAPI_SYNCH_H
#define SPINNAKER_GENAPI_SYNCH_H

#include "SpinnakerPlatform.h"

namespace Spinnaker
{
	namespace GenApi
	{

		//-----------------------------------------------------------------
		// CLock
		//-----------------------------------------------------------------

		/**
		\brief A lock class
		\ingroup GenApi_PublicImpl
		*/
		class SPINNAKER_API CLock
		{
		public:
			//! Constructor
			CLock();

			//! Constructor
			CLock(void* pLock);

			//! Destructor
			~CLock();

			//! tries to enter the critical section; returns true if successful
			bool TryLock();

			//! enters the critical section (may block)
			void Lock();

			//! leaves the critical section
			void Unlock();

		private:
			//! no copy constructor
			CLock(const CLock&);

			//! no assignment operator
			CLock& operator=(const CLock&);

		protected:
		
			friend class NodeMap;
			void* m_lock;
			bool m_bOwnLock;
		};

		//! This class is for testing purposes only. It should not be used for
		//! client code because it exists only for Windows but not for Linux
		//! since it uses internal data structures of a Win32 object
		class SPINNAKER_API CLockEx : public CLock
		{
		public:


	#       if defined (_WIN32)

				//! Gives access to internal data member for test and purposes
				int64_t GetLockCount();

				//! Gives access to internal data member for test and purposes
				int64_t GetRecursionCount();

	#       elif defined (__GNUC__) && (defined (__linux__) || defined (__APPLE__))
				// nothing implemented for Unix
	#       else
	#           error No/unknown platform support
	#       endif

		private:
			//! no copy constructor
			CLockEx( const CLockEx& );

			//! no assignment operator
			CLockEx& operator=( const CLockEx& );

		protected:

			void* m_lockEx;

		};

		//-----------------------------------------------------------------
		// AutoLock
		//-----------------------------------------------------------------
		class AutoLock
		{
			CLock& m_Lock;
		public:
			AutoLock(CLock& lock)
				: m_Lock(lock)
			{
				m_Lock.Lock();
			}

			~AutoLock()
			{
				m_Lock.Unlock();
			}

		private:
			AutoLock& operator=(const AutoLock&);
			AutoLock(const AutoLock&);
		};
	} // namespace GenApi
}//namespace Spinnaker

#endif // SPINNAKER_GENAPI_SYNCH_H
