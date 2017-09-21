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

#ifndef PGR_SPINNAKER_CAMERA_H
#define PGR_SPINNAKER_CAMERA_H

#include "SpinnakerPlatform.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include "CameraBase.h"
#include "CameraDefs.h"

namespace Spinnaker
{
	/**
	* @defgroup SpinnakerClasses Spinnaker Classes
	*/
	/*@{*/

	/**
	* @defgroup Camera_h Camera Class
	*/
	/*@{*/

	/**
	*@brief The camera object class.
	*/

	class SPINNAKER_API Camera : public CameraBase
	{
	public:
		~Camera();

		void Init();

	protected:
		Camera();
	private:
		Camera(const Camera &);
		Camera& operator=(const Camera&);

	public:
		/**
		 * Description: Returns the device type.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<DeviceTypeEnums> &DeviceType;

		/**
		 * Description: Scan type of the sensor of the device.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceScanTypeEnums> &DeviceScanType;

		/**
		 * Description: Name of the manufacturer of the device.
		 * Visibility: Beginner
		 */
		GenApi::IString &DeviceVendorName;

		/**
		 * Description: Model of the device.
		 * Visibility: Beginner
		 */
		GenApi::IString &DeviceModelName;

		/**
		 * Description: Identifier of the product family of the device.
		 * Visibility: Beginner
		 */
		GenApi::IString &DeviceFamilyName;

		/**
		 * Description: Manufacturer information about the device.
		 * Visibility: Beginner
		 */
		GenApi::IString &DeviceManufacturerInfo;

		/**
		 * Description: Version of the device.
		 * Visibility: Beginner
		 */
		GenApi::IString &DeviceVersion;

		/**
		 * Description: Version of the firmware in the device.
		 * Visibility: Beginner
		 */
		GenApi::IString &DeviceFirmwareVersion;

		/**
		 * Description: Device's serial number. This string is a unique identifier of the device.
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceSerialNumber;

		/**
		 * Description: User-programmable device identifier.
		 * Visibility: Beginner
		 */
		GenApi::IString &DeviceUserID;

		/**
		 * Description: Major version of the Standard Features Naming Convention that was used to create the device's GenICam XML.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &DeviceSFNCVersionMajor;

		/**
		 * Description: Minor version of the Standard Features Naming Convention that was used to create the device's GenICam XML.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &DeviceSFNCVersionMinor;

		/**
		 * Description: Sub minor version of Standard Features Naming Convention that was used to create the device's GenICam XML.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &DeviceSFNCVersionSubMinor;

		/**
		 * Description: Selects the manifest entry to reference.
		 * Visibility: Guru
		 */
		GenApi::IInteger &DeviceManifestEntrySelector;

		/**
		 * Description: Indicates the major version number of the GenICam XML file of the selected manifest entry.
		 * Visibility: Guru
		 */
		GenApi::IInteger &DeviceManifestXMLMajorVersion;

		/**
		 * Description: Indicates the minor version number of the GenICam XML file of the selected manifest entry.
		 * Visibility: Guru
		 */
		GenApi::IInteger &DeviceManifestXMLMinorVersion;

		/**
		 * Description: Indicates the subminor version number of the GenICam XML file of the selected manifest entry.
		 * Visibility: Guru
		 */
		GenApi::IInteger &DeviceManifestXMLSubMinorVersion;

		/**
		 * Description: Indicates the major version number of the schema file of the selected manifest entry.
		 * Visibility: Guru
		 */
		GenApi::IInteger &DeviceManifestSchemaMajorVersion;

		/**
		 * Description: Indicates the minor version number of the schema file of the selected manifest entry.
		 * Visibility: Guru
		 */
		GenApi::IInteger &DeviceManifestSchemaMinorVersion;

		/**
		 * Description: Indicates the first URL to the GenICam XML device description file of the selected manifest entry.
		 * Visibility: Guru
		 */
		GenApi::IString &DeviceManifestPrimaryURL;

		/**
		 * Description: Indicates the second URL to the GenICam XML device description file of the selected manifest entry.
		 * Visibility: Guru
		 */
		GenApi::IString &DeviceManifestSecondaryURL;

		/**
		 * Description: Transport Layer type of the device.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<DeviceTLTypeEnums> &DeviceTLType;

		/**
		 * Description: Major version of the Transport Layer of the device.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &DeviceTLVersionMajor;

		/**
		 * Description: Minor version of the Transport Layer of the device.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &DeviceTLVersionMinor;

		/**
		 * Description: Sub minor version of the Transport Layer of the device.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &DeviceTLVersionSubMinor;

		/**
		 * Description: Major version of the GenCP protocol supported by the device.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &DeviceGenCPVersionMajor;

		/**
		 * Description: Minor version of the GenCP protocol supported by the device.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &DeviceGenCPVersionMinor;

		/**
		 * Description: Maximum bandwidth of the data that can be streamed out of the device. This can be used to estimate if the physical connection(s) can sustain transfer of free-running images from the camera at its maximum speed.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DeviceMaxThroughput;

		/**
		 * Description: Selects which Connection of the device to control.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &DeviceConnectionSelector;

		/**
		 * Description: Indicates the speed of transmission of the specified Connection
		 * Visibility: Expert
		 */
		GenApi::IInteger &DeviceConnectionSpeed;

		/**
		 * Description: Indicates the status of the specified Connection.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceConnectionStatusEnums> &DeviceConnectionStatus;

		/**
		 * Description: Selects which Link of the device to control.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &DeviceLinkSelector;

		/**
		 * Description: Indicates the speed of transmission negotiated on the specified Link.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DeviceLinkSpeed;

		/**
		 * Description: Controls if the DeviceLinkThroughputLimit is active. When disabled, lower level TL specific features are expected to control the throughput. When enabled, DeviceLinkThroughputLimit controls the overall throughput.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceLinkThroughputLimitModeEnums> &DeviceLinkThroughputLimitMode;

		/**
		 * Description: Limits the maximum bandwidth of the data that will be streamed out by the device on the selected Link. If necessary, delays will be uniformly inserted between transport layer packets in order to control the peak bandwidth.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DeviceLinkThroughputLimit;

		/**
		 * Description: Returns the number of physical connection of the device used by a particular Link.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &DeviceLinkConnectionCount;

		/**
		 * Description: Activate or deactivate the Link's heartbeat.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceLinkHeartbeatModeEnums> &DeviceLinkHeartbeatMode;

		/**
		 * Description: Controls the current heartbeat timeout of the specific Link.
		 * Visibility: Guru
		 */
		GenApi::IFloat &DeviceLinkHeartbeatTimeout;

		/**
		 * Description: Indicates the command timeout of the specified Link. This corresponds to the maximum response time of the device for a command sent on that link.
		 * Visibility: Guru
		 */
		GenApi::IFloat &DeviceLinkCommandTimeout;

		/**
		 * Description: Indicates the number of streaming channels supported by the device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DeviceStreamChannelCount;

		/**
		 * Description: Selects the stream channel to control.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DeviceStreamChannelSelector;

		/**
		 * Description: Reports the type of the stream channel.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<DeviceStreamChannelTypeEnums> &DeviceStreamChannelType;

		/**
		 * Description: Index of device's Link to use for streaming the specifed stream channel.
		 * Visibility: Guru
		 */
		GenApi::IInteger &DeviceStreamChannelLink;

		/**
		 * Description: Endianess of multi-byte pixel data for this stream.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<DeviceStreamChannelEndiannessEnums> &DeviceStreamChannelEndianness;

		/**
		 * Description: Specifies the stream packet size, in bytes, to send on the selected channel for a Transmitter or specifies the maximum packet size supported by a receiver.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DeviceStreamChannelPacketSize;

		/**
		 * Description: Indicates the number of event channels supported by the device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DeviceEventChannelCount;

		/**
		 * Description: Character set used by the strings of the device's bootstrap registers.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<DeviceCharacterSetEnums> &DeviceCharacterSet;

		/**
		 * Description: Resets the device to its power up state. After reset, the device must be rediscovered.
		 * Visibility: Guru
		 */
		GenApi::ICommand &DeviceReset;

		/**
		 * Description: Controls the behavior of the indicators (such as LEDs) showing the status of the Device.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceIndicatorModeEnums> &DeviceIndicatorMode;

		/**
		 * Description: Indicate to the device and GenICam XML to get ready for persisting of all streamable features.
		 * Visibility: Guru
		 */
		GenApi::ICommand &DeviceFeaturePersistenceStart;

		/**
		 * Description: Indicate to the device the end of feature persistence.
		 * Visibility: Guru
		 */
		GenApi::ICommand &DeviceFeaturePersistenceEnd;

		/**
		 * Description: Prepare the device for registers streaming without checking for consistency.
		 * Visibility: Guru
		 */
		GenApi::ICommand &DeviceRegistersStreamingStart;

		/**
		 * Description: Announce the end of registers streaming. This will do a register set validation for consistency and activate it. This will also update the DeviceRegistersValid flag.
		 * Visibility: Guru
		 */
		GenApi::ICommand &DeviceRegistersStreamingEnd;

		/**
		 * Description: Perform the validation of the current register set for consistency. This will update the DeviceRegistersValid flag.
		 * Visibility: Expert
		 */
		GenApi::ICommand &DeviceRegistersCheck;

		/**
		 * Description: Returns if the current register set is valid and consistent.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &DeviceRegistersValid;

		/**
		 * Description: Endianess of the registers of the device.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<DeviceRegistersEndiannessEnums> &DeviceRegistersEndianness;

		/**
		 * Description: Selects the location within the device, where the temperature will be measured.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceTemperatureSelectorEnums> &DeviceTemperatureSelector;

		/**
		 * Description: Device temperature in degrees Celsius (C). It is measured at the location selected by DeviceTemperatureSelector.
		 * Visibility: Expert
		 */
		GenApi::IFloat &DeviceTemperature;

		/**
		 * Description: Selects the clock frequency to access from the device.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceClockSelectorEnums> &DeviceClockSelector;

		/**
		 * Description: Returns the frequency of the selected Clock.
		 * Visibility: Expert
		 */
		GenApi::IFloat &DeviceClockFrequency;

