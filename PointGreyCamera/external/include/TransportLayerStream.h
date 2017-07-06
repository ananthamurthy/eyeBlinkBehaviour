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

#ifndef PGR_SPINNAKER_TRANSPORTLAYERSTREAM_H
#define PGR_SPINNAKER_TRANSPORTLAYERSTREAM_H

#include "SpinnakerPlatform.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include "TransportLayerDefs.h"
#include <string>

namespace Spinnaker
{
	/**
	* @defgroup SpinnakerQuickSpinClasses Spinnaker QuickSpin Classes
	*/
	/*@{*/

	/**
	* @defgroup TransportLayerStream_h TransportLayerStream Class
	*/
	/*@{*/

	/**
	*@brief Part of the QuickSpin API to provide access to camera information without having to first initialize the camera.
	*/

	class SPINNAKER_API TransportLayerStream
	{
	public:
		TransportLayerStream(GenApi::INodeMap *nodeMapTLDevice);
		~TransportLayerStream();

	protected:
		TransportLayerStream();

	private:
		TransportLayerStream(const TransportLayerStream&);
		TransportLayerStream& operator=(const TransportLayerStream&);
		TransportLayerStream& operator=(GenApi::INodeMap &);

	public:
		/**
		 * Description: Device unique ID for the data stream, e.g. a GUID.
		 * Visibility: Expert
		 */
		GenApi::IString &StreamID;

		/**
		 * Description: Stream type of the device.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<StreamTypeEnum> &StreamType;

		/**
		 * Description: Counts the number of image buffers that arrived since stream started.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamTotalBufferCount;

		/**
		 * Description: Controls the number of buffers that should be used by default on this stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamDefaultBufferCount;

		/**
		 * Description: Controls the maximum number of buffers that should be used on this stream. This value is calculated based on the available system memory.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamDefaultBufferCountMax;

		/**
		 * Description: Controls the number of buffers used for the stream.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<StreamDefaultBufferCountModeEnum> &StreamDefaultBufferCountMode;

		/**
		 * Description: Available buffer handling modes of this data stream:
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<StreamBufferHandlingModeEnum> &StreamBufferHandlingMode;

		/**
		 * Description: Enables or disables CRC checks on received images.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &StreamCRCCheckEnable;

		/**
		 * Description: Enables or disables the packet resend mechanism.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &GevPacketResendMode;

		/**
		 * Description: Maximum number of resend requests per image.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevMaximumNumberResendRequests;

		/**
		 * Description: Time in milliseconds to wait until a resend request is issued.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevPacketResendTimeout;

		/**
		 * Description: The maximum number of buffers that can be resend simultaneously.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevMaximumNumberResendBuffers;

		/**
		 * Description: Displays number of packets received on this stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevTotalPacketCount;

		/**
		 * Description: Displays number of packets missed on this stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevFailedPacketCount;

		/**
		 * Description: Displays number of packets received after retransmit request on this stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevResendPacketCount;

		/**
		 * Description: Displays number of corrupt images on this stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamFailedBufferCount;

		/**
		 * Description: Displays number of dropped images on this stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamBufferUnderrunCount;

		/**
		 * Description: Displays number of packets requested to be retransmitted on this stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevResendRequestCount;


	protected:
		friend class CameraBase;
		friend class CameraInternal;

	};
	/*@}*/

	/*@}*/

}
#endif // PGR_SPINNAKER_TRANSPORTLAYERSTREAM_H