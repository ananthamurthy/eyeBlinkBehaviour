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
// PROVIDED ON AN "AS-IS" BASIS AND POINT GREY RESEARCH INC. MAKES NO
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
   
/* Auto-generated file. Do not modify. */
/* Generated Fri Aug 19 10:27:33 2016 */

#include "QuickSpinC.h"

#ifndef PGR_SPINNAKERC_TLSTREAM_H
#define PGR_SPINNAKERC_TLSTREAM_H

/**	
* @defgroup TLStreamC_h TLStream Structures
* @ingroup CQuickSpin
*/
/*@{*/

typedef struct _quickSpinTLStream
{
	quickSpinStringNode StreamID;
	quickSpinEnumerationNode StreamType;
	quickSpinIntegerNode StreamTotalBufferCount;
	quickSpinIntegerNode StreamDefaultBufferCount;
	quickSpinIntegerNode StreamDefaultBufferCountMax;
	quickSpinEnumerationNode StreamDefaultBufferCountMode;
	quickSpinEnumerationNode StreamBufferHandlingMode;
	quickSpinBooleanNode StreamCRCCheckEnable;
	quickSpinBooleanNode GevPacketResendMode;
	quickSpinIntegerNode GevMaximumNumberResendRequests;
	quickSpinIntegerNode GevPacketResendTimeout;
	quickSpinIntegerNode GevMaximumNumberResendBuffers;
	quickSpinIntegerNode GevTotalPacketCount;
	quickSpinIntegerNode GevFailedPacketCount;
	quickSpinIntegerNode GevResendPacketCount;
	quickSpinIntegerNode StreamFailedBufferCount;
	quickSpinIntegerNode StreamBufferUnderrunCount;
	quickSpinIntegerNode GevResendRequestCount;
} quickSpinTLStream;

/*@}*/

#endif // PGR_SPINNAKERC_TLSTREAM_H