		/**
		 * Description: Selects which serial port of the device to control.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceSerialPortSelectorEnums> &DeviceSerialPortSelector;

		/**
		 * Description: This feature controls the baud rate used by the selected serial port.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceSerialPortBaudRateEnums> &DeviceSerialPortBaudRate;

		/**
		 * Description: Reports the current value of the device timestamp counter.
		 * Visibility: Expert
		 */
		GenApi::IInteger &Timestamp;

		/**
		 * Description: Resets the current value of the device timestamp counter.
		 * Visibility: Expert
		 */
		GenApi::ICommand &TimestampReset;

		/**
		 * Description: Latches the current timestamp counter into TimestampLatchValue.
		 * Visibility: Expert
		 */
		GenApi::ICommand &TimestampLatch;

		/**
		 * Description: Returns the latched value of the timestamp counter.
		 * Visibility: Expert
		 */
		GenApi::IInteger &TimestampLatchValue;

		/**
		 * Description: Effective width of the sensor in pixels.
		 * Visibility: Expert
		 */
		GenApi::IInteger &SensorWidth;

		/**
		 * Description: Effective height of the sensor in pixels.
		 * Visibility: Expert
		 */
		GenApi::IInteger &SensorHeight;

		/**
		 * Description: Number of taps of the camera sensor.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<SensorTapsEnums> &SensorTaps;

		/**
		 * Description: Number of digitized samples outputted simultaneously by the camera A/D conversion stage.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<SensorDigitizationTapsEnums> &SensorDigitizationTaps;

		/**
		 * Description: Maximum width of the image (in pixels). The dimension is calculated after horizontal binning, decimation or any other function changing the horizontal dimension of the image.
		 * Visibility: Expert
		 */
		GenApi::IInteger &WidthMax;

		/**
		 * Description: Maximum height of the image (in pixels). This dimension is calculated after vertical binning, decimation or any other function changing the vertical dimension of the image
		 * Visibility: Expert
		 */
		GenApi::IInteger &HeightMax;

		/**
		 * Description: Selects the Region of interest to control. The RegionSelector feature allows devices that are able to extract multiple regions out of an image, to configure the features of those individual regions independently.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<RegionSelectorEnums> &RegionSelector;

		/**
		 * Description: Controls if the selected Region of interest is active and streaming.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<RegionModeEnums> &RegionMode;

		/**
		 * Description: Control the destination of the selected region.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<RegionDestinationEnums> &RegionDestination;

		/**
		 * Description: Selects a component to activate data streaming from.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<ImageComponentSelectorEnums> &ImageComponentSelector;

		/**
		 * Description: Controls if the selected component streaming is active.
		 * Visibility: Beginner
		 */
		GenApi::IBoolean &ImageComponentEnable;

		/**
		 * Description: Width of the image provided by the device (in pixels).
		 * Visibility: Beginner
		 */
		GenApi::IInteger &Width;

		/**
		 * Description: Height of the image provided by the device (in pixels).
		 * Visibility: Beginner
		 */
		GenApi::IInteger &Height;

		/**
		 * Description: Horizontal offset from the origin to the region of interest (in pixels).
		 * Visibility: Beginner
		 */
		GenApi::IInteger &OffsetX;

		/**
		 * Description: Vertical offset from the origin to the region of interest (in pixels).
		 * Visibility: Beginner
		 */
		GenApi::IInteger &OffsetY;

		/**
		 * Description: Total number of bytes between 2 successive lines. This feature is used to facilitate alignment of image data.
		 * Visibility: Expert
		 */
		GenApi::IInteger &LinePitch;

		/**
		 * Description: Selects which binning engine is controlled by the BinningHorizontal and BinningVertical features.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<BinningSelectorEnums> &BinningSelector;

		/**
		 * Description: Sets the mode to use to combine horizontal photo-sensitive cells together when BinningHorizontal is used.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<BinningHorizontalModeEnums> &BinningHorizontalMode;

		/**
		 * Description: Number of horizontal photo-sensitive cells to combine together. This reduces the horizontal resolution (width) of the image.
		 * Visibility: Expert
		 */
		GenApi::IInteger &BinningHorizontal;

		/**
		 * Description: Sets the mode used to combine horizontal photo-sensitive cells together when BinningVertical is used.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<BinningVerticalModeEnums> &BinningVerticalMode;

		/**
		 * Description: Number of vertical photo-sensitive cells to combine together. This reduces the vertical resolution (height) of the image.
		 * Visibility: Expert
		 */
		GenApi::IInteger &BinningVertical;

		/**
		 * Description: Sets the mode used to reduce the horizontal resolution when DecimationHorizontal is used.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DecimationHorizontalModeEnums> &DecimationHorizontalMode;

		/**
		 * Description: Horizontal sub-sampling of the image. This reduces the horizontal resolution (width) of the image by the specified horizontal decimation factor.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DecimationHorizontal;

		/**
		 * Description: Sets the mode used to reduce the Vertical resolution when DecimationVertical is used.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DecimationVerticalModeEnums> &DecimationVerticalMode;

		/**
		 * Description: Vertical sub-sampling of the image. This reduces the vertical resolution (height) of the image by the specified vertical decimation factor.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DecimationVertical;

		/**
		 * Description: Flip horizontally the image sent by the device. The Region of interest is applied after the flipping.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &ReverseX;

		/**
		 * Description: Flip vertically the image sent by the device. The Region of interest is applied after the flipping.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &ReverseY;

		/**
		 * Description: Format of the pixels provided by the device. It represents all the information provided by PixelSize, PixelColorFilter combined in a single feature.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<PixelFormatEnums> &PixelFormat;

		/**
		 * Description: Select the pixel format for which the information will be returned.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<PixelFormatInfoSelectorEnums> &PixelFormatInfoSelector;

		/**
		 * Description: Returns the value used by the streaming channels to identify the selected pixel format.
		 * Visibility: Guru
		 */
		GenApi::IInteger &PixelFormatInfoID;

		/**
		 * Description: Total size in bits of a pixel of the image.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<PixelSizeEnums> &PixelSize;

		/**
		 * Description: Type of color filter that is applied to the image.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<PixelColorFilterEnums> &PixelColorFilter;

		/**
		 * Description: Minimum value that can be returned during the digitization process. This corresponds to the darkest value of the camera. For color camera, this returns the smallest value that each color component can take.
		 * Visibility: Expert
		 */
		GenApi::IInteger &PixelDynamicRangeMin;

		/**
		 * Description: Maximum value that will be returned during the digitization process. This corresponds to the brightest value of the camera. For color camera, this returns the biggest value that each color component can take.
		 * Visibility: Expert
		 */
		GenApi::IInteger &PixelDynamicRangeMax;

		/**
		 * Description: Selects which test pattern generator is controlled by the TestPattern feature.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<TestPatternGeneratorSelectorEnums> &TestPatternGeneratorSelector;

		/**
		 * Description: Selects the type of test pattern that is generated by the device as image source.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<TestPatternEnums> &TestPattern;

		/**
		 * Description: Controls how the device performs de-interlacing.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<DeinterlacingEnums> &Deinterlacing;

		/**
		 * Description: Enable a specific image compression mode as the base mode for image transfer. Optionally, chunk data can be appended to the compressed image (See chunk section).
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<ImageCompressionModeEnums> &ImageCompressionMode;

		/**
		 * Description: Two rate controlling options are offered: fixed bit rate or fixed quality. The exact implementation to achieve one or the other is vendor-specific.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ImageCompressionRateOptionEnums> &ImageCompressionRateOption;

		/**
		 * Description: Control the quality of the produced compressed stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ImageCompressionQuality;

		/**
		 * Description: Control the rate of the produced compressed stream.
		 * Visibility: Expert
		 */
		GenApi::IFloat &ImageCompressionBitrate;

		/**
		 * Description: When JPEG is selected as the compression format, a device might optionally offer better control over JPEG-specific options through this feature.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ImageCompressionJPEGFormatOptionEnums> &ImageCompressionJPEGFormatOption;

		/**
		 * Description: Sets the shutter mode of the device.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<SensorShutterModeEnums> &SensorShutterMode;

		/**
		 * Description: Sets the acquisition mode of the device. It defines mainly the number of frames to capture during an acquisition and the way the acquisition stops.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<AcquisitionModeEnums> &AcquisitionMode;

		/**
		 * Description: Starts the Acquisition of the device. The number of frames captured is specified by AcquisitionMode.
		 * Visibility: Beginner
		 */
		GenApi::ICommand &AcquisitionStart;

		/**
		 * Description: Stops the Acquisition of the device at the end of the current Frame. It is mainly used when AcquisitionMode is Continuous but can be used in any acquisition mode.
		 * Visibility: Beginner
		 */
		GenApi::ICommand &AcquisitionStop;

		/**
		 * Description: Aborts the Acquisition immediately. This will end the capture without completing the current Frame or waiting on a trigger. If no Acquisition is in progress, the command is ignored.
		 * Visibility: Expert
		 */
		GenApi::ICommand &AcquisitionAbort;

		/**
		 * Description: Arms the device before an AcquisitionStart command. This optional command validates all the current features for consistency and prepares the device for a fast start of the Acquisition.
		 * Visibility: Expert
		 */
		GenApi::ICommand &AcquisitionArm;

		/**
		 * Description: Number of frames to acquire in MultiFrame Acquisition mode.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &AcquisitionFrameCount;

		/**
		 * Description: Number of frames to acquire for each FrameBurstStart trigger.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &AcquisitionBurstFrameCount;

		/**
		 * Description: Controls the acquisition rate (in Hertz) at which the frames are captured.
		 * Visibility: Beginner
		 */
		GenApi::IFloat &AcquisitionFrameRate;

		/**
		 * Description: Controls the rate (in Hertz) at which the Lines in a Frame are captured.
		 * Visibility: Beginner
		 */
		GenApi::IFloat &AcquisitionLineRate;

