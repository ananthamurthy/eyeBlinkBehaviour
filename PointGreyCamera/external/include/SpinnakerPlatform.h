//=============================================================================
// Copyright © 2015 Point Grey Research, Inc. All Rights Reserved.
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

#ifndef PGR_SPINNAKER_PLATFORM_H
#define PGR_SPINNAKER_PLATFORM_H

/**
*  @defgroup SpinnakerHeaders Spinnaker Headers
*/

/*@{*/

/**
* @defgroup SpinnakerPlatform Spinnaker Platform 
*
* Platform-specific header file for Spinnaker.
* All the platform-specific code that is required by individual compilers
* to produce the appropriate code for each platform.
*/

/*@{*/

#define SPINNAKER_API_ABSTRACT /*nothing*/
// Windows 32-bit and 64-bit
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)

#ifdef SPINNAKER_EXPORT
#define SPINNAKER_API __declspec( dllexport )
#elif defined(Spinnaker_STATIC)
#define SPINNAKER_API
#else
#define SPINNAKER_API __declspec( dllimport )
#endif

#if _MSC_VER > 1000
#pragma once
#endif

//#elif defined(MAC_OSX)

// Mac OSX

#else
// Linux and all others

// Using GCC 4 where hiding attributes is possible
#define SPINNAKER_API    __attribute__((visibility ("default")) )
#define SPINNAKER_LOCAL  __attribute__((visibility ("hidden"))  )

#endif

#endif // PGR_SPINNAKER_PLATFORM_H

/*@}*/

/*@}*/
