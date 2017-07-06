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
\brief   Portable string vector implementation
\ingroup Spinnaker_GenICam_PublicUtilities
*/
#ifndef SPINNAKER_GENICAM_GCSTRINGLIST_H
#define SPINNAKER_GENICAM_GCSTRINGLIST_H

#include "SpinnakerPlatform.h"
#include "GCString.h"

#if defined (_WIN32) || (defined (__GNUC__) && (defined (__linux__) || defined(__APPLE__) ||  defined(VXWORKS)))


namespace Spinnaker 
{
	namespace GenICam
	{

		/**
		\brief A vector of gcstrings which is a clone of std::vector<std::string>
		\ingroup Base_PublicUtilities
		*/
		class SPINNAKER_API gcstring_vector
		{
			// Nested types
			// ---------------------------------------------------------------------------
		public:
			class SPINNAKER_API const_iterator
			{
				// Ctor / Dtor
				// -------------------------------------------------------------------------
			public:
				const_iterator(gcstring *pStr = 0);

				// Operators
				// -------------------------------------------------------------------------
			public:
				const gcstring &        operator *        (void)                  const;
				const gcstring *        operator ->       (void)                  const;
				const_iterator &        operator ++       (void);
				const_iterator          operator ++       (int);
				const_iterator &        operator --       (void);
				const_iterator          operator --       (int);
				const_iterator &        operator +=       (intptr_t iInc);
				const_iterator          operator +        (intptr_t iInc)         const;
				const_iterator &        operator -=       (intptr_t iDec);
				intptr_t                operator -        (const const_iterator &iter) const;
				const_iterator          operator -        (intptr_t iDec)         const;
				const gcstring &        operator []       (intptr_t iIndex)       const;
				bool                    operator ==       (const const_iterator &iter) const;
				bool                    operator !=       (const const_iterator &iter) const;
				bool                    operator <        (const const_iterator &iter) const;
				bool                    operator >        (const const_iterator &iter) const;
				bool                    operator <=       (const const_iterator &iter) const;
				bool                    operator >=       (const const_iterator &iter) const;
				SPINNAKER_API
					friend const_iterator   operator +        (intptr_t iInc, const const_iterator &iter);

				// Member
				// -------------------------------------------------------------------------
			protected:
				gcstring *              _ps;
			};

			class SPINNAKER_API iterator :
				public const_iterator
			{
				// Ctor / Dtor
				// -------------------------------------------------------------------------
			public:
				iterator(gcstring *pStr = 0);

				// Operators
				// -------------------------------------------------------------------------
			public:
				gcstring &              operator *        (void)                  const;
				gcstring *              operator ->       (void)                  const;
				iterator &              operator ++       (void);
				iterator                operator ++       (int);
				iterator &              operator --       (void);
				iterator                operator --       (int);
				iterator &              operator +=       (intptr_t iInc);
				iterator                operator +        (intptr_t iInc)         const;
				iterator &              operator -=       (intptr_t iDec);
				intptr_t                operator -        (const iterator &iter)  const;
				iterator                operator -        (intptr_t iDec)         const;
				gcstring &              operator []       (intptr_t iIndex)       const;
				SPINNAKER_API
				friend iterator         operator +        (intptr_t iInc, const iterator &iter);
			};

			// Ctor / Dtor
			// ---------------------------------------------------------------------------
		public:
			gcstring_vector(void);
			explicit                  gcstring_vector(size_t uiSize, const gcstring &str = gcstring());
			gcstring_vector(const gcstring_vector &obj);
			virtual                   ~gcstring_vector(void);

			// Element access
			// ---------------------------------------------------------------------------
		public:
			virtual void              assign(size_t n, const gcstring &val);
			virtual void              clear(void);
			virtual iterator          erase(iterator pos);
			virtual gcstring &        at(size_t uiIndex);
			virtual const gcstring &  at(size_t uiIndex)        const;
			virtual gcstring &        back(void);
			virtual const gcstring &  back(void)                  const;
			virtual iterator          begin(void);
			virtual const_iterator    begin(void)                  const;
			virtual size_t            capacity(void)                  const;
			virtual iterator          end(void);
			virtual const_iterator    end(void)                  const;
			virtual gcstring &        front(void);
			virtual const gcstring &  front(void)                  const;
			virtual size_t            max_size(void)                  const;
			virtual size_t            size(void)                  const;
			virtual iterator          insert(iterator pos, const gcstring &str);
			virtual bool              empty(void)                  const;
			virtual void              pop_back(void);
			virtual void              push_back(const gcstring &str);
			virtual void              resize(size_t uiSize, const gcstring &str = gcstring());
			virtual void              reserve(size_t uiSize);

			// Do not use the methods below - they only exist for
			// backwards compatibility
			virtual gcstring_vector & assign(const gcstring_vector &obj);
			virtual void              erase(size_t uiIndex);
			virtual void              insert(size_t uiIndex, const gcstring &str);


			// Operators
			// ---------------------------------------------------------------------------
		public:
			gcstring_vector &         operator =        (const gcstring_vector &obj);
			gcstring &                operator []       (size_t uiIndex);
			const gcstring &          operator []       (size_t uiIndex)        const;
			void                      operator delete   (void *pWhere);
			void *                    operator new      (size_t uiSize);

			// Member
			// ---------------------------------------------------------------------------
		private:
			void *                    _pv;
		};
	}
}


#else
#   error No known support for shared libraries
#endif

#endif // SPINNAKER_GENICAM_GCSTRINGLIST_H