		/**
		 * Description: Selects the internal acquisition signal to read using AcquisitionStatus.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<AcquisitionStatusSelectorEnums> &AcquisitionStatusSelector;

		/**
		 * Description: Reads the state of the internal acquisition signal selected using AcquisitionStatusSelector.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &AcquisitionStatus;

		/**
		 * Description: Selects the type of trigger to configure.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<TriggerSelectorEnums> &TriggerSelector;

		/**
		 * Description: Controls if the selected trigger is active.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<TriggerModeEnums> &TriggerMode;

		/**
		 * Description: Generates an internal trigger. TriggerSource must be set to Software.
		 * Visibility: Beginner
		 */
		GenApi::ICommand &TriggerSoftware;

		/**
		 * Description: Specifies the internal signal or physical input Line to use as the trigger source. The selected trigger must have its TriggerMode set to On.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<TriggerSourceEnums> &TriggerSource;

		/**
		 * Description: Specifies the activation mode of the trigger.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<TriggerActivationEnums> &TriggerActivation;

		/**
		 * Description: Specifies the type trigger overlap permitted with the previous frame or line. This defines when a valid trigger will be accepted (or latched) for a new frame or a new line.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<TriggerOverlapEnums> &TriggerOverlap;

		/**
		 * Description: Specifies the delay in microseconds (us) to apply after the trigger reception before activating it.
		 * Visibility: Expert
		 */
		GenApi::IFloat &TriggerDelay;

		/**
		 * Description: Specifies a division factor for the incoming trigger pulses.
		 * Visibility: Expert
		 */
		GenApi::IInteger &TriggerDivider;

		/**
		 * Description: Specifies a multiplication factor for the incoming trigger pulses. It is used generally used in conjunction with TriggerDivider to control the ratio of triggers that are accepted.
		 * Visibility: Expert
		 */
		GenApi::IInteger &TriggerMultiplier;

		/**
		 * Description: Sets the operation mode of the Exposure.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<ExposureModeEnums> &ExposureMode;

		/**
		 * Description: Sets the configuration mode of the ExposureTime feature.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<ExposureTimeModeEnums> &ExposureTimeMode;

		/**
		 * Description: Selects which exposure time is controlled by the ExposureTime feature. This allows for independent control over the exposure components.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<ExposureTimeSelectorEnums> &ExposureTimeSelector;

		/**
		 * Description: Sets the Exposure time when ExposureMode is Timed and ExposureAuto is Off. This controls the duration where the photosensitive cells are exposed to light.
		 * Visibility: Beginner
		 */
		GenApi::IFloat &ExposureTime;

		/**
		 * Description: Sets the automatic exposure mode when ExposureMode is Timed. The exact algorithm used to implement this control is device-specific.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<ExposureAutoEnums> &ExposureAuto;

		/**
		 * Description: Selects which Gain is controlled by the various Gain features.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<GainSelectorEnums> &GainSelector;

		/**
		 * Description: Controls the selected gain as an absolute physical value. This is an amplification factor applied to the video signal.
		 * Visibility: Beginner
		 */
		GenApi::IFloat &Gain;

		/**
		 * Description: Sets the automatic gain control (AGC) mode. The exact algorithm used to implement AGC is device-specific.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<GainAutoEnums> &GainAuto;

		/**
		 * Description: Sets the mode for automatic gain balancing between the sensor color channels or taps. The gain coefficients of each channel or tap are adjusted so they are matched.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<GainAutoBalanceEnums> &GainAutoBalance;

		/**
		 * Description: Selects which Black Level is controlled by the various Black Level features.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<BlackLevelSelectorEnums> &BlackLevelSelector;

		/**
		 * Description: Controls the analog black level as an absolute physical value. This represents a DC offset applied to the video signal.
		 * Visibility: Expert
		 */
		GenApi::IFloat &BlackLevel;

		/**
		 * Description: Controls the mode for automatic black level adjustment. The exact algorithm used to implement this adjustment is device-specific.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<BlackLevelAutoEnums> &BlackLevelAuto;

		/**
		 * Description: Controls the mode for automatic black level balancing between the sensor color channels or taps. The black level coefficients of each channel are adjusted so they are matched.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<BlackLevelAutoBalanceEnums> &BlackLevelAutoBalance;

		/**
		 * Description: Selects which White Clip to control.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<WhiteClipSelectorEnums> &WhiteClipSelector;

		/**
		 * Description: Controls the maximal intensity taken by the video signal before being clipped as an absolute physical value. The video signal will never exceed the white clipping point: it will saturate at that level.
		 * Visibility: Expert
		 */
		GenApi::IFloat &WhiteClip;

		/**
		 * Description: Selects which Balance ratio to control.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<BalanceRatioSelectorEnums> &BalanceRatioSelector;

		/**
		 * Description: Controls ratio of the selected color component to a reference color component. It is used for white balancing.
		 * Visibility: Expert
		 */
		GenApi::IFloat &BalanceRatio;

		/**
		 * Description: Controls the mode for automatic white balancing between the color channels. The white balancing ratios are automatically adjusted.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<BalanceWhiteAutoEnums> &BalanceWhiteAuto;

		/**
		 * Description: Controls the gamma correction of pixel intensity. This is typically used to compensate for non-linearity of the display system (such as CRT).
		 * Visibility: Beginner
		 */
		GenApi::IFloat &Gamma;

		/**
		 * Description: Selects which LUT to control.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<LUTSelectorEnums> &LUTSelector;

		/**
		 * Description: Activates the selected LUT.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &LUTEnable;

		/**
		 * Description: Control the index (offset) of the coefficient to access in the selected LUT.
		 * Visibility: Guru
		 */
		GenApi::IInteger &LUTIndex;

		/**
		 * Description: Returns the Value at entry LUTIndex of the LUT selected by LUTSelector.
		 * Visibility: Guru
		 */
		GenApi::IInteger &LUTValue;

		/**
		 * Description: Accesses all the LUT coefficients in a single access without using individual LUTIndex.
		 * Visibility: Guru
		 */
		GenApi::IRegister &LUTValueAll;

		/**
		 * Description: Selects which Color Transformation module is controlled by the various Color Transformation features.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ColorTransformationSelectorEnums> &ColorTransformationSelector;

		/**
		 * Description: Activates the selected Color Transformation module.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &ColorTransformationEnable;

		/**
		 * Description: Selects the Gain factor or Offset of the Transformation matrix to access in the selected Color Transformation module.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ColorTransformationValueSelectorEnums> &ColorTransformationValueSelector;

		/**
		 * Description: Represents the value of the selected Gain factor or Offset inside the Transformation matrix.
		 * Visibility: Expert
		 */
		GenApi::IFloat &ColorTransformationValue;

		/**
		 * Description: Selects the physical line (or pin) of the external device connector or the virtual line of the Transport Layer to configure.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<LineSelectorEnums> &LineSelector;

		/**
		 * Description: Controls if the physical Line is used to Input or Output a signal.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<LineModeEnums> &LineMode;

		/**
		 * Description: Controls the inversion of the signal of the selected input or output Line.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &LineInverter;

		/**
		 * Description: Returns the current status of the selected input or output Line.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &LineStatus;

		/**
		 * Description: Returns the current status of all available Line signals at time of polling in a single bitfield.
		 * Visibility: Expert
		 */
		GenApi::IInteger &LineStatusAll;

		/**
		 * Description: Selects which internal acquisition or I/O source signal to output on the selected Line. LineMode must be Output.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<LineSourceEnums> &LineSource;

		/**
		 * Description: Controls the current electrical format of the selected physical input or output Line.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<LineFormatEnums> &LineFormat;

		/**
		 * Description: Selects which bit of the User Output register will be set by UserOutputValue.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<UserOutputSelectorEnums> &UserOutputSelector;

		/**
		 * Description: Sets the value of the bit selected by UserOutputSelector.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &UserOutputValue;

		/**
		 * Description: Sets the value of all the bits of the User Output register. It is subject to the UserOutputValueAllMask.
		 * Visibility: Expert
		 */
		GenApi::IInteger &UserOutputValueAll;

		/**
		 * Description: Sets the write mask to apply to the value specified by UserOutputValueAll before writing it in the User Output register. If the UserOutputValueAllMask feature is present, setting the user Output register using UserOutputValueAll will only change the bits that have a corresponding bit in the mask set to one.
		 * Visibility: Expert
		 */
		GenApi::IInteger &UserOutputValueAllMask;

		/**
		 * Description: Selects which Counter to configure.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<CounterSelectorEnums> &CounterSelector;

		/**
		 * Description: Select the events that will be the source to increment the Counter.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<CounterEventSourceEnums> &CounterEventSource;

		/**
		 * Description: Selects the Activation mode Event Source signal.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<CounterEventActivationEnums> &CounterEventActivation;

		/**
		 * Description: Selects the signals that will be the source to reset the Counter.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<CounterResetSourceEnums> &CounterResetSource;

		/**
		 * Description: Selects the Activation mode of the Counter Reset Source signal.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<CounterResetActivationEnums> &CounterResetActivation;

		/**
		 * Description: Does a software reset of the selected Counter and starts it. The counter starts counting events immediately after the reset unless a Counter trigger is active. CounterReset can be used to reset the Counter independently from the CounterResetSource. To disable the counter temporarily, set CounterEventSource to Off.
		 * Visibility: Expert
		 */
		GenApi::ICommand &CounterReset;

		/**
		 * Description: Reads or writes the current value of the selected Counter.
		 * Visibility: Expert
		 */
		GenApi::IInteger &CounterValue;

		/**
		 * Description: Reads the value of the selected Counter when it was reset by a trigger or by an explicit CounterReset command.
		 * Visibility: Expert
		 */
		GenApi::IInteger &CounterValueAtReset;

		/**
		 * Description: Sets the duration (or number of events) before the CounterEnd event is generated.
		 * Visibility: Expert
		 */
		GenApi::IInteger &CounterDuration;

