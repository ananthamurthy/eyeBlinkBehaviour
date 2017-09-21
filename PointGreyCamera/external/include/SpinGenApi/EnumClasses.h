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
\brief   Definition of enum classes for Sign, Endianness, Access mode and Visibility
\ingroup Spinnaker_GenApi_PublicUtilities
*/

#ifndef SPINNAKER_GENAPI_ENUMCLASSES_H
#define SPINNAKER_GENAPI_ENUMCLASSES_H

#include "GCString.h"
#include "Types.h"

namespace Spinnaker
{
	namespace GenApi
	{
		//*************************************************************
		// Build in enumeration classes
		//*************************************************************

		//! ESignClass holds conversion methods for the sign enumeration

		class SPINNAKER_API ESignClass
		{
		public:
			//! Converts a string to enum value
            static bool FromString(const GenICam::gcstring &ValueStr, ESign *pValue);

			//! Converts a string to an int32_t property
            static void ToString(GenICam::gcstring &ValueStr, ESign *pValue);

			//! Converts a string to an int32_t property
            static GenICam::gcstring ToString(ESign Value);
		};

		/**
		\brief EEndianessClass holds conversion methods for the endianess enumeration
		*/
		class SPINNAKER_API EEndianessClass
		{
		public:
			//! Converts a string to enum value
            static bool FromString(const GenICam::gcstring &ValueStr, EEndianess *pValue);

			//! Converts a string to an int32_t property
            static void ToString(GenICam::gcstring &ValueStr, EEndianess *pValue);

			//! Converts a string to an int32_t property
            static GenICam::gcstring ToString(EEndianess Value);
		};

		/**
		\brief ERepresentationClass holds conversion methods for the representation enumeration
		*/
		class SPINNAKER_API ERepresentationClass
		{
		public:
			//! Converts a string to enum value
            static bool FromString(const GenICam::gcstring &ValueStr, ERepresentation *pValue);

			//! Converts a string to an int32_t property
            static void ToString(GenICam::gcstring &ValueStr, ERepresentation *pValue);

			//! Converts a string to an int32_t property
            static GenICam::gcstring ToString(ERepresentation Value);
		};

		/**
		\brief EVisibilityClass holds conversion methods for the visibility enumeration
		*/
		class SPINNAKER_API EVisibilityClass
		{
		public:
			//! Converts a string to enum value
            static bool FromString(const GenICam::gcstring &ValueStr, EVisibility *pValue);

			//! Converts a string to an int32_t property
            static void ToString(GenICam::gcstring &ValueStr, EVisibility *pValue);

			//! Converts a string to an int32_t property
            static GenICam::gcstring ToString(EVisibility Value);
		};

		/**
		\brief EAccessModeClass holds conversion methods for the access mode enumeration
		*/
		class SPINNAKER_API EAccessModeClass
		{
		public:
			//! Converts a string to enum value
            static bool FromString(const GenICam::gcstring &ValueStr, EAccessMode *pValue);

			//! Converts a string to an int32_t property
            static void ToString(GenICam::gcstring &ValueStr, EAccessMode *pValue);

			//! Converts a string to an int32_t property
            static GenICam::gcstring ToString(EAccessMode Value);
		};

		/**
		\brief ECachingModeClass holds conversion methods for the caching mode enumeration
		*/
	  class SPINNAKER_API ECachingModeClass
	  {
	  public:
		  //! Converts a string to enum value
          static bool FromString(const GenICam::gcstring &ValueStr, ECachingMode *pValue);

          static void ToString(GenICam::gcstring &ValueStr, ECachingMode *pValue);

		  //! Converts a string to an int32_t property
          static GenICam::gcstring ToString(ECachingMode Value);

	  };

		/**
		\brief Holds conversion methods for the namespace enumeration
		*/
		class SPINNAKER_API ENameSpaceClass
		{
		public:
			//! Converts a string to enum value
            static bool FromString(const GenICam::gcstring &ValueStr, ENameSpace *pValue);

			//! Converts a string to an int32_t property
            static void ToString(GenICam::gcstring &ValueStr, ENameSpace *pValue);
			//! Converts a string to an int32_t property
            static GenICam::gcstring ToString(ENameSpace Value);
		};

		/**
		\brief Holds conversion methods for the standard namespace enumeration
		*/
		class SPINNAKER_API EYesNoClass
		{
		public:
			//! Converts a string to enum value
            static bool FromString(const GenICam::gcstring &ValueStr, EYesNo *pValue);

			//! Converts a string to an int32_t property
            static void ToString(GenICam::gcstring &ValueStr, EYesNo *pValue);

			//! Converts a string to an int32_t property
            static GenICam::gcstring ToString(EYesNo Value);
		};

		/**
		\brief Holds conversion methods for the standard namespace enumeration
		*/
		class SPINNAKER_API EStandardNameSpaceClass
		{
		public:
			//! Converts a string to enum value
			static bool FromString(const GenICam::gcstring &ValueStr, EStandardNameSpace *pValue);

			//! Converts a string to an int32_t property
			static void ToString(GenICam::gcstring &ValueStr, EStandardNameSpace *pValue);

			//! Converts a string to an int32_t property
            static GenICam::gcstring ToString(EStandardNameSpace Value);
		};

		/**
		\brief Holds conversion methods for the converter formulas
		*/
		class SPINNAKER_API ESlopeClass
		{
		public:
			//! Converts a string to enum value
			static bool FromString(const GenICam::gcstring &ValueStr, ESlope *pValue);

			//! Converts a string to an int32_t property
			static void ToString(GenICam::gcstring &ValueStr, ESlope *pValue);

			//! Converts a string to an int32_t property
			static GenICam::gcstring ToString(ESlope Value);
		};

		/**
		\brief Holds conversion methods for the notation type of floats
		*/
		class SPINNAKER_API EDisplayNotationClass
		{
		public:
			//! Converts a string to enum value
            static bool FromString(const GenICam::gcstring &ValueStr, EDisplayNotation *pValue);

			//! Converts a string to an int32_t property
            static void ToString(GenICam::gcstring &ValueStr, EDisplayNotation *pValue);

			//! Converts a string to an int32_t property
            static GenICam::gcstring ToString(EDisplayNotation Value);
		};

		/**
		\brief Holds conversion methods for the notation type of floats
		*/
		class SPINNAKER_API EInputDirectionClass
		{
		public:
			//! Converts a string to enum value
            static bool FromString(const GenICam::gcstring &ValueStr, EInputDirection *pValue);

			//! Converts a string to an int32_t property
            static void ToString(GenICam::gcstring &ValueStr, EInputDirection *pValue);

			//! Converts a string to an int32_t property
            static GenICam::gcstring ToString(EInputDirection Value);
		};
		
		//! helper class converting EGenApiSchemaVersion from and to string
		class SPINNAKER_API EGenApiSchemaVersionClass
		{
		public:
			//! Converts a string to enum value
			static bool FromString(const GenICam::gcstring &ValueStr, EGenApiSchemaVersion *pValue);

			//! Converts a string to an int32_t property
			static void ToString(GenICam::gcstring &ValueStr, EGenApiSchemaVersion *pValue);

			//! Converts a string to an int32_t property
			static GenICam::gcstring ToString(EGenApiSchemaVersion Value);
		};
	};
};


#endif // ifndef SPINNAKER_GENAPI_ENUMCLASSES_H
