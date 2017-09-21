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
// PROVIDED ON AN “AS-IS�? BASIS AND POINT GREY RESEARCH INC. MAKES NO 
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

#ifndef PGR_SPINNAKER_PLATFORM_C_H
#define PGR_SPINNAKER_PLATFORM_C_H

#if defined(_WIN32) || defined(_WIN64)

// Windows 32-bit and 64-bit
#if defined(_MSC_VER) && _MSC_VER >= 1600 /* VS2010 provides stdint.h */
#include <stdint.h>
#elif !defined _STDINT_H && !defined _STDINT
/* stdint.h is usually not available under Windows */
typedef unsigned char uint8_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
typedef __int32 int32_t;
typedef __int64	int64_t;
#endif
#else

// Linux and all others
#include <stdint.h>
#endif

#include <stddef.h>

/* Function declaration modifiers */
#if defined (_WIN32) || defined(_WIN64)

// Windows 32-bit and 64-bit
#ifndef SPINC_NO_DECLSPEC_STATEMENTS
#ifdef SPINCDLL
#define SPINC_IMPORT_EXPORT __declspec(dllexport)
#else
#define SPINC_IMPORT_EXPORT __declspec(dllimport)
#endif
#else
#define SPINC_IMPORT_EXPORT
#endif /* #  ifndef GCTLI_NO_DECLSPEC_STATEMENTS */
#ifndef _M_X64
#define SPINC_CALLTYPE __stdcall
#else
#define SPINC_CALLTYPE /* default */
#endif
#ifndef EXTERN_C
#define EXTERN_C extern "C"
#endif

#elif defined (__GNUC__) && (__GNUC__ >= 4) && (defined (__linux__) || defined (__APPLE__))

// Linux
#define SPINC_IMPORT_EXPORT __attribute__((visibility("default")))
#ifndef __x86_64
#define SPINC_CALLTYPE __attribute__((stdcall))
#else
#define SPINC_CALLTYPE /* default */
#endif
#ifndef EXTERN_C
#define EXTERN_C extern "C"
#endif

#else

#error Unknown platform, file needs adaptation
#endif

/* C API Interface Functions */
#define SPINNAKERC_API SPINC_IMPORT_EXPORT spinError SPINC_CALLTYPE

#endif //PGR_SPINNAKER_PLATFORM_C_H