		/**
		 * Description: Returns the current status of the Counter.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<CounterStatusEnums> &CounterStatus;

		/**
		 * Description: Selects the source to start the Counter.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<CounterTriggerSourceEnums> &CounterTriggerSource;

		/**
		 * Description: Selects the activation mode of the trigger to start the Counter.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<CounterTriggerActivationEnums> &CounterTriggerActivation;

		/**
		 * Description: Selects which Timer to configure.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<TimerSelectorEnums> &TimerSelector;

		/**
		 * Description: Sets the duration (in microseconds) of the Timer pulse.
		 * Visibility: Expert
		 */
		GenApi::IFloat &TimerDuration;

		/**
		 * Description: Sets the duration (in microseconds) of the delay to apply at the reception of a trigger before starting the Timer.
		 * Visibility: Expert
		 */
		GenApi::IFloat &TimerDelay;

		/**
		 * Description: Does a software reset of the selected timer and starts it. The timer starts immediately after the reset unless a timer trigger is active.
		 * Visibility: Expert
		 */
		GenApi::ICommand &TimerReset;

		/**
		 * Description: Reads or writes the current value (in microseconds) of the selected Timer.
		 * Visibility: Expert
		 */
		GenApi::IFloat &TimerValue;

		/**
		 * Description: Returns the current status of the Timer.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<TimerStatusEnums> &TimerStatus;

		/**
		 * Description: Selects the source of the trigger to start the Timer.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<TimerTriggerSourceEnums> &TimerTriggerSource;

		/**
		 * Description: Selects the activation mode of the trigger to start the Timer.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<TimerTriggerActivationEnums> &TimerTriggerActivation;

		/**
		 * Description: Selects which Encoder to configure.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<EncoderSelectorEnums> &EncoderSelector;

		/**
		 * Description: Selects the signal which will be the source of the A input of the Encoder.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<EncoderSourceAEnums> &EncoderSourceA;

		/**
		 * Description: Selects the signal which will be the source of the B input of the Encoder.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<EncoderSourceBEnums> &EncoderSourceB;

		/**
		 * Description: Selects if the count of encoder uses FourPhase mode with jitter filtering or the HighResolution mode without jitter filtering.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<EncoderModeEnums> &EncoderMode;

		/**
		 * Description: Sets how many Encoder increment/decrements that are needed generate an Encoder output pulse signal.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EncoderDivider;

		/**
		 * Description: Selects the conditions for the Encoder interface to generate a valid Encoder output signal.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<EncoderOutputModeEnums> &EncoderOutputMode;

		/**
		 * Description: Returns the motion status of the encoder.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<EncoderStatusEnums> &EncoderStatus;

		/**
		 * Description: Sets the maximum time interval between encoder counter increments before the status turns to static.
		 * Visibility: Expert
		 */
		GenApi::IFloat &EncoderTimeout;

		/**
		 * Description: Selects the signals that will be the source to reset the Encoder.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<EncoderResetSourceEnums> &EncoderResetSource;

		/**
		 * Description: Selects the Activation mode of the Encoder Reset Source signal.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<EncoderResetActivationEnums> &EncoderResetActivation;

		/**
		 * Description: Does a software reset of the selected Encoder and starts it. The Encoder starts counting events immediately after the reset. EncoderReset can be used to reset the Encoder independently from the EncoderResetSource.
		 * Visibility: Expert
		 */
		GenApi::ICommand &EncoderReset;

		/**
		 * Description: Reads or writes the current value of the position counter of the selected Encoder.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EncoderValue;

		/**
		 * Description: Reads the value of the of the position counter of the selected Encoder when it was reset by a signal or by an explicit EncoderReset command.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EncoderValueAtReset;

		/**
		 * Description: Selects which Software Signal features to control.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<SoftwareSignalSelectorEnums> &SoftwareSignalSelector;

		/**
		 * Description: Generates a pulse signal that can be used as a software trigger. This command can be used to trigger other modules that accept a SoftwareSignal as trigger source.
		 * Visibility: Beginner
		 */
		GenApi::ICommand &SoftwareSignalPulse;

		/**
		 * Description: Enables the unconditional action command mode where action commands are processed even when the primary control channel is closed.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<ActionUnconditionalModeEnums> &ActionUnconditionalMode;

		/**
		 * Description: Provides the device key that allows the device to check the validity of action commands. The device internal assertion of an action signal is only authorized if the ActionDeviceKey and the action device key value in the protocol message are equal.
		 * Visibility: Guru
		 */
		GenApi::IInteger &ActionDeviceKey;

		/**
		 * Description: Indicates the size of the scheduled action commands queue. This number represents the maximum number of scheduled action commands that can be pending at a given point in time.
		 * Visibility: Guru
		 */
		GenApi::IInteger &ActionQueueSize;

		/**
		 * Description: Selects to which Action Signal further Action settings apply.
		 * Visibility: Guru
		 */
		GenApi::IInteger &ActionSelector;

		/**
		 * Description: Provides the mask that the device will use to validate the action on reception of the action protocol message.
		 * Visibility: Guru
		 */
		GenApi::IInteger &ActionGroupMask;

		/**
		 * Description: Provides the key that the device will use to validate the action on reception of the action protocol message.
		 * Visibility: Guru
		 */
		GenApi::IInteger &ActionGroupKey;

