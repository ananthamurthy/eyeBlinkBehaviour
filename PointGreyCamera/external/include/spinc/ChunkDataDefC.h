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
/* Generated Fri Aug 19 10:27:56 2016 */

#ifndef PGR_SPINNAKER_CHUNKDATADEF_C_H
#define PGR_SPINNAKER_CHUNKDATADEF_C_H

#include "SpinnakerPlatformC.h"

/**
* @defgroup SpinnakerDefsC Spinnaker C Definitions
* @ingroup SpinnakerC
*
* Definitions for Spinnaker C
*/
/*@{*/

/**
* @defgroup ChunkDataDefC_h Chunk Data Structures
*/
/*@{*/

/**
* @brief The type of information that can be obtained from image chunk data.
*/

typedef struct _spinChunkData
{
	int64_t m_partSelector;
	int64_t m_offsetX;
	int64_t m_offsetY;
	int64_t m_width;
	int64_t m_height;
	int64_t m_pixelDynamicRangeMin;
	int64_t m_pixelDynamicRangeMax;
	int64_t m_timestamp;
	int64_t m_timestampLatchValue;
	int64_t m_lineStatusAll;
	int64_t m_counterValue;
	double m_timerValue;
	int64_t m_scanLineSelector;
	int64_t m_encoderValue;
	double m_exposureTime;
	double m_gain;
	double m_blackLevel;
	int64_t m_linePitch;
	int64_t m_frameID;
	int64_t m_transferBlockID;
	int64_t m_transferQueueCurrentBlockCount;
	int64_t m_streamChannelID;
	int64_t m_sequencerSetActive;
	double m_scan3dCoordinateScale;
	double m_scan3dCoordinateOffset;
	double m_scan3dInvalidDataValue;
	double m_scan3dAxisMin;
	double m_scan3dAxisMax;
	double m_scan3dTransformValue;
	double m_scan3dCoordinateReferenceValue;
} spinChunkData;

/*@}*/

/*@}*/

#endif // PGR_SPINNAKER_CHUNKDATADEF_C_H