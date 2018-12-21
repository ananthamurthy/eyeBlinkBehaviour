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

#ifndef PGR_SPINNAKER_CHUNKDATA_H
#define PGR_SPINNAKER_CHUNKDATA_H

#include "SpinGenApi/GCTypes.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include "CameraDefs.h"

namespace Spinnaker
{
	/**
	* @defgroup SpinnakerClasses Spinnaker Classes
	*/
	/*@{*/

	/**
	* @defgroup ChunkData_h ChunkData Class
	*/
	/*@{*/

	/**
	*@brief The chunk data which contains additional information about an image.
	*/

	class SPINNAKER_API ChunkData
	{
	public:
		ChunkData();

		ChunkData(const ChunkData& src);

		virtual ~ChunkData(void);

		void SetChunks(GenApi::INodeMap & pNodeMap);

		/**
		 * Description: Selects the part to access in chunk data in a multipart transmission.
		 * Visibility: Expert
		 */
		int64_t GetPartSelector() const;

		/**
		 * Description: Returns the OffsetX of the image included in the payload.
		 * Visibility: Expert
		 */
		int64_t GetOffsetX() const;

		/**
		 * Description: Returns the OffsetY of the image included in the payload.
		 * Visibility: Expert
		 */
		int64_t GetOffsetY() const;

		/**
		 * Description: Returns the Width of the image included in the payload.
		 * Visibility: Expert
		 */
		int64_t GetWidth() const;

		/**
		 * Description: Returns the Height of the image included in the payload.
		 * Visibility: Expert
		 */
		int64_t GetHeight() const;

		/**
		 * Description: Returns the minimum value of dynamic range of the image included in the payload.
		 * Visibility: Expert
		 */
		int64_t GetPixelDynamicRangeMin() const;

		/**
		 * Description: Returns the maximum value of dynamic range of the image included in the payload.
		 * Visibility: Expert
		 */
		int64_t GetPixelDynamicRangeMax() const;

		/**
		 * Description: Returns the Timestamp of the image included in the payload at the time of the FrameStart internal event.
		 * Visibility: Expert
		 */
		int64_t GetTimestamp() const;

		/**
		 * Description: Returns the last Timestamp latched with the TimestampLatch command.
		 * Visibility: Expert
		 */
		int64_t GetTimestampLatchValue() const;

		/**
		 * Description: Returns the status of all the I/O lines at the time of the FrameStart internal event.
		 * Visibility: Expert
		 */
		int64_t GetLineStatusAll() const;

		/**
		 * Description: Returns the value of the selected Chunk counter at the time of the FrameStart event.
		 * Visibility: Expert
		 */
		int64_t GetCounterValue() const;

		/**
		 * Description: Returns the value of the selected Timer at the time of the FrameStart internal event.
		 * Visibility: Expert
		 */
		float64_t GetTimerValue() const;

		/**
		 * Description: Index for vector representation of one chunk value per line in an image.
		 * Visibility: Expert
		 */
		int64_t GetScanLineSelector() const;

		/**
		 * Description: Returns the counter's value of the selected Encoder at the time of the FrameStart in area scan mode or the counter's value at the time of the LineStart selected by ChunkScanLineSelector in LineScan mode.
		 * Visibility: Expert
		 */
		int64_t GetEncoderValue() const;

		/**
		 * Description: Returns the exposure time used to capture the image.
		 * Visibility: Expert
		 */
		float64_t GetExposureTime() const;

		/**
		 * Description: Returns the gain used to capture the image.
		 * Visibility: Expert
		 */
		float64_t GetGain() const;

		/**
		 * Description: Returns the black level used to capture the image included in the payload.
		 * Visibility: Expert
		 */
		float64_t GetBlackLevel() const;

		/**
		 * Description: Returns the LinePitch of the image included in the payload.
		 * Visibility: Expert
		 */
		int64_t GetLinePitch() const;

		/**
		 * Description: Returns the unique Identifier of the frame (or image) included in the payload.
		 * Visibility: Expert
		 */
		int64_t GetFrameID() const;

		/**
		 * Description: Returns the unique identifier of the transfer block used to transport the payload.
		 * Visibility: Expert
		 */
		int64_t GetTransferBlockID() const;

		/**
		 * Description: Returns the current number of blocks in the transfer queue.
		 * Visibility: Expert
		 */
		int64_t GetTransferQueueCurrentBlockCount() const;

		/**
		 * Description: Returns identifier of the stream channel used to carry the block.
		 * Visibility: Expert
		 */
		int64_t GetStreamChannelID() const;

		/**
		 * Description: Return the index of the active set of the running sequencer included in the payload.
		 * Visibility: Expert
		 */
		int64_t GetSequencerSetActive() const;

		/**
		 * Description: Returns the Scale for the selected coordinate axis of the image included in the payload.
		 * Visibility: Expert
		 */
		float64_t GetScan3dCoordinateScale() const;

		/**
		 * Description: Returns the Offset for the selected coordinate axis of the image included in the payload.
		 * Visibility: Expert
		 */
		float64_t GetScan3dCoordinateOffset() const;

		/**
		 * Description: Returns the Invalid Data Value used for the image included in the payload.
		 * Visibility: Expert
		 */
		float64_t GetScan3dInvalidDataValue() const;

		/**
		 * Description: Returns the Minimum Axis value for the selected coordinate axis of the image included in the payload.
		 * Visibility: Expert
		 */
		float64_t GetScan3dAxisMin() const;

		/**
		 * Description: Returns the Maximum Axis value for the selected coordinate axis of the image included in the payload.
		 * Visibility: Expert
		 */
		float64_t GetScan3dAxisMax() const;

		/**
		 * Description: Returns the transform value.
		 * Visibility: Expert
		 */
		float64_t GetScan3dTransformValue() const;

		/**
		 * Description: Reads the value of a position or pose coordinate for the anchor or transformed coordinate systems relative to the reference point.
		 * Visibility: Expert
		 */
		float64_t GetScan3dCoordinateReferenceValue() const;


	private:
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
		float64_t m_timerValue;
		int64_t m_scanLineSelector;
		int64_t m_encoderValue;
		float64_t m_exposureTime;
		float64_t m_gain;
		float64_t m_blackLevel;
		int64_t m_linePitch;
		int64_t m_frameID;
		int64_t m_transferBlockID;
		int64_t m_transferQueueCurrentBlockCount;
		int64_t m_streamChannelID;
		int64_t m_sequencerSetActive;
		float64_t m_scan3dCoordinateScale;
		float64_t m_scan3dCoordinateOffset;
		float64_t m_scan3dInvalidDataValue;
		float64_t m_scan3dAxisMin;
		float64_t m_scan3dAxisMax;
		float64_t m_scan3dTransformValue;
		float64_t m_scan3dCoordinateReferenceValue;

	};
	/*@}*/

	/*@}*/

}
#endif // PGR_SPINNAKER_CHUNKDATA_H