		/**
		 * Description: Selects which Event to signal to the host application.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<EventSelectorEnums> &EventSelector;

		/**
		 * Description: Activate or deactivate the notification to the host application of the occurrence of the selected Event.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<EventNotificationEnums> &EventNotification;

		/**
		 * Description: Returns the unique Identifier of the Acquisition Trigger type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionTrigger;

		/**
		 * Description: Returns the Timestamp of the Acquisition Trigger Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionTriggerTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Acquisition Trigger Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionTriggerFrameID;

		/**
		 * Description: Returns the unique Identifier of the Acquisition Start type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionStart;

		/**
		 * Description: Returns the Timestamp of the Acquisition Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionStartTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Acquisition Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionStartFrameID;

		/**
		 * Description: Returns the unique Identifier of the Acquisition End type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionEnd;

		/**
		 * Description: Returns the Timestamp of the Acquisition End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionEndTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Acquisition End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionEndFrameID;

		/**
		 * Description: Returns the unique Identifier of the Acquisition Transfer Start type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionTransferStart;

		/**
		 * Description: Returns the Timestamp of the Acquisition Transfer Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionTransferStartTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Acquisition Transfer Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionTransferStartFrameID;

		/**
		 * Description: Returns the unique Identifier of the Acquisition Transfer End type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionTransferEnd;

		/**
		 * Description: Returns the Timestamp of the Acquisition Transfer End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionTransferEndTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Acquisition Transfer End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionTransferEndFrameID;

		/**
		 * Description: Returns the unique Identifier of the Acquisition Error type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionError;

		/**
		 * Description: Returns the Timestamp of the Acquisition Error Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionErrorTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Acquisition Error Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventAcquisitionErrorFrameID;

		/**
		 * Description: Returns the unique Identifier of the FrameTrigger type of Event. It can be used to register a callback function to be notified of the event occurrence. Its value uniquely identifies the type event received.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameTrigger;

		/**
		 * Description: Returns the Timestamp of the FrameTrigger Event. It can be used to determine precisely when the event occurred.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameTriggerTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the FrameTrigger Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameTriggerFrameID;

		/**
		 * Description: Returns the unique Identifier of the Frame Start type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameStart;

		/**
		 * Description: Returns the Timestamp of the Frame Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameStartTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Frame Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameStartFrameID;

		/**
		 * Description: Returns the unique Identifier of the Frame End type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameEnd;

		/**
		 * Description: Returns the Timestamp of the Frame End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameEndTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Frame End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameEndFrameID;

		/**
		 * Description: Returns the unique Identifier of the Frame Burst Start type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameBurstStart;

		/**
		 * Description: Returns the Timestamp of the Frame Burst Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameBurstStartTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Frame Burst Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameBurstStartFrameID;

		/**
		 * Description: Returns the unique Identifier of the Frame Burst End type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameBurstEnd;

		/**
		 * Description: Returns the Timestamp of the Frame Burst End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameBurstEndTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Frame Burst End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameBurstEndFrameID;

		/**
		 * Description: Returns the unique Identifier of the Frame Transfer Start type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameTransferStart;

		/**
		 * Description: Returns the Timestamp of the Frame Transfer Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameTransferStartTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Frame Transfer Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameTransferStartFrameID;

		/**
		 * Description: Returns the unique Identifier of the Frame Transfer End type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameTransferEnd;

		/**
		 * Description: Returns the Timestamp of the Frame Transfer End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameTransferEndTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Frame Transfer End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventFrameTransferEndFrameID;

		/**
		 * Description: Returns the unique Identifier of the Exposure Start type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventExposureStart;

		/**
		 * Description: Returns the Timestamp of the Exposure Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventExposureStartTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Exposure Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventExposureStartFrameID;

		/**
		 * Description: Returns the unique identifier of the ExposureEnd type of Event. This feature can be used to register a callback function to be notified of the event occurrence. Its value uniquely identifies the type of event that will be received.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventExposureEnd;

		/**
		 * Description: Returns the Timestamp of the ExposureEnd Event. It can be used to determine precisely when the event occurred.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventExposureEndTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the ExposureEnd Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventExposureEndFrameID;

		/**
		 * Description: Returns the unique Identifier of the Stream 0 Transfer Start type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferStart;

		/**
		 * Description: Returns the Timestamp of the Stream 0 Transfer Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferStartTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferStartFrameID;

		/**
		 * Description: Returns the unique Identifier of the Stream 0 Transfer End type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferEnd;

		/**
		 * Description: Returns the Timestamp of the Stream 0 Transfer End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferEndTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferEndFrameID;

		/**
		 * Description: Returns the unique Identifier of the Stream 0 Transfer Pause type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferPause;

		/**
		 * Description: Returns the Timestamp of the Stream 0 Transfer Pause Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferPauseTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Pause Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferPauseFrameID;

		/**
		 * Description: Returns the unique Identifier of the Stream 0 Transfer Resume type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferResume;

		/**
		 * Description: Returns the Timestamp of the Stream 0 Transfer Resume Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferResumeTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Resume Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferResumeFrameID;

		/**
		 * Description: Returns the unique Identifier of the Stream 0 Transfer Block Start type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBlockStart;

		/**
		 * Description: Returns the Timestamp of the Stream 0 Transfer Block Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBlockStartTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Block Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBlockStartFrameID;

		/**
		 * Description: Returns the unique Identifier of the Stream 0 Transfer Block End type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBlockEnd;

		/**
		 * Description: Returns the Timestamp of the Stream 0 Transfer Block End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBlockEndTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Block End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBlockEndFrameID;

		/**
		 * Description: Returns the unique Identifier of the Stream 0 Transfer Block Trigger type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBlockTrigger;

		/**
		 * Description: Returns the Timestamp of the Stream 0 Transfer Block Trigger Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBlockTriggerTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Block Trigger Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBlockTriggerFrameID;

		/**
		 * Description: Returns the unique Identifier of the Stream 0 Transfer Burst Start type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBurstStart;

		/**
		 * Description: Returns the Timestamp of the Stream 0 Transfer Burst Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBurstStartTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Burst Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBurstStartFrameID;

		/**
		 * Description: Returns the unique Identifier of the Stream 0 Transfer Burst End type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBurstEnd;

		/**
		 * Description: Returns the Timestamp of the Stream 0 Transfer Burst End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBurstEndTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Burst End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferBurstEndFrameID;

		/**
		 * Description: Returns the unique Identifier of the Stream 0 Transfer Overflow type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferOverflow;

		/**
		 * Description: Returns the Timestamp of the Stream 0 Transfer Overflow Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferOverflowTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Overflow Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventStream0TransferOverflowFrameID;

		/**
		 * Description: Returns the unique Identifier of the Sequencer Set Change type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventSequencerSetChange;

		/**
		 * Description: Returns the Timestamp of the Sequencer Set Change Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventSequencerSetChangeTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Sequencer Set Change Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventSequencerSetChangeFrameID;

		/**
		 * Description: Returns the unique Identifier of the Counter 0 Start type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventCounter0Start;

		/**
		 * Description: Returns the Timestamp of the Counter 0 Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventCounter0StartTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Counter 0 Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventCounter0StartFrameID;

		/**
		 * Description: Returns the unique Identifier of the Counter 1 Start type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventCounter1Start;

		/**
		 * Description: Returns the Timestamp of the Counter 1 Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventCounter1StartTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Counter 1 Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventCounter1StartFrameID;

		/**
		 * Description: Returns the unique Identifier of the Counter 0 End type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventCounter0End;

		/**
		 * Description: Returns the Timestamp of the Counter 0 End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventCounter0EndTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Counter 0 End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventCounter0EndFrameID;

		/**
		 * Description: Returns the unique Identifier of the Counter 1 End type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventCounter1End;

		/**
		 * Description: Returns the Timestamp of the Counter 1 End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventCounter1EndTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Counter 1 End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventCounter1EndFrameID;

		/**
		 * Description: Returns the unique Identifier of the Timer 0 Start type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventTimer0Start;

		/**
		 * Description: Returns the Timestamp of the Timer 0 Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventTimer0StartTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Timer 0 Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventTimer0StartFrameID;

		/**
		 * Description: Returns the unique Identifier of the Timer 1 Start type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventTimer1Start;

		/**
		 * Description: Returns the Timestamp of the Timer 1 Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventTimer1StartTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Timer 1 Start Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventTimer1StartFrameID;

		/**
		 * Description: Returns the unique Identifier of the Timer 0 End type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventTimer0End;

		/**
		 * Description: Returns the Timestamp of the Timer 0 End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventTimer0EndTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Timer 0 End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventTimer0EndFrameID;

		/**
		 * Description: Returns the unique Identifier of the Timer 1 End type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventTimer1End;

		/**
		 * Description: Returns the Timestamp of the Timer 1 End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventTimer1EndTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Timer 1 End Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventTimer1EndFrameID;

		/**
		 * Description: Returns the unique Identifier of the Encoder 0 Stopped type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventEncoder0Stopped;

		/**
		 * Description: Returns the Timestamp of the Encoder 0 Stopped Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventEncoder0StoppedTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Encoder 0 Stopped Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventEncoder0StoppedFrameID;

		/**
		 * Description: Returns the unique Identifier of the Encoder 1 Stopped type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventEncoder1Stopped;

		/**
		 * Description: Returns the Timestamp of the Encoder 1 Stopped Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventEncoder1StoppedTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Encoder 1 Stopped Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventEncoder1StoppedFrameID;

		/**
		 * Description: Returns the unique Identifier of the Encoder 0 Restarted type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventEncoder0Restarted;

		/**
		 * Description: Returns the Timestamp of the Encoder 0 Restarted Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventEncoder0RestartedTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Encoder 0 Restarted Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventEncoder0RestartedFrameID;

		/**
		 * Description: Returns the unique Identifier of the Encoder 1 Restarted type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventEncoder1Restarted;

		/**
		 * Description: Returns the Timestamp of the Encoder 1 Restarted Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventEncoder1RestartedTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Encoder 1 Restarted Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventEncoder1RestartedFrameID;

		/**
		 * Description: Returns the unique Identifier of the Line 0 Rising Edge type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine0RisingEdge;

		/**
		 * Description: Returns the Timestamp of the Line 0 Rising Edge Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine0RisingEdgeTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Line 0 Rising Edge Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine0RisingEdgeFrameID;

		/**
		 * Description: Returns the unique Identifier of the Line 1 Rising Edge type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine1RisingEdge;

		/**
		 * Description: Returns the Timestamp of the Line 1 Rising Edge Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine1RisingEdgeTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Line 1 Rising Edge Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine1RisingEdgeFrameID;

		/**
		 * Description: Returns the unique Identifier of the Line 0 Falling Edge type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine0FallingEdge;

		/**
		 * Description: Returns the Timestamp of the Line 0 Falling Edge Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine0FallingEdgeTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Line 0 Falling Edge Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine0FallingEdgeFrameID;

		/**
		 * Description: Returns the unique Identifier of the Line 1 Falling Edge type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine1FallingEdge;

		/**
		 * Description: Returns the Timestamp of the Line 1 Falling Edge Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine1FallingEdgeTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Line 1 Falling Edge Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine1FallingEdgeFrameID;

		/**
		 * Description: Returns the unique Identifier of the Line 0 Any Edge type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine0AnyEdge;

		/**
		 * Description: Returns the Timestamp of the Line 0 Any Edge Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine0AnyEdgeTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Line 0 Any Edge Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine0AnyEdgeFrameID;

		/**
		 * Description: Returns the unique Identifier of the Line 1 Any Edge type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine1AnyEdge;

		/**
		 * Description: Returns the Timestamp of the Line 1 Any Edge Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine1AnyEdgeTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Line 1 Any Edge Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLine1AnyEdgeFrameID;

		/**
		 * Description: Returns the unique Identifier of the Link Trigger 0 type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLinkTrigger0;

		/**
		 * Description: Returns the Timestamp of the Link Trigger 0 Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLinkTrigger0Timestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Link Trigger 0 Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLinkTrigger0FrameID;

		/**
		 * Description: Returns the unique Identifier of the Link Trigger 1 type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLinkTrigger1;

		/**
		 * Description: Returns the Timestamp of the Link Trigger 1 Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLinkTrigger1Timestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Link Trigger 1 Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLinkTrigger1FrameID;

		/**
		 * Description: Returns the unique Identifier of the Action Late type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventActionLate;

		/**
		 * Description: Returns the Timestamp of the Action Late Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventActionLateTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Action Late Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventActionLateFrameID;

		/**
		 * Description: Returns the unique Identifier of the Link Speed Change type of Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLinkSpeedChange;

		/**
		 * Description: Returns the Timestamp of the Link Speed Change Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLinkSpeedChangeTimestamp;

		/**
		 * Description: Returns the unique Identifier of the Frame (or image) that generated the Link Speed Change Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventLinkSpeedChangeFrameID;

		/**
		 * Description: Returns the unique identifier of the Error type of Event. It can be used to register a callback function to be notified of the Error event occurrence. Its value uniquely identifies that the event received was an Error.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventError;

		/**
		 * Description: Returns the Timestamp of the Error Event. It can be used to determine when the event occurred.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventErrorTimestamp;

		/**
		 * Description: If applicable, returns the unique Identifier of the Frame (or image) that generated the Error Event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventErrorFrameID;

		/**
		 * Description: Returns an error code for the error(s) that happened.
		 * Visibility: Expert
		 */
		GenApi::IInteger &EventErrorCode;

		/**
		 * Description: Selects the feature User Set to load, save or configure.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<UserSetSelectorEnums> &UserSetSelector;

		/**
		 * Description: Loads the User Set specified by UserSetSelector to the device and makes it active.
		 * Visibility: Beginner
		 */
		GenApi::ICommand &UserSetLoad;

		/**
		 * Description: Save the User Set specified by UserSetSelector to the non-volatile memory of the device.
		 * Visibility: Beginner
		 */
		GenApi::ICommand &UserSetSave;

		/**
		 * Description: Selects the feature User Set to load and make active by default when the device is reset.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<UserSetDefaultEnums> &UserSetDefault;

		/**
		 * Description: Selects which individual UserSet feature to control.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<UserSetFeatureSelectorEnums> &UserSetFeatureSelector;

		/**
		 * Description: Enables the selected feature and make it active in all the UserSets.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &UserSetFeatureEnable;

		/**
		 * Description: Controls if the sequencer mechanism is active.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<SequencerModeEnums> &SequencerMode;

		/**
		 * Description: Controls if the sequencer configuration mode is active.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<SequencerConfigurationModeEnums> &SequencerConfigurationMode;

		/**
		 * Description: Selects which sequencer features to control.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<SequencerFeatureSelectorEnums> &SequencerFeatureSelector;

		/**
		 * Description: Enables the selected feature and make it active in all the sequencer sets.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &SequencerFeatureEnable;

		/**
		 * Description: Selects the sequencer set to which further feature settings applies.
		 * Visibility: Expert
		 */
		GenApi::IInteger &SequencerSetSelector;

