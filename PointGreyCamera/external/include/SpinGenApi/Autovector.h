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
 
//
/*!
\file
\brief   This file contains the public definition of the autovector classes.
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_AUTOVECTOR_H
#define SPINNAKER_GENAPI_AUTOVECTOR_H

#include <vector>
#include "GCTypes.h"
#include "SpinnakerPlatform.h"

#if defined (WIN32)
    typedef long ATOMIC_VARIABLE;
#elif defined (__GNUC__) && (defined (__linux__) || defined (__APPLE__))
    typedef uint32_t ATOMIC_VARIABLE;
#else
#   error Unsupported platform
#endif

namespace Spinnaker
{

	namespace GenApi
	{
		/**
		\brief Vector of integers with reference counting
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		class SPINNAKER_API int64_autovector_t
		{
		public:
			int64_autovector_t();
			int64_autovector_t(const int64_autovector_t &obj);
			explicit           int64_autovector_t(size_t n);
			virtual            ~int64_autovector_t(void);

			int64_autovector_t    &  operator =        (const int64_autovector_t &obj);


			void               operator delete   (void *pWhere);
			void *             operator new      (size_t uiSize);
			int64_t &          operator []       (size_t uiIndex);
			const int64_t &    operator []       (size_t uiIndex) const;
			size_t             size() const;
		protected:
			std::vector<int64_t> * _pv;
			ATOMIC_VARIABLE *_pCount;

		};

		/**
		\brief Vector of doubles with reference counting
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		class SPINNAKER_API double_autovector_t
		{
		public:
			double_autovector_t();
			double_autovector_t(const double_autovector_t &obj);
			explicit           double_autovector_t(size_t n);
			virtual            ~double_autovector_t(void);

			double_autovector_t    &  operator =        (const double_autovector_t &obj);


			void               operator delete   (void *pWhere);
			void *             operator new      (size_t uiSize);
			double &           operator []       (size_t uiIndex);
			const double &     operator []       (size_t uiIndex) const;
			size_t             size() const;
		protected:
			std::vector<double> * _pv;
			ATOMIC_VARIABLE *_pCount;

		};
	}

}



#endif // SPINNAKER_GENAPI_AUTOVECTOR_H