		/**
		 * Description: Saves the current device state to the sequencer set selected by the SequencerSetSelector.
		 * Visibility: Expert
		 */
		GenApi::ICommand &SequencerSetSave;

		/**
		 * Description: Loads the sequencer set selected by SequencerSetSelector in the device. Even if SequencerMode is off, this will change the device state to the configuration of the selected set.
		 * Visibility: Expert
		 */
		GenApi::ICommand &SequencerSetLoad;

		/**
		 * Description: Contains the currently active sequencer set.
		 * Visibility: Expert
		 */
		GenApi::IInteger &SequencerSetActive;

		/**
		 * Description: Sets the initial/start sequencer set, which is the first set used within a sequencer.
		 * Visibility: Expert
		 */
		GenApi::IInteger &SequencerSetStart;

		/**
		 * Description: Selects to which branching path further path settings applies.
		 * Visibility: Expert
		 */
		GenApi::IInteger &SequencerPathSelector;

		/**
		 * Description: Specifies the next sequencer set.
		 * Visibility: Expert
		 */
		GenApi::IInteger &SequencerSetNext;

		/**
		 * Description: Specifies the internal signal or physical input line to use as the sequencer trigger source.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<SequencerTriggerSourceEnums> &SequencerTriggerSource;

		/**
		 * Description: Specifies the activation mode of the sequencer trigger.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<SequencerTriggerActivationEnums> &SequencerTriggerActivation;

		/**
		 * Description: Selects the target file in the device.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<FileSelectorEnums> &FileSelector;

		/**
		 * Description: Selects the target operation for the selected file in the device. This Operation is executed when the FileOperationExecute feature is called.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<FileOperationSelectorEnums> &FileOperationSelector;

		/**
		 * Description: Executes the operation selected by FileOperationSelector on the selected file.
		 * Visibility: Guru
		 */
		GenApi::ICommand &FileOperationExecute;

		/**
		 * Description: Selects the access mode in which a file is opened in the device.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<FileOpenModeEnums> &FileOpenMode;

		/**
		 * Description: Defines the intermediate access buffer that allows the exchange of data between the device file storage and the application.
		 * Visibility: Guru
		 */
		GenApi::IRegister &FileAccessBuffer;

		/**
		 * Description: Controls the Offset of the mapping between the device file storage and the FileAccessBuffer.
		 * Visibility: Guru
		 */
		GenApi::IInteger &FileAccessOffset;

		/**
		 * Description: Controls the Length of the mapping between the device file storage and the FileAccessBuffer.
		 * Visibility: Guru
		 */
		GenApi::IInteger &FileAccessLength;

		/**
		 * Description: Represents the file operation execution status.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<FileOperationStatusEnums> &FileOperationStatus;

		/**
		 * Description: Represents the file operation result. For Read or Write operations, the number of successfully read/written bytes is returned.
		 * Visibility: Guru
		 */
		GenApi::IInteger &FileOperationResult;

		/**
		 * Description: Represents the size of the selected file in bytes.
		 * Visibility: Guru
		 */
		GenApi::IInteger &FileSize;

		/**
		 * Description: Controls or returns the number of sources supported by the device.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &SourceCount;

		/**
		 * Description: Selects the source to control.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<SourceSelectorEnums> &SourceSelector;

		/**
		 * Description: Selects which stream transfers are currently controlled by the selected Transfer features.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<TransferSelectorEnums> &TransferSelector;

		/**
		 * Description: Selects the control method for the transfers.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<TransferControlModeEnums> &TransferControlMode;

		/**
		 * Description: Selects the operation mode of the transfer.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<TransferOperationModeEnums> &TransferOperationMode;

		/**
		 * Description: Specifies the number of data Blocks that the device should stream before stopping. This feature is only active if the TransferOperationMode is set to MultiBlock.
		 * Visibility: Expert
		 */
		GenApi::IInteger &TransferBlockCount;

		/**
		 * Description: Number of Block(s) to transfer for each TransferBurstStart trigger.
		 * Visibility: Expert
		 */
		GenApi::IInteger &TransferBurstCount;

		/**
		 * Description: Controls the maximum number of data blocks that can be stored in the block queue of the selected stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &TransferQueueMaxBlockCount;

		/**
		 * Description: Returns the number of Block(s) currently in the transfer queue.
		 * Visibility: Expert
		 */
		GenApi::IInteger &TransferQueueCurrentBlockCount;

		/**
		 * Description: Specifies the operation mode of the transfer queue.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<TransferQueueModeEnums> &TransferQueueMode;

		/**
		 * Description: Starts the streaming of data blocks out of the device. This feature must be available when the TransferControlMode is set to "UserControled". If the TransferStart feature is not writable (locked), the application should not start the transfer and should avoid using the feature until it becomes writable again.
		 * Visibility: Expert
		 */
		GenApi::ICommand &TransferStart;

		/**
		 * Description: Stops the streaming of data Block(s). The current block transmission will be completed. This feature must be available when the TransferControlMode is set to "UserControlled".
		 * Visibility: Expert
		 */
		GenApi::ICommand &TransferStop;

		/**
		 * Description: Aborts immediately the streaming of data block(s). Aborting the transfer will result in the lost of the data that is present or currently entering in the block queue. However, the next new block received will be stored in the queue and transferred to the host when the streaming is restarted. If implemented, this feature should be available when the TransferControlMode is set to "UserControlled".
		 * Visibility: Expert
		 */
		GenApi::ICommand &TransferAbort;

		/**
		 * Description: Pauses the streaming of data Block(s). Pausing the streaming will immediately suspend the ongoing data transfer even if a block is partially transfered. The device will resume its transmission at the reception of a TransferResume command.
		 * Visibility: Guru
		 */
		GenApi::ICommand &TransferPause;

		/**
		 * Description: Resumes a data Blocks streaming that was previously paused by a TransferPause command.
		 * Visibility: Guru
		 */
		GenApi::ICommand &TransferResume;

		/**
		 * Description: Selects the type of transfer trigger to configure.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<TransferTriggerSelectorEnums> &TransferTriggerSelector;

		/**
		 * Description: Controls if the selected trigger is active.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<TransferTriggerModeEnums> &TransferTriggerMode;

		/**
		 * Description: Specifies the signal to use as the trigger source for transfers.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<TransferTriggerSourceEnums> &TransferTriggerSource;

		/**
		 * Description: Specifies the activation mode of the transfer control trigger.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<TransferTriggerActivationEnums> &TransferTriggerActivation;

		/**
		 * Description: Selects which status of the transfer module to read.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<TransferStatusSelectorEnums> &TransferStatusSelector;

		/**
		 * Description: Reads the status of the Transfer module signal selected by TransferStatusSelector.
		 * Visibility: Guru
		 */
		GenApi::IBoolean &TransferStatus;

		/**
		 * Description: Selects the color component for the control of the TransferStreamChannel feature.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<TransferComponentSelectorEnums> &TransferComponentSelector;

		/**
		 * Description: Selects the streaming channel that will be used to transfer the selected stream of data. In general, this feature can be omitted and the default streaming channel will be used.
		 * Visibility: Guru
		 */
		GenApi::IInteger &TransferStreamChannel;

		/**
		 * Description: Specifies the unit used when delivering calibrated distance data.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<Scan3dDistanceUnitEnums> &Scan3dDistanceUnit;

		/**
		 * Description: Specifies the Coordinate system to use for the device.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<Scan3dCoordinateSystemEnums> &Scan3dCoordinateSystem;

		/**
		 * Description: Controls the Calibration and data organization of the device, naming the coordinates transmitted.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<Scan3dOutputModeEnums> &Scan3dOutputMode;

		/**
		 * Description: Defines coordinate system reference location.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<Scan3dCoordinateSystemReferenceEnums> &Scan3dCoordinateSystemReference;

		/**
		 * Description: Selects the individual coordinates in the vectors for 3D information/transformation.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<Scan3dCoordinateSelectorEnums> &Scan3dCoordinateSelector;

		/**
		 * Description: Scale factor when transforming a pixel from relative coordinates to world coordinates.
		 * Visibility: Expert
		 */
		GenApi::IFloat &Scan3dCoordinateScale;

		/**
		 * Description: Offset when transforming a pixel from relative coordinates to world coordinates.
		 * Visibility: Expert
		 */
		GenApi::IFloat &Scan3dCoordinateOffset;

		/**
		 * Description: Enables the definition of a non-valid flag value in the data stream. Note that the confidence output is an alternate recommended way to identify non-valid pixels. Using an Scan3dInvalidDataValue may give processing penalties due to special handling.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &Scan3dInvalidDataFlag;

		/**
		 * Description: Value which identifies a non-valid pixel if Scan3dInvalidDataFlag is enabled.
		 * Visibility: Expert
		 */
		GenApi::IFloat &Scan3dInvalidDataValue;

		/**
		 * Description: Minimum valid transmitted coordinate value of the selected Axis.
		 * Visibility: Expert
		 */
		GenApi::IFloat &Scan3dAxisMin;

		/**
		 * Description: Maximum valid transmitted coordinate value of the selected Axis.
		 * Visibility: Expert
		 */
		GenApi::IFloat &Scan3dAxisMax;

		/**
		 * Description: Sets the index to read/write a coordinate transform value.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<Scan3dCoordinateTransformSelectorEnums> &Scan3dCoordinateTransformSelector;

		/**
		 * Description: Specifies the transform value selected. For translations (Scan3dCoordinateTransformSelector = TranslationX/Y/Z) it is expressed in the distance unit of the system, for rotations (Scan3dCoordinateTransformSelector =RotationX/Y/Z) in degrees.
		 * Visibility: Expert
		 */
		GenApi::IFloat &Scan3dTransformValue;

		/**
		 * Description: Sets the index to read a coordinate system reference value defining the transform of a point from the current (Anchor or Transformed) system to the reference system.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<Scan3dCoordinateReferenceSelectorEnums> &Scan3dCoordinateReferenceSelector;

		/**
		 * Description: Returns the reference value selected. Reads the value of a rotation or translation value for the current (Anchor or Transformed) coordinate system transformation to the Reference system.
		 * Visibility: Expert
		 */
		GenApi::IFloat &Scan3dCoordinateReferenceValue;

		/**
		 * Description: Activates the inclusion of Chunk data in the payload of the image.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &ChunkModeActive;

		/**
		 * Description: Selects which Chunk to enable or control.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkSelectorEnums> &ChunkSelector;

		/**
		 * Description: Enables the inclusion of the selected Chunk data in the payload of the image.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &ChunkEnable;

		/**
		 * Description: Selects the part to access in chunk data in a multipart transmission.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkPartSelector;

		/**
		 * Description: Returns the component of the payload image. This can be used to identify the image component of a generic part in a multipart transfer.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkImageComponentEnums> &ChunkImageComponent;

		/**
		 * Description: Returns the entire image data included in the payload.
		 * Visibility: Guru
		 */
		GenApi::IRegister &ChunkImage;

		/**
		 * Description: Returns the OffsetX of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkOffsetX;

		/**
		 * Description: Returns the OffsetY of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkOffsetY;

		/**
		 * Description: Returns the Width of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkWidth;

		/**
		 * Description: Returns the Height of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkHeight;

		/**
		 * Description: Returns the PixelFormat of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkPixelFormatEnums> &ChunkPixelFormat;

		/**
		 * Description: Returns the minimum value of dynamic range of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkPixelDynamicRangeMin;

		/**
		 * Description: Returns the maximum value of dynamic range of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkPixelDynamicRangeMax;

		/**
		 * Description: Returns the Timestamp of the image included in the payload at the time of the FrameStart internal event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkTimestamp;

		/**
		 * Description: Returns the last Timestamp latched with the TimestampLatch command.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkTimestampLatchValue;

		/**
		 * Description: Returns the status of all the I/O lines at the time of the FrameStart internal event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkLineStatusAll;

		/**
		 * Description: Selects which counter to retrieve data from.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkCounterSelectorEnums> &ChunkCounterSelector;

		/**
		 * Description: Returns the value of the selected Chunk counter at the time of the FrameStart event.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkCounterValue;

		/**
		 * Description: Selects which Timer to retrieve data from.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkTimerSelectorEnums> &ChunkTimerSelector;

		/**
		 * Description: Returns the value of the selected Timer at the time of the FrameStart internal event.
		 * Visibility: Expert
		 */
		GenApi::IFloat &ChunkTimerValue;

		/**
		 * Description: Selects which Encoder to retrieve data from.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkEncoderSelectorEnums> &ChunkEncoderSelector;

		/**
		 * Description: Index for vector representation of one chunk value per line in an image.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkScanLineSelector;

		/**
		 * Description: Returns the counter's value of the selected Encoder at the time of the FrameStart in area scan mode or the counter's value at the time of the LineStart selected by ChunkScanLineSelector in LineScan mode.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkEncoderValue;

		/**
		 * Description: Returns the motion status of the selected encoder.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkEncoderStatusEnums> &ChunkEncoderStatus;

		/**
		 * Description: Selects which exposure time is read by the ChunkExposureTime feature.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkExposureTimeSelectorEnums> &ChunkExposureTimeSelector;

		/**
		 * Description: Returns the exposure time used to capture the image.
		 * Visibility: Expert
		 */
		GenApi::IFloat &ChunkExposureTime;

		/**
		 * Description: Selects which Gain to return.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkGainSelectorEnums> &ChunkGainSelector;

		/**
		 * Description: Returns the gain used to capture the image.
		 * Visibility: Expert
		 */
		GenApi::IFloat &ChunkGain;

		/**
		 * Description: Selects which Black Level to return. Possible values are:
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkBlackLevelSelectorEnums> &ChunkBlackLevelSelector;

		/**
		 * Description: Returns the black level used to capture the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IFloat &ChunkBlackLevel;

		/**
		 * Description: Returns the LinePitch of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkLinePitch;

		/**
		 * Description: Returns the unique Identifier of the frame (or image) included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkFrameID;

		/**
		 * Description: Returns the identifier of Source that the image comes from.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkSourceIDEnums> &ChunkSourceID;

		/**
		 * Description: Returns the identifier of Region that the image comes from.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkRegionIDEnums> &ChunkRegionID;

		/**
		 * Description: Returns the unique identifier of the transfer block used to transport the payload.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkTransferBlockID;

		/**
		 * Description: Returns identifier of the stream that generated this block.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkTransferStreamIDEnums> &ChunkTransferStreamID;

		/**
		 * Description: Returns the current number of blocks in the transfer queue.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkTransferQueueCurrentBlockCount;

		/**
		 * Description: Returns identifier of the stream channel used to carry the block.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkStreamChannelID;

		/**
		 * Description: Return the index of the active set of the running sequencer included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IInteger &ChunkSequencerSetActive;

		/**
		 * Description: Returns the Distance Unit of the payload image.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkScan3dDistanceUnitEnums> &ChunkScan3dDistanceUnit;

		/**
		 * Description: Returns the Calibrated Mode of the payload image.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkScan3dOutputModeEnums> &ChunkScan3dOutputMode;

		/**
		 * Description: Returns the Coordinate System of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkScan3dCoordinateSystemEnums> &ChunkScan3dCoordinateSystem;

		/**
		 * Description: Returns the Coordinate System Position of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkScan3dCoordinateSystemReferenceEnums> &ChunkScan3dCoordinateSystemReference;

		/**
		 * Description: Selects which Coordinate to retrieve data from.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkScan3dCoordinateSelectorEnums> &ChunkScan3dCoordinateSelector;

		/**
		 * Description: Returns the Scale for the selected coordinate axis of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IFloat &ChunkScan3dCoordinateScale;

		/**
		 * Description: Returns the Offset for the selected coordinate axis of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IFloat &ChunkScan3dCoordinateOffset;

		/**
		 * Description: Returns if a specific non-valid data flag is used in the data stream.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &ChunkScan3dInvalidDataFlag;

		/**
		 * Description: Returns the Invalid Data Value used for the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IFloat &ChunkScan3dInvalidDataValue;

		/**
		 * Description: Returns the Minimum Axis value for the selected coordinate axis of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IFloat &ChunkScan3dAxisMin;

		/**
		 * Description: Returns the Maximum Axis value for the selected coordinate axis of the image included in the payload.
		 * Visibility: Expert
		 */
		GenApi::IFloat &ChunkScan3dAxisMax;

		/**
		 * Description: Selector for transform values.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkScan3dCoordinateTransformSelectorEnums> &ChunkScan3dCoordinateTransformSelector;

		/**
		 * Description: Returns the transform value.
		 * Visibility: Expert
		 */
		GenApi::IFloat &ChunkScan3dTransformValue;

		/**
		 * Description: Selector to read a coordinate system reference value defining the transform of a point from one system to the other.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ChunkScan3dCoordinateReferenceSelectorEnums> &ChunkScan3dCoordinateReferenceSelector;

		/**
		 * Description: Reads the value of a position or pose coordinate for the anchor or transformed coordinate systems relative to the reference point.
		 * Visibility: Expert
		 */
		GenApi::IFloat &ChunkScan3dCoordinateReferenceValue;

		/**
		 * Description: Tests the device's pending acknowledge feature. When this feature is written, the device waits a time period corresponding to the value of TestPendingAck before acknowledging the write.
		 * Visibility: Guru
		 */
		GenApi::IInteger &TestPendingAck;

		/**
		 * Description: Generates a Test Event.
		 * Visibility: Guru
		 */
		GenApi::ICommand &TestEventGenerate;

		/**
		 * Description: Provides the number of bytes transferred for each image or chunk on the stream channel. This includes any end-of-line, end-of-frame statistics or other stamp data. This is the total size of data payload for a data block.
		 * Visibility: Expert
		 */
		GenApi::IInteger &PayloadSize;

		/**
		 * Description: This device tap geometry feature describes the geometrical properties characterizing the taps of a camera as presented at the output of the device.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceTapGeometryEnums> &DeviceTapGeometry;

		/**
		 * Description: Controls the principal physical link configuration to use on next restart/power-up of the device.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<GevPhysicalLinkConfigurationEnums> &GevPhysicalLinkConfiguration;

		/**
		 * Description: Indicates the current physical link configuration of the device.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<GevCurrentPhysicalLinkConfigurationEnums> &GevCurrentPhysicalLinkConfiguration;

		/**
		 * Description: Indicates the current number of active logical links.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevActiveLinkCount;

		/**
		 * Description: Selects the GEV option to interrogate for existing support.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<GevSupportedOptionSelectorEnums> &GevSupportedOptionSelector;

		/**
		 * Description: Returns if the selected GEV option is supported.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &GevSupportedOption;

		/**
		 * Description: Selects which logical link to control.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &GevInterfaceSelector;

		/**
		 * Description: MAC address of the logical link.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &GevMACAddress;

		/**
		 * Description: Controls whether incoming PAUSE Frames are handled on the given logical link.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &GevPAUSEFrameReception;

		/**
		 * Description: Controls whether PAUSE Frames can be generated on the given logical link.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &GevPAUSEFrameTransmission;

		/**
		 * Description: Controls whether the Link Local Address IP configuration scheme is activated on the given logical link.
		 * Visibility: Beginner
		 */
		GenApi::IBoolean &GevCurrentIPConfigurationLLA;

		/**
		 * Description: Controls whether the DHCP IP configuration scheme is activated on the given logical link.
		 * Visibility: Beginner
		 */
		GenApi::IBoolean &GevCurrentIPConfigurationDHCP;

		/**
		 * Description: Controls whether the PersistentIP configuration scheme is activated on the given logical link.
		 * Visibility: Beginner
		 */
		GenApi::IBoolean &GevCurrentIPConfigurationPersistentIP;

		/**
		 * Description: Reports the IP address for the given logical link.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &GevCurrentIPAddress;

		/**
		 * Description: Reports the subnet mask of the given logical link.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &GevCurrentSubnetMask;

		/**
		 * Description: Reports the default gateway IP address to be used on the given logical link.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &GevCurrentDefaultGateway;

		/**
		 * Description: Reports the current IP configuration status.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<GevIPConfigurationStatusEnums> &GevIPConfigurationStatus;

		/**
		 * Description: Indicates the first URL to the GenICam XML device description file. The First URL is used as the first choice by the application to retrieve the GenICam XML device description file.
		 * Visibility: Guru
		 */
		GenApi::IString &GevFirstURL;

		/**
		 * Description: Indicates the second URL to the GenICam XML device description file. This URL is an alternative if the application was unsuccessful to retrieve the device description file using the first URL.
		 * Visibility: Guru
		 */
		GenApi::IString &GevSecondURL;

		/**
		 * Description: Controls the Persistent IP address for this logical link. It is only used when the device boots with the Persistent IP configuration scheme.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &GevPersistentIPAddress;

		/**
		 * Description: Controls the Persistent subnet mask associated with the Persistent IP address on this logical link. It is only used when the device boots with the Persistent IP configuration scheme.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &GevPersistentSubnetMask;

		/**
		 * Description: Controls the persistent default gateway for this logical link. It is only used when the device boots with the Persistent IP configuration scheme.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &GevPersistentDefaultGateway;

		/**
		 * Description: Indicates the maximum randomized delay the device will wait to acknowledge a discovery command.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDiscoveryAckDelay;

		/**
		 * Description: Enables the IEEE 1588 Precision Time Protocol to control the timestamp register.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &GevIEEE1588;

		/**
		 * Description: Indicates the expected accuracy of the device clock when it is the grandmaster, or in the event it becomes the grandmaster.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<GevIEEE1588ClockAccuracyEnums> &GevIEEE1588ClockAccuracy;

		/**
		 * Description: Provides the status of the IEEE 1588 clock.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<GevIEEE1588StatusEnums> &GevIEEE1588Status;

		/**
		 * Description: Selects the GigE Vision version to control extended status codes for.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<GevGVCPExtendedStatusCodesSelectorEnums> &GevGVCPExtendedStatusCodesSelector;

		/**
		 * Description: Enables the generation of extended status codes.
		 * Visibility: Guru
		 */
		GenApi::IBoolean &GevGVCPExtendedStatusCodes;

		/**
		 * Description: Enables the generation of PENDING_ACK.
		 * Visibility: Guru
		 */
		GenApi::IBoolean &GevGVCPPendingAck;

		/**
		 * Description: Controls the key to use to authenticate primary application switchover requests.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevPrimaryApplicationSwitchoverKey;

		/**
		 * Description: Enables the extended IDs mode.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<GevGVSPExtendedIDModeEnums> &GevGVSPExtendedIDMode;

		/**
		 * Description: Controls the device access privilege of an application.
		 * Visibility: Guru
		 */
		GenApi::IEnumerationT<GevCCPEnums> &GevCCP;

		/**
		 * Description: Returns the UDP source port of the primary application.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevPrimaryApplicationSocket;

		/**
		 * Description: Returns the address of the primary application.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevPrimaryApplicationIPAddress;

		/**
		 * Description: Controls the port to which the device must send messages. Setting this value to 0 closes the message channel.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevMCPHostPort;

		/**
		 * Description: Controls the destination IP address for the message channel.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevMCDA;

		/**
		 * Description: Provides the transmission timeout value in milliseconds.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevMCTT;

		/**
		 * Description: Controls the number of retransmissions allowed when a message channel message times out.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevMCRC;

		/**
		 * Description: This feature indicates the source port for the message channel.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevMCSP;

		/**
		 * Description: Selects the stream channel to control.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevStreamChannelSelector;

		/**
		 * Description: Enables the alternate IP destination for stream packets resent due to a packet resend request. When True, the source IP address provided in the packet resend command packet is used. When False, the value set in the GevSCDA[GevStreamChannelSelector] feature is used.
		 * Visibility: Guru
		 */
		GenApi::IBoolean &GevSCCFGPacketResendDestination;

		/**
		 * Description: Enables the selected GVSP transmitter to use the single packet per data block All-in Transmission mode.
		 * Visibility: Guru
		 */
		GenApi::IBoolean &GevSCCFGAllInTransmission;

		/**
		 * Description: Enables the camera to continue to stream, for this stream channel, if its control channel is closed or regardless of the reception of any ICMP messages (such as destination unreachable messages).
		 * Visibility: Guru
		 */
		GenApi::IBoolean &GevSCCFGUnconditionalStreaming;

		/**
		 * Description: Enables cameras to use the extended chunk data payload type for this stream channel.
		 * Visibility: Guru
		 */
		GenApi::IBoolean &GevSCCFGExtendedChunkData;

		/**
		 * Description: Index of the logical link to use.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevSCPInterfaceIndex;

		/**
		 * Description: Controls the port of the selected channel to which a GVSP transmitter must send data stream or the port from which a GVSP receiver may receive data stream. Setting this value to 0 closes the stream channel.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevSCPHostPort;

		/**
		 * Description: Sends a test packet. When this feature is set, the device will fire one test packet.
		 * Visibility: Guru
		 */
		GenApi::IBoolean &GevSCPSFireTestPacket;

		/**
		 * Description: The state of this feature is copied into the "do not fragment" bit of IP header of each stream packet. It can be used by the application to prevent IP fragmentation of packets on the stream channel.
		 * Visibility: Guru
		 */
		GenApi::IBoolean &GevSCPSDoNotFragment;

		/**
		 * Description: Controls the delay (in GEV timestamp counter unit) to insert between each packet for this stream channel. This can be used as a crude flow-control mechanism if the application or the network infrastructure cannot keep up with the packets coming from the device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevSCPD;

		/**
		 * Description: Controls the destination IP address of the selected stream channel to which a GVSP transmitter must send data stream or the destination IP address from which a GVSP receiver may receive data stream.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevSCDA;

		/**
		 * Description: Indicates the source port of the stream channel.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevSCSP;

		/**
		 * Description: Reports the number of zones per block transmitted on the selected stream channel.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevSCZoneCount;

		/**
		 * Description: Reports the transmission direction of each zone transmitted on the selected stream channel.
		 * Visibility: Guru
		 */
		GenApi::IInteger &GevSCZoneDirectionAll;

		/**
		 * Description: Controls whether the selected stream channel multi-zone configuration is locked. When locked, the GVSP transmitter is not allowed to change the number of zones and their direction during block acquisition and transmission.
		 * Visibility: Guru
		 */
		GenApi::IBoolean &GevSCZoneConfigurationLock;

		/**
		 * Description: Reports the number of transmitted PAUSE frames.
		 * Visibility: Guru
		 */
		GenApi::IInteger &aPAUSEMACCtrlFramesTransmitted;

		/**
		 * Description: Reports the number of received PAUSE frames.
		 * Visibility: Guru
		 */
		GenApi::IInteger &aPAUSEMACCtrlFramesReceived;

		/**
		 * Description: This Camera Link specific feature describes the configuration used by the camera. It helps especially when a camera is capable of operation in a non-standard configuration, and when the features PixelSize, SensorDigitizationTaps, and DeviceTapGeometry do not provide enough information for interpretation of the image data provided by the camera.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<ClConfigurationEnums> &ClConfiguration;

		/**
		 * Description: This Camera Link specific feature describes the time multiplexing of the camera link connection to transfer more than the configuration allows, in one single clock.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<ClTimeSlotsCountEnums> &ClTimeSlotsCount;

		/**
		 * Description: This feature indicates the current and active Link configuration used by the Device.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<CxpLinkConfigurationStatusEnums> &CxpLinkConfigurationStatus;

		/**
		 * Description: Provides the Link configuration that allows the Transmitter Device to operate in its default mode.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<CxpLinkConfigurationPreferredEnums> &CxpLinkConfigurationPreferred;

		/**
		 * Description: This feature allows specifying the Link configuration for the communication between the Receiver and Transmitter Device. In most cases this feature does not need to be written because automatic discovery will set configuration correctly to the value returned by CxpLinkConfigurationPreferred. Note that the currently active configuration of the Link can be read using CxpLinkConfigurationStatus.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<CxpLinkConfigurationEnums> &CxpLinkConfiguration;

		/**
		 * Description: Selects the CoaXPress physical connection to control.
		 * Visibility: Expert
		 */
		GenApi::IInteger &CxpConnectionSelector;

		/**
		 * Description: Enables the test mode for an individual physical connection of the Device.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<CxpConnectionTestModeEnums> &CxpConnectionTestMode;

		/**
		 * Description: Reports the current connection error count for test packets recieved by the device on the connection selected by CxpConnectionSelector.
		 * Visibility: Expert
		 */
		GenApi::IInteger &CxpConnectionTestErrorCount;

		/**
		 * Description: Reports the current count for test packets recieved by the device on the connection selected by CxpConnectionSelector.
		 * Visibility: Expert
		 */
		GenApi::IInteger &CxpConnectionTestPacketCount;

		/**
		 * Description: Activate automatic control of the Power over CoaXPress (PoCXP) for the Link.
		 * Visibility: Expert
		 */
		GenApi::ICommand &CxpPoCxpAuto;

		/**
		 * Description: Disable Power over CoaXPress (PoCXP) for the Link.
		 * Visibility: Expert
		 */
		GenApi::ICommand &CxpPoCxpTurnOff;

		/**
		 * Description: Reset the Power over CoaXPress (PoCXP) Link after an over-current trip on the Device connection(s).
		 * Visibility: Expert
		 */
		GenApi::ICommand &CxpPoCxpTripReset;

		/**
		 * Description: Returns the Power over CoaXPress (PoCXP) status of the Device.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<CxpPoCxpStatusEnums> &CxpPoCxpStatus;

	};
	/*@}*/

	/*@}*/

}
#endif // PGR_SPINNAKER_CAMERA_H