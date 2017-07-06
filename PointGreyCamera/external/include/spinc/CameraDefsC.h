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

#ifndef PGR_SPINNAKER_CAMERA_DEFS_C_H
#define PGR_SPINNAKER_CAMERA_DEFS_C_H

/**
* @defgroup SpinnakerDefsC Spinnaker C Definitions
* @ingroup SpinnakerC
*
* Definitions for Spinnaker C
*/
/*@{*/

/**
* @defgroup CameraDefsC_h Camera Enumerations
*/
/*@{*/

/**
*@brief The enum definitions for camera nodes.
*/

typedef enum _spinDeviceTypeEnums	/*!< Returns the device type.*/
{
	DeviceType_Transmitter,	/*!< Data stream transmitter device.*/
	DeviceType_Receiver,	/*!< Data stream receiver device.*/
	DeviceType_Transceiver,	/*!< Data stream receiver and transmitter device.*/
	DeviceType_Peripheral,	/*!< Controllable device (with no data stream handling).*/
	NUM_DEVICETYPE
} spinDeviceTypeEnums;

typedef enum _spinDeviceScanTypeEnums	/*!< Scan type of the sensor of the device.*/
{
	DeviceScanType_Areascan,	/*!< 2D sensor.*/
	DeviceScanType_Linescan,	/*!< 1D sensor.*/
	DeviceScanType_Areascan3D,	/*!< device outputs 2D range image.*/
	DeviceScanType_Linescan3D,	/*!< device outputs 1D range image.*/
	NUM_DEVICESCANTYPE
} spinDeviceScanTypeEnums;

typedef enum _spinDeviceTLTypeEnums	/*!< Transport Layer type of the device.*/
{
	DeviceTLType_GigEVision,	/*!< GigE Vision.*/
	DeviceTLType_CameraLink,	/*!< Camera Link.*/
	DeviceTLType_CameraLinkHS,	/*!< Camera Link High Speed.*/
	DeviceTLType_CoaXPress,	/*!< CoaXPress.*/
	DeviceTLType_USB3Vision,	/*!< USB3 Vision.*/
	DeviceTLType_Custom,	/*!< Custom Transport Layer.*/
	NUM_DEVICETLTYPE
} spinDeviceTLTypeEnums;

typedef enum _spinDeviceConnectionStatusEnums	/*!< Indicates the status of the specified Connection.*/
{
	DeviceConnectionStatus_Active,	/*!< Connection is in use.*/
	DeviceConnectionStatus_Inactive,	/*!< Connection is not in use.*/
	NUM_DEVICECONNECTIONSTATUS
} spinDeviceConnectionStatusEnums;

typedef enum _spinDeviceLinkThroughputLimitModeEnums	/*!< Controls if the DeviceLinkThroughputLimit is active. When disabled, lower level TL specific features are expected to control the throughput. When enabled, DeviceLinkThroughputLimit controls the overall throughput.*/
{
	DeviceLinkThroughputLimitMode_On,	/*!< Enables the DeviceLinkThroughputLimit feature.*/
	DeviceLinkThroughputLimitMode_Off,	/*!< Disables the DeviceLinkThroughputLimit feature.*/
	NUM_DEVICELINKTHROUGHPUTLIMITMODE
} spinDeviceLinkThroughputLimitModeEnums;

typedef enum _spinDeviceLinkHeartbeatModeEnums	/*!< Activate or deactivate the Link's heartbeat.*/
{
	DeviceLinkHeartbeatMode_On,	/*!< Enables the Link heartbeat.*/
	DeviceLinkHeartbeatMode_Off,	/*!< Disables the Link heartbeat.*/
	NUM_DEVICELINKHEARTBEATMODE
} spinDeviceLinkHeartbeatModeEnums;

typedef enum _spinDeviceStreamChannelTypeEnums	/*!< Reports the type of the stream channel.*/
{
	DeviceStreamChannelType_Transmitter,	/*!< Data stream transmitter channel.*/
	DeviceStreamChannelType_Receiver,	/*!< Data stream receiver channel.*/
	NUM_DEVICESTREAMCHANNELTYPE
} spinDeviceStreamChannelTypeEnums;

typedef enum _spinDeviceStreamChannelEndiannessEnums	/*!< Endianess of multi-byte pixel data for this stream.*/
{
	DeviceStreamChannelEndianness_Big,	/*!< Stream channel data is big Endian.*/
	DeviceStreamChannelEndianness_Little,	/*!< Stream channel data is little Endian.*/
	NUM_DEVICESTREAMCHANNELENDIANNESS
} spinDeviceStreamChannelEndiannessEnums;

typedef enum _spinDeviceCharacterSetEnums	/*!< Character set used by the strings of the device's bootstrap registers.*/
{
	DeviceCharacterSet_UTF8,	/*!< Device use UTF8 character set.*/
	DeviceCharacterSet_ASCII,	/*!< Device use ASCII character set.*/
	NUM_DEVICECHARACTERSET
} spinDeviceCharacterSetEnums;

typedef enum _spinDeviceIndicatorModeEnums	/*!< Controls the behavior of the indicators (such as LEDs) showing the status of the Device.*/
{
	DeviceIndicatorMode_Inactive,	/*!< Device's indicators are inactive (Off).*/
	DeviceIndicatorMode_Active,	/*!< Device's indicators are active showing their respective status.*/
	DeviceIndicatorMode_ErrorStatus,	/*!< Device's indicators are inactive unless an error occurs.*/
	NUM_DEVICEINDICATORMODE
} spinDeviceIndicatorModeEnums;

typedef enum _spinDeviceRegistersEndiannessEnums	/*!< Endianess of the registers of the device.*/
{
	DeviceRegistersEndianness_Big,	/*!< Device's registers are big Endian.*/
	DeviceRegistersEndianness_Little,	/*!< Device's registers are little Endian.*/
	NUM_DEVICEREGISTERSENDIANNESS
} spinDeviceRegistersEndiannessEnums;

typedef enum _spinDeviceTemperatureSelectorEnums	/*!< Selects the location within the device, where the temperature will be measured.*/
{
	DeviceTemperatureSelector_Sensor,	/*!< Temperature of the image sensor of the camera.*/
	DeviceTemperatureSelector_Mainboard,	/*!< Temperature of the device's mainboard.*/
	NUM_DEVICETEMPERATURESELECTOR
} spinDeviceTemperatureSelectorEnums;

typedef enum _spinDeviceClockSelectorEnums	/*!< Selects the clock frequency to access from the device.*/
{
	DeviceClockSelector_Sensor,	/*!< Clock frequency of the image sensor of the camera.*/
	DeviceClockSelector_SensorDigitization,	/*!< Clock frequency of the camera A/D conversion stage.*/
	DeviceClockSelector_CameraLink,	/*!< Frequency of the Camera Link clock.*/
	NUM_DEVICECLOCKSELECTOR
} spinDeviceClockSelectorEnums;

typedef enum _spinDeviceSerialPortSelectorEnums	/*!< Selects which serial port of the device to control.*/
{
	DeviceSerialPortSelector_CameraLink,	/*!< Serial port associated to the Camera link connection.*/
	NUM_DEVICESERIALPORTSELECTOR
} spinDeviceSerialPortSelectorEnums;

typedef enum _spinDeviceSerialPortBaudRateEnums	/*!< This feature controls the baud rate used by the selected serial port.*/
{
	DeviceSerialPortBaudRate_Baud9600,	/*!< Serial port speed of 9600 baud.*/
	DeviceSerialPortBaudRate_Baud19200,	/*!< Serial port speed of 19200 baud.*/
	DeviceSerialPortBaudRate_Baud38400,	/*!< Serial port speed of 38400 baud.*/
	DeviceSerialPortBaudRate_Baud57600,	/*!< Serial port speed of 57600 baud.*/
	DeviceSerialPortBaudRate_Baud115200,	/*!< Serial port speed of 115200 baud.*/
	DeviceSerialPortBaudRate_Baud230400,	/*!< Serial port speed of 230400 baud.*/
	DeviceSerialPortBaudRate_Baud460800,	/*!< Serial port speed of 460800 baud.*/
	DeviceSerialPortBaudRate_Baud921600,	/*!< Serial port speed of 921600 baud.*/
	NUM_DEVICESERIALPORTBAUDRATE
} spinDeviceSerialPortBaudRateEnums;

typedef enum _spinSensorTapsEnums	/*!< Number of taps of the camera sensor.*/
{
	SensorTaps_One,	/*!< 1 tap.*/
	SensorTaps_Two,	/*!< 2 taps.*/
	SensorTaps_Three,	/*!< 3 taps.*/
	SensorTaps_Four,	/*!< 4 taps.*/
	SensorTaps_Eight,	/*!< 8 taps.*/
	SensorTaps_Ten,	/*!< 10 taps.*/
	NUM_SENSORTAPS
} spinSensorTapsEnums;

typedef enum _spinSensorDigitizationTapsEnums	/*!< Number of digitized samples outputted simultaneously by the camera A/D conversion stage.*/
{
	SensorDigitizationTaps_One,	/*!< 1 tap.*/
	SensorDigitizationTaps_Two,	/*!< 2 taps.*/
	SensorDigitizationTaps_Three,	/*!< 3 taps.*/
	SensorDigitizationTaps_Four,	/*!< 4 taps.*/
	SensorDigitizationTaps_Eight,	/*!< 8 taps.*/
	SensorDigitizationTaps_Ten,	/*!< 10 taps.*/
	NUM_SENSORDIGITIZATIONTAPS
} spinSensorDigitizationTapsEnums;

typedef enum _spinRegionSelectorEnums	/*!< Selects the Region of interest to control. The RegionSelector feature allows devices that are able to extract multiple regions out of an image, to configure the features of those individual regions independently.*/
{
	RegionSelector_Region0,	/*!< Selected feature will control the region 0.*/
	RegionSelector_Region1,	/*!< Selected feature will control the region 1.*/
	RegionSelector_Region2,	/*!< Selected feature will control the region 2.*/
	RegionSelector_All,	/*!< Selected features will control all the regions at the same time.*/
	NUM_REGIONSELECTOR
} spinRegionSelectorEnums;

typedef enum _spinRegionModeEnums	/*!< Controls if the selected Region of interest is active and streaming.*/
{
	RegionMode_Off,	/*!< Disable the usage of the Region.*/
	RegionMode_On,	/*!< Enable the usage of the Region.*/
	NUM_REGIONMODE
} spinRegionModeEnums;

typedef enum _spinRegionDestinationEnums	/*!< Control the destination of the selected region.*/
{
	RegionDestination_Stream0,	/*!< The destination of the region is the data stream 0.*/
	RegionDestination_Stream1,	/*!< The destination of the region is the data stream 1.*/
	RegionDestination_Stream2,	/*!< The destination of the region is the data stream 2.*/
	NUM_REGIONDESTINATION
} spinRegionDestinationEnums;

typedef enum _spinImageComponentSelectorEnums	/*!< Selects a component to activate data streaming from.*/
{
	ImageComponentSelector_Intensity,	/*!< The acquisition of intensity of the reflected light is controlled.*/
	ImageComponentSelector_Color,	/*!< The acquisition of color of the reflected light is controlled*/
	ImageComponentSelector_Infrared,	/*!< The acquisition of non-visible infrared light is controlled.*/
	ImageComponentSelector_Ultraviolet,	/*!< The acquisition of non-visible ultraviolet light is controlled.*/
	ImageComponentSelector_Range,	/*!< The acquisition of range (distance) data is controlled. The data produced may be only range (2.5D) or a point cloud 3D coordinates depending on the Scan3dControl.*/
	ImageComponentSelector_Disparity,	/*!< The acquisition of stereo camera disparity data is controlled. Disparity is a more specific range format approximately inversely proportional to distance. Disparity is typically given in pixel units.*/
	ImageComponentSelector_Confidence,	/*!< The acquisition of confidence map of the acquired image is controlled. Confidence data may be binary (0 - invalid) or an integer where 0 is invalid and increasing value is increased confidence in the data in the corresponding pixel. If floating point representation is used the confidence image is normalized to the range [0,1], for integer representation the maximum possible integer represents maximum confidence.*/
	ImageComponentSelector_Scatter,	/*!< The acquisition of data measuring how much light is scattered around the reflected light. In processing this is used as an additional intensity image, often together with the standard intensity.*/
	NUM_IMAGECOMPONENTSELECTOR
} spinImageComponentSelectorEnums;

typedef enum _spinBinningSelectorEnums	/*!< Selects which binning engine is controlled by the BinningHorizontal and BinningVertical features.*/
{
	BinningSelector_Sensor,	/*!< Selected features will control the sensor binning.*/
	BinningSelector_Region0,	/*!< Selected feature will control the region 0 binning.*/
	BinningSelector_Region1,	/*!< Selected feature will control the region 1 binning.*/
	BinningSelector_Region2,	/*!< Selected feature will control the region 2 binning.*/
	NUM_BINNINGSELECTOR
} spinBinningSelectorEnums;

typedef enum _spinBinningHorizontalModeEnums	/*!< Sets the mode to use to combine horizontal photo-sensitive cells together when BinningHorizontal is used.*/
{
	BinningHorizontalMode_Sum,	/*!< The response from the combined cells will be added, resulting in increased sensitivity.*/
	BinningHorizontalMode_Average,	/*!< The response from the combined cells will be averaged, resulting in increased signal/noise ratio.*/
	NUM_BINNINGHORIZONTALMODE
} spinBinningHorizontalModeEnums;

typedef enum _spinBinningVerticalModeEnums	/*!< Sets the mode used to combine horizontal photo-sensitive cells together when BinningVertical is used.*/
{
	BinningVerticalMode_Sum,	/*!< The response from the combined cells will be added, resulting in increased sensitivity.*/
	BinningVerticalMode_Average,	/*!< The response from the combined cells will be averaged, resulting in increased signal/noise ratio.*/
	NUM_BINNINGVERTICALMODE
} spinBinningVerticalModeEnums;

typedef enum _spinDecimationHorizontalModeEnums	/*!< Sets the mode used to reduce the horizontal resolution when DecimationHorizontal is used.*/
{
	DecimationHorizontalMode_Discard,	/*!< The value of every Nth pixel is kept, others are discarded.*/
	DecimationHorizontalMode_Average,	/*!< The value of a group of N adjacents pixels are averaged.*/
	NUM_DECIMATIONHORIZONTALMODE
} spinDecimationHorizontalModeEnums;

typedef enum _spinDecimationVerticalModeEnums	/*!< Sets the mode used to reduce the Vertical resolution when DecimationVertical is used.*/
{
	DecimationVerticalMode_Discard,	/*!< The value of every Nth pixel is kept, others are discarded.*/
	DecimationVerticalMode_Average,	/*!< The value of a group of N adjacents pixels are averaged.*/
	NUM_DECIMATIONVERTICALMODE
} spinDecimationVerticalModeEnums;

typedef enum _spinPixelFormatEnums	/*!< Format of the pixels provided by the device. It represents all the information provided by PixelSize, PixelColorFilter combined in a single feature.*/
{
	PixelFormat_Mono1p,	/*!< Monochrome 1-bit packed*/
	PixelFormat_Mono2p,	/*!< Monochrome 2-bit packed*/
	PixelFormat_Mono4p,	/*!< Monochrome 4-bit packed*/
	PixelFormat_Mono8,	/*!< Monochrome 8-bit*/
	PixelFormat_Mono8s,	/*!< Monochrome 8-bit signed*/
	PixelFormat_Mono10,	/*!< Monochrome 10-bit unpacked*/
	PixelFormat_Mono10p,	/*!< Monochrome 10-bit packed*/
	PixelFormat_Mono12,	/*!< Monochrome 12-bit unpacked*/
	PixelFormat_Mono12p,	/*!< Monochrome 12-bit packed*/
	PixelFormat_Mono14,	/*!< Monochrome 14-bit unpacked*/
	PixelFormat_Mono16,	/*!< Monochrome 16-bit*/
	PixelFormat_BayerBG8,	/*!< Bayer Blue-Green 8-bit*/
	PixelFormat_BayerBG10,	/*!< Bayer Blue-Green 10-bit unpacked*/
	PixelFormat_BayerBG10p,	/*!< Bayer Blue-Green 10-bit packed*/
	PixelFormat_BayerBG12,	/*!< Bayer Blue-Green 12-bit unpacked*/
	PixelFormat_BayerBG12p,	/*!< Bayer Blue-Green 12-bit packed*/
	PixelFormat_BayerBG16,	/*!< Bayer Blue-Green 16-bit*/
	PixelFormat_BayerGB8,	/*!< Bayer Green-Blue 8-bit*/
	PixelFormat_BayerGB10,	/*!< Bayer Green-Blue 10-bit unpacked*/
	PixelFormat_BayerGB10p,	/*!< Bayer Green-Blue 10-bit packed*/
	PixelFormat_BayerGB12,	/*!< Bayer Green-Blue 12-bit unpacked*/
	PixelFormat_BayerGB12p,	/*!< Bayer Green-Blue 12-bit packed*/
	PixelFormat_BayerGB16,	/*!< Bayer Green-Blue 16-bit*/
	PixelFormat_BayerGR8,	/*!< Bayer Green-Red 8-bit*/
	PixelFormat_BayerGR10,	/*!< Bayer Green-Red 10-bit unpacked*/
	PixelFormat_BayerGR10p,	/*!< Bayer Green-Red 10-bit packed*/
	PixelFormat_BayerGR12,	/*!< Bayer Green-Red 12-bit unpacked*/
	PixelFormat_BayerGR12p,	/*!< Bayer Green-Red 12-bit packed*/
	PixelFormat_BayerGR16,	/*!< Bayer Green-Red 16-bit*/
	PixelFormat_BayerRG8,	/*!< Bayer Red-Green 8-bit*/
	PixelFormat_BayerRG10,	/*!< Bayer Red-Green 10-bit unpacked*/
	PixelFormat_BayerRG10p,	/*!< Bayer Red-Green 10-bit packed*/
	PixelFormat_BayerRG12,	/*!< Bayer Red-Green 12-bit unpacked*/
	PixelFormat_BayerRG12p,	/*!< Bayer Red-Green 12-bit packed*/
	PixelFormat_BayerRG16,	/*!< Bayer Red-Green 16-bit*/
	PixelFormat_RGBa8,	/*!< Red-Green-Blue-alpha 8-bit*/
	PixelFormat_RGBa10,	/*!< Red-Green-Blue-alpha 10-bit unpacked*/
	PixelFormat_RGBa10p,	/*!< Red-Green-Blue-alpha 10-bit packed*/
	PixelFormat_RGBa12,	/*!< Red-Green-Blue-alpha 12-bit unpacked*/
	PixelFormat_RGBa12p,	/*!< Red-Green-Blue-alpha 12-bit packed*/
	PixelFormat_RGBa14,	/*!< Red-Green-Blue-alpha 14-bit unpacked*/
	PixelFormat_RGBa16,	/*!< Red-Green-Blue-alpha 16-bit*/
	PixelFormat_RGB8,	/*!< Red-Green-Blue 8-bit*/
	PixelFormat_RGB8_Planar,	/*!< Red-Green-Blue 8-bit planar*/
	PixelFormat_RGB10,	/*!< Red-Green-Blue 10-bit unpacked*/
	PixelFormat_RGB10_Planar,	/*!< Red-Green-Blue 10-bit unpacked planar*/
	PixelFormat_RGB10p,	/*!< Red-Green-Blue 10-bit packed*/
	PixelFormat_RGB10p32,	/*!< Red-Green-Blue 10-bit packed into 32-bit*/
	PixelFormat_RGB12,	/*!< Red-Green-Blue 12-bit unpacked*/
	PixelFormat_RGB12_Planar,	/*!< Red-Green-Blue 12-bit unpacked planar*/
	PixelFormat_RGB12p,	/*!< Red-Green-Blue 12-bit packed  */
	PixelFormat_RGB14,	/*!< Red-Green-Blue 14-bit unpacked*/
	PixelFormat_RGB16,	/*!< Red-Green-Blue 16-bit  */
	PixelFormat_RGB16_Planar,	/*!< Red-Green-Blue 16-bit planar*/
	PixelFormat_RGB565p,	/*!< Red-Green-Blue 5/6/5-bit packed*/
	PixelFormat_BGRa8,	/*!< Blue-Green-Red-alpha 8-bit*/
	PixelFormat_BGRa10,	/*!< Blue-Green-Red-alpha 10-bit unpacked*/
	PixelFormat_BGRa10p,	/*!< Blue-Green-Red-alpha 10-bit packed*/
	PixelFormat_BGRa12,	/*!< Blue-Green-Red-alpha 12-bit unpacked*/
	PixelFormat_BGRa12p,	/*!< Blue-Green-Red-alpha 12-bit packed*/
	PixelFormat_BGRa14,	/*!< Blue-Green-Red-alpha 14-bit unpacked*/
	PixelFormat_BGRa16,	/*!< Blue-Green-Red-alpha 16-bit*/
	PixelFormat_BGR8,	/*!< Blue-Green-Red 8-bit*/
	PixelFormat_BGR10,	/*!< Blue-Green-Red 10-bit unpacked*/
	PixelFormat_BGR10p,	/*!< Blue-Green-Red 10-bit packed*/
	PixelFormat_BGR12,	/*!< Blue-Green-Red 12-bit unpacked*/
	PixelFormat_BGR12p,	/*!< Blue-Green-Red 12-bit packed*/
	PixelFormat_BGR14,	/*!< Blue-Green-Red 14-bit unpacked*/
	PixelFormat_BGR16,	/*!< Blue-Green-Red 16-bit*/
	PixelFormat_BGR565p,	/*!< Blue-Green-Red 5/6/5-bit packed*/
	PixelFormat_R8,	/*!< Red 8-bit*/
	PixelFormat_R10,	/*!< Red 10-bit*/
	PixelFormat_R12,	/*!< Red 12-bit*/
	PixelFormat_R16,	/*!< Red 16-bit*/
	PixelFormat_G8,	/*!< Green 8-bit*/
	PixelFormat_G10,	/*!< Green 10-bit*/
	PixelFormat_G12,	/*!< Green 12-bit*/
	PixelFormat_G16,	/*!< Green 16-bit*/
	PixelFormat_B8,	/*!< Blue 8-bit*/
	PixelFormat_B10,	/*!< Blue 10-bit*/
	PixelFormat_B12,	/*!< Blue 12-bit*/
	PixelFormat_B16,	/*!< Blue 16-bit*/
	PixelFormat_Coord3D_ABC8,	/*!< 3D coordinate A-B-C 8-bit*/
	PixelFormat_Coord3D_ABC8_Planar,	/*!< 3D coordinate A-B-C 8-bit planar*/
	PixelFormat_Coord3D_ABC10p,	/*!< 3D coordinate A-B-C 10-bit packed*/
	PixelFormat_Coord3D_ABC10p_Planar,	/*!< 3D coordinate A-B-C 10-bit packed planar*/
	PixelFormat_Coord3D_ABC12p,	/*!< 3D coordinate A-B-C 12-bit packed*/
	PixelFormat_Coord3D_ABC12p_Planar,	/*!< 3D coordinate A-B-C 12-bit packed planar*/
	PixelFormat_Coord3D_ABC16,	/*!< 3D coordinate A-B-C 16-bit*/
	PixelFormat_Coord3D_ABC16_Planar,	/*!< 3D coordinate A-B-C 16-bit planar*/
	PixelFormat_Coord3D_ABC32f,	/*!< 3D coordinate A-B-C 32-bit floating point*/
	PixelFormat_Coord3D_ABC32f_Planar,	/*!< 3D coordinate A-B-C 32-bit floating point planar*/
	PixelFormat_Coord3D_AC8,	/*!< 3D coordinate A-C 8-bit*/
	PixelFormat_Coord3D_AC8_Planar,	/*!< 3D coordinate A-C 8-bit planar*/
	PixelFormat_Coord3D_AC10p,	/*!< 3D coordinate A-C 10-bit packed*/
	PixelFormat_Coord3D_AC10p_Planar,	/*!< 3D coordinate A-C 10-bit packed planar*/
	PixelFormat_Coord3D_AC12p,	/*!< 3D coordinate A-C 12-bit packed*/
	PixelFormat_Coord3D_AC12p_Planar,	/*!< 3D coordinate A-C 12-bit packed planar*/
	PixelFormat_Coord3D_AC16,	/*!< 3D coordinate A-C 16-bit*/
	PixelFormat_Coord3D_AC16_Planar,	/*!< 3D coordinate A-C 16-bit planar*/
	PixelFormat_Coord3D_AC32f,	/*!< 3D coordinate A-C 32-bit floating point*/
	PixelFormat_Coord3D_AC32f_Planar,	/*!< 3D coordinate A-C 32-bit floating point planar*/
	PixelFormat_Coord3D_A8,	/*!< 3D coordinate A 8-bit*/
	PixelFormat_Coord3D_A10p,	/*!< 3D coordinate A 10-bit packed*/
	PixelFormat_Coord3D_A12p,	/*!< 3D coordinate A 12-bit packed*/
	PixelFormat_Coord3D_A16,	/*!< 3D coordinate A 16-bit*/
	PixelFormat_Coord3D_A32f,	/*!< 3D coordinate A 32-bit floating point*/
	PixelFormat_Coord3D_B8,	/*!< 3D coordinate B 8-bit*/
	PixelFormat_Coord3D_B10p,	/*!< 3D coordinate B 10-bit packed*/
	PixelFormat_Coord3D_B12p,	/*!< 3D coordinate B 12-bit packed*/
	PixelFormat_Coord3D_B16,	/*!< 3D coordinate B 16-bit*/
	PixelFormat_Coord3D_B32f,	/*!< 3D coordinate B 32-bit floating point*/
	PixelFormat_Coord3D_C8,	/*!< 3D coordinate C 8-bit*/
	PixelFormat_Coord3D_C10p,	/*!< 3D coordinate C 10-bit packed*/
	PixelFormat_Coord3D_C12p,	/*!< 3D coordinate C 12-bit packed*/
	PixelFormat_Coord3D_C16,	/*!< 3D coordinate C 16-bit*/
	PixelFormat_Coord3D_C32f,	/*!< 3D coordinate C 32-bit floating point*/
	PixelFormat_Confidence1,	/*!< Confidence 1-bit unpacked*/
	PixelFormat_Confidence1p,	/*!< Confidence 1-bit packed*/
	PixelFormat_Confidence8,	/*!< Confidence 8-bit*/
	PixelFormat_Confidence16,	/*!< Confidence 16-bit*/
	PixelFormat_Confidence32f,	/*!< Confidence 32-bit floating point*/
	PixelFormat_BiColorBGRG8,	/*!< Bi-color Blue/Green - Red/Green 8-bit*/
	PixelFormat_BiColorBGRG10,	/*!< Bi-color Blue/Green - Red/Green 10-bit unpacked*/
	PixelFormat_BiColorBGRG10p,	/*!< Bi-color Blue/Green - Red/Green 10-bit packed*/
	PixelFormat_BiColorBGRG12,	/*!< Bi-color Blue/Green - Red/Green 12-bit unpacked*/
	PixelFormat_BiColorBGRG12p,	/*!< Bi-color Blue/Green - Red/Green 12-bit packed*/
	PixelFormat_BiColorRGBG8,	/*!< Bi-color Red/Green - Blue/Green 8-bit*/
	PixelFormat_BiColorRGBG10,	/*!< Bi-color Red/Green - Blue/Green 10-bit unpacked*/
	PixelFormat_BiColorRGBG10p,	/*!< Bi-color Red/Green - Blue/Green 10-bit packed*/
	PixelFormat_BiColorRGBG12,	/*!< Bi-color Red/Green - Blue/Green 12-bit unpacked*/
	PixelFormat_BiColorRGBG12p,	/*!< Bi-color Red/Green - Blue/Green 12-bit packed*/
	PixelFormat_SCF1WBWG8,	/*!< Sparse Color Filter #1 White-Blue-White-Green 8-bit*/
	PixelFormat_SCF1WBWG10,	/*!< Sparse Color Filter #1 White-Blue-White-Green 10-bit unpacked*/
	PixelFormat_SCF1WBWG10p,	/*!< Sparse Color Filter #1 White-Blue-White-Green 10-bit packed*/
	PixelFormat_SCF1WBWG12,	/*!< Sparse Color Filter #1 White-Blue-White-Green 12-bit unpacked*/
	PixelFormat_SCF1WBWG12p,	/*!< Sparse Color Filter #1 White-Blue-White-Green 12-bit packed*/
	PixelFormat_SCF1WBWG14,	/*!< Sparse Color Filter #1 White-Blue-White-Green 14-bit unpacked*/
	PixelFormat_SCF1WBWG16,	/*!< Sparse Color Filter #1 White-Blue-White-Green 16-bit unpacked*/
	PixelFormat_SCF1WGWB8,	/*!< Sparse Color Filter #1 White-Green-White-Blue 8-bit*/
	PixelFormat_SCF1WGWB10,	/*!< Sparse Color Filter #1 White-Green-White-Blue 10-bit unpacked*/
	PixelFormat_SCF1WGWB10p,	/*!< Sparse Color Filter #1 White-Green-White-Blue 10-bit packed*/
	PixelFormat_SCF1WGWB12,	/*!< Sparse Color Filter #1 White-Green-White-Blue 12-bit unpacked*/
	PixelFormat_SCF1WGWB12p,	/*!< Sparse Color Filter #1 White-Green-White-Blue 12-bit packed*/
	PixelFormat_SCF1WGWB14,	/*!< Sparse Color Filter #1 White-Green-White-Blue 14-bit unpacked*/
	PixelFormat_SCF1WGWB16,	/*!< Sparse Color Filter #1 White-Green-White-Blue 16-bit*/
	PixelFormat_SCF1WGWR8,	/*!< Sparse Color Filter #1 White-Green-White-Red 8-bit*/
	PixelFormat_SCF1WGWR10,	/*!< Sparse Color Filter #1 White-Green-White-Red 10-bit unpacked*/
	PixelFormat_SCF1WGWR10p,	/*!< Sparse Color Filter #1 White-Green-White-Red 10-bit packed*/
	PixelFormat_SCF1WGWR12,	/*!< Sparse Color Filter #1 White-Green-White-Red 12-bit unpacked*/
	PixelFormat_SCF1WGWR12p,	/*!< Sparse Color Filter #1 White-Green-White-Red 12-bit packed*/
	PixelFormat_SCF1WGWR14,	/*!< Sparse Color Filter #1 White-Green-White-Red 14-bit unpacked*/
	PixelFormat_SCF1WGWR16,	/*!< Sparse Color Filter #1 White-Green-White-Red 16-bit*/
	PixelFormat_SCF1WRWG8,	/*!< Sparse Color Filter #1 White-Red-White-Green 8-bit*/
	PixelFormat_SCF1WRWG10,	/*!< Sparse Color Filter #1 White-Red-White-Green 10-bit unpacked*/
	PixelFormat_SCF1WRWG10p,	/*!< Sparse Color Filter #1 White-Red-White-Green 10-bit packed*/
	PixelFormat_SCF1WRWG12,	/*!< Sparse Color Filter #1 White-Red-White-Green 12-bit unpacked*/
	PixelFormat_SCF1WRWG12p,	/*!< Sparse Color Filter #1 White-Red-White-Green 12-bit packed*/
	PixelFormat_SCF1WRWG14,	/*!< Sparse Color Filter #1 White-Red-White-Green 14-bit unpacked*/
	PixelFormat_SCF1WRWG16,	/*!< Sparse Color Filter #1 White-Red-White-Green 16-bit*/
	PixelFormat_YCbCr8,	/*!< YCbCr 4:4:4 8-bit*/
	PixelFormat_YCbCr8_CbYCr,	/*!< YCbCr 4:4:4 8-bit*/
	PixelFormat_YCbCr10_CbYCr,	/*!< YCbCr 4:4:4 10-bit unpacked*/
	PixelFormat_YCbCr10p_CbYCr,	/*!< YCbCr 4:4:4 10-bit packed*/
	PixelFormat_YCbCr12_CbYCr,	/*!< YCbCr 4:4:4 12-bit unpacked*/
	PixelFormat_YCbCr12p_CbYCr,	/*!< YCbCr 4:4:4 12-bit packed*/
	PixelFormat_YCbCr411_8,	/*!< YCbCr 4:1:1 8-bit*/
	PixelFormat_YCbCr411_8_CbYYCrYY,	/*!< YCbCr 4:1:1 8-bit*/
	PixelFormat_YCbCr422_8,	/*!< YCbCr 4:2:2 8-bit*/
	PixelFormat_YCbCr422_8_CbYCrY,	/*!< YCbCr 4:2:2 8-bit*/
	PixelFormat_YCbCr422_10,	/*!< YCbCr 4:2:2 10-bit unpacked*/
	PixelFormat_YCbCr422_10_CbYCrY,	/*!< YCbCr 4:2:2 10-bit unpacked*/
	PixelFormat_YCbCr422_10p,	/*!< YCbCr 4:2:2 10-bit packed*/
	PixelFormat_YCbCr422_10p_CbYCrY,	/*!< YCbCr 4:2:2 10-bit packed*/
	PixelFormat_YCbCr422_12,	/*!< YCbCr 4:2:2 12-bit unpacked*/
	PixelFormat_YCbCr422_12_CbYCrY,	/*!< YCbCr 4:2:2 12-bit unpacked*/
	PixelFormat_YCbCr422_12p,	/*!< YCbCr 4:2:2 12-bit packed*/
	PixelFormat_YCbCr422_12p_CbYCrY,	/*!< YCbCr 4:2:2 12-bit packed*/
	PixelFormat_YCbCr601_8_CbYCr,	/*!< YCbCr 4:4:4 8-bit BT.601*/
	PixelFormat_YCbCr601_10_CbYCr,	/*!< YCbCr 4:4:4 10-bit unpacked BT.601*/
	PixelFormat_YCbCr601_10p_CbYCr,	/*!< YCbCr 4:4:4 10-bit packed BT.601*/
	PixelFormat_YCbCr601_12_CbYCr,	/*!< YCbCr 4:4:4 12-bit unpacked BT.601*/
	PixelFormat_YCbCr601_12p_CbYCr,	/*!< YCbCr 4:4:4 12-bit packed BT.601*/
	PixelFormat_YCbCr601_411_8_CbYYCrYY,	/*!< YCbCr 4:1:1 8-bit BT.601*/
	PixelFormat_YCbCr601_422_8,	/*!< YCbCr 4:2:2 8-bit BT.601*/
	PixelFormat_YCbCr601_422_8_CbYCrY,	/*!< YCbCr 4:2:2 8-bit BT.601*/
	PixelFormat_YCbCr601_422_10,	/*!< YCbCr 4:2:2 10-bit unpacked BT.601*/
	PixelFormat_YCbCr601_422_10_CbYCrY,	/*!< YCbCr 4:2:2 10-bit unpacked BT.601*/
	PixelFormat_YCbCr601_422_10p,	/*!< YCbCr 4:2:2 10-bit packed BT.601*/
	PixelFormat_YCbCr601_422_10p_CbYCrY,	/*!< YCbCr 4:2:2 10-bit packed BT.601*/
	PixelFormat_YCbCr601_422_12,	/*!< YCbCr 4:2:2 12-bit unpacked BT.601*/
	PixelFormat_YCbCr601_422_12_CbYCrY,	/*!< YCbCr 4:2:2 12-bit unpacked BT.601*/
	PixelFormat_YCbCr601_422_12p,	/*!< YCbCr 4:2:2 12-bit packed BT.601*/
	PixelFormat_YCbCr601_422_12p_CbYCrY,	/*!< YCbCr 4:2:2 12-bit packed BT.601*/
	PixelFormat_YCbCr709_8_CbYCr,	/*!< YCbCr 4:4:4 8-bit BT.709*/
	PixelFormat_YCbCr709_10_CbYCr,	/*!< YCbCr 4:4:4 10-bit unpacked BT.709*/
	PixelFormat_YCbCr709_10p_CbYCr,	/*!< YCbCr 4:4:4 10-bit packed BT.709*/
	PixelFormat_YCbCr709_12_CbYCr,	/*!< YCbCr 4:4:4 12-bit unpacked BT.709*/
	PixelFormat_YCbCr709_12p_CbYCr,	/*!< YCbCr 4:4:4 12-bit packed BT.709*/
	PixelFormat_YCbCr709_411_8_CbYYCrYY,	/*!< YCbCr 4:1:1 8-bit BT.709*/
	PixelFormat_YCbCr709_422_8,	/*!< YCbCr 4:2:2 8-bit BT.709*/
	PixelFormat_YCbCr709_422_8_CbYCrY,	/*!< YCbCr 4:2:2 8-bit BT.709*/
	PixelFormat_YCbCr709_422_10,	/*!< YCbCr 4:2:2 10-bit unpacked BT.709*/
	PixelFormat_YCbCr709_422_10_CbYCrY,	/*!< YCbCr 4:2:2 10-bit unpacked BT.709*/
	PixelFormat_YCbCr709_422_10p,	/*!< YCbCr 4:2:2 10-bit packed BT.709*/
	PixelFormat_YCbCr709_422_10p_CbYCrY,	/*!< YCbCr 4:2:2 10-bit packed BT.709*/
	PixelFormat_YCbCr709_422_12,	/*!< YCbCr 4:2:2 12-bit unpacked BT.709*/
	PixelFormat_YCbCr709_422_12_CbYCrY,	/*!< YCbCr 4:2:2 12-bit unpacked BT.709*/
	PixelFormat_YCbCr709_422_12p,	/*!< YCbCr 4:2:2 12-bit packed BT.709*/
	PixelFormat_YCbCr709_422_12p_CbYCrY,	/*!< YCbCr 4:2:2 12-bit packed BT.709*/
	PixelFormat_YUV8_UYV,	/*!< YUV 4:4:4 8-bit*/
	PixelFormat_YUV411_8_UYYVYY,	/*!< YUV 4:1:1 8-bit*/
	PixelFormat_YUV422_8,	/*!< YUV 4:2:2 8-bit*/
	PixelFormat_YUV422_8_UYVY,	/*!< YUV 4:2:2 8-bit*/
	PixelFormat_Mono12Packed,	/*!< Pixel format set Mono 12 Packed.*/
	PixelFormat_BayerGR12Packed,	/*!< Pixel format set BayerGR 12 Packed. (GigE Vision 2.0)*/
	PixelFormat_BayerRG12Packed,	/*!< Pixel format set BayerRG 12 Packed. (GigE Vision 2.0)*/
	PixelFormat_BayerGB12Packed,	/*!< Pixel format set BayerGB 12 Packed. (GigE Vision 2.0)*/
	PixelFormat_BayerBG12Packed,	/*!< Pixel format set BayerBG 12 Packed. (GigE Vision 2.0)*/
	PixelFormat_YUV411Packed,	/*!< Pixel format set YUV411 Packed.*/
	PixelFormat_YUV422Packed,	/*!< Pixel format set to YUV 422 Packed.*/
	PixelFormat_YUV444Packed,	/*!< Pixel format set to YUV 444 Packed.*/
	PixelFormat_RGB8Packed,	/*!< Pixel format set RGB 8 Packed.*/
	PixelFormat_Raw16,	/*!< Raw 16 bit.*/
	PixelFormat_Raw8,	/*!< Raw bit.*/
	PixelFormat_BayerGR10Packed,	/*!< Bayer GR 10 bit packed (GigE Vision 2.0).*/
	PixelFormat_BayerRG10Packed,	/*!< Bayer RG 10 bit packed (GigE Vision 2.0).*/
	PixelFormat_BayerGB10Packed,	/*!< Bayer GB 10 bit packed (GigE Vision 2.0).*/
	PixelFormat_BayerBG10Packed,	/*!< Bayer BG 10 bit packed (GigE Vision 2.0).*/
	UNKNOWN_PIXELFORMAT,
	NUM_PIXELFORMAT
} spinPixelFormatEnums;

typedef enum _spinPixelFormatInfoSelectorEnums	/*!< Select the pixel format for which the information will be returned.*/
{
	PixelFormatInfoSelector_Mono1p,	/*!< Monochrome 1-bit packed*/
	PixelFormatInfoSelector_Mono2p,	/*!< Monochrome 2-bit packed*/
	PixelFormatInfoSelector_Mono4p,	/*!< Monochrome 4-bit packed*/
	PixelFormatInfoSelector_Mono8,	/*!< Monochrome 8-bit*/
	PixelFormatInfoSelector_Mono8s,	/*!< Monochrome 8-bit signed*/
	PixelFormatInfoSelector_Mono10,	/*!< Monochrome 10-bit unpacked*/
	PixelFormatInfoSelector_Mono10p,	/*!< Monochrome 10-bit packed*/
	PixelFormatInfoSelector_Mono12,	/*!< Monochrome 12-bit unpacked*/
	PixelFormatInfoSelector_Mono12p,	/*!< Monochrome 12-bit packed*/
	PixelFormatInfoSelector_Mono14,	/*!< Monochrome 14-bit unpacked*/
	PixelFormatInfoSelector_Mono16,	/*!< Monochrome 16-bit*/
	PixelFormatInfoSelector_BayerBG8,	/*!< Bayer Blue-Green 8-bit*/
	PixelFormatInfoSelector_BayerBG10,	/*!< Bayer Blue-Green 10-bit unpacked*/
	PixelFormatInfoSelector_BayerBG10p,	/*!< Bayer Blue-Green 10-bit packed*/
	PixelFormatInfoSelector_BayerBG12,	/*!< Bayer Blue-Green 12-bit unpacked*/
	PixelFormatInfoSelector_BayerBG12p,	/*!< Bayer Blue-Green 12-bit packed*/
	PixelFormatInfoSelector_BayerBG16,	/*!< Bayer Blue-Green 16-bit*/
	PixelFormatInfoSelector_BayerGB8,	/*!< Bayer Green-Blue 8-bit*/
	PixelFormatInfoSelector_BayerGB10,	/*!< Bayer Green-Blue 10-bit unpacked*/
	PixelFormatInfoSelector_BayerGB10p,	/*!< Bayer Green-Blue 10-bit packed*/
	PixelFormatInfoSelector_BayerGB12,	/*!< Bayer Green-Blue 12-bit unpacked*/
	PixelFormatInfoSelector_BayerGB12p,	/*!< Bayer Green-Blue 12-bit packed*/
	PixelFormatInfoSelector_BayerGB16,	/*!< Bayer Green-Blue 16-bit*/
	PixelFormatInfoSelector_BayerGR8,	/*!< Bayer Green-Red 8-bit*/
	PixelFormatInfoSelector_BayerGR10,	/*!< Bayer Green-Red 10-bit unpacked*/
	PixelFormatInfoSelector_BayerGR10p,	/*!< Bayer Green-Red 10-bit packed*/
	PixelFormatInfoSelector_BayerGR12,	/*!< Bayer Green-Red 12-bit unpacked*/
	PixelFormatInfoSelector_BayerGR12p,	/*!< Bayer Green-Red 12-bit packed*/
	PixelFormatInfoSelector_BayerGR16,	/*!< Bayer Green-Red 16-bit*/
	PixelFormatInfoSelector_BayerRG8,	/*!< Bayer Red-Green 8-bit*/
	PixelFormatInfoSelector_BayerRG10,	/*!< Bayer Red-Green 10-bit unpacked*/
	PixelFormatInfoSelector_BayerRG10p,	/*!< Bayer Red-Green 10-bit packed*/
	PixelFormatInfoSelector_BayerRG12,	/*!< Bayer Red-Green 12-bit unpacked*/
	PixelFormatInfoSelector_BayerRG12p,	/*!< Bayer Red-Green 12-bit packed*/
	PixelFormatInfoSelector_BayerRG16,	/*!< Bayer Red-Green 16-bit*/
	PixelFormatInfoSelector_RGBa8,	/*!< Red-Green-Blue-alpha 8-bit*/
	PixelFormatInfoSelector_RGBa10,	/*!< Red-Green-Blue-alpha 10-bit unpacked*/
	PixelFormatInfoSelector_RGBa10p,	/*!< Red-Green-Blue-alpha 10-bit packed*/
	PixelFormatInfoSelector_RGBa12,	/*!< Red-Green-Blue-alpha 12-bit unpacked*/
	PixelFormatInfoSelector_RGBa12p,	/*!< Red-Green-Blue-alpha 12-bit packed*/
	PixelFormatInfoSelector_RGBa14,	/*!< Red-Green-Blue-alpha 14-bit unpacked*/
	PixelFormatInfoSelector_RGBa16,	/*!< Red-Green-Blue-alpha 16-bit*/
	PixelFormatInfoSelector_RGB8,	/*!< Red-Green-Blue 8-bit*/
	PixelFormatInfoSelector_RGB8_Planar,	/*!< Red-Green-Blue 8-bit planar*/
	PixelFormatInfoSelector_RGB10,	/*!< Red-Green-Blue 10-bit unpacked*/
	PixelFormatInfoSelector_RGB10_Planar,	/*!< Red-Green-Blue 10-bit unpacked planar*/
	PixelFormatInfoSelector_RGB10p,	/*!< Red-Green-Blue 10-bit packed*/
	PixelFormatInfoSelector_RGB10p32,	/*!< Red-Green-Blue 10-bit packed into 32-bit*/
	PixelFormatInfoSelector_RGB12,	/*!< Red-Green-Blue 12-bit unpacked*/
	PixelFormatInfoSelector_RGB12_Planar,	/*!< Red-Green-Blue 12-bit unpacked planar*/
	PixelFormatInfoSelector_RGB12p,	/*!< Red-Green-Blue 12-bit packed  */
	PixelFormatInfoSelector_RGB14,	/*!< Red-Green-Blue 14-bit unpacked*/
	PixelFormatInfoSelector_RGB16,	/*!< Red-Green-Blue 16-bit  */
	PixelFormatInfoSelector_RGB16_Planar,	/*!< Red-Green-Blue 16-bit planar*/
	PixelFormatInfoSelector_RGB565p,	/*!< Red-Green-Blue 5/6/5-bit packed*/
	PixelFormatInfoSelector_BGRa8,	/*!< Blue-Green-Red-alpha 8-bit*/
	PixelFormatInfoSelector_BGRa10,	/*!< Blue-Green-Red-alpha 10-bit unpacked*/
	PixelFormatInfoSelector_BGRa10p,	/*!< Blue-Green-Red-alpha 10-bit packed*/
	PixelFormatInfoSelector_BGRa12,	/*!< Blue-Green-Red-alpha 12-bit unpacked*/
	PixelFormatInfoSelector_BGRa12p,	/*!< Blue-Green-Red-alpha 12-bit packed*/
	PixelFormatInfoSelector_BGRa14,	/*!< Blue-Green-Red-alpha 14-bit unpacked*/
	PixelFormatInfoSelector_BGRa16,	/*!< Blue-Green-Red-alpha 16-bit*/
	PixelFormatInfoSelector_BGR8,	/*!< Blue-Green-Red 8-bit*/
	PixelFormatInfoSelector_BGR10,	/*!< Blue-Green-Red 10-bit unpacked*/
	PixelFormatInfoSelector_BGR10p,	/*!< Blue-Green-Red 10-bit packed*/
	PixelFormatInfoSelector_BGR12,	/*!< Blue-Green-Red 12-bit unpacked*/
	PixelFormatInfoSelector_BGR12p,	/*!< Blue-Green-Red 12-bit packed*/
	PixelFormatInfoSelector_BGR14,	/*!< Blue-Green-Red 14-bit unpacked*/
	PixelFormatInfoSelector_BGR16,	/*!< Blue-Green-Red 16-bit*/
	PixelFormatInfoSelector_BGR565p,	/*!< Blue-Green-Red 5/6/5-bit packed*/
	PixelFormatInfoSelector_R8,	/*!< Red 8-bit*/
	PixelFormatInfoSelector_R10,	/*!< Red 10-bit*/
	PixelFormatInfoSelector_R12,	/*!< Red 12-bit*/
	PixelFormatInfoSelector_R16,	/*!< Red 16-bit*/
	PixelFormatInfoSelector_G8,	/*!< Green 8-bit*/
	PixelFormatInfoSelector_G10,	/*!< Green 10-bit*/
	PixelFormatInfoSelector_G12,	/*!< Green 12-bit*/
	PixelFormatInfoSelector_G16,	/*!< Green 16-bit*/
	PixelFormatInfoSelector_B8,	/*!< Blue 8-bit*/
	PixelFormatInfoSelector_B10,	/*!< Blue 10-bit*/
	PixelFormatInfoSelector_B12,	/*!< Blue 12-bit*/
	PixelFormatInfoSelector_B16,	/*!< Blue 16-bit*/
	PixelFormatInfoSelector_Coord3D_ABC8,	/*!< 3D coordinate A-B-C 8-bit*/
	PixelFormatInfoSelector_Coord3D_ABC8_Planar,	/*!< 3D coordinate A-B-C 8-bit planar*/
	PixelFormatInfoSelector_Coord3D_ABC10p,	/*!< 3D coordinate A-B-C 10-bit packed*/
	PixelFormatInfoSelector_Coord3D_ABC10p_Planar,	/*!< 3D coordinate A-B-C 10-bit packed planar*/
	PixelFormatInfoSelector_Coord3D_ABC12p,	/*!< 3D coordinate A-B-C 12-bit packed*/
	PixelFormatInfoSelector_Coord3D_ABC12p_Planar,	/*!< 3D coordinate A-B-C 12-bit packed planar*/
	PixelFormatInfoSelector_Coord3D_ABC16,	/*!< 3D coordinate A-B-C 16-bit*/
	PixelFormatInfoSelector_Coord3D_ABC16_Planar,	/*!< 3D coordinate A-B-C 16-bit planar*/
	PixelFormatInfoSelector_Coord3D_ABC32f,	/*!< 3D coordinate A-B-C 32-bit floating point*/
	PixelFormatInfoSelector_Coord3D_ABC32f_Planar,	/*!< 3D coordinate A-B-C 32-bit floating point planar*/
	PixelFormatInfoSelector_Coord3D_AC8,	/*!< 3D coordinate A-C 8-bit*/
	PixelFormatInfoSelector_Coord3D_AC8_Planar,	/*!< 3D coordinate A-C 8-bit planar*/
	PixelFormatInfoSelector_Coord3D_AC10p,	/*!< 3D coordinate A-C 10-bit packed*/
	PixelFormatInfoSelector_Coord3D_AC10p_Planar,	/*!< 3D coordinate A-C 10-bit packed planar*/
	PixelFormatInfoSelector_Coord3D_AC12p,	/*!< 3D coordinate A-C 12-bit packed*/
	PixelFormatInfoSelector_Coord3D_AC12p_Planar,	/*!< 3D coordinate A-C 12-bit packed planar*/
	PixelFormatInfoSelector_Coord3D_AC16,	/*!< 3D coordinate A-C 16-bit*/
	PixelFormatInfoSelector_Coord3D_AC16_Planar,	/*!< 3D coordinate A-C 16-bit planar*/
	PixelFormatInfoSelector_Coord3D_AC32f,	/*!< 3D coordinate A-C 32-bit floating point*/
	PixelFormatInfoSelector_Coord3D_AC32f_Planar,	/*!< 3D coordinate A-C 32-bit floating point planar*/
	PixelFormatInfoSelector_Coord3D_A8,	/*!< 3D coordinate A 8-bit*/
	PixelFormatInfoSelector_Coord3D_A10p,	/*!< 3D coordinate A 10-bit packed*/
	PixelFormatInfoSelector_Coord3D_A12p,	/*!< 3D coordinate A 12-bit packed*/
	PixelFormatInfoSelector_Coord3D_A16,	/*!< 3D coordinate A 16-bit*/
	PixelFormatInfoSelector_Coord3D_A32f,	/*!< 3D coordinate A 32-bit floating point*/
	PixelFormatInfoSelector_Coord3D_B8,	/*!< 3D coordinate B 8-bit*/
	PixelFormatInfoSelector_Coord3D_B10p,	/*!< 3D coordinate B 10-bit packed*/
	PixelFormatInfoSelector_Coord3D_B12p,	/*!< 3D coordinate B 12-bit packed*/
	PixelFormatInfoSelector_Coord3D_B16,	/*!< 3D coordinate B 16-bit*/
	PixelFormatInfoSelector_Coord3D_B32f,	/*!< 3D coordinate B 32-bit floating point*/
	PixelFormatInfoSelector_Coord3D_C8,	/*!< 3D coordinate C 8-bit*/
	PixelFormatInfoSelector_Coord3D_C10p,	/*!< 3D coordinate C 10-bit packed*/
	PixelFormatInfoSelector_Coord3D_C12p,	/*!< 3D coordinate C 12-bit packed*/
	PixelFormatInfoSelector_Coord3D_C16,	/*!< 3D coordinate C 16-bit*/
	PixelFormatInfoSelector_Coord3D_C32f,	/*!< 3D coordinate C 32-bit floating point*/
	PixelFormatInfoSelector_Confidence1,	/*!< Confidence 1-bit unpacked*/
	PixelFormatInfoSelector_Confidence1p,	/*!< Confidence 1-bit packed*/
	PixelFormatInfoSelector_Confidence8,	/*!< Confidence 8-bit*/
	PixelFormatInfoSelector_Confidence16,	/*!< Confidence 16-bit*/
	PixelFormatInfoSelector_Confidence32f,	/*!< Confidence 32-bit floating point*/
	PixelFormatInfoSelector_BiColorBGRG8,	/*!< Bi-color Blue/Green - Red/Green 8-bit*/
	PixelFormatInfoSelector_BiColorBGRG10,	/*!< Bi-color Blue/Green - Red/Green 10-bit unpacked*/
	PixelFormatInfoSelector_BiColorBGRG10p,	/*!< Bi-color Blue/Green - Red/Green 10-bit packed*/
	PixelFormatInfoSelector_BiColorBGRG12,	/*!< Bi-color Blue/Green - Red/Green 12-bit unpacked*/
	PixelFormatInfoSelector_BiColorBGRG12p,	/*!< Bi-color Blue/Green - Red/Green 12-bit packed*/
	PixelFormatInfoSelector_BiColorRGBG8,	/*!< Bi-color Red/Green - Blue/Green 8-bit*/
	PixelFormatInfoSelector_BiColorRGBG10,	/*!< Bi-color Red/Green - Blue/Green 10-bit unpacked*/
	PixelFormatInfoSelector_BiColorRGBG10p,	/*!< Bi-color Red/Green - Blue/Green 10-bit packed*/
	PixelFormatInfoSelector_BiColorRGBG12,	/*!< Bi-color Red/Green - Blue/Green 12-bit unpacked*/
	PixelFormatInfoSelector_BiColorRGBG12p,	/*!< Bi-color Red/Green - Blue/Green 12-bit packed*/
	PixelFormatInfoSelector_SCF1WBWG8,	/*!< Sparse Color Filter #1 White-Blue-White-Green 8-bit*/
	PixelFormatInfoSelector_SCF1WBWG10,	/*!< Sparse Color Filter #1 White-Blue-White-Green 10-bit unpacked*/
	PixelFormatInfoSelector_SCF1WBWG10p,	/*!< Sparse Color Filter #1 White-Blue-White-Green 10-bit packed*/
	PixelFormatInfoSelector_SCF1WBWG12,	/*!< Sparse Color Filter #1 White-Blue-White-Green 12-bit unpacked*/
	PixelFormatInfoSelector_SCF1WBWG12p,	/*!< Sparse Color Filter #1 White-Blue-White-Green 12-bit packed*/
	PixelFormatInfoSelector_SCF1WBWG14,	/*!< Sparse Color Filter #1 White-Blue-White-Green 14-bit unpacked*/
	PixelFormatInfoSelector_SCF1WBWG16,	/*!< Sparse Color Filter #1 White-Blue-White-Green 16-bit unpacked*/
	PixelFormatInfoSelector_SCF1WGWB8,	/*!< Sparse Color Filter #1 White-Green-White-Blue 8-bit*/
	PixelFormatInfoSelector_SCF1WGWB10,	/*!< Sparse Color Filter #1 White-Green-White-Blue 10-bit unpacked*/
	PixelFormatInfoSelector_SCF1WGWB10p,	/*!< Sparse Color Filter #1 White-Green-White-Blue 10-bit packed*/
	PixelFormatInfoSelector_SCF1WGWB12,	/*!< Sparse Color Filter #1 White-Green-White-Blue 12-bit unpacked*/
	PixelFormatInfoSelector_SCF1WGWB12p,	/*!< Sparse Color Filter #1 White-Green-White-Blue 12-bit packed*/
	PixelFormatInfoSelector_SCF1WGWB14,	/*!< Sparse Color Filter #1 White-Green-White-Blue 14-bit unpacked*/
	PixelFormatInfoSelector_SCF1WGWB16,	/*!< Sparse Color Filter #1 White-Green-White-Blue 16-bit*/
	PixelFormatInfoSelector_SCF1WGWR8,	/*!< Sparse Color Filter #1 White-Green-White-Red 8-bit*/
	PixelFormatInfoSelector_SCF1WGWR10,	/*!< Sparse Color Filter #1 White-Green-White-Red 10-bit unpacked*/
	PixelFormatInfoSelector_SCF1WGWR10p,	/*!< Sparse Color Filter #1 White-Green-White-Red 10-bit packed*/
	PixelFormatInfoSelector_SCF1WGWR12,	/*!< Sparse Color Filter #1 White-Green-White-Red 12-bit unpacked*/
	PixelFormatInfoSelector_SCF1WGWR12p,	/*!< Sparse Color Filter #1 White-Green-White-Red 12-bit packed*/
	PixelFormatInfoSelector_SCF1WGWR14,	/*!< Sparse Color Filter #1 White-Green-White-Red 14-bit unpacked*/
	PixelFormatInfoSelector_SCF1WGWR16,	/*!< Sparse Color Filter #1 White-Green-White-Red 16-bit*/
	PixelFormatInfoSelector_SCF1WRWG8,	/*!< Sparse Color Filter #1 White-Red-White-Green 8-bit*/
	PixelFormatInfoSelector_SCF1WRWG10,	/*!< Sparse Color Filter #1 White-Red-White-Green 10-bit unpacked*/
	PixelFormatInfoSelector_SCF1WRWG10p,	/*!< Sparse Color Filter #1 White-Red-White-Green 10-bit packed*/
	PixelFormatInfoSelector_SCF1WRWG12,	/*!< Sparse Color Filter #1 White-Red-White-Green 12-bit unpacked*/
	PixelFormatInfoSelector_SCF1WRWG12p,	/*!< Sparse Color Filter #1 White-Red-White-Green 12-bit packed*/
	PixelFormatInfoSelector_SCF1WRWG14,	/*!< Sparse Color Filter #1 White-Red-White-Green 14-bit unpacked*/
	PixelFormatInfoSelector_SCF1WRWG16,	/*!< Sparse Color Filter #1 White-Red-White-Green 16-bit*/
	PixelFormatInfoSelector_YCbCr8,	/*!< YCbCr 4:4:4 8-bit*/
	PixelFormatInfoSelector_YCbCr8_CbYCr,	/*!< YCbCr 4:4:4 8-bit*/
	PixelFormatInfoSelector_YCbCr10_CbYCr,	/*!< YCbCr 4:4:4 10-bit unpacked*/
	PixelFormatInfoSelector_YCbCr10p_CbYCr,	/*!< YCbCr 4:4:4 10-bit packed*/
	PixelFormatInfoSelector_YCbCr12_CbYCr,	/*!< YCbCr 4:4:4 12-bit unpacked*/
	PixelFormatInfoSelector_YCbCr12p_CbYCr,	/*!< YCbCr 4:4:4 12-bit packed*/
	PixelFormatInfoSelector_YCbCr411_8,	/*!< YCbCr 4:1:1 8-bit*/
	PixelFormatInfoSelector_YCbCr411_8_CbYYCrYY,	/*!< YCbCr 4:1:1 8-bit*/
	PixelFormatInfoSelector_YCbCr422_8,	/*!< YCbCr 4:2:2 8-bit*/
	PixelFormatInfoSelector_YCbCr422_8_CbYCrY,	/*!< YCbCr 4:2:2 8-bit*/
	PixelFormatInfoSelector_YCbCr422_10,	/*!< YCbCr 4:2:2 10-bit unpacked*/
	PixelFormatInfoSelector_YCbCr422_10_CbYCrY,	/*!< YCbCr 4:2:2 10-bit unpacked*/
	PixelFormatInfoSelector_YCbCr422_10p,	/*!< YCbCr 4:2:2 10-bit packed*/
	PixelFormatInfoSelector_YCbCr422_10p_CbYCrY,	/*!< YCbCr 4:2:2 10-bit packed*/
	PixelFormatInfoSelector_YCbCr422_12,	/*!< YCbCr 4:2:2 12-bit unpacked*/
	PixelFormatInfoSelector_YCbCr422_12_CbYCrY,	/*!< YCbCr 4:2:2 12-bit unpacked*/
	PixelFormatInfoSelector_YCbCr422_12p,	/*!< YCbCr 4:2:2 12-bit packed*/
	PixelFormatInfoSelector_YCbCr422_12p_CbYCrY,	/*!< YCbCr 4:2:2 12-bit packed*/
	PixelFormatInfoSelector_YCbCr601_8_CbYCr,	/*!< YCbCr 4:4:4 8-bit BT.601*/
	PixelFormatInfoSelector_YCbCr601_10_CbYCr,	/*!< YCbCr 4:4:4 10-bit unpacked BT.601*/
	PixelFormatInfoSelector_YCbCr601_10p_CbYCr,	/*!< YCbCr 4:4:4 10-bit packed BT.601*/
	PixelFormatInfoSelector_YCbCr601_12_CbYCr,	/*!< YCbCr 4:4:4 12-bit unpacked BT.601*/
	PixelFormatInfoSelector_YCbCr601_12p_CbYCr,	/*!< YCbCr 4:4:4 12-bit packed BT.601*/
	PixelFormatInfoSelector_YCbCr601_411_8_CbYYCrYY,	/*!< YCbCr 4:1:1 8-bit BT.601*/
	PixelFormatInfoSelector_YCbCr601_422_8,	/*!< YCbCr 4:2:2 8-bit BT.601*/
	PixelFormatInfoSelector_YCbCr601_422_8_CbYCrY,	/*!< YCbCr 4:2:2 8-bit BT.601*/
	PixelFormatInfoSelector_YCbCr601_422_10,	/*!< YCbCr 4:2:2 10-bit unpacked BT.601*/
	PixelFormatInfoSelector_YCbCr601_422_10_CbYCrY,	/*!< YCbCr 4:2:2 10-bit unpacked BT.601*/
	PixelFormatInfoSelector_YCbCr601_422_10p,	/*!< YCbCr 4:2:2 10-bit packed BT.601*/
	PixelFormatInfoSelector_YCbCr601_422_10p_CbYCrY,	/*!< YCbCr 4:2:2 10-bit packed BT.601*/
	PixelFormatInfoSelector_YCbCr601_422_12,	/*!< YCbCr 4:2:2 12-bit unpacked BT.601*/
	PixelFormatInfoSelector_YCbCr601_422_12_CbYCrY,	/*!< YCbCr 4:2:2 12-bit unpacked BT.601*/
	PixelFormatInfoSelector_YCbCr601_422_12p,	/*!< YCbCr 4:2:2 12-bit packed BT.601*/
	PixelFormatInfoSelector_YCbCr601_422_12p_CbYCrY,	/*!< YCbCr 4:2:2 12-bit packed BT.601*/
	PixelFormatInfoSelector_YCbCr709_8_CbYCr,	/*!< YCbCr 4:4:4 8-bit BT.709*/
	PixelFormatInfoSelector_YCbCr709_10_CbYCr,	/*!< YCbCr 4:4:4 10-bit unpacked BT.709*/
	PixelFormatInfoSelector_YCbCr709_10p_CbYCr,	/*!< YCbCr 4:4:4 10-bit packed BT.709*/
	PixelFormatInfoSelector_YCbCr709_12_CbYCr,	/*!< YCbCr 4:4:4 12-bit unpacked BT.709*/
	PixelFormatInfoSelector_YCbCr709_12p_CbYCr,	/*!< YCbCr 4:4:4 12-bit packed BT.709*/
	PixelFormatInfoSelector_YCbCr709_411_8_CbYYCrYY,	/*!< YCbCr 4:1:1 8-bit BT.709*/
	PixelFormatInfoSelector_YCbCr709_422_8,	/*!< YCbCr 4:2:2 8-bit BT.709*/
	PixelFormatInfoSelector_YCbCr709_422_8_CbYCrY,	/*!< YCbCr 4:2:2 8-bit BT.709*/
	PixelFormatInfoSelector_YCbCr709_422_10,	/*!< YCbCr 4:2:2 10-bit unpacked BT.709*/
	PixelFormatInfoSelector_YCbCr709_422_10_CbYCrY,	/*!< YCbCr 4:2:2 10-bit unpacked BT.709*/
	PixelFormatInfoSelector_YCbCr709_422_10p,	/*!< YCbCr 4:2:2 10-bit packed BT.709*/
	PixelFormatInfoSelector_YCbCr709_422_10p_CbYCrY,	/*!< YCbCr 4:2:2 10-bit packed BT.709*/
	PixelFormatInfoSelector_YCbCr709_422_12,	/*!< YCbCr 4:2:2 12-bit unpacked BT.709*/
	PixelFormatInfoSelector_YCbCr709_422_12_CbYCrY,	/*!< YCbCr 4:2:2 12-bit unpacked BT.709*/
	PixelFormatInfoSelector_YCbCr709_422_12p,	/*!< YCbCr 4:2:2 12-bit packed BT.709*/
	PixelFormatInfoSelector_YCbCr709_422_12p_CbYCrY,	/*!< YCbCr 4:2:2 12-bit packed BT.709*/
	PixelFormatInfoSelector_YUV8_UYV,	/*!< YUV 4:4:4 8-bit*/
	PixelFormatInfoSelector_YUV411_8_UYYVYY,	/*!< YUV 4:1:1 8-bit*/
	PixelFormatInfoSelector_YUV422_8,	/*!< YUV 4:2:2 8-bit*/
	PixelFormatInfoSelector_YUV422_8_UYVY,	/*!< YUV 4:2:2 8-bit*/
	NUM_PIXELFORMATINFOSELECTOR
} spinPixelFormatInfoSelectorEnums;

typedef enum _spinPixelSizeEnums	/*!< Total size in bits of a pixel of the image.*/
{
	PixelSize_Bpp1,	/*!< 1 bit per pixel.*/
	PixelSize_Bpp2,	/*!< 2 bits per pixel.*/
	PixelSize_Bpp4,	/*!< 4 bits per pixel.*/
	PixelSize_Bpp8,	/*!< 8 bits per pixel.*/
	PixelSize_Bpp10,	/*!< 10 bits per pixel.*/
	PixelSize_Bpp12,	/*!< 12 bits per pixel.*/
	PixelSize_Bpp14,	/*!< 14 bits per pixel.*/
	PixelSize_Bpp16,	/*!< 16 bits per pixel.*/
	PixelSize_Bpp20,	/*!< 20 bits per pixel.*/
	PixelSize_Bpp24,	/*!< 24 bits per pixel.*/
	PixelSize_Bpp30,	/*!< 30 bits per pixel.*/
	PixelSize_Bpp32,	/*!< 32 bits per pixel.*/
	PixelSize_Bpp36,	/*!< 36 bits per pixel.*/
	PixelSize_Bpp48,	/*!< 48 bits per pixel.*/
	PixelSize_Bpp64,	/*!< 64 bits per pixel.*/
	PixelSize_Bpp96,	/*!< 96 bits per pixel.*/
	NUM_PIXELSIZE
} spinPixelSizeEnums;

typedef enum _spinPixelColorFilterEnums	/*!< Type of color filter that is applied to the image.*/
{
	PixelColorFilter_None,	/*!< No color filter.*/
	PixelColorFilter_BayerRG,	/*!< Bayer Red Green filter.*/
	PixelColorFilter_BayerGB,	/*!< Bayer Green Blue filter.*/
	PixelColorFilter_BayerGR,	/*!< Bayer Green Red filter.*/
	PixelColorFilter_BayerBG,	/*!< Bayer Blue Green filter.*/
	NUM_PIXELCOLORFILTER
} spinPixelColorFilterEnums;

typedef enum _spinTestPatternGeneratorSelectorEnums	/*!< Selects which test pattern generator is controlled by the TestPattern feature.*/
{
	TestPatternGeneratorSelector_Sensor,	/*!< TestPattern feature will control the sensor's test pattern generator.*/
	TestPatternGeneratorSelector_Region0,	/*!< TestPattern feature will control the region 0 test pattern generator.*/
	TestPatternGeneratorSelector_Region1,	/*!< TestPattern feature will control the region 1 test pattern generator.*/
	TestPatternGeneratorSelector_Region2,	/*!< TestPattern feature will control the region 2 test pattern generator.*/
	NUM_TESTPATTERNGENERATORSELECTOR
} spinTestPatternGeneratorSelectorEnums;

typedef enum _spinTestPatternEnums	/*!< Selects the type of test pattern that is generated by the device as image source.*/
{
	TestPattern_Off,	/*!< Image is coming from the sensor.*/
	TestPattern_Black,	/*!< Image is filled with the darkest possible image.*/
	TestPattern_White,	/*!< Image is filled with the brightest possible image.*/
	TestPattern_GreyHorizontalRamp,	/*!< Image is filled horizontally with an image that goes from the darkest possible value to the brightest.*/
	TestPattern_GreyVerticalRamp,	/*!< Image is filled vertically with an image that goes from the darkest possible value to the brightest.*/
	TestPattern_GreyHorizontalRampMoving,	/*!< Image is filled horizontally with an image that goes from the darkest possible value to the brightest and that moves horizontally from left to right at each frame.*/
	TestPattern_GreyVerticalRampMoving,	/*!< Image is filled vertically with an image that goes from the darkest possible value to the brightest and that moves verticaly from top to bottom at each frame.*/
	TestPattern_HorizontalLineMoving,	/*!< A moving horizontal line is superimposed on the live image.*/
	TestPattern_VerticalLineMoving,	/*!< A moving vertical line is superimposed on the live image.*/
	TestPattern_ColorBar,	/*!< Image is filled with stripes of color including White, Black, Red, Green, Blue, Cyan, Magenta and Yellow.*/
	TestPattern_FrameCounter,	/*!< A frame counter is superimposed on the live image.*/
	NUM_TESTPATTERN
} spinTestPatternEnums;

typedef enum _spinDeinterlacingEnums	/*!< Controls how the device performs de-interlacing.*/
{
	Deinterlacing_Off,	/*!< The device doesn't perform de-interlacing.*/
	Deinterlacing_LineDuplication,	/*!< The device performs de-interlacing by outputting each line of each field twice.*/
	Deinterlacing_Weave,	/*!< The device performs de-interlacing by interleaving the lines of all fields.*/
	NUM_DEINTERLACING
} spinDeinterlacingEnums;

typedef enum _spinImageCompressionModeEnums	/*!< Enable a specific image compression mode as the base mode for image transfer. Optionally, chunk data can be appended to the compressed image (See chunk section).*/
{
	ImageCompressionMode_Off,	/*!< Default value. Image compression is disabled. Images are transmitted uncompressed.*/
	ImageCompressionMode_JPEG,	/*!< JPEG compression is selected.*/
	ImageCompressionMode_JPEG2000,	/*!< JPEG 2000 compression is selected.*/
	ImageCompressionMode_H264,	/*!< H.264 compression is selected.*/
	NUM_IMAGECOMPRESSIONMODE
} spinImageCompressionModeEnums;

typedef enum _spinImageCompressionRateOptionEnums	/*!< Two rate controlling options are offered: fixed bit rate or fixed quality. The exact implementation to achieve one or the other is vendor-specific.*/
{
	ImageCompressionRateOption_FixBitrate,	/*!< Output stream follows a constant bit rate. Allows easy bandwidth management on the link.*/
	ImageCompressionRateOption_FixQuality,	/*!< Output stream has a constant image quality. Can be used when image processing algorithms are sensitive to image degradation caused by excessive data compression.*/
	NUM_IMAGECOMPRESSIONRATEOPTION
} spinImageCompressionRateOptionEnums;

typedef enum _spinImageCompressionJPEGFormatOptionEnums	/*!< When JPEG is selected as the compression format, a device might optionally offer better control over JPEG-specific options through this feature.*/
{
	ImageCompressionJPEGFormatOption_Lossless,	/*!< Selects lossless JPEG compression based on a predictive coding model.*/
	ImageCompressionJPEGFormatOption_BaselineStandard,	/*!< Indicates this is a baseline sequential (single-scan) DCT-based JPEG.*/
	ImageCompressionJPEGFormatOption_BaselineOptimized,	/*!< Provides optimized color and slightly better compression than baseline standard by using custom Huffman tables optimized after statistical analysis of the image content.*/
	ImageCompressionJPEGFormatOption_Progressive,	/*!< Indicates this is a progressive (multi-scan) DCT-based JPEG.*/
	NUM_IMAGECOMPRESSIONJPEGFORMATOPTION
} spinImageCompressionJPEGFormatOptionEnums;

typedef enum _spinSensorShutterModeEnums	/*!< Sets the shutter mode of the device.*/
{
	SensorShutterMode_Global,	/*!< The shutter opens and closes at the same time for all pixels. All the pixels are exposed for the same length of time at the same time.*/
	SensorShutterMode_Rolling,	/*!< The shutter opens and closes sequentially for groups (typically lines) of pixels. All the pixels are exposed for the same length of time but not at the same time.*/
	SensorShutterMode_GlobalReset,	/*!< The shutter opens at the same time for all pixels but ends in a sequential manner. The pixels are exposed for different lengths of time.*/
	NUM_SENSORSHUTTERMODE
} spinSensorShutterModeEnums;

typedef enum _spinAcquisitionModeEnums	/*!< Sets the acquisition mode of the device. It defines mainly the number of frames to capture during an acquisition and the way the acquisition stops.*/
{
	AcquisitionMode_SingleFrame,	/*!< One frame is captured.*/
	AcquisitionMode_MultiFrame,	/*!< The number of frames specified by AcquisitionFrameCount is captured.*/
	AcquisitionMode_Continuous,	/*!< Frames are captured continuously until stopped with the AcquisitionStop command.*/
	NUM_ACQUISITIONMODE
} spinAcquisitionModeEnums;

typedef enum _spinAcquisitionStatusSelectorEnums	/*!< Selects the internal acquisition signal to read using AcquisitionStatus.*/
{
	AcquisitionStatusSelector_AcquisitionTriggerWait,	/*!< Device is currently waiting for a trigger for the capture of one or many frames.*/
	AcquisitionStatusSelector_AcquisitionActive,	/*!< Device is currently doing an acquisition of one or many frames.*/
	AcquisitionStatusSelector_AcquisitionTransfer,	/*!< Device is currently transferring an acquisition of one or many frames.*/
	AcquisitionStatusSelector_FrameTriggerWait,	/*!< Device is currently waiting for a frame start trigger.*/
	AcquisitionStatusSelector_FrameActive,	/*!< Device is currently doing the capture of a frame.*/
	AcquisitionStatusSelector_ExposureActive,	/*!< Device is doing the exposure of a frame.*/
	NUM_ACQUISITIONSTATUSSELECTOR
} spinAcquisitionStatusSelectorEnums;

typedef enum _spinTriggerSelectorEnums	/*!< Selects the type of trigger to configure.*/
{
	TriggerSelector_AcquisitionStart,	/*!< Selects a trigger that starts the Acquisition of one or many frames according to AcquisitionMode.*/
	TriggerSelector_AcquisitionEnd,	/*!< Selects a trigger that ends the Acquisition of one or many frames according to AcquisitionMode.*/
	TriggerSelector_AcquisitionActive,	/*!< Selects a trigger that controls the duration of the Acquisition of one or many frames. The Acquisition is activated when the trigger signal becomes active and terminated when it goes back to the inactive state.*/
	TriggerSelector_FrameStart,	/*!< Selects a trigger starting the capture of one frame.*/
	TriggerSelector_FrameEnd,	/*!< Selects a trigger ending the capture of one frame (mainly used in line scan mode).*/
	TriggerSelector_FrameActive,	/*!< Selects a trigger controlling the duration of one frame (mainly used in line scan mode).*/
	TriggerSelector_FrameBurstStart,	/*!< Selects a trigger starting the capture of the bursts of frames in an acquisition. AcquisitionBurstFrameCount controls the length of each burst unless a FrameBurstEnd trigger is active. The total number of frames captured is also conditioned by AcquisitionFrameCount if AcquisitionMode is MultiFrame.*/
	TriggerSelector_FrameBurstEnd,	/*!< Selects a trigger ending the capture of the bursts of frames in an acquisition.*/
	TriggerSelector_FrameBurstActive,	/*!< Selects a trigger controlling the duration of the capture of the bursts of frames in an acquisition.*/
	TriggerSelector_LineStart,	/*!< Selects a trigger starting the capture of one Line of a Frame (mainly used in line scan mode).*/
	TriggerSelector_ExposureStart,	/*!< Selects a trigger controlling the start of the exposure of one Frame (or Line).*/
	TriggerSelector_ExposureEnd,	/*!< Selects a trigger controlling the end of the exposure of one Frame (or Line).*/
	TriggerSelector_ExposureActive,	/*!< Selects a trigger controlling the duration of the exposure of one frame (or Line).*/
	NUM_TRIGGERSELECTOR
} spinTriggerSelectorEnums;

typedef enum _spinTriggerModeEnums	/*!< Controls if the selected trigger is active.*/
{
	TriggerMode_Off,	/*!< Disables the selected trigger.*/
	TriggerMode_On,	/*!< Enable the selected trigger.*/
	NUM_TRIGGERMODE
} spinTriggerModeEnums;

typedef enum _spinTriggerSourceEnums	/*!< Specifies the internal signal or physical input Line to use as the trigger source. The selected trigger must have its TriggerMode set to On.*/
{
	TriggerSource_Software,	/*!< Specifies that the trigger source will be generated by software using the TriggerSoftware command.*/
	TriggerSource_SoftwareSignal0,	/*!< Specifies that the trigger source will be a signal generated by software using the SoftwareSignalPulse command.*/
	TriggerSource_SoftwareSignal1,	/*!< Specifies that the trigger source will be a signal generated by software using the SoftwareSignalPulse command.*/
	TriggerSource_SoftwareSignal2,	/*!< Specifies that the trigger source will be a signal generated by software using the SoftwareSignalPulse command.*/
	TriggerSource_Line0,	/*!< Specifies which physical line (or pin) and associated I/O control block to use as external source for the trigger signal.*/
	TriggerSource_Line1,	/*!< Specifies which physical line (or pin) and associated I/O control block to use as external source for the trigger signal.*/
	TriggerSource_Line2,	/*!< Specifies which physical line (or pin) and associated I/O control block to use as external source for the trigger signal.*/
	TriggerSource_Counter0Start,	/*!< Specifies which of the Counter signal to use as internal source for the trigger.*/
	TriggerSource_Counter1Start,	/*!< Specifies which of the Counter signal to use as internal source for the trigger.*/
	TriggerSource_Counter2Start,	/*!< Specifies which of the Counter signal to use as internal source for the trigger.*/
	TriggerSource_Counter0End,	/*!< Specifies which of the Counter signal to use as internal source for the trigger.*/
	TriggerSource_Counter1End,	/*!< Specifies which of the Counter signal to use as internal source for the trigger.*/
	TriggerSource_Counter2End,	/*!< Specifies which of the Counter signal to use as internal source for the trigger.*/
	TriggerSource_Timer0Start,	/*!< Specifies which Timer signal to use as internal source for the trigger.*/
	TriggerSource_Timer1Start,	/*!< Specifies which Timer signal to use as internal source for the trigger.*/
	TriggerSource_Timer2Start,	/*!< Specifies which Timer signal to use as internal source for the trigger.*/
	TriggerSource_Timer0End,	/*!< Specifies which Timer signal to use as internal source for the trigger.*/
	TriggerSource_Timer1End,	/*!< Specifies which Timer signal to use as internal source for the trigger.*/
	TriggerSource_Timer2End,	/*!< Specifies which Timer signal to use as internal source for the trigger.*/
	TriggerSource_Encoder0,	/*!< Specifies which Encoder signal to use as internal source for the trigger.*/
	TriggerSource_Encoder1,	/*!< Specifies which Encoder signal to use as internal source for the trigger.*/
	TriggerSource_Encoder2,	/*!< Specifies which Encoder signal to use as internal source for the trigger.*/
	TriggerSource_UserOutput0,	/*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
	TriggerSource_UserOutput1,	/*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
	TriggerSource_UserOutput2,	/*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
	TriggerSource_Action0,	/*!< Specifies which Action command to use as internal source for the trigger.*/
	TriggerSource_Action1,	/*!< Specifies which Action command to use as internal source for the trigger.*/
	TriggerSource_Action2,	/*!< Specifies which Action command to use as internal source for the trigger.*/
	TriggerSource_LinkTrigger0,	/*!< Specifies which Link Trigger to use as  source for the trigger (received from the transport layer).*/
	TriggerSource_LinkTrigger1,	/*!< Specifies which Link Trigger to use as  source for the trigger (received from the transport layer).*/
	TriggerSource_LinkTrigger2,	/*!< Specifies which Link Trigger to use as  source for the trigger (received from the transport layer).*/
	TriggerSource_CC1,	/*!< Index of the Camera Link physical line and associated I/O control block to use. This ensures a direct mapping between the lines on the frame grabber and on the camera. Applicable to CameraLink products only.*/
	TriggerSource_CC2,	/*!< Index of the Camera Link physical line and associated I/O control block to use. This ensures a direct mapping between the lines on the frame grabber and on the camera. Applicable to CameraLink products only.*/
	TriggerSource_CC3,	/*!< Index of the Camera Link physical line and associated I/O control block to use. This ensures a direct mapping between the lines on the frame grabber and on the camera. Applicable to CameraLink products only.*/
	TriggerSource_CC4,	/*!< Index of the Camera Link physical line and associated I/O control block to use. This ensures a direct mapping between the lines on the frame grabber and on the camera. Applicable to CameraLink products only.*/
	NUM_TRIGGERSOURCE
} spinTriggerSourceEnums;

typedef enum _spinTriggerActivationEnums	/*!< Specifies the activation mode of the trigger.*/
{
	TriggerActivation_RisingEdge,	/*!< Specifies that the trigger is considered valid on the rising edge of the source signal.*/
	TriggerActivation_FallingEdge,	/*!< Specifies that the trigger is considered valid on the falling edge of the source signal.*/
	TriggerActivation_AnyEdge,	/*!< Specifies that the trigger is considered valid on the falling or rising edge of the source signal.*/
	TriggerActivation_LevelHigh,	/*!< Specifies that the trigger is considered valid as long as the level of the source signal is high.*/
	TriggerActivation_LevelLow,	/*!< Specifies that the trigger is considered valid as long as the level of the source signal is low.*/
	NUM_TRIGGERACTIVATION
} spinTriggerActivationEnums;

typedef enum _spinTriggerOverlapEnums	/*!< Specifies the type trigger overlap permitted with the previous frame or line. This defines when a valid trigger will be accepted (or latched) for a new frame or a new line.*/
{
	TriggerOverlap_Off,	/*!< No trigger overlap is permitted.*/
	TriggerOverlap_ReadOut,	/*!< Trigger is accepted immediately after the exposure period.*/
	TriggerOverlap_PreviousFrame,	/*!< Trigger is accepted (latched) at any time during the capture of the previous frame.*/
	TriggerOverlap_PreviousLine,	/*!< Trigger is accepted (latched) at any time during the capture of the previous line.*/
	NUM_TRIGGEROVERLAP
} spinTriggerOverlapEnums;

typedef enum _spinExposureModeEnums	/*!< Sets the operation mode of the Exposure.*/
{
	ExposureMode_Off,	/*!< Disables the Exposure and let the shutter open.*/
	ExposureMode_Timed,	/*!< Timed exposure. The exposure duration time is set using the ExposureTime or ExposureAuto features and the exposure starts with the FrameStart or LineStart.*/
	ExposureMode_TriggerWidth,	/*!< Uses the width of the current Frame or Line trigger signal(s) pulse to control the exposure duration. Note that if the Frame or Line TriggerActivation is RisingEdge or LevelHigh, the exposure duration will be the time the trigger stays High. If TriggerActivation is FallingEdge or LevelLow, the exposure time will last as long as the trigger stays Low.*/
	ExposureMode_TriggerControlled,	/*!< Uses one or more trigger signal(s) to control the exposure duration independently from the current Frame or Line triggers. See ExposureStart, ExposureEnd and ExposureActive of the TriggerSelector feature.*/
	NUM_EXPOSUREMODE
} spinExposureModeEnums;

typedef enum _spinExposureTimeModeEnums	/*!< Sets the configuration mode of the ExposureTime feature.*/
{
	ExposureTimeMode_Common,	/*!< The exposure time is common to all the color components. The common ExposureTime value to use can be set selecting it with ExposureTimeSelector[Common].*/
	ExposureTimeMode_Individual,	/*!< The exposure time is individual for each color component. Each individual ExposureTime values to use can be set by selecting them with ExposureTimeSelector.*/
	NUM_EXPOSURETIMEMODE
} spinExposureTimeModeEnums;

typedef enum _spinExposureTimeSelectorEnums	/*!< Selects which exposure time is controlled by the ExposureTime feature. This allows for independent control over the exposure components.*/
{
	ExposureTimeSelector_Common,	/*!< Selects the common ExposureTime.*/
	ExposureTimeSelector_Red,	/*!< Selects the red common ExposureTime.*/
	ExposureTimeSelector_Green,	/*!< Selects the green ExposureTime.*/
	ExposureTimeSelector_Blue,	/*!< Selects the blue ExposureTime.*/
	ExposureTimeSelector_Cyan,	/*!< Selects the cyan common ExposureTime.*/
	ExposureTimeSelector_Magenta,	/*!< Selects the magenta ExposureTime.*/
	ExposureTimeSelector_Yellow,	/*!< Selects the yellow ExposureTime.*/
	ExposureTimeSelector_Infrared,	/*!< Selects the infrared ExposureTime.*/
	ExposureTimeSelector_Ultraviolet,	/*!< Selects the ultraviolet ExposureTime.*/
	ExposureTimeSelector_Stage1,	/*!< Selects the first stage ExposureTime.*/
	ExposureTimeSelector_Stage2,	/*!< Selects the second stage ExposureTime.*/
	NUM_EXPOSURETIMESELECTOR
} spinExposureTimeSelectorEnums;

typedef enum _spinExposureAutoEnums	/*!< Sets the automatic exposure mode when ExposureMode is Timed. The exact algorithm used to implement this control is device-specific.*/
{
	ExposureAuto_Off,	/*!< Exposure duration is user controlled using ExposureTime.*/
	ExposureAuto_Once,	/*!< Exposure duration is adapted once by the device. Once it has converged, it returns to the Off state.*/
	ExposureAuto_Continuous,	/*!< Exposure duration is constantly adapted by the device to maximize the dynamic range.*/
	NUM_EXPOSUREAUTO
} spinExposureAutoEnums;

typedef enum _spinGainSelectorEnums	/*!< Selects which Gain is controlled by the various Gain features.*/
{
	GainSelector_All,	/*!< Gain will be applied to all channels or taps.*/
	GainSelector_Red,	/*!< Gain will be applied to the red channel.*/
	GainSelector_Green,	/*!< Gain will be applied to the green channel.*/
	GainSelector_Blue,	/*!< Gain will be applied to the blue channel.*/
	GainSelector_Y,	/*!< Gain will be applied to Y channel.*/
	GainSelector_U,	/*!< Gain will be applied to U channel.*/
	GainSelector_V,	/*!< Gain will be applied to V channel.*/
	GainSelector_Tap1,	/*!< Gain will be applied to Tap 1.*/
	GainSelector_Tap2,	/*!< Gain will be applied to Tap 2.*/
	GainSelector_AnalogAll,	/*!< Gain will be applied to all analog channels or taps.*/
	GainSelector_AnalogRed,	/*!< Gain will be applied to the red analog channel.*/
	GainSelector_AnalogGreen,	/*!< Gain will be applied to the green analog channel.*/
	GainSelector_AnalogBlue,	/*!< Gain will be applied to the blue analog channel.*/
	GainSelector_AnalogY,	/*!< Gain will be applied to Y analog channel.*/
	GainSelector_AnalogU,	/*!< Gain will be applied to U analog channel.*/
	GainSelector_AnalogV,	/*!< Gain will be applied to V analog channel.*/
	GainSelector_AnalogTap1,	/*!< Analog gain will be applied to Tap 1.*/
	GainSelector_AnalogTap2,	/*!< Analog gain will be applied to Tap 2.*/
	GainSelector_DigitalAll,	/*!< Gain will be applied to all digital channels or taps.*/
	GainSelector_DigitalRed,	/*!< Gain will be applied to the red digital channel.*/
	GainSelector_DigitalGreen,	/*!< Gain will be applied to the green digital channel.*/
	GainSelector_DigitalBlue,	/*!< Gain will be applied to the blue digital channel.*/
	GainSelector_DigitalY,	/*!< Gain will be applied to Y digital channel.*/
	GainSelector_DigitalU,	/*!< Gain will be applied to U digital channel.*/
	GainSelector_DigitalV,	/*!< Gain will be applied to V digital channel.*/
	GainSelector_DigitalTap1,	/*!< Digital gain will be applied to Tap 1.*/
	GainSelector_DigitalTap2,	/*!< Digital gain will be applied to Tap 2.*/
	NUM_GAINSELECTOR
} spinGainSelectorEnums;

typedef enum _spinGainAutoEnums	/*!< Sets the automatic gain control (AGC) mode. The exact algorithm used to implement AGC is device-specific.*/
{
	GainAuto_Off,	/*!< Gain is User controlled using Gain.*/
	GainAuto_Once,	/*!< Gain is automatically adjusted once by the device. Once it has converged, it automatically returns to the Off state.*/
	GainAuto_Continuous,	/*!< Gain is constantly adjusted by the device.*/
	NUM_GAINAUTO
} spinGainAutoEnums;

typedef enum _spinGainAutoBalanceEnums	/*!< Sets the mode for automatic gain balancing between the sensor color channels or taps. The gain coefficients of each channel or tap are adjusted so they are matched.*/
{
	GainAutoBalance_Off,	/*!< Gain tap balancing is user controlled using Gain .*/
	GainAutoBalance_Once,	/*!< Gain tap balancing is automatically adjusted once by the device. Once it has converged, it automatically returns to the Off state.*/
	GainAutoBalance_Continuous,	/*!< Gain tap balancing is constantly adjusted by the device.*/
	NUM_GAINAUTOBALANCE
} spinGainAutoBalanceEnums;

typedef enum _spinBlackLevelSelectorEnums	/*!< Selects which Black Level is controlled by the various Black Level features.*/
{
	BlackLevelSelector_All,	/*!< Black Level will be applied to all channels or taps.*/
	BlackLevelSelector_Red,	/*!< Black Level will be applied to the red channel.*/
	BlackLevelSelector_Green,	/*!< Black Level will be applied to the green channel.*/
	BlackLevelSelector_Blue,	/*!< Black Level will be applied to the blue channel.*/
	BlackLevelSelector_Y,	/*!< Black Level will be applied to Y channel.*/
	BlackLevelSelector_U,	/*!< Black Level will be applied to U channel.*/
	BlackLevelSelector_V,	/*!< Black Level will be applied to V channel.*/
	BlackLevelSelector_Tap1,	/*!< Black Level will be applied to Tap 1.*/
	BlackLevelSelector_Tap2,	/*!< Black Level will be applied to Tap 2.*/
	NUM_BLACKLEVELSELECTOR
} spinBlackLevelSelectorEnums;

typedef enum _spinBlackLevelAutoEnums	/*!< Controls the mode for automatic black level adjustment. The exact algorithm used to implement this adjustment is device-specific.*/
{
	BlackLevelAuto_Off,	/*!< Analog black level is user controlled using BlackLevel.*/
	BlackLevelAuto_Once,	/*!< Analog black level is automatically adjusted once by the device. Once it has converged, it automatically returns to the Off state.*/
	BlackLevelAuto_Continuous,	/*!< Analog black level is constantly adjusted by the device.*/
	NUM_BLACKLEVELAUTO
} spinBlackLevelAutoEnums;

typedef enum _spinBlackLevelAutoBalanceEnums	/*!< Controls the mode for automatic black level balancing between the sensor color channels or taps. The black level coefficients of each channel are adjusted so they are matched.*/
{
	BlackLevelAutoBalance_Off,	/*!< Black level tap balancing is user controlled using BlackLevel.*/
	BlackLevelAutoBalance_Once,	/*!< Black level tap balancing is automatically adjusted once by the device. Once it has converged, it automatically returns to the Off state.*/
	BlackLevelAutoBalance_Continuous,	/*!< Black level tap balancing is constantly adjusted by the device.*/
	NUM_BLACKLEVELAUTOBALANCE
} spinBlackLevelAutoBalanceEnums;

typedef enum _spinWhiteClipSelectorEnums	/*!< Selects which White Clip to control.*/
{
	WhiteClipSelector_All,	/*!< White Clip will be applied to all channels or taps.*/
	WhiteClipSelector_Red,	/*!< White Clip will be applied to the red channel.*/
	WhiteClipSelector_Green,	/*!< White Clip will be applied to the green channel.*/
	WhiteClipSelector_Blue,	/*!< White Clip will be applied to the blue channel.*/
	WhiteClipSelector_Y,	/*!< White Clip will be applied to Y channel.*/
	WhiteClipSelector_U,	/*!< White Clip will be applied to U channel.*/
	WhiteClipSelector_V,	/*!< White Clip will be applied to V channel.*/
	WhiteClipSelector_Tap1,	/*!< White Clip will be applied to Tap 1.*/
	WhiteClipSelector_Tap2,	/*!< White Clip will be applied to Tap 2.*/
	NUM_WHITECLIPSELECTOR
} spinWhiteClipSelectorEnums;

typedef enum _spinBalanceRatioSelectorEnums	/*!< Selects which Balance ratio to control.*/
{
	BalanceRatioSelector_All,	/*!< Balance Ratio will be applied to all channels or taps.*/
	BalanceRatioSelector_Red,	/*!< Balance Ratio will be applied to the red channel.*/
	BalanceRatioSelector_Green,	/*!< Balance Ratio will be applied to the green channel.*/
	BalanceRatioSelector_Blue,	/*!< Balance Ratio will be applied to the blue channel.*/
	BalanceRatioSelector_Y,	/*!< Balance Ratio will be applied to Y channel.*/
	BalanceRatioSelector_U,	/*!< Balance Ratio will be applied to U channel.*/
	BalanceRatioSelector_V,	/*!< Balance Ratio will be applied to V channel.*/
	BalanceRatioSelector_Tap1,	/*!< Balance Ratio will be applied to Tap 1.*/
	BalanceRatioSelector_Tap2,	/*!< Balance Ratio will be applied to Tap 2.*/
	NUM_BALANCERATIOSELECTOR
} spinBalanceRatioSelectorEnums;

typedef enum _spinBalanceWhiteAutoEnums	/*!< Controls the mode for automatic white balancing between the color channels. The white balancing ratios are automatically adjusted.*/
{
	BalanceWhiteAuto_Off,	/*!< White balancing is user controlled using BalanceRatioSelector and BalanceRatio.*/
	BalanceWhiteAuto_Once,	/*!< White balancing is automatically adjusted once by the device. Once it has converged, it automatically returns to the Off state.*/
	BalanceWhiteAuto_Continuous,	/*!< White balancing is constantly adjusted by the device.*/
	NUM_BALANCEWHITEAUTO
} spinBalanceWhiteAutoEnums;

typedef enum _spinLUTSelectorEnums	/*!< Selects which LUT to control.*/
{
	LUTSelector_Luminance,	/*!< Selects the Luminace LUT.*/
	LUTSelector_Red,	/*!< Selects the Red LUT.*/
	LUTSelector_Green,	/*!< Selects the Green LUT.*/
	LUTSelector_Blue,	/*!< Selects the Blue LUT.*/
	NUM_LUTSELECTOR
} spinLUTSelectorEnums;

typedef enum _spinColorTransformationSelectorEnums	/*!< Selects which Color Transformation module is controlled by the various Color Transformation features.*/
{
	ColorTransformationSelector_RGBtoRGB,	/*!< RGB to RGB color transformation.*/
	ColorTransformationSelector_RGBtoYUV,	/*!< RGB to YUV color transformation.*/
	NUM_COLORTRANSFORMATIONSELECTOR
} spinColorTransformationSelectorEnums;

typedef enum _spinColorTransformationValueSelectorEnums	/*!< Selects the Gain factor or Offset of the Transformation matrix to access in the selected Color Transformation module.*/
{
	ColorTransformationValueSelector_Gain00,	/*!< Gain 0,0 of the transformation matrix.*/
	ColorTransformationValueSelector_Gain01,	/*!< Gain 0,1 of the transformation matrix.*/
	ColorTransformationValueSelector_Gain02,	/*!< Gain 0,2 of the transformation matrix.*/
	ColorTransformationValueSelector_Gain10,	/*!< Gain 1,0 of the transformation matrix.*/
	ColorTransformationValueSelector_Gain11,	/*!< Gain 1,1 of the transformation matrix.*/
	ColorTransformationValueSelector_Gain12,	/*!< Gain 1,2 of the transformation matrix.*/
	ColorTransformationValueSelector_Gain20,	/*!< Gain 2,0 of the transformation matrix.*/
	ColorTransformationValueSelector_Gain21,	/*!< Gain 2,1 of the transformation matrix.*/
	ColorTransformationValueSelector_Gain22,	/*!< Gain 2,2 of the transformation matrix.*/
	ColorTransformationValueSelector_Offset0,	/*!< Offset 0 of the transformation matrix.*/
	ColorTransformationValueSelector_Offset1,	/*!< Offset 1 of the transformation matrix.*/
	ColorTransformationValueSelector_Offset2,	/*!< Offset 2 of the transformation matrix.*/
	NUM_COLORTRANSFORMATIONVALUESELECTOR
} spinColorTransformationValueSelectorEnums;

typedef enum _spinLineSelectorEnums	/*!< Selects the physical line (or pin) of the external device connector or the virtual line of the Transport Layer to configure.*/
{
	LineSelector_Line0,	/*!< Index of the physical line and associated I/O control block to use.*/
	LineSelector_Line1,	/*!< Index of the physical line and associated I/O control block to use.*/
	LineSelector_Line2,	/*!< Index of the physical line and associated I/O control block to use.*/
	LineSelector_LinkTrigger0,	/*!< Index of the virtual line going on the Transport layer to use.*/
	LineSelector_LinkTrigger1,	/*!< Index of the virtual line going on the Transport layer to use.*/
	LineSelector_LinkTrigger2,	/*!< Index of the virtual line going on the Transport layer to use.*/
	LineSelector_CC1,	/*!< Index of the Camera Link physical line and associated I/O control block to use. This ensures a direct mapping between the lines on the frame grabber and on the camera. Applicable to CameraLink Product only.*/
	LineSelector_CC2,	/*!< Index of the Camera Link physical line and associated I/O control block to use. This ensures a direct mapping between the lines on the frame grabber and on the camera. Applicable to CameraLink Product only.*/
	LineSelector_CC3,	/*!< Index of the Camera Link physical line and associated I/O control block to use. This ensures a direct mapping between the lines on the frame grabber and on the camera. Applicable to CameraLink Product only.*/
	LineSelector_CC4,	/*!< Index of the Camera Link physical line and associated I/O control block to use. This ensures a direct mapping between the lines on the frame grabber and on the camera. Applicable to CameraLink Product only.*/
	NUM_LINESELECTOR
} spinLineSelectorEnums;

typedef enum _spinLineModeEnums	/*!< Controls if the physical Line is used to Input or Output a signal.*/
{
	LineMode_Input,	/*!< The selected physical line is used to Input an electrical signal.*/
	LineMode_Output,	/*!< The selected physical line is used to Output an electrical signal.*/
	NUM_LINEMODE
} spinLineModeEnums;

typedef enum _spinLineSourceEnums	/*!< Selects which internal acquisition or I/O source signal to output on the selected Line. LineMode must be Output.*/
{
	LineSource_Off,	/*!< Line output is disabled (Tri-State).*/
	LineSource_AcquisitionTriggerWait,	/*!< Device is currently waiting for a trigger for the capture of one or many Frames.*/
	LineSource_AcquisitionActive,	/*!< Device is currently doing an acquisition of one or many Frames.*/
	LineSource_FrameTriggerWait,	/*!< Device is currently waiting for a Frame start trigger.*/
	LineSource_FrameActive,	/*!< Device is currently doing the capture of a Frame.*/
	LineSource_ExposureActive,	/*!< Device is doing the exposure of a Frame (or Line).*/
	LineSource_Counter0Active,	/*!< The chosen counter is in active state (counting).*/
	LineSource_Counter1Active,	/*!< The chosen counter is in active state (counting).*/
	LineSource_Counter2Active,	/*!< The chosen counter is in active state (counting).*/
	LineSource_Timer0Active,	/*!< The chosen Timer is in active state.*/
	LineSource_Timer1Active,	/*!< The chosen Timer is in active state.*/
	LineSource_Timer2Active,	/*!< The chosen Timer is in active state.*/
	LineSource_UserOutput0,	/*!< The chosen User Output Bit state as defined by its current UserOutputValue.*/
	LineSource_UserOutput1,	/*!< The chosen User Output Bit state as defined by its current UserOutputValue.*/
	LineSource_UserOutput2,	/*!< The chosen User Output Bit state as defined by its current UserOutputValue.*/
	LineSource_Stream0TransferActive,	/*!< Transfer on the stream is active.*/
	LineSource_Stream1TransferActive,	/*!< Transfer on the stream is active.*/
	LineSource_Stream0TransferPaused,	/*!< Transfer on the stream is paused.*/
	LineSource_Stream1TransferPaused,	/*!< Transfer on the stream is paused.*/
	LineSource_Stream0TransferStopping,	/*!< Transfer on the stream is stopping.*/
	LineSource_Stream1TransferStopping,	/*!< Transfer on the stream is stopping.*/
	LineSource_Stream0TransferStopped,	/*!< Transfer on the stream is stopped.*/
	LineSource_Stream1TransferStopped,	/*!< Transfer on the stream is stopped.*/
	LineSource_Stream0TransferOverflow,	/*!< Transfer on the stream is in overflow.*/
	LineSource_Stream1TransferOverflow,	/*!< Transfer on the stream is in overflow.*/
	NUM_LINESOURCE
} spinLineSourceEnums;

typedef enum _spinLineFormatEnums	/*!< Controls the current electrical format of the selected physical input or output Line.*/
{
	LineFormat_NoConnect,	/*!< The Line is not connected.*/
	LineFormat_TriState,	/*!< The Line is currently in Tri-State mode (Not driven).*/
	LineFormat_TTL,	/*!< The Line is currently accepting or sending TTL level signals.*/
	LineFormat_LVDS,	/*!< The Line is currently accepting or sending LVDS level signals.*/
	LineFormat_RS422,	/*!< The Line is currently accepting or sending RS422 level signals.*/
	LineFormat_OptoCoupled,	/*!< The Line is opto-coupled.*/
	LineFormat_OpenDrain,	/*!< The Line is Open Drain (or Open Collector).*/
	NUM_LINEFORMAT
} spinLineFormatEnums;

typedef enum _spinUserOutputSelectorEnums	/*!< Selects which bit of the User Output register will be set by UserOutputValue.*/
{
	UserOutputSelector_UserOutput0,	/*!< Selects the bit 0 of the User Output register.*/
	UserOutputSelector_UserOutput1,	/*!< Selects the bit 1 of the User Output register.*/
	UserOutputSelector_UserOutput2,	/*!< Selects the bit 2 of the User Output register.*/
	NUM_USEROUTPUTSELECTOR
} spinUserOutputSelectorEnums;

typedef enum _spinCounterSelectorEnums	/*!< Selects which Counter to configure.*/
{
	CounterSelector_Counter0,	/*!< Selects the counter 0.*/
	CounterSelector_Counter1,	/*!< Selects the counter 1.*/
	CounterSelector_Counter2,	/*!< Selects the counter 2.*/
	NUM_COUNTERSELECTOR
} spinCounterSelectorEnums;

typedef enum _spinCounterEventSourceEnums	/*!< Select the events that will be the source to increment the Counter.*/
{
	CounterEventSource_Off,	/*!< Counter is stopped.*/
	CounterEventSource_AcquisitionTrigger,	/*!< Counts the number of Acquisition Trigger.*/
	CounterEventSource_AcquisitionStart,	/*!< Counts the number of Acquisition Start.*/
	CounterEventSource_AcquisitionEnd,	/*!< Counts the number of Acquisition End.*/
	CounterEventSource_FrameTrigger,	/*!< Counts the number of Frame Start Trigger.*/
	CounterEventSource_FrameStart,	/*!< Counts the number of Frame Start.*/
	CounterEventSource_FrameEnd,	/*!< Counts the number of Frame End.*/
	CounterEventSource_FrameBurstStart,	/*!< Counts the number of Frame Burst Start.*/
	CounterEventSource_FrameBurstEnd,	/*!< Counts the number of Frame Burst End.*/
	CounterEventSource_LineTrigger,	/*!< Counts the number of Line Start Trigger.*/
	CounterEventSource_LineStart,	/*!< Counts the number of Line Start.*/
	CounterEventSource_LineEnd,	/*!< Counts the number of Line End.*/
	CounterEventSource_ExposureStart,	/*!< Counts the number of Exposure Start.*/
	CounterEventSource_ExposureEnd,	/*!< Counts the number of Exposure End.*/
	CounterEventSource_Line0,	/*!< Counts the number of transitions on the chosen I/O Line.*/
	CounterEventSource_Line1,	/*!< Counts the number of transitions on the chosen I/O Line.*/
	CounterEventSource_Line2,	/*!< Counts the number of transitions on the chosen I/O Line.*/
	CounterEventSource_Counter0Start,	/*!< Counts the number of Counter Start.*/
	CounterEventSource_Counter1Start,	/*!< Counts the number of Counter Start.*/
	CounterEventSource_Counter2Start,	/*!< Counts the number of Counter Start.*/
	CounterEventSource_Counter0End,	/*!< Counts the number of Counter End.*/
	CounterEventSource_Counter1End,	/*!< Counts the number of Counter End.*/
	CounterEventSource_Counter2End,	/*!< Counts the number of Counter End.*/
	CounterEventSource_Timer0Start,	/*!< Counts the number of Timer Start pulses generated.*/
	CounterEventSource_Timer1Start,	/*!< Counts the number of Timer Start pulses generated.*/
	CounterEventSource_Timer2Start,	/*!< Counts the number of Timer Start pulses generated.*/
	CounterEventSource_Timer0End,	/*!< Counts the number of Timer End pulses generated.*/
	CounterEventSource_Timer1End,	/*!< Counts the number of Timer End pulses generated.*/
	CounterEventSource_Timer2End,	/*!< Counts the number of Timer End pulses generated.*/
	CounterEventSource_Encoder0,	/*!< Starts with the reception of the Encoder output signal.*/
	CounterEventSource_Encoder1,	/*!< Starts with the reception of the Encoder output signal.*/
	CounterEventSource_Encoder2,	/*!< Starts with the reception of the Encoder output signal.*/
	CounterEventSource_TimestampTick,	/*!< Counts the number of clock ticks of the Timestamp clock. Can be used to create a programmable timer.*/
	CounterEventSource_SoftwareSignal0,	/*!< Counts the number of Software Signal.*/
	CounterEventSource_SoftwareSignal1,	/*!< Counts the number of Software Signal.*/
	CounterEventSource_SoftwareSignal2,	/*!< Counts the number of Software Signal.*/
	CounterEventSource_Action0,	/*!< Counts the number of assertions of the chosen action signal.*/
	CounterEventSource_Action1,	/*!< Counts the number of assertions of the chosen action signal.*/
	CounterEventSource_Action2,	/*!< Counts the number of assertions of the chosen action signal.*/
	CounterEventSource_LinkTrigger0,	/*!< Counts the number of  Link Trigger.*/
	CounterEventSource_LinkTrigger1,	/*!< Counts the number of  Link Trigger.*/
	CounterEventSource_LinkTrigger2,	/*!< Counts the number of  Link Trigger.*/
	NUM_COUNTEREVENTSOURCE
} spinCounterEventSourceEnums;

typedef enum _spinCounterEventActivationEnums	/*!< Selects the Activation mode Event Source signal.*/
{
	CounterEventActivation_RisingEdge,	/*!< Counts on the Rising Edge of the signal.*/
	CounterEventActivation_FallingEdge,	/*!< Counts on the Falling Edge of the signal.*/
	CounterEventActivation_AnyEdge,	/*!< Counts on the Falling or rising Edge of the selected signal.*/
	NUM_COUNTEREVENTACTIVATION
} spinCounterEventActivationEnums;

typedef enum _spinCounterResetSourceEnums	/*!< Selects the signals that will be the source to reset the Counter.*/
{
	CounterResetSource_Off,	/*!< Disable the Counter Reset trigger.*/
	CounterResetSource_CounterTrigger,	/*!< Resets with the reception of a trigger on the CounterTriggerSource.*/
	CounterResetSource_AcquisitionTrigger,	/*!< Resets with the reception of the Acquisition Trigger.*/
	CounterResetSource_AcquisitionStart,	/*!< Resets with the reception of the Acquisition Start.*/
	CounterResetSource_AcquisitionEnd,	/*!< Resets with the reception of the Acquisition End.*/
	CounterResetSource_FrameTrigger,	/*!< Resets with the reception of the Frame Start Trigger.*/
	CounterResetSource_FrameStart,	/*!< Resets with the reception of the Frame Start.*/
	CounterResetSource_FrameEnd,	/*!< Resets with the reception of the Frame End.*/
	CounterResetSource_LineTrigger,	/*!< Resets with the reception of the Line Start Trigger.*/
	CounterResetSource_LineStart,	/*!< Resets with the reception of the Line Start.*/
	CounterResetSource_LineEnd,	/*!< Resets with the reception of the Line End.*/
	CounterResetSource_ExposureStart,	/*!< Resets with the reception of the Exposure Start.*/
	CounterResetSource_ExposureEnd,	/*!< Resets with the reception of the Exposure End.*/
	CounterResetSource_Line0,	/*!< Resets by the chosen I/O Line.*/
	CounterResetSource_Line1,	/*!< Resets by the chosen I/O Line.*/
	CounterResetSource_Line2,	/*!< Resets by the chosen I/O Line.*/
	CounterResetSource_Counter0Start,	/*!< Resets with the reception of the Counter Start.*/
	CounterResetSource_Counter1Start,	/*!< Resets with the reception of the Counter Start.*/
	CounterResetSource_Counter2Start,	/*!< Resets with the reception of the Counter Start.*/
	CounterResetSource_Counter0End,	/*!< Resets with the reception of the Counter End.*/
	CounterResetSource_Counter1End,	/*!< Resets with the reception of the Counter End.*/
	CounterResetSource_Counter2End,	/*!< Resets with the reception of the Counter End.*/
	CounterResetSource_Timer0Start,	/*!< Resets with the reception of the Timer Start.*/
	CounterResetSource_Timer1Start,	/*!< Resets with the reception of the Timer Start.*/
	CounterResetSource_Timer2Start,	/*!< Resets with the reception of the Timer Start.*/
	CounterResetSource_Timer0End,	/*!< Resets with the reception of the Timer End.*/
	CounterResetSource_Timer1End,	/*!< Resets with the reception of the Timer End.*/
	CounterResetSource_Timer2End,	/*!< Resets with the reception of the Timer End.*/
	CounterResetSource_Encoder0,	/*!< Starts with the reception of the Encoder output signal.*/
	CounterResetSource_Encoder1,	/*!< Starts with the reception of the Encoder output signal.*/
	CounterResetSource_Encoder2,	/*!< Starts with the reception of the Encoder output signal.*/
	CounterResetSource_UserOutput0,	/*!< Resets by the chosen User Output bit.*/
	CounterResetSource_UserOutput1,	/*!< Resets by the chosen User Output bit.*/
	CounterResetSource_UserOutput2,	/*!< Resets by the chosen User Output bit.*/
	CounterResetSource_SoftwareSignal0,	/*!< Resets on the reception of the Software Signal.*/
	CounterResetSource_SoftwareSignal1,	/*!< Resets on the reception of the Software Signal.*/
	CounterResetSource_SoftwareSignal2,	/*!< Resets on the reception of the Software Signal.*/
	CounterResetSource_Action0,	/*!< Resets on assertions of the chosen action signal (Broadcasted signal on the transport layer).*/
	CounterResetSource_Action1,	/*!< Resets on assertions of the chosen action signal (Broadcasted signal on the transport layer).*/
	CounterResetSource_Action2,	/*!< Resets on assertions of the chosen action signal (Broadcasted signal on the transport layer).*/
	CounterResetSource_LinkTrigger0,	/*!< Resets on the reception of the chosen Link Trigger (received from the transport layer).*/
	CounterResetSource_LinkTrigger1,	/*!< Resets on the reception of the chosen Link Trigger (received from the transport layer).*/
	CounterResetSource_LinkTrigger2,	/*!< Resets on the reception of the chosen Link Trigger (received from the transport layer).*/
	NUM_COUNTERRESETSOURCE
} spinCounterResetSourceEnums;

typedef enum _spinCounterResetActivationEnums	/*!< Selects the Activation mode of the Counter Reset Source signal.*/
{
	CounterResetActivation_RisingEdge,	/*!< Resets the counter on the Rising Edge of the signal.*/
	CounterResetActivation_FallingEdge,	/*!< Resets the counter on the Falling Edge of the signal.*/
	CounterResetActivation_AnyEdge,	/*!< Resets the counter on the Falling or rising Edge of the selected signal.*/
	CounterResetActivation_LevelHigh,	/*!< Resets the counter as long as the selected signal level is High.*/
	CounterResetActivation_LevelLow,	/*!< Resets the counter as long as the selected signal level is Low.*/
	NUM_COUNTERRESETACTIVATION
} spinCounterResetActivationEnums;

typedef enum _spinCounterStatusEnums	/*!< Returns the current status of the Counter.*/
{
	CounterStatus_CounterIdle,	/*!< The counter is idle.*/
	CounterStatus_CounterTriggerWait,	/*!< The counter is waiting for a start trigger.*/
	CounterStatus_CounterActive,	/*!< The counter is counting for the specified duration.*/
	CounterStatus_CounterCompleted,	/*!< The counter reached the CounterDuration count.*/
	CounterStatus_CounterOverflow,	/*!< The counter reached its maximum possible count.*/
	NUM_COUNTERSTATUS
} spinCounterStatusEnums;

typedef enum _spinCounterTriggerSourceEnums	/*!< Selects the source to start the Counter.*/
{
	CounterTriggerSource_Off,	/*!< Disables the Counter trigger.*/
	CounterTriggerSource_AcquisitionTrigger,	/*!< Starts with the reception of the Acquisition Trigger.*/
	CounterTriggerSource_AcquisitionStart,	/*!< Starts with the reception of the Acquisition Start.*/
	CounterTriggerSource_AcquisitionEnd,	/*!< Starts with the reception of the Acquisition End.*/
	CounterTriggerSource_FrameTrigger,	/*!< Starts with the reception of the Frame Start Trigger.*/
	CounterTriggerSource_FrameStart,	/*!< Starts with the reception of the Frame Start.*/
	CounterTriggerSource_FrameEnd,	/*!< Starts with the reception of the Frame End.*/
	CounterTriggerSource_FrameBurstStart,	/*!< Starts with the reception of the Frame Burst Start.*/
	CounterTriggerSource_FrameBurstEnd,	/*!< Starts with the reception of the Frame Burst End.*/
	CounterTriggerSource_LineTrigger,	/*!< Starts with the reception of the Line Start Trigger.*/
	CounterTriggerSource_LineStart,	/*!< Starts with the reception of the Line Start.*/
	CounterTriggerSource_LineEnd,	/*!< Starts with the reception of the Line End.*/
	CounterTriggerSource_ExposureStart,	/*!< Starts with the reception of the Exposure Start.*/
	CounterTriggerSource_ExposureEnd,	/*!< Starts with the reception of the Exposure End.*/
	CounterTriggerSource_Line0,	/*!< Starts when the specified CounterTriggerActivation condition is met on the chosen I/O Line.*/
	CounterTriggerSource_Line1,	/*!< Starts when the specified CounterTriggerActivation condition is met on the chosen I/O Line.*/
	CounterTriggerSource_Line2,	/*!< Starts when the specified CounterTriggerActivation condition is met on the chosen I/O Line.*/
	CounterTriggerSource_UserOutput0,	/*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
	CounterTriggerSource_UserOutput1,	/*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
	CounterTriggerSource_UserOutput2,	/*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
	CounterTriggerSource_Counter0Start,	/*!< Starts with the reception of the Counter Start.*/
	CounterTriggerSource_Counter1Start,	/*!< Starts with the reception of the Counter Start.*/
	CounterTriggerSource_Counter2Start,	/*!< Starts with the reception of the Counter Start.*/
	CounterTriggerSource_Counter0End,	/*!< Starts with the reception of the Counter End.*/
	CounterTriggerSource_Counter1End,	/*!< Starts with the reception of the Counter End.*/
	CounterTriggerSource_Counter2End,	/*!< Starts with the reception of the Counter End.*/
	CounterTriggerSource_Timer0Start,	/*!< Starts with the reception of the Timer Start.*/
	CounterTriggerSource_Timer1Start,	/*!< Starts with the reception of the Timer Start.*/
	CounterTriggerSource_Timer2Start,	/*!< Starts with the reception of the Timer Start.*/
	CounterTriggerSource_Timer0End,	/*!< Starts with the reception of the Timer End.*/
	CounterTriggerSource_Timer1End,	/*!< Starts with the reception of the Timer End.*/
	CounterTriggerSource_Timer2End,	/*!< Starts with the reception of the Timer End.*/
	CounterTriggerSource_Encoder0,	/*!< Starts with the reception of the Encoder output signal.*/
	CounterTriggerSource_Encoder1,	/*!< Starts with the reception of the Encoder output signal.*/
	CounterTriggerSource_Encoder2,	/*!< Starts with the reception of the Encoder output signal.*/
	CounterTriggerSource_SoftwareSignal0,	/*!< Starts on the reception of the Software Signal.*/
	CounterTriggerSource_SoftwareSignal1,	/*!< Starts on the reception of the Software Signal.*/
	CounterTriggerSource_SoftwareSignal2,	/*!< Starts on the reception of the Software Signal.*/
	CounterTriggerSource_Action0,	/*!< Starts with the assertion of the chosen action signal.*/
	CounterTriggerSource_Action1,	/*!< Starts with the assertion of the chosen action signal.*/
	CounterTriggerSource_Action2,	/*!< Starts with the assertion of the chosen action signal.*/
	CounterTriggerSource_LinkTrigger0,	/*!< Starts with the reception of the chosen Link Trigger signal.*/
	CounterTriggerSource_LinkTrigger1,	/*!< Starts with the reception of the chosen Link Trigger signal.*/
	CounterTriggerSource_LinkTrigger2,	/*!< Starts with the reception of the chosen Link Trigger signal.*/
	NUM_COUNTERTRIGGERSOURCE
} spinCounterTriggerSourceEnums;

typedef enum _spinCounterTriggerActivationEnums	/*!< Selects the activation mode of the trigger to start the Counter.*/
{
	CounterTriggerActivation_RisingEdge,	/*!< Starts counting on the Rising Edge of the selected trigger signal.*/
	CounterTriggerActivation_FallingEdge,	/*!< Starts counting on the Falling Edge of the selected trigger signal.*/
	CounterTriggerActivation_AnyEdge,	/*!< Starts counting on the Falling or rising Edge of the selected trigger signal.*/
	CounterTriggerActivation_LevelHigh,	/*!< Counts as long as the selected trigger signal level is High.*/
	CounterTriggerActivation_LevelLow,	/*!< Counts as long as the selected trigger signal level is Low.*/
	NUM_COUNTERTRIGGERACTIVATION
} spinCounterTriggerActivationEnums;

typedef enum _spinTimerSelectorEnums	/*!< Selects which Timer to configure.*/
{
	TimerSelector_Timer0,	/*!< Selects the Timer 0.*/
	TimerSelector_Timer1,	/*!< Selects the Timer 1.*/
	TimerSelector_Timer2,	/*!< Selects the Timer 2.*/
	NUM_TIMERSELECTOR
} spinTimerSelectorEnums;

typedef enum _spinTimerStatusEnums	/*!< Returns the current status of the Timer.*/
{
	TimerStatus_TimerIdle,	/*!< The Timer is idle.*/
	TimerStatus_TimerTriggerWait,	/*!< The Timer is waiting for a start trigger.*/
	TimerStatus_TimerActive,	/*!< The Timer is counting for the specified duration.*/
	TimerStatus_TimerCompleted,	/*!< The Timer reached the TimerDuration count.*/
	NUM_TIMERSTATUS
} spinTimerStatusEnums;

typedef enum _spinTimerTriggerSourceEnums	/*!< Selects the source of the trigger to start the Timer.*/
{
	TimerTriggerSource_Off,	/*!< Disables the Timer trigger.*/
	TimerTriggerSource_AcquisitionTrigger,	/*!< Starts with the reception of the Acquisition Trigger.*/
	TimerTriggerSource_AcquisitionStart,	/*!< Starts with the reception of the Acquisition Start.*/
	TimerTriggerSource_AcquisitionEnd,	/*!< Starts with the reception of the Acquisition End.*/
	TimerTriggerSource_FrameTrigger,	/*!< Starts with the reception of the Frame Start Trigger.*/
	TimerTriggerSource_FrameStart,	/*!< Starts with the reception of the Frame Start.*/
	TimerTriggerSource_FrameEnd,	/*!< Starts with the reception of the Frame End.*/
	TimerTriggerSource_FrameBurstStart,	/*!< Starts with the reception of the Frame Burst Start.*/
	TimerTriggerSource_FrameBurstEnd,	/*!< Starts with the reception of the Frame Burst End.*/
	TimerTriggerSource_LineTrigger,	/*!< Starts with the reception of the Line Start Trigger.*/
	TimerTriggerSource_LineStart,	/*!< Starts with the reception of the Line Start.*/
	TimerTriggerSource_LineEnd,	/*!< Starts with the reception of the Line End.*/
	TimerTriggerSource_ExposureStart,	/*!< Starts with the reception of the Exposure Start.*/
	TimerTriggerSource_ExposureEnd,	/*!< Starts with the reception of the Exposure End.*/
	TimerTriggerSource_Line0,	/*!< Starts when the specidfied TimerTriggerActivation condition is met on the chosen I/O Line.*/
	TimerTriggerSource_Line1,	/*!< Starts when the specidfied TimerTriggerActivation condition is met on the chosen I/O Line.*/
	TimerTriggerSource_Line2,	/*!< Starts when the specidfied TimerTriggerActivation condition is met on the chosen I/O Line.*/
	TimerTriggerSource_UserOutput0,	/*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
	TimerTriggerSource_UserOutput1,	/*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
	TimerTriggerSource_UserOutput2,	/*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
	TimerTriggerSource_Counter0Start,	/*!< Starts with the reception of the Counter Start.*/
	TimerTriggerSource_Counter1Start,	/*!< Starts with the reception of the Counter Start.*/
	TimerTriggerSource_Counter2Start,	/*!< Starts with the reception of the Counter Start.*/
	TimerTriggerSource_Counter0End,	/*!< Starts with the reception of the Counter End.*/
	TimerTriggerSource_Counter1End,	/*!< Starts with the reception of the Counter End.*/
	TimerTriggerSource_Counter2End,	/*!< Starts with the reception of the Counter End.*/
	TimerTriggerSource_Timer0Start,	/*!< Starts with the reception of the Timer Start.*/
	TimerTriggerSource_Timer1Start,	/*!< Starts with the reception of the Timer Start.*/
	TimerTriggerSource_Timer2Start,	/*!< Starts with the reception of the Timer Start.*/
	TimerTriggerSource_Timer0End,	/*!< Starts with the reception of the Timer End. Note that a timer can retrigger itself to achieve a free running Timer.*/
	TimerTriggerSource_Timer1End,	/*!< Starts with the reception of the Timer End. Note that a timer can retrigger itself to achieve a free running Timer.*/
	TimerTriggerSource_Timer2End,	/*!< Starts with the reception of the Timer End. Note that a timer can retrigger itself to achieve a free running Timer.*/
	TimerTriggerSource_Encoder0,	/*!< Starts with the reception of the Encoder output signal.*/
	TimerTriggerSource_Encoder1,	/*!< Starts with the reception of the Encoder output signal.*/
	TimerTriggerSource_Encoder2,	/*!< Starts with the reception of the Encoder output signal.*/
	TimerTriggerSource_SoftwareSignal0,	/*!< Starts on the reception of the Software Signal.*/
	TimerTriggerSource_SoftwareSignal1,	/*!< Starts on the reception of the Software Signal.*/
	TimerTriggerSource_SoftwareSignal2,	/*!< Starts on the reception of the Software Signal.*/
	TimerTriggerSource_Action0,	/*!< Starts with the assertion of the chosen action signal.*/
	TimerTriggerSource_Action1,	/*!< Starts with the assertion of the chosen action signal.*/
	TimerTriggerSource_Action2,	/*!< Starts with the assertion of the chosen action signal.*/
	TimerTriggerSource_LinkTrigger0,	/*!< Starts with the reception of the chosen Link Trigger.*/
	TimerTriggerSource_LinkTrigger1,	/*!< Starts with the reception of the chosen Link Trigger.*/
	TimerTriggerSource_LinkTrigger2,	/*!< Starts with the reception of the chosen Link Trigger.*/
	NUM_TIMERTRIGGERSOURCE
} spinTimerTriggerSourceEnums;

typedef enum _spinTimerTriggerActivationEnums	/*!< Selects the activation mode of the trigger to start the Timer.*/
{
	TimerTriggerActivation_RisingEdge,	/*!< Starts counting on the Rising Edge of the selected trigger signal.*/
	TimerTriggerActivation_FallingEdge,	/*!< Starts counting on the Falling Edge of the selected trigger signal.*/
	TimerTriggerActivation_AnyEdge,	/*!< Starts counting on the Falling or Rising Edge of the selected trigger signal.*/
	TimerTriggerActivation_LevelHigh,	/*!< Counts as long as the selected trigger signal level is High.*/
	TimerTriggerActivation_LevelLow,	/*!< Counts as long as the selected trigger signal level is Low.*/
	NUM_TIMERTRIGGERACTIVATION
} spinTimerTriggerActivationEnums;

typedef enum _spinEncoderSelectorEnums	/*!< Selects which Encoder to configure.*/
{
	EncoderSelector_Encoder0,	/*!< Selects Encoder 0.*/
	EncoderSelector_Encoder1,	/*!< Selects Encoder 1.*/
	EncoderSelector_Encoder2,	/*!< Selects Encoder 2.*/
	NUM_ENCODERSELECTOR
} spinEncoderSelectorEnums;

typedef enum _spinEncoderSourceAEnums	/*!< Selects the signal which will be the source of the A input of the Encoder.*/
{
	EncoderSourceA_Off,	/*!< Counter is stopped.*/
	EncoderSourceA_Line0,	/*!< Encoder Forward input is taken from the chosen I/O Line.*/
	EncoderSourceA_Line1,	/*!< Encoder Forward input is taken from the chosen I/O Line.*/
	EncoderSourceA_Line2,	/*!< Encoder Forward input is taken from the chosen I/O Line.*/
	NUM_ENCODERSOURCEA
} spinEncoderSourceAEnums;

typedef enum _spinEncoderSourceBEnums	/*!< Selects the signal which will be the source of the B input of the Encoder.*/
{
	EncoderSourceB_Off,	/*!< Counter is stopped.*/
	EncoderSourceB_Line0,	/*!< Encoder Reverse input is taken from the chosen I/O Line..*/
	EncoderSourceB_Line1,	/*!< Encoder Reverse input is taken from the chosen I/O Line..*/
	EncoderSourceB_Line2,	/*!< Encoder Reverse input is taken from the chosen I/O Line..*/
	NUM_ENCODERSOURCEB
} spinEncoderSourceBEnums;

typedef enum _spinEncoderModeEnums	/*!< Selects if the count of encoder uses FourPhase mode with jitter filtering or the HighResolution mode without jitter filtering.*/
{
	EncoderMode_FourPhase,	/*!< The counter increments or decrements 1 for every full quadrature cycle with jitter filtering.*/
	EncoderMode_HighResolution,	/*!< The counter increments or decrements every quadrature phase for high resolution counting, but without jitter filtering.*/
	NUM_ENCODERMODE
} spinEncoderModeEnums;

typedef enum _spinEncoderOutputModeEnums	/*!< Selects the conditions for the Encoder interface to generate a valid Encoder output signal.*/
{
	EncoderOutputMode_Off,	/*!< No output pulse are generated.*/
	EncoderOutputMode_PositionUp,	/*!< Output pulses are generated at all new positions in the positive direction. If the encoder reverses no output pulse are generated until it has again passed the position where the reversal started.*/
	EncoderOutputMode_PositionDown,	/*!< Output pulses are generated at all new positions in the negative direction. If the encoder reverses no output pulse are generated until it has again passed the position where the reversal started.*/
	EncoderOutputMode_DirectionUp,	/*!< Output pulses are generated at all position increments in the positive direction while ignoring negative direction motion.*/
	EncoderOutputMode_DirectionDown,	/*!< Output pulses are generated at all position increments in the negative direction while ignoring positive direction motion.*/
	EncoderOutputMode_Motion,	/*!< Output pulses are generated at all motion increments in both directions.*/
	NUM_ENCODEROUTPUTMODE
} spinEncoderOutputModeEnums;

typedef enum _spinEncoderStatusEnums	/*!< Returns the motion status of the encoder.*/
{
	EncoderStatus_EncoderUp,	/*!< The encoder counter last incremented.*/
	EncoderStatus_EncoderDown,	/*!< The encoder counter last decremented.*/
	EncoderStatus_EncoderIdle,	/*!< The encoder is not active.*/
	EncoderStatus_EncoderStatic,	/*!< No motion within the EncoderTimeout time.*/
	NUM_ENCODERSTATUS
} spinEncoderStatusEnums;

typedef enum _spinEncoderResetSourceEnums	/*!< Selects the signals that will be the source to reset the Encoder.*/
{
	EncoderResetSource_Off,	/*!< Disable the Encoder Reset trigger.*/
	EncoderResetSource_AcquisitionTrigger,	/*!< Resets with the reception of the Acquisition Trigger.*/
	EncoderResetSource_AcquisitionStart,	/*!< Resets with the reception of the Acquisition Start.*/
	EncoderResetSource_AcquisitionEnd,	/*!< Resets with the reception of the Acquisition End.*/
	EncoderResetSource_FrameTrigger,	/*!< Resets with the reception of the Frame Start Trigger.*/
	EncoderResetSource_FrameStart,	/*!< Resets with the reception of the Frame Start.*/
	EncoderResetSource_FrameEnd,	/*!< Resets with the reception of the Frame End.*/
	EncoderResetSource_ExposureStart,	/*!< Resets with the reception of the Exposure Start.*/
	EncoderResetSource_ExposureEnd,	/*!< Resets with the reception of the Exposure End.*/
	EncoderResetSource_Line0,	/*!< Resets by the chosen I/O Line.*/
	EncoderResetSource_Line1,	/*!< Resets by the chosen I/O Line.*/
	EncoderResetSource_Line2,	/*!< Resets by the chosen I/O Line.*/
	EncoderResetSource_Counter0Start,	/*!< Resets with the reception of the Counter Start.*/
	EncoderResetSource_Counter1Start,	/*!< Resets with the reception of the Counter Start.*/
	EncoderResetSource_Counter2Start,	/*!< Resets with the reception of the Counter Start.*/
	EncoderResetSource_Counter0End,	/*!< Resets with the reception of the Counter End.*/
	EncoderResetSource_Counter1End,	/*!< Resets with the reception of the Counter End.*/
	EncoderResetSource_Counter2End,	/*!< Resets with the reception of the Counter End.*/
	EncoderResetSource_Timer0Start,	/*!< Resets with the reception of the Timer Start.*/
	EncoderResetSource_Timer1Start,	/*!< Resets with the reception of the Timer Start.*/
	EncoderResetSource_Timer2Start,	/*!< Resets with the reception of the Timer Start.*/
	EncoderResetSource_Timer0End,	/*!< Resets with the reception of the Timer End.*/
	EncoderResetSource_Timer1End,	/*!< Resets with the reception of the Timer End.*/
	EncoderResetSource_Timer2End,	/*!< Resets with the reception of the Timer End.*/
	EncoderResetSource_UserOutput0,	/*!< Resets by the chosen User Output bit.*/
	EncoderResetSource_UserOutput1,	/*!< Resets by the chosen User Output bit.*/
	EncoderResetSource_UserOutput2,	/*!< Resets by the chosen User Output bit.*/
	EncoderResetSource_SoftwareSignal0,	/*!< Resets on the reception of the Software Signal.*/
	EncoderResetSource_SoftwareSignal1,	/*!< Resets on the reception of the Software Signal.*/
	EncoderResetSource_SoftwareSignal2,	/*!< Resets on the reception of the Software Signal.*/
	EncoderResetSource_Action0,	/*!< Resets on assertions of the chosen action signal (Broadcasted signal on the transport layer).*/
	EncoderResetSource_Action1,	/*!< Resets on assertions of the chosen action signal (Broadcasted signal on the transport layer).*/
	EncoderResetSource_Action2,	/*!< Resets on assertions of the chosen action signal (Broadcasted signal on the transport layer).*/
	EncoderResetSource_LinkTrigger0,	/*!< Resets on the reception of the chosen Link Trigger (received from the transport layer).*/
	EncoderResetSource_LinkTrigger1,	/*!< Resets on the reception of the chosen Link Trigger (received from the transport layer).*/
	EncoderResetSource_LinkTrigger2,	/*!< Resets on the reception of the chosen Link Trigger (received from the transport layer).*/
	NUM_ENCODERRESETSOURCE
} spinEncoderResetSourceEnums;

typedef enum _spinEncoderResetActivationEnums	/*!< Selects the Activation mode of the Encoder Reset Source signal.*/
{
	EncoderResetActivation_RisingEdge,	/*!< Resets the Encoder on the Rising Edge of the signal.*/
	EncoderResetActivation_FallingEdge,	/*!< Resets the Encoder on the Falling Edge of the signal.*/
	EncoderResetActivation_AnyEdge,	/*!< Resets the Encoder on the Falling or rising Edge of the selected signal.*/
	EncoderResetActivation_LevelHigh,	/*!< Resets the Encoder as long as the selected signal level is High.*/
	EncoderResetActivation_LevelLow,	/*!< Resets the Encoder as long as the selected signal level is Low.*/
	NUM_ENCODERRESETACTIVATION
} spinEncoderResetActivationEnums;

typedef enum _spinSoftwareSignalSelectorEnums	/*!< Selects which Software Signal features to control.*/
{
	SoftwareSignalSelector_SoftwareSignal0,	/*!< Selects the software generated signal to control.*/
	SoftwareSignalSelector_SoftwareSignal1,	/*!< Selects the software generated signal to control.*/
	SoftwareSignalSelector_SoftwareSignal2,	/*!< Selects the software generated signal to control.*/
	NUM_SOFTWARESIGNALSELECTOR
} spinSoftwareSignalSelectorEnums;

typedef enum _spinActionUnconditionalModeEnums	/*!< Enables the unconditional action command mode where action commands are processed even when the primary control channel is closed.*/
{
	ActionUnconditionalMode_Off,	/*!< Unconditional mode is disabled.*/
	ActionUnconditionalMode_On,	/*!< Unconditional mode is enabled.*/
	NUM_ACTIONUNCONDITIONALMODE
} spinActionUnconditionalModeEnums;

typedef enum _spinEventSelectorEnums	/*!< Selects which Event to signal to the host application.*/
{
	EventSelector_AcquisitionTrigger,	/*!< Device just received a trigger for the Acquisition of one or many Frames.*/
	EventSelector_AcquisitionStart,	/*!< Device just started the Acquisition of one or many Frames.*/
	EventSelector_AcquisitionEnd,	/*!< Device just completed the Acquisition of one or many Frames.*/
	EventSelector_AcquisitionTransferStart,	/*!< Device just started the transfer of one or many Frames.*/
	EventSelector_AcquisitionTransferEnd,	/*!< Device just completed the transfer of one or many Frames.*/
	EventSelector_AcquisitionError,	/*!< Device just detected an error during the active Acquisition.*/
	EventSelector_FrameTrigger,	/*!< Device just received a trigger to start the capture of one Frame.*/
	EventSelector_FrameStart,	/*!< Device just started the capture of one Frame.*/
	EventSelector_FrameEnd,	/*!< Device just completed the capture of one Frame.*/
	EventSelector_FrameBurstStart,	/*!< Device just started the capture of a burst of Frames.*/
	EventSelector_FrameBurstEnd,	/*!< Device just completed the capture of a burst of Frames.*/
	EventSelector_FrameTransferStart,	/*!< Device just started the transfer of one Frame.*/
	EventSelector_FrameTransferEnd,	/*!< Device just completed the transfer of one Frame.*/
	EventSelector_ExposureStart,	/*!< Device just started the exposure of one Frame (or Line).*/
	EventSelector_ExposureEnd,	/*!< Device just completed the exposure of one Frame (or Line).*/
	EventSelector_Stream0TransferStart,	/*!< Device just started the transfer of one or many Blocks.*/
	EventSelector_Stream0TransferEnd,	/*!< Device just completed the transfer of one or many Blocks.*/
	EventSelector_Stream0TransferPause,	/*!< Device just paused the transfer.*/
	EventSelector_Stream0TransferResume,	/*!< Device just resumed the transfer.*/
	EventSelector_Stream0TransferBlockStart,	/*!< Device just started the transfer of one Block.*/
	EventSelector_Stream0TransferBlockEnd,	/*!< Device just completed the transfer of one Block.*/
	EventSelector_Stream0TransferBlockTrigger,	/*!< Device just received a trigger to start the transfer of one Block.*/
	EventSelector_Stream0TransferBurstStart,	/*!< Device just started the transfer of a burst of Blocks.*/
	EventSelector_Stream0TransferBurstEnd,	/*!< Device just completed the transfer of a burst of Blocks.*/
	EventSelector_Stream0TransferOverflow,	/*!< Device transfer queue overflowed.*/
	EventSelector_SequencerSetChange,	/*!< Device sequencer set has changed.*/
	EventSelector_Counter0Start,	/*!< The event will be generated when counter 0 starts counting.*/
	EventSelector_Counter1Start,	/*!< The event will be generated when counter 1 starts counting.*/
	EventSelector_Counter0End,	/*!< The event will be generated when counter 0 ends counting.*/
	EventSelector_Counter1End,	/*!< The event will be generated when counter 1 ends counting.*/
	EventSelector_Timer0Start,	/*!< The event will be generated when Timer 0 starts counting.*/
	EventSelector_Timer1Start,	/*!< The event will be generated when Timer 1 starts counting.*/
	EventSelector_Timer0End,	/*!< The event will be generated when Timer 0 ends counting.*/
	EventSelector_Timer1End,	/*!< The event will be generated when Timer 1 ends counting.*/
	EventSelector_Encoder0Stopped,	/*!< The event will be generated when the Encoder 0 stops for longer than EncoderTimeout.*/
	EventSelector_Encoder1Stopped,	/*!< The event will be generated when the Encoder 1 stops for longer than EncoderTimeout.*/
	EventSelector_Encoder0Restarted,	/*!< The event will be generated when the Encoder 0 restarts moving.*/
	EventSelector_Encoder1Restarted,	/*!< The event will be generated when the Encoder 1 restarts moving.*/
	EventSelector_Line0RisingEdge,	/*!< The event will be generated when a Rising Edge is detected on the Line 0.*/
	EventSelector_Line1RisingEdge,	/*!< The event will be generated when a Rising Edge is detected on the Line 1.*/
	EventSelector_Line0FallingEdge,	/*!< The event will be generated when a Falling Edge is detected on the Line 0.*/
	EventSelector_Line1FallingEdge,	/*!< The event will be generated when a Falling Edge is detected on the Line 1.*/
	EventSelector_Line0AnyEdge,	/*!< The event will be generated when a Falling or Rising Edge is detected on the Line 0.*/
	EventSelector_Line1AnyEdge,	/*!< The event will be generated when a Falling or Rising Edge is detected on the Line 1.*/
	EventSelector_LinkTrigger0,	/*!< The event will be generated when a Rising Edge is detected on the LinkTrigger 0.*/
	EventSelector_LinkTrigger1,	/*!< The event will be generated when a Rising Edge is detected on the LinkTrigger 1.*/
	EventSelector_ActionLate,	/*!< Then event will be generated when a valid scheduled action command is received and is scheduled to be executed at a time that is already past.*/
	EventSelector_LinkSpeedChange,	/*!< Then event will be generated when the link speed has changed.*/
	EventSelector_Error,	/*!< Device just detected an error during the active Acquisition.*/
	EventSelector_Test,	/*!< The test event will be generated when the device receives the TestEventGenerate command(EventNotification for the Test event is always On).*/
	EventSelector_PrimaryApplicationSwitch,	/*!< Then event will be generated when a primary application switchover has been granted.*/
	NUM_EVENTSELECTOR
} spinEventSelectorEnums;

typedef enum _spinEventNotificationEnums	/*!< Activate or deactivate the notification to the host application of the occurrence of the selected Event.*/
{
	EventNotification_Off,	/*!< The selected Event notification is disabled.*/
	EventNotification_On,	/*!< The selected Event notification is enabled.*/
	NUM_EVENTNOTIFICATION
} spinEventNotificationEnums;

typedef enum _spinUserSetSelectorEnums	/*!< Selects the feature User Set to load, save or configure.*/
{
	UserSetSelector_Default,	/*!< Selects the factory setting user set.*/
	UserSetSelector_UserSet0,	/*!< Selects the user set 0.*/
	UserSetSelector_UserSet1,	/*!< Selects the user set 1.*/
	NUM_USERSETSELECTOR
} spinUserSetSelectorEnums;

typedef enum _spinUserSetDefaultEnums	/*!< Selects the feature User Set to load and make active by default when the device is reset.*/
{
	UserSetDefault_Default,	/*!< Select the factory setting user set.*/
	UserSetDefault_UserSet0,	/*!< Select the user set 0.*/
	UserSetDefault_UserSet1,	/*!< Select the user set 1.*/
	NUM_USERSETDEFAULT
} spinUserSetDefaultEnums;

typedef enum _spinUserSetFeatureSelectorEnums	/*!< Selects which individual UserSet feature to control.*/
{

	NUM_USERSETFEATURESELECTOR
} spinUserSetFeatureSelectorEnums;

typedef enum _spinSequencerModeEnums	/*!< Controls if the sequencer mechanism is active.*/
{
	SequencerMode_On,	/*!< Enables the sequencer.*/
	SequencerMode_Off,	/*!< Disables the sequencer.*/
	NUM_SEQUENCERMODE
} spinSequencerModeEnums;

typedef enum _spinSequencerConfigurationModeEnums	/*!< Controls if the sequencer configuration mode is active.*/
{
	SequencerConfigurationMode_On,	/*!< Enables the sequencer configuration mode.*/
	SequencerConfigurationMode_Off,	/*!< Disables the sequencer configuration mode.*/
	NUM_SEQUENCERCONFIGURATIONMODE
} spinSequencerConfigurationModeEnums;

typedef enum _spinSequencerFeatureSelectorEnums	/*!< Selects which sequencer features to control.*/
{
	SequencerFeatureSelector_ExposureTime,	/*!< */
	SequencerFeatureSelector_Gain,	/*!< */
	SequencerFeatureSelector_OffsetX,	/*!< */
	SequencerFeatureSelector_OffsetY,	/*!< */
	SequencerFeatureSelector_Width,	/*!< */
	SequencerFeatureSelector_Height,	/*!< */
	NUM_SEQUENCERFEATURESELECTOR
} spinSequencerFeatureSelectorEnums;

typedef enum _spinSequencerTriggerSourceEnums	/*!< Specifies the internal signal or physical input line to use as the sequencer trigger source.*/
{
	SequencerTriggerSource_Off,	/*!< Disables the sequencer trigger.*/
	SequencerTriggerSource_AcquisitionTrigger,	/*!< Starts with the reception of the Acquisition Trigger.*/
	SequencerTriggerSource_AcquisitionStart,	/*!< Starts with the reception of the Acquisition Start.*/
	SequencerTriggerSource_AcquisitionEnd,	/*!< Starts with the reception of the Acquisition End.*/
	SequencerTriggerSource_FrameTrigger,	/*!< Starts with the reception of the Frame Start Trigger.*/
	SequencerTriggerSource_FrameStart,	/*!< Starts with the reception of the Frame Start.*/
	SequencerTriggerSource_FrameEnd,	/*!< Starts with the reception of the Frame End.*/
	SequencerTriggerSource_FrameBurstStart,	/*!< Starts with the reception of the Frame Burst Start.*/
	SequencerTriggerSource_FrameBurstEnd,	/*!< Starts with the reception of the Frame Burst End.*/
	SequencerTriggerSource_ExposureStart,	/*!< Starts with the reception of the Exposure Start.*/
	SequencerTriggerSource_ExposureEnd,	/*!< Starts with the reception of the Exposure End.*/
	SequencerTriggerSource_Line0,	/*!< Starts when the specidfied TimerTriggerActivation condition is met on the chosen I/O Line.*/
	SequencerTriggerSource_Line1,	/*!< Starts when the specidfied TimerTriggerActivation condition is met on the chosen I/O Line.*/
	SequencerTriggerSource_Line2,	/*!< Starts when the specidfied TimerTriggerActivation condition is met on the chosen I/O Line.*/
	SequencerTriggerSource_UserOutput0,	/*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
	SequencerTriggerSource_UserOutput1,	/*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
	SequencerTriggerSource_UserOutput2,	/*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
	SequencerTriggerSource_Counter0Start,	/*!< Starts with the reception of the Counter Start.*/
	SequencerTriggerSource_Counter1Start,	/*!< Starts with the reception of the Counter Start.*/
	SequencerTriggerSource_Counter2Start,	/*!< Starts with the reception of the Counter Start.*/
	SequencerTriggerSource_Counter0End,	/*!< Starts with the reception of the Counter End.*/
	SequencerTriggerSource_Counter1End,	/*!< Starts with the reception of the Counter End.*/
	SequencerTriggerSource_Counter2End,	/*!< Starts with the reception of the Counter End.*/
	SequencerTriggerSource_Timer0Start,	/*!< Starts with the reception of the Timer Start.*/
	SequencerTriggerSource_Timer1Start,	/*!< Starts with the reception of the Timer Start.*/
	SequencerTriggerSource_Timer2Start,	/*!< Starts with the reception of the Timer Start.*/
	SequencerTriggerSource_Timer0End,	/*!< Starts with the reception of the Timer End.*/
	SequencerTriggerSource_Timer1End,	/*!< Starts with the reception of the Timer End.*/
	SequencerTriggerSource_Timer2End,	/*!< Starts with the reception of the Timer End.*/
	SequencerTriggerSource_Encoder0,	/*!< Starts with the reception of the Encoder output signal.*/
	SequencerTriggerSource_Encoder1,	/*!< Starts with the reception of the Encoder output signal.*/
	SequencerTriggerSource_Encoder2,	/*!< Starts with the reception of the Encoder output signal.*/
	SequencerTriggerSource_SoftwareSignal0,	/*!< Starts on the reception of the Software Signal.*/
	SequencerTriggerSource_SoftwareSignal1,	/*!< Starts on the reception of the Software Signal.*/
	SequencerTriggerSource_SoftwareSignal2,	/*!< Starts on the reception of the Software Signal.*/
	SequencerTriggerSource_Action0,	/*!< Starts with the assertion of the chosen action signal.*/
	SequencerTriggerSource_Action1,	/*!< Starts with the assertion of the chosen action signal.*/
	SequencerTriggerSource_Action2,	/*!< Starts with the assertion of the chosen action signal.*/
	SequencerTriggerSource_LinkTrigger0,	/*!< Starts with the reception of the chosen Link Trigger.*/
	SequencerTriggerSource_LinkTrigger1,	/*!< Starts with the reception of the chosen Link Trigger.*/
	SequencerTriggerSource_LinkTrigger2,	/*!< Starts with the reception of the chosen Link Trigger.*/
	SequencerTriggerSource_CC1,	/*!< Index of the Camera Link physical line and associated I/O control block to use. This ensures a direct mapping between the lines on the frame grabber and on the camera. Applicable to CameraLink products only.*/
	SequencerTriggerSource_CC2,	/*!< Index of the Camera Link physical line and associated I/O control block to use. This ensures a direct mapping between the lines on the frame grabber and on the camera. Applicable to CameraLink products only.*/
	SequencerTriggerSource_CC3,	/*!< Index of the Camera Link physical line and associated I/O control block to use. This ensures a direct mapping between the lines on the frame grabber and on the camera. Applicable to CameraLink products only.*/
	SequencerTriggerSource_CC4,	/*!< Index of the Camera Link physical line and associated I/O control block to use. This ensures a direct mapping between the lines on the frame grabber and on the camera. Applicable to CameraLink products only.*/
	NUM_SEQUENCERTRIGGERSOURCE
} spinSequencerTriggerSourceEnums;

typedef enum _spinSequencerTriggerActivationEnums	/*!< Specifies the activation mode of the sequencer trigger.*/
{
	SequencerTriggerActivation_RisingEdge,	/*!< Specifies that the trigger is considered valid on the rising edge of the source signal.*/
	SequencerTriggerActivation_FallingEdge,	/*!< Specifies that the trigger is considered valid on the falling edge of the source signal.*/
	SequencerTriggerActivation_AnyEdge,	/*!< Specifies that the trigger is considered valid on the falling or rising edge of the source signal.*/
	SequencerTriggerActivation_LevelHigh,	/*!< Specifies that the trigger is considered valid as long as the level of the source signal is high.*/
	SequencerTriggerActivation_LevelLow,	/*!< Specifies that the trigger is considered valid as long as the level of the source signal is low.*/
	NUM_SEQUENCERTRIGGERACTIVATION
} spinSequencerTriggerActivationEnums;

typedef enum _spinFileSelectorEnums	/*!< Selects the target file in the device.*/
{
	FileSelector_UserSetDefault,	/*!< The default user set of the device.*/
	FileSelector_UserSet1,	/*!< The first user set of the device.*/
	FileSelector_UserSet2,	/*!< The second user set of the device.*/
	FileSelector_UserSet3,	/*!< The third user set of the device.*/
	FileSelector_LUTLuminance,	/*!< The Luminance LUT of the camera.*/
	FileSelector_LUTRed,	/*!< The Red LUT of the camera.*/
	FileSelector_LUTGreen,	/*!< The Green LUT of the camera.*/
	FileSelector_LUTBlue,	/*!< The Blue LUT of the camera.*/
	NUM_FILESELECTOR
} spinFileSelectorEnums;

typedef enum _spinFileOperationSelectorEnums	/*!< Selects the target operation for the selected file in the device. This Operation is executed when the FileOperationExecute feature is called.*/
{
	FileOperationSelector_Open,	/*!< Opens the file selected by FileSelector in the device. The access mode in which the file is opened is selected by FileOpenMode.*/
	FileOperationSelector_Close,	/*!< Closes the file selected by FileSelector in the device.*/
	FileOperationSelector_Read,	/*!< Reads FileAccessLength bytes from the device storage at the file relative offset FileAccessOffset into FileAccessBuffer.*/
	FileOperationSelector_Write,	/*!< Writes FileAccessLength bytes taken from the FileAccessBuffer into the device storage at the file relative offset FileAccessOffset.*/
	FileOperationSelector_Delete,	/*!< Deletes the file selected by FileSelector in the device. Note that deleting a device file should not remove the associated FileSelector entry to allow future operation on this file.*/
	NUM_FILEOPERATIONSELECTOR
} spinFileOperationSelectorEnums;

typedef enum _spinFileOpenModeEnums	/*!< Selects the access mode in which a file is opened in the device.*/
{
	FileOpenMode_Read,	/*!< This mode selects read-only open mode.*/
	FileOpenMode_Write,	/*!< This mode selects write-only open mode.*/
	FileOpenMode_ReadWrite,	/*!< This mode selects read and write open mode.*/
	NUM_FILEOPENMODE
} spinFileOpenModeEnums;

typedef enum _spinFileOperationStatusEnums	/*!< Represents the file operation execution status.*/
{
	FileOperationStatus_Success,	/*!< File Operation was sucessful.*/
	FileOperationStatus_Failure,	/*!< File Operation failed.*/
	NUM_FILEOPERATIONSTATUS
} spinFileOperationStatusEnums;

typedef enum _spinSourceSelectorEnums	/*!< Selects the source to control.*/
{
	SourceSelector_Source0,	/*!< Selects the data source 0.*/
	SourceSelector_Source1,	/*!< Selects the data source 1.*/
	SourceSelector_Source2,	/*!< Selects the data source 2.*/
	SourceSelector_All,	/*!< Selects all the data sources.*/
	NUM_SOURCESELECTOR
} spinSourceSelectorEnums;

typedef enum _spinTransferSelectorEnums	/*!< Selects which stream transfers are currently controlled by the selected Transfer features.*/
{
	TransferSelector_Stream0,	/*!< The transfer features control the data stream 0.*/
	TransferSelector_Stream1,	/*!< The transfer features control the data stream 1.*/
	TransferSelector_Stream2,	/*!< The transfer features control the data stream 2.*/
	TransferSelector_All,	/*!< The transfer features control all the data streams simulateneously.*/
	NUM_TRANSFERSELECTOR
} spinTransferSelectorEnums;

typedef enum _spinTransferControlModeEnums	/*!< Selects the control method for the transfers.*/
{
	TransferControlMode_Basic,	/*!< Basic*/
	TransferControlMode_Automatic,	/*!< Automatic*/
	TransferControlMode_UserControlled,	/*!< User Controlled*/
	NUM_TRANSFERCONTROLMODE
} spinTransferControlModeEnums;

typedef enum _spinTransferOperationModeEnums	/*!< Selects the operation mode of the transfer.*/
{
	TransferOperationMode_Continuous,	/*!< Continuous*/
	TransferOperationMode_MultiBlock,	/*!< Multi Block*/
	NUM_TRANSFEROPERATIONMODE
} spinTransferOperationModeEnums;

typedef enum _spinTransferQueueModeEnums	/*!< Specifies the operation mode of the transfer queue.*/
{
	TransferQueueMode_FirstInFirstOut,	/*!< Blocks first In are transferred Out first.*/
	NUM_TRANSFERQUEUEMODE
} spinTransferQueueModeEnums;

typedef enum _spinTransferTriggerSelectorEnums	/*!< Selects the type of transfer trigger to configure.*/
{
	TransferTriggerSelector_TransferStart,	/*!< Selects a trigger to start the transfers.*/
	TransferTriggerSelector_TransferStop,	/*!< Selects a trigger to stop the transfers.*/
	TransferTriggerSelector_TransferAbort,	/*!< Selects a trigger to abort the transfers.*/
	TransferTriggerSelector_TransferPause,	/*!< Selects a trigger to pause the transfers.*/
	TransferTriggerSelector_TransferResume,	/*!< Selects a trigger to Resume the transfers.*/
	TransferTriggerSelector_TransferActive,	/*!< Selects a trigger to Activate the transfers. This trigger type is used when TriggerActivation is set LevelHigh or levelLow.*/
	TransferTriggerSelector_TransferBurstStart,	/*!< Selects a trigger to start the transfer of a burst of frames specified by TransferBurstCount.*/
	TransferTriggerSelector_TransferBurstStop,	/*!< Selects a trigger to end the transfer of a burst of frames.*/
	NUM_TRANSFERTRIGGERSELECTOR
} spinTransferTriggerSelectorEnums;

typedef enum _spinTransferTriggerModeEnums	/*!< Controls if the selected trigger is active.*/
{
	TransferTriggerMode_Off,	/*!< Disables the selected trigger.*/
	TransferTriggerMode_On,	/*!< Enable the selected trigger.*/
	NUM_TRANSFERTRIGGERMODE
} spinTransferTriggerModeEnums;

typedef enum _spinTransferTriggerSourceEnums	/*!< Specifies the signal to use as the trigger source for transfers.*/
{
	TransferTriggerSource_Line0,	/*!< Specifies which physical line (or pin) and associated I/O control block to use as external source for the transfer control trigger signal.*/
	TransferTriggerSource_Line1,	/*!< Specifies which physical line (or pin) and associated I/O control block to use as external source for the transfer control trigger signal.*/
	TransferTriggerSource_Line2,	/*!< Specifies which physical line (or pin) and associated I/O control block to use as external source for the transfer control trigger signal.*/
	TransferTriggerSource_Counter0Start,	/*!< Specifies which of the Counter signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Counter1Start,	/*!< Specifies which of the Counter signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Counter2Start,	/*!< Specifies which of the Counter signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Counter0End,	/*!< Specifies which of the Counter signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Counter1End,	/*!< Specifies which of the Counter signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Counter2End,	/*!< Specifies which of the Counter signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Timer0Start,	/*!< Specifies which Timer signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Timer1Start,	/*!< Specifies which Timer signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Timer2Start,	/*!< Specifies which Timer signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Timer0End,	/*!< Specifies which Timer signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Timer1End,	/*!< Specifies which Timer signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Timer2End,	/*!< Specifies which Timer signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_SoftwareSignal0,	/*!< Specifies which Software Signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_SoftwareSignal1,	/*!< Specifies which Software Signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_SoftwareSignal2,	/*!< Specifies which Software Signal to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Action0,	/*!< Specifies which Action command to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Action1,	/*!< Specifies which Action command to use as internal source for the transfer control trigger signal.*/
	TransferTriggerSource_Action2,	/*!< Specifies which Action command to use as internal source for the transfer control trigger signal.*/
	NUM_TRANSFERTRIGGERSOURCE
} spinTransferTriggerSourceEnums;

typedef enum _spinTransferTriggerActivationEnums	/*!< Specifies the activation mode of the transfer control trigger.*/
{
	TransferTriggerActivation_RisingEdge,	/*!< Specifies that the trigger is considered valid on the rising edge of the source signal.*/
	TransferTriggerActivation_FallingEdge,	/*!< Specifies that the trigger is considered valid on the falling edge of the source signal.*/
	TransferTriggerActivation_AnyEdge,	/*!< Specifies that the trigger is considered valid on the falling or rising edge of the source signal.*/
	TransferTriggerActivation_LevelHigh,	/*!< Specifies that the trigger is considered valid as long as the level of the source signal is high. This can apply to TransferActive and TransferPause trigger.*/
	TransferTriggerActivation_LevelLow,	/*!< Specifies that the trigger is considered valid as long as the level of the source signal is low. This can apply to TransferActive and TransferPause trigger.*/
	NUM_TRANSFERTRIGGERACTIVATION
} spinTransferTriggerActivationEnums;

typedef enum _spinTransferStatusSelectorEnums	/*!< Selects which status of the transfer module to read.*/
{
	TransferStatusSelector_Streaming,	/*!< Data blocks are transmitted when enough data is available.*/
	TransferStatusSelector_Paused,	/*!< Data blocks transmission is suspended immediately.*/
	TransferStatusSelector_Stopping,	/*!< Data blocks transmission is stopping. The current block transmission will be completed and the transfer state will stop.*/
	TransferStatusSelector_Stopped,	/*!< Data blocks transmission is stopped.*/
	TransferStatusSelector_QueueOverflow,	/*!< Data blocks queue is in overflow state.*/
	NUM_TRANSFERSTATUSSELECTOR
} spinTransferStatusSelectorEnums;

typedef enum _spinTransferComponentSelectorEnums	/*!< Selects the color component for the control of the TransferStreamChannel feature.*/
{
	TransferComponentSelector_Red,	/*!< The TransferStreamChannel feature controls the index of the stream channel for the streaming of the red plane of the planar pixel formats.*/
	TransferComponentSelector_Green,	/*!< The TransferStreamChannel feature controls the index of the stream channel for the streaming of the green plane of the planar pixel formats.*/
	TransferComponentSelector_Blue,	/*!< The TransferStreamChannel feature controls the index of the stream channel for the streaming of blue plane of the planar pixel formats.*/
	TransferComponentSelector_All,	/*!< The TransferStreamChannel feature controls the index of the stream channel for the streaming of all the planes of the planar pixel formats simultaneously or non planar pixel formats.*/
	NUM_TRANSFERCOMPONENTSELECTOR
} spinTransferComponentSelectorEnums;

typedef enum _spinScan3dDistanceUnitEnums	/*!< Specifies the unit used when delivering calibrated distance data.*/
{
	Scan3dDistanceUnit_Millimeter,	/*!< Distance values are in millimeter units (default).*/
	Scan3dDistanceUnit_Inch,	/*!< Distance values are in inch units.*/
	NUM_SCAN3DDISTANCEUNIT
} spinScan3dDistanceUnitEnums;

typedef enum _spinScan3dCoordinateSystemEnums	/*!< Specifies the Coordinate system to use for the device.*/
{
	Scan3dCoordinateSystem_Cartesian,	/*!< Default value. 3-axis orthogonal, right-hand X-Y-Z.*/
	Scan3dCoordinateSystem_Spherical,	/*!< A Theta-Phi-Rho coordinate system.*/
	Scan3dCoordinateSystem_Cylindrical,	/*!< A Theta-Y-Rho coordinate system.*/
	NUM_SCAN3DCOORDINATESYSTEM
} spinScan3dCoordinateSystemEnums;

typedef enum _spinScan3dOutputModeEnums	/*!< Controls the Calibration and data organization of the device, naming the coordinates transmitted.*/
{
	Scan3dOutputMode_UncalibratedC,	/*!< Uncalibrated 2.5D Depth map. The distance data does not represent a physical unit and may be non-linear. The data is a 2.5D range map only.*/
	Scan3dOutputMode_CalibratedABC_Grid,	/*!< 3 Coordinates in grid organization. The full 3 coordinate data with the grid array organization from the sensor kept.*/
	Scan3dOutputMode_CalibratedABC_PointCloud,	/*!< 3 Coordinates without organization. The full 3 coordinate data without any organization of data points. Typically only valid points transmitted giving varying image size.*/
	Scan3dOutputMode_CalibratedAC,	/*!< 2 Coordinates with fixed B sampling. The data is sent as a A and C coordinates (X,Z or Theta,Rho). The B (Y) axis uses the scale and offset parameters for the B axis.*/
	Scan3dOutputMode_CalibratedAC_Linescan,	/*!< 2 Coordinates with varying sampling. The data is sent as a A and C coordinates (X,Z or Theta,Rho). The B (Y) axis comes from the encoder chunk value.*/
	Scan3dOutputMode_CalibratedC,	/*!< Calibrated 2.5D Depth map. The distance data is expressed in the chosen distance unit. The data is a 2.5D range map. No information on X-Y axes available.*/
	Scan3dOutputMode_CalibratedC_Linescan,	/*!< Depth Map with varying B sampling. The distance data is expressed in the chosen distance unit. The data is a 2.5D range map. The B (Y) axis comes from the encoder chunk value.*/
	Scan3dOutputMode_RectifiedC,	/*!< Rectified 2.5D Depth map. The distance data has been rectified to a uniform sampling pattern in the X and Y direction. The data is a 2.5D range map only. If a complete 3D point cloud is rectified but transmitted as explicit coordinates it should be transmitted as one of the "CalibratedABC" formats.*/
	Scan3dOutputMode_RectifiedC_Linescan,	/*!< Rectified 2.5D Depth map with varying B sampling. The data is sent as rectified 1D profiles using Coord3D_C pixels. The B (Y) axis comes from the encoder chunk value.*/
	Scan3dOutputMode_DisparityC,	/*!< Disparity 2.5D Depth map. The distance is inversely proportional to the pixel (disparity) value.*/
	Scan3dOutputMode_DisparityC_Linescan,	/*!< Disparity 2.5D Depth map with varying B sampling. The distance is inversely proportional to the pixel (disparity) value. The B (Y) axis comes from the encoder chunk value.*/
	NUM_SCAN3DOUTPUTMODE
} spinScan3dOutputModeEnums;

typedef enum _spinScan3dCoordinateSystemReferenceEnums	/*!< Defines coordinate system reference location.*/
{
	Scan3dCoordinateSystemReference_Anchor,	/*!< Default value. Original fixed reference. The coordinate system fixed relative the camera reference point marker is used.*/
	Scan3dCoordinateSystemReference_Transformed,	/*!< Transformed reference system. The transformed coordinate system is used according to the definition in the rotation and translation matrices.*/
	NUM_SCAN3DCOORDINATESYSTEMREFERENCE
} spinScan3dCoordinateSystemReferenceEnums;

typedef enum _spinScan3dCoordinateSelectorEnums	/*!< Selects the individual coordinates in the vectors for 3D information/transformation.*/
{
	Scan3dCoordinateSelector_CoordinateA,	/*!< The first (X or Theta) coordinate*/
	Scan3dCoordinateSelector_CoordinateB,	/*!< The second (Y or Phi) coordinate*/
	Scan3dCoordinateSelector_CoordinateC,	/*!< The third (Z or Rho) coordinate.*/
	NUM_SCAN3DCOORDINATESELECTOR
} spinScan3dCoordinateSelectorEnums;

typedef enum _spinScan3dCoordinateTransformSelectorEnums	/*!< Sets the index to read/write a coordinate transform value.*/
{
	Scan3dCoordinateTransformSelector_RotationX,	/*!< Rotation around X axis.*/
	Scan3dCoordinateTransformSelector_RotationY,	/*!< Rotation around Y axis.*/
	Scan3dCoordinateTransformSelector_RotationZ,	/*!< Rotation around Z axis.*/
	Scan3dCoordinateTransformSelector_TranslationX,	/*!< Translation along X axis.*/
	Scan3dCoordinateTransformSelector_TranslationY,	/*!< Translation along Y axis.*/
	Scan3dCoordinateTransformSelector_TranslationZ,	/*!< Translation along Z axis.*/
	NUM_SCAN3DCOORDINATETRANSFORMSELECTOR
} spinScan3dCoordinateTransformSelectorEnums;

typedef enum _spinScan3dCoordinateReferenceSelectorEnums	/*!< Sets the index to read a coordinate system reference value defining the transform of a point from the current (Anchor or Transformed) system to the reference system.*/
{
	Scan3dCoordinateReferenceSelector_RotationX,	/*!< Rotation around X axis.*/
	Scan3dCoordinateReferenceSelector_RotationY,	/*!< Rotation around Y axis.*/
	Scan3dCoordinateReferenceSelector_RotationZ,	/*!< Rotation around Z axis.*/
	Scan3dCoordinateReferenceSelector_TranslationX,	/*!< X axis translation.*/
	Scan3dCoordinateReferenceSelector_TranslationY,	/*!< Y axis translation.*/
	Scan3dCoordinateReferenceSelector_TranslationZ,	/*!< Z axis translation.*/
	NUM_SCAN3DCOORDINATEREFERENCESELECTOR
} spinScan3dCoordinateReferenceSelectorEnums;

typedef enum _spinChunkSelectorEnums	/*!< Selects which Chunk to enable or control.*/
{
	ChunkSelector_ImageComponent,	/*!< Image Component*/
	ChunkSelector_Image,	/*!< Image*/
	ChunkSelector_OffsetX,	/*!< Offset X*/
	ChunkSelector_OffsetY,	/*!< Offset Y*/
	ChunkSelector_Width,	/*!< Width*/
	ChunkSelector_Height,	/*!< Height*/
	ChunkSelector_PixelFormat,	/*!< Pixel Format*/
	ChunkSelector_PixelDynamicRangeMax,	/*!< Pixel Dynamic Range Max*/
	ChunkSelector_PixelDynamicRangeMin,	/*!< Pixel Dynamic Range Min*/
	ChunkSelector_Timestamp,	/*!< Timestamp*/
	ChunkSelector_LineStatusAll,	/*!< Line Status All*/
	ChunkSelector_CounterValue,	/*!< Counter Value*/
	ChunkSelector_TimerValue,	/*!< Timer Value*/
	ChunkSelector_EncoderValue,	/*!< Encoder Value*/
	ChunkSelector_ExposureTime,	/*!< Exposure Time*/
	ChunkSelector_Gain,	/*!< Gain*/
	ChunkSelector_BlackLevel,	/*!< Black Level*/
	ChunkSelector_LinePitch,	/*!< Line Pitch*/
	ChunkSelector_FrameID,	/*!< Frame ID*/
	ChunkSelector_SourceID,	/*!< Source ID*/
	ChunkSelector_RegionID,	/*!< Region ID*/
	ChunkSelector_TransferBlockID,	/*!< Transfer Block ID*/
	ChunkSelector_TransferStreamID,	/*!< Transfer Stream ID*/
	ChunkSelector_TransferQueue,	/*!< Transfer Queue*/
	ChunkSelector_CurrentBlockCount,	/*!< Current Block Count*/
	ChunkSelector_StreamChannelID,	/*!< Stream Channel ID*/
	ChunkSelector_Scan3dDistanceUnit,	/*!< Scan 3d Distance Unit*/
	ChunkSelector_Scan3dOutputMode,	/*!< Scan 3d Output Mode*/
	ChunkSelector_Scan3dCoordinateSystem,	/*!< Scan 3d Coordinate System*/
	ChunkSelector_Scan3dCoordinateSystemReference,	/*!< Scan 3d Coordinate System Reference*/
	ChunkSelector_Scan3dCoordinateScale,	/*!< Scan 3d Coordinate Scale*/
	ChunkSelector_Scan3dCoordinateOffset,	/*!< Scan 3d Coordinate Offset*/
	ChunkSelector_Scan3dInvalidDataFlag,	/*!< Scan 3d Invalid Data Flag*/
	ChunkSelector_Scan3dInvalidDataValue,	/*!< Scan 3d Invalid Data Value*/
	ChunkSelector_Scan3dAxisMin,	/*!< Scan 3d Axis Min*/
	ChunkSelector_Scan3dAxisMax,	/*!< Scan 3d Axis Max*/
	ChunkSelector_Scan3dCoordinateTransformValueScan3dCoordinateReferenceValue,	/*!< Scan 3d Coordinate Transform Value Scan 3d Coordinate Reference Value*/
	NUM_CHUNKSELECTOR
} spinChunkSelectorEnums;

typedef enum _spinChunkImageComponentEnums	/*!< Returns the component of the payload image. This can be used to identify the image component of a generic part in a multipart transfer.*/
{
	ChunkImageComponent_Intensity,	/*!< The image data is the intensity component.*/
	ChunkImageComponent_Color,	/*!< The image data is color component.*/
	ChunkImageComponent_Infrared,	/*!< The image data is infrared component.*/
	ChunkImageComponent_Ultraviolet,	/*!< The image data is the ultraviolet component.*/
	ChunkImageComponent_Range,	/*!< The image data is the range (distance) component.*/
	ChunkImageComponent_Disparity,	/*!< The image data is the disparity component.*/
	ChunkImageComponent_Confidence,	/*!< The image data is the confidence map component.*/
	ChunkImageComponent_Scatter,	/*!< The image data is the scatter component.*/
	NUM_CHUNKIMAGECOMPONENT
} spinChunkImageComponentEnums;

typedef enum _spinChunkPixelFormatEnums	/*!< Returns the PixelFormat of the image included in the payload.*/
{
	ChunkPixelFormat_Mono1p,	/*!< Monochrome 1-bit packed*/
	ChunkPixelFormat_Mono2p,	/*!< Monochrome 2-bit packed*/
	ChunkPixelFormat_Mono4p,	/*!< Monochrome 4-bit packed*/
	ChunkPixelFormat_Mono8,	/*!< Monochrome 8-bit*/
	ChunkPixelFormat_Mono8s,	/*!< Monochrome 8-bit signed*/
	ChunkPixelFormat_Mono10,	/*!< Monochrome 10-bit unpacked*/
	ChunkPixelFormat_Mono10p,	/*!< Monochrome 10-bit packed*/
	ChunkPixelFormat_Mono12,	/*!< Monochrome 12-bit unpacked*/
	ChunkPixelFormat_Mono12p,	/*!< Monochrome 12-bit packed*/
	ChunkPixelFormat_Mono14,	/*!< Monochrome 14-bit unpacked*/
	ChunkPixelFormat_Mono16,	/*!< Monochrome 16-bit*/
	ChunkPixelFormat_BayerBG8,	/*!< Bayer Blue-Green 8-bit*/
	ChunkPixelFormat_BayerBG10,	/*!< Bayer Blue-Green 10-bit unpacked*/
	ChunkPixelFormat_BayerBG10p,	/*!< Bayer Blue-Green 10-bit packed*/
	ChunkPixelFormat_BayerBG12,	/*!< Bayer Blue-Green 12-bit unpacked*/
	ChunkPixelFormat_BayerBG12p,	/*!< Bayer Blue-Green 12-bit packed*/
	ChunkPixelFormat_BayerBG16,	/*!< Bayer Blue-Green 16-bit*/
	ChunkPixelFormat_BayerGB8,	/*!< Bayer Green-Blue 8-bit*/
	ChunkPixelFormat_BayerGB10,	/*!< Bayer Green-Blue 10-bit unpacked*/
	ChunkPixelFormat_BayerGB10p,	/*!< Bayer Green-Blue 10-bit packed*/
	ChunkPixelFormat_BayerGB12,	/*!< Bayer Green-Blue 12-bit unpacked*/
	ChunkPixelFormat_BayerGB12p,	/*!< Bayer Green-Blue 12-bit packed*/
	ChunkPixelFormat_BayerGB16,	/*!< Bayer Green-Blue 16-bit*/
	ChunkPixelFormat_BayerGR8,	/*!< Bayer Green-Red 8-bit*/
	ChunkPixelFormat_BayerGR10,	/*!< Bayer Green-Red 10-bit unpacked*/
	ChunkPixelFormat_BayerGR10p,	/*!< Bayer Green-Red 10-bit packed*/
	ChunkPixelFormat_BayerGR12,	/*!< Bayer Green-Red 12-bit unpacked*/
	ChunkPixelFormat_BayerGR12p,	/*!< Bayer Green-Red 12-bit packed*/
	ChunkPixelFormat_BayerGR16,	/*!< Bayer Green-Red 16-bit*/
	ChunkPixelFormat_BayerRG8,	/*!< Bayer Red-Green 8-bit*/
	ChunkPixelFormat_BayerRG10,	/*!< Bayer Red-Green 10-bit unpacked*/
	ChunkPixelFormat_BayerRG10p,	/*!< Bayer Red-Green 10-bit packed*/
	ChunkPixelFormat_BayerRG12,	/*!< Bayer Red-Green 12-bit unpacked*/
	ChunkPixelFormat_BayerRG12p,	/*!< Bayer Red-Green 12-bit packed*/
	ChunkPixelFormat_BayerRG16,	/*!< Bayer Red-Green 16-bit*/
	ChunkPixelFormat_RGBa8,	/*!< Red-Green-Blue-alpha 8-bit*/
	ChunkPixelFormat_RGBa10,	/*!< Red-Green-Blue-alpha 10-bit unpacked*/
	ChunkPixelFormat_RGBa10p,	/*!< Red-Green-Blue-alpha 10-bit packed*/
	ChunkPixelFormat_RGBa12,	/*!< Red-Green-Blue-alpha 12-bit unpacked*/
	ChunkPixelFormat_RGBa12p,	/*!< Red-Green-Blue-alpha 12-bit packed*/
	ChunkPixelFormat_RGBa14,	/*!< Red-Green-Blue-alpha 14-bit unpacked*/
	ChunkPixelFormat_RGBa16,	/*!< Red-Green-Blue-alpha 16-bit*/
	ChunkPixelFormat_RGB8,	/*!< Red-Green-Blue 8-bit*/
	ChunkPixelFormat_RGB8_Planar,	/*!< Red-Green-Blue 8-bit planar*/
	ChunkPixelFormat_RGB10,	/*!< Red-Green-Blue 10-bit unpacked*/
	ChunkPixelFormat_RGB10_Planar,	/*!< Red-Green-Blue 10-bit unpacked planar*/
	ChunkPixelFormat_RGB10p,	/*!< Red-Green-Blue 10-bit packed*/
	ChunkPixelFormat_RGB10p32,	/*!< Red-Green-Blue 10-bit packed into 32-bit*/
	ChunkPixelFormat_RGB12,	/*!< Red-Green-Blue 12-bit unpacked*/
	ChunkPixelFormat_RGB12_Planar,	/*!< Red-Green-Blue 12-bit unpacked planar*/
	ChunkPixelFormat_RGB12p,	/*!< Red-Green-Blue 12-bit packed  */
	ChunkPixelFormat_RGB14,	/*!< Red-Green-Blue 14-bit unpacked*/
	ChunkPixelFormat_RGB16,	/*!< Red-Green-Blue 16-bit  */
	ChunkPixelFormat_RGB16_Planar,	/*!< Red-Green-Blue 16-bit planar*/
	ChunkPixelFormat_RGB565p,	/*!< Red-Green-Blue 5/6/5-bit packed*/
	ChunkPixelFormat_BGRa8,	/*!< Blue-Green-Red-alpha 8-bit*/
	ChunkPixelFormat_BGRa10,	/*!< Blue-Green-Red-alpha 10-bit unpacked*/
	ChunkPixelFormat_BGRa10p,	/*!< Blue-Green-Red-alpha 10-bit packed*/
	ChunkPixelFormat_BGRa12,	/*!< Blue-Green-Red-alpha 12-bit unpacked*/
	ChunkPixelFormat_BGRa12p,	/*!< Blue-Green-Red-alpha 12-bit packed*/
	ChunkPixelFormat_BGRa14,	/*!< Blue-Green-Red-alpha 14-bit unpacked*/
	ChunkPixelFormat_BGRa16,	/*!< Blue-Green-Red-alpha 16-bit*/
	ChunkPixelFormat_BGR8,	/*!< Blue-Green-Red 8-bit*/
	ChunkPixelFormat_BGR10,	/*!< Blue-Green-Red 10-bit unpacked*/
	ChunkPixelFormat_BGR10p,	/*!< Blue-Green-Red 10-bit packed*/
	ChunkPixelFormat_BGR12,	/*!< Blue-Green-Red 12-bit unpacked*/
	ChunkPixelFormat_BGR12p,	/*!< Blue-Green-Red 12-bit packed*/
	ChunkPixelFormat_BGR14,	/*!< Blue-Green-Red 14-bit unpacked*/
	ChunkPixelFormat_BGR16,	/*!< Blue-Green-Red 16-bit*/
	ChunkPixelFormat_BGR565p,	/*!< Blue-Green-Red 5/6/5-bit packed*/
	ChunkPixelFormat_R8,	/*!< Red 8-bit*/
	ChunkPixelFormat_R10,	/*!< Red 10-bit*/
	ChunkPixelFormat_R12,	/*!< Red 12-bit*/
	ChunkPixelFormat_R16,	/*!< Red 16-bit*/
	ChunkPixelFormat_G8,	/*!< Green 8-bit*/
	ChunkPixelFormat_G10,	/*!< Green 10-bit*/
	ChunkPixelFormat_G12,	/*!< Green 12-bit*/
	ChunkPixelFormat_G16,	/*!< Green 16-bit*/
	ChunkPixelFormat_B8,	/*!< Blue 8-bit*/
	ChunkPixelFormat_B10,	/*!< Blue 10-bit*/
	ChunkPixelFormat_B12,	/*!< Blue 12-bit*/
	ChunkPixelFormat_B16,	/*!< Blue 16-bit*/
	ChunkPixelFormat_Coord3D_ABC8,	/*!< 3D coordinate A-B-C 8-bit*/
	ChunkPixelFormat_Coord3D_ABC8_Planar,	/*!< 3D coordinate A-B-C 8-bit planar*/
	ChunkPixelFormat_Coord3D_ABC10p,	/*!< 3D coordinate A-B-C 10-bit packed*/
	ChunkPixelFormat_Coord3D_ABC10p_Planar,	/*!< 3D coordinate A-B-C 10-bit packed planar*/
	ChunkPixelFormat_Coord3D_ABC12p,	/*!< 3D coordinate A-B-C 12-bit packed*/
	ChunkPixelFormat_Coord3D_ABC12p_Planar,	/*!< 3D coordinate A-B-C 12-bit packed planar*/
	ChunkPixelFormat_Coord3D_ABC16,	/*!< 3D coordinate A-B-C 16-bit*/
	ChunkPixelFormat_Coord3D_ABC16_Planar,	/*!< 3D coordinate A-B-C 16-bit planar*/
	ChunkPixelFormat_Coord3D_ABC32f,	/*!< 3D coordinate A-B-C 32-bit floating point*/
	ChunkPixelFormat_Coord3D_ABC32f_Planar,	/*!< 3D coordinate A-B-C 32-bit floating point planar*/
	ChunkPixelFormat_Coord3D_AC8,	/*!< 3D coordinate A-C 8-bit*/
	ChunkPixelFormat_Coord3D_AC8_Planar,	/*!< 3D coordinate A-C 8-bit planar*/
	ChunkPixelFormat_Coord3D_AC10p,	/*!< 3D coordinate A-C 10-bit packed*/
	ChunkPixelFormat_Coord3D_AC10p_Planar,	/*!< 3D coordinate A-C 10-bit packed planar*/
	ChunkPixelFormat_Coord3D_AC12p,	/*!< 3D coordinate A-C 12-bit packed*/
	ChunkPixelFormat_Coord3D_AC12p_Planar,	/*!< 3D coordinate A-C 12-bit packed planar*/
	ChunkPixelFormat_Coord3D_AC16,	/*!< 3D coordinate A-C 16-bit*/
	ChunkPixelFormat_Coord3D_AC16_Planar,	/*!< 3D coordinate A-C 16-bit planar*/
	ChunkPixelFormat_Coord3D_AC32f,	/*!< 3D coordinate A-C 32-bit floating point*/
	ChunkPixelFormat_Coord3D_AC32f_Planar,	/*!< 3D coordinate A-C 32-bit floating point planar*/
	ChunkPixelFormat_Coord3D_A8,	/*!< 3D coordinate A 8-bit*/
	ChunkPixelFormat_Coord3D_A10p,	/*!< 3D coordinate A 10-bit packed*/
	ChunkPixelFormat_Coord3D_A12p,	/*!< 3D coordinate A 12-bit packed*/
	ChunkPixelFormat_Coord3D_A16,	/*!< 3D coordinate A 16-bit*/
	ChunkPixelFormat_Coord3D_A32f,	/*!< 3D coordinate A 32-bit floating point*/
	ChunkPixelFormat_Coord3D_B8,	/*!< 3D coordinate B 8-bit*/
	ChunkPixelFormat_Coord3D_B10p,	/*!< 3D coordinate B 10-bit packed*/
	ChunkPixelFormat_Coord3D_B12p,	/*!< 3D coordinate B 12-bit packed*/
	ChunkPixelFormat_Coord3D_B16,	/*!< 3D coordinate B 16-bit*/
	ChunkPixelFormat_Coord3D_B32f,	/*!< 3D coordinate B 32-bit floating point*/
	ChunkPixelFormat_Coord3D_C8,	/*!< 3D coordinate C 8-bit*/
	ChunkPixelFormat_Coord3D_C10p,	/*!< 3D coordinate C 10-bit packed*/
	ChunkPixelFormat_Coord3D_C12p,	/*!< 3D coordinate C 12-bit packed*/
	ChunkPixelFormat_Coord3D_C16,	/*!< 3D coordinate C 16-bit*/
	ChunkPixelFormat_Coord3D_C32f,	/*!< 3D coordinate C 32-bit floating point*/
	ChunkPixelFormat_Confidence1,	/*!< Confidence 1-bit unpacked*/
	ChunkPixelFormat_Confidence1p,	/*!< Confidence 1-bit packed*/
	ChunkPixelFormat_Confidence8,	/*!< Confidence 8-bit*/
	ChunkPixelFormat_Confidence16,	/*!< Confidence 16-bit*/
	ChunkPixelFormat_Confidence32f,	/*!< Confidence 32-bit floating point*/
	ChunkPixelFormat_BiColorBGRG8,	/*!< Bi-color Blue/Green - Red/Green 8-bit*/
	ChunkPixelFormat_BiColorBGRG10,	/*!< Bi-color Blue/Green - Red/Green 10-bit unpacked*/
	ChunkPixelFormat_BiColorBGRG10p,	/*!< Bi-color Blue/Green - Red/Green 10-bit packed*/
	ChunkPixelFormat_BiColorBGRG12,	/*!< Bi-color Blue/Green - Red/Green 12-bit unpacked*/
	ChunkPixelFormat_BiColorBGRG12p,	/*!< Bi-color Blue/Green - Red/Green 12-bit packed*/
	ChunkPixelFormat_BiColorRGBG8,	/*!< Bi-color Red/Green - Blue/Green 8-bit*/
	ChunkPixelFormat_BiColorRGBG10,	/*!< Bi-color Red/Green - Blue/Green 10-bit unpacked*/
	ChunkPixelFormat_BiColorRGBG10p,	/*!< Bi-color Red/Green - Blue/Green 10-bit packed*/
	ChunkPixelFormat_BiColorRGBG12,	/*!< Bi-color Red/Green - Blue/Green 12-bit unpacked*/
	ChunkPixelFormat_BiColorRGBG12p,	/*!< Bi-color Red/Green - Blue/Green 12-bit packed*/
	ChunkPixelFormat_SCF1WBWG8,	/*!< Sparse Color Filter #1 White-Blue-White-Green 8-bit*/
	ChunkPixelFormat_SCF1WBWG10,	/*!< Sparse Color Filter #1 White-Blue-White-Green 10-bit unpacked*/
	ChunkPixelFormat_SCF1WBWG10p,	/*!< Sparse Color Filter #1 White-Blue-White-Green 10-bit packed*/
	ChunkPixelFormat_SCF1WBWG12,	/*!< Sparse Color Filter #1 White-Blue-White-Green 12-bit unpacked*/
	ChunkPixelFormat_SCF1WBWG12p,	/*!< Sparse Color Filter #1 White-Blue-White-Green 12-bit packed*/
	ChunkPixelFormat_SCF1WBWG14,	/*!< Sparse Color Filter #1 White-Blue-White-Green 14-bit unpacked*/
	ChunkPixelFormat_SCF1WBWG16,	/*!< Sparse Color Filter #1 White-Blue-White-Green 16-bit unpacked*/
	ChunkPixelFormat_SCF1WGWB8,	/*!< Sparse Color Filter #1 White-Green-White-Blue 8-bit*/
	ChunkPixelFormat_SCF1WGWB10,	/*!< Sparse Color Filter #1 White-Green-White-Blue 10-bit unpacked*/
	ChunkPixelFormat_SCF1WGWB10p,	/*!< Sparse Color Filter #1 White-Green-White-Blue 10-bit packed*/
	ChunkPixelFormat_SCF1WGWB12,	/*!< Sparse Color Filter #1 White-Green-White-Blue 12-bit unpacked*/
	ChunkPixelFormat_SCF1WGWB12p,	/*!< Sparse Color Filter #1 White-Green-White-Blue 12-bit packed*/
	ChunkPixelFormat_SCF1WGWB14,	/*!< Sparse Color Filter #1 White-Green-White-Blue 14-bit unpacked*/
	ChunkPixelFormat_SCF1WGWB16,	/*!< Sparse Color Filter #1 White-Green-White-Blue 16-bit*/
	ChunkPixelFormat_SCF1WGWR8,	/*!< Sparse Color Filter #1 White-Green-White-Red 8-bit*/
	ChunkPixelFormat_SCF1WGWR10,	/*!< Sparse Color Filter #1 White-Green-White-Red 10-bit unpacked*/
	ChunkPixelFormat_SCF1WGWR10p,	/*!< Sparse Color Filter #1 White-Green-White-Red 10-bit packed*/
	ChunkPixelFormat_SCF1WGWR12,	/*!< Sparse Color Filter #1 White-Green-White-Red 12-bit unpacked*/
	ChunkPixelFormat_SCF1WGWR12p,	/*!< Sparse Color Filter #1 White-Green-White-Red 12-bit packed*/
	ChunkPixelFormat_SCF1WGWR14,	/*!< Sparse Color Filter #1 White-Green-White-Red 14-bit unpacked*/
	ChunkPixelFormat_SCF1WGWR16,	/*!< Sparse Color Filter #1 White-Green-White-Red 16-bit*/
	ChunkPixelFormat_SCF1WRWG8,	/*!< Sparse Color Filter #1 White-Red-White-Green 8-bit*/
	ChunkPixelFormat_SCF1WRWG10,	/*!< Sparse Color Filter #1 White-Red-White-Green 10-bit unpacked*/
	ChunkPixelFormat_SCF1WRWG10p,	/*!< Sparse Color Filter #1 White-Red-White-Green 10-bit packed*/
	ChunkPixelFormat_SCF1WRWG12,	/*!< Sparse Color Filter #1 White-Red-White-Green 12-bit unpacked*/
	ChunkPixelFormat_SCF1WRWG12p,	/*!< Sparse Color Filter #1 White-Red-White-Green 12-bit packed*/
	ChunkPixelFormat_SCF1WRWG14,	/*!< Sparse Color Filter #1 White-Red-White-Green 14-bit unpacked*/
	ChunkPixelFormat_SCF1WRWG16,	/*!< Sparse Color Filter #1 White-Red-White-Green 16-bit*/
	ChunkPixelFormat_YCbCr8,	/*!< YCbCr 4:4:4 8-bit*/
	ChunkPixelFormat_YCbCr8_CbYCr,	/*!< YCbCr 4:4:4 8-bit*/
	ChunkPixelFormat_YCbCr10_CbYCr,	/*!< YCbCr 4:4:4 10-bit unpacked*/
	ChunkPixelFormat_YCbCr10p_CbYCr,	/*!< YCbCr 4:4:4 10-bit packed*/
	ChunkPixelFormat_YCbCr12_CbYCr,	/*!< YCbCr 4:4:4 12-bit unpacked*/
	ChunkPixelFormat_YCbCr12p_CbYCr,	/*!< YCbCr 4:4:4 12-bit packed*/
	ChunkPixelFormat_YCbCr411_8,	/*!< YCbCr 4:1:1 8-bit*/
	ChunkPixelFormat_YCbCr411_8_CbYYCrYY,	/*!< YCbCr 4:1:1 8-bit*/
	ChunkPixelFormat_YCbCr422_8,	/*!< YCbCr 4:2:2 8-bit*/
	ChunkPixelFormat_YCbCr422_8_CbYCrY,	/*!< YCbCr 4:2:2 8-bit*/
	ChunkPixelFormat_YCbCr422_10,	/*!< YCbCr 4:2:2 10-bit unpacked*/
	ChunkPixelFormat_YCbCr422_10_CbYCrY,	/*!< YCbCr 4:2:2 10-bit unpacked*/
	ChunkPixelFormat_YCbCr422_10p,	/*!< YCbCr 4:2:2 10-bit packed*/
	ChunkPixelFormat_YCbCr422_10p_CbYCrY,	/*!< YCbCr 4:2:2 10-bit packed*/
	ChunkPixelFormat_YCbCr422_12,	/*!< YCbCr 4:2:2 12-bit unpacked*/
	ChunkPixelFormat_YCbCr422_12_CbYCrY,	/*!< YCbCr 4:2:2 12-bit unpacked*/
	ChunkPixelFormat_YCbCr422_12p,	/*!< YCbCr 4:2:2 12-bit packed*/
	ChunkPixelFormat_YCbCr422_12p_CbYCrY,	/*!< YCbCr 4:2:2 12-bit packed*/
	ChunkPixelFormat_YCbCr601_8_CbYCr,	/*!< YCbCr 4:4:4 8-bit BT.601*/
	ChunkPixelFormat_YCbCr601_10_CbYCr,	/*!< YCbCr 4:4:4 10-bit unpacked BT.601*/
	ChunkPixelFormat_YCbCr601_10p_CbYCr,	/*!< YCbCr 4:4:4 10-bit packed BT.601*/
	ChunkPixelFormat_YCbCr601_12_CbYCr,	/*!< YCbCr 4:4:4 12-bit unpacked BT.601*/
	ChunkPixelFormat_YCbCr601_12p_CbYCr,	/*!< YCbCr 4:4:4 12-bit packed BT.601*/
	ChunkPixelFormat_YCbCr601_411_8_CbYYCrYY,	/*!< YCbCr 4:1:1 8-bit BT.601*/
	ChunkPixelFormat_YCbCr601_422_8,	/*!< YCbCr 4:2:2 8-bit BT.601*/
	ChunkPixelFormat_YCbCr601_422_8_CbYCrY,	/*!< YCbCr 4:2:2 8-bit BT.601*/
	ChunkPixelFormat_YCbCr601_422_10,	/*!< YCbCr 4:2:2 10-bit unpacked BT.601*/
	ChunkPixelFormat_YCbCr601_422_10_CbYCrY,	/*!< YCbCr 4:2:2 10-bit unpacked BT.601*/
	ChunkPixelFormat_YCbCr601_422_10p,	/*!< YCbCr 4:2:2 10-bit packed BT.601*/
	ChunkPixelFormat_YCbCr601_422_10p_CbYCrY,	/*!< YCbCr 4:2:2 10-bit packed BT.601*/
	ChunkPixelFormat_YCbCr601_422_12,	/*!< YCbCr 4:2:2 12-bit unpacked BT.601*/
	ChunkPixelFormat_YCbCr601_422_12_CbYCrY,	/*!< YCbCr 4:2:2 12-bit unpacked BT.601*/
	ChunkPixelFormat_YCbCr601_422_12p,	/*!< YCbCr 4:2:2 12-bit packed BT.601*/
	ChunkPixelFormat_YCbCr601_422_12p_CbYCrY,	/*!< YCbCr 4:2:2 12-bit packed BT.601*/
	ChunkPixelFormat_YCbCr709_8_CbYCr,	/*!< YCbCr 4:4:4 8-bit BT.709*/
	ChunkPixelFormat_YCbCr709_10_CbYCr,	/*!< YCbCr 4:4:4 10-bit unpacked BT.709*/
	ChunkPixelFormat_YCbCr709_10p_CbYCr,	/*!< YCbCr 4:4:4 10-bit packed BT.709*/
	ChunkPixelFormat_YCbCr709_12_CbYCr,	/*!< YCbCr 4:4:4 12-bit unpacked BT.709*/
	ChunkPixelFormat_YCbCr709_12p_CbYCr,	/*!< YCbCr 4:4:4 12-bit packed BT.709*/
	ChunkPixelFormat_YCbCr709_411_8_CbYYCrYY,	/*!< YCbCr 4:1:1 8-bit BT.709*/
	ChunkPixelFormat_YCbCr709_422_8,	/*!< YCbCr 4:2:2 8-bit BT.709*/
	ChunkPixelFormat_YCbCr709_422_8_CbYCrY,	/*!< YCbCr 4:2:2 8-bit BT.709*/
	ChunkPixelFormat_YCbCr709_422_10,	/*!< YCbCr 4:2:2 10-bit unpacked BT.709*/
	ChunkPixelFormat_YCbCr709_422_10_CbYCrY,	/*!< YCbCr 4:2:2 10-bit unpacked BT.709*/
	ChunkPixelFormat_YCbCr709_422_10p,	/*!< YCbCr 4:2:2 10-bit packed BT.709*/
	ChunkPixelFormat_YCbCr709_422_10p_CbYCrY,	/*!< YCbCr 4:2:2 10-bit packed BT.709*/
	ChunkPixelFormat_YCbCr709_422_12,	/*!< YCbCr 4:2:2 12-bit unpacked BT.709*/
	ChunkPixelFormat_YCbCr709_422_12_CbYCrY,	/*!< YCbCr 4:2:2 12-bit unpacked BT.709*/
	ChunkPixelFormat_YCbCr709_422_12p,	/*!< YCbCr 4:2:2 12-bit packed BT.709*/
	ChunkPixelFormat_YCbCr709_422_12p_CbYCrY,	/*!< YCbCr 4:2:2 12-bit packed BT.709*/
	ChunkPixelFormat_YUV8_UYV,	/*!< YUV 4:4:4 8-bit*/
	ChunkPixelFormat_YUV411_8_UYYVYY,	/*!< YUV 4:1:1 8-bit*/
	ChunkPixelFormat_YUV422_8,	/*!< YUV 4:2:2 8-bit*/
	ChunkPixelFormat_YUV422_8_UYVY,	/*!< YUV 4:2:2 8-bit*/
	NUM_CHUNKPIXELFORMAT
} spinChunkPixelFormatEnums;

typedef enum _spinChunkCounterSelectorEnums	/*!< Selects which counter to retrieve data from.*/
{
	ChunkCounterSelector_Counter0,	/*!< Selects the counter 0.*/
	ChunkCounterSelector_Counter1,	/*!< Selects the counter 1.*/
	ChunkCounterSelector_Counter2,	/*!< Selects the counter 2.*/
	NUM_CHUNKCOUNTERSELECTOR
} spinChunkCounterSelectorEnums;

typedef enum _spinChunkTimerSelectorEnums	/*!< Selects which Timer to retrieve data from.*/
{
	ChunkTimerSelector_Timer0,	/*!< Selects the first Timer.*/
	ChunkTimerSelector_Timer1,	/*!< Selects the first Timer.*/
	ChunkTimerSelector_Timer2,	/*!< Selects the second Timer.*/
	NUM_CHUNKTIMERSELECTOR
} spinChunkTimerSelectorEnums;

typedef enum _spinChunkEncoderSelectorEnums	/*!< Selects which Encoder to retrieve data from.*/
{
	ChunkEncoderSelector_Encoder0,	/*!< Selects the first Encoder.*/
	ChunkEncoderSelector_Encoder1,	/*!< Selects the first Encoder.*/
	ChunkEncoderSelector_Encoder2,	/*!< Selects the second Encoder.*/
	NUM_CHUNKENCODERSELECTOR
} spinChunkEncoderSelectorEnums;

typedef enum _spinChunkEncoderStatusEnums	/*!< Returns the motion status of the selected encoder.*/
{
	ChunkEncoderStatus_EncoderUp,	/*!< The encoder counter last incremented.*/
	ChunkEncoderStatus_EncoderDown,	/*!< The encoder counter last decremented.*/
	ChunkEncoderStatus_EncoderIdle,	/*!< The encoder is not active.*/
	ChunkEncoderStatus_EncoderStatic,	/*!< No motion within the EncoderTimeout time.*/
	NUM_CHUNKENCODERSTATUS
} spinChunkEncoderStatusEnums;

typedef enum _spinChunkExposureTimeSelectorEnums	/*!< Selects which exposure time is read by the ChunkExposureTime feature.*/
{
	ChunkExposureTimeSelector_Common,	/*!< Selects the common ExposureTime.*/
	ChunkExposureTimeSelector_Red,	/*!< Selects the red common ExposureTime.*/
	ChunkExposureTimeSelector_Green,	/*!< Selects the green ExposureTime.*/
	ChunkExposureTimeSelector_Blue,	/*!< Selects the blue ExposureTime.*/
	ChunkExposureTimeSelector_Cyan,	/*!< Selects the cyan common ExposureTime..*/
	ChunkExposureTimeSelector_Magenta,	/*!< Selects the magenta ExposureTime..*/
	ChunkExposureTimeSelector_Yellow,	/*!< Selects the yellow ExposureTime..*/
	ChunkExposureTimeSelector_Infrared,	/*!< Selects the infrared ExposureTime.*/
	ChunkExposureTimeSelector_Ultraviolet,	/*!< Selects the ultraviolet ExposureTime.*/
	ChunkExposureTimeSelector_Stage1,	/*!< Selects the first stage ExposureTime.*/
	ChunkExposureTimeSelector_Stage2,	/*!< Selects the second stage ExposureTime.*/
	NUM_CHUNKEXPOSURETIMESELECTOR
} spinChunkExposureTimeSelectorEnums;

typedef enum _spinChunkGainSelectorEnums	/*!< Selects which Gain to return.*/
{
	ChunkGainSelector_All,	/*!< Gain will be applied to all channels or taps.*/
	ChunkGainSelector_Red,	/*!< Gain will be applied to the red channel.*/
	ChunkGainSelector_Green,	/*!< Gain will be applied to the green channel.*/
	ChunkGainSelector_Blue,	/*!< Gain will be applied to the blue channel.*/
	ChunkGainSelector_Y,	/*!< Gain will be applied to Y channel.*/
	ChunkGainSelector_U,	/*!< Gain will be applied to U channel.*/
	ChunkGainSelector_V,	/*!< Gain will be applied to V channel.*/
	ChunkGainSelector_Tap1,	/*!< Gain will be applied to Tap 1.*/
	ChunkGainSelector_Tap2,	/*!< Gain will be applied to Tap 2.*/
	ChunkGainSelector_AnalogAll,	/*!< Gain will be applied to all analog channels or taps.*/
	ChunkGainSelector_AnalogRed,	/*!< Gain will be applied to the red analog channel.*/
	ChunkGainSelector_AnalogGreen,	/*!< Gain will be applied to the green analog channel.*/
	ChunkGainSelector_AnalogBlue,	/*!< Gain will be applied to the blue analog channel.*/
	ChunkGainSelector_AnalogY,	/*!< Gain will be applied to Y analog channel.*/
	ChunkGainSelector_AnalogU,	/*!< Gain will be applied to U analog channel.*/
	ChunkGainSelector_AnalogV,	/*!< Gain will be applied to V analog channel.*/
	ChunkGainSelector_AnalogTap1,	/*!< Analog gain will be applied to Tap 1.*/
	ChunkGainSelector_AnalogTap2,	/*!< Analog gain will be applied to Tap 2.*/
	ChunkGainSelector_DigitalAll,	/*!< Gain will be applied to all digital channels or taps.*/
	ChunkGainSelector_DigitalRed,	/*!< Gain will be applied to the red digital channel.*/
	ChunkGainSelector_DigitalGreen,	/*!< Gain will be applied to the green digital channel.*/
	ChunkGainSelector_DigitalBlue,	/*!< Gain will be applied to the blue digital channel.*/
	ChunkGainSelector_DigitalY,	/*!< Gain will be applied to Y digital channel.*/
	ChunkGainSelector_DigitalU,	/*!< Gain will be applied to U digital channel.*/
	ChunkGainSelector_DigitalV,	/*!< Gain will be applied to V digital channel.*/
	ChunkGainSelector_DigitalTap1,	/*!< Digital gain will be applied to Tap 1.*/
	ChunkGainSelector_DigitalTap2,	/*!< Digital gain will be applied to Tap 2.*/
	NUM_CHUNKGAINSELECTOR
} spinChunkGainSelectorEnums;

typedef enum _spinChunkBlackLevelSelectorEnums	/*!< Selects which Black Level to return. Possible values are:*/
{
	ChunkBlackLevelSelector_All,	/*!< Black Level will be applied to all channels or taps.*/
	ChunkBlackLevelSelector_Red,	/*!< Black Level will be applied to the red channel.*/
	ChunkBlackLevelSelector_Green,	/*!< Black Level will be applied to the green channel.*/
	ChunkBlackLevelSelector_Blue,	/*!< Black Level will be applied to the blue channel.*/
	ChunkBlackLevelSelector_Y,	/*!< Black Level will be applied to Y channel.*/
	ChunkBlackLevelSelector_U,	/*!< Black Level will be applied to U channel.*/
	ChunkBlackLevelSelector_V,	/*!< Black Level will be applied to V channel.*/
	ChunkBlackLevelSelector_Tap1,	/*!< Black Level will be applied to Tap 1.*/
	ChunkBlackLevelSelector_Tap2,	/*!< Black Level will be applied to Tap 2.*/
	NUM_CHUNKBLACKLEVELSELECTOR
} spinChunkBlackLevelSelectorEnums;

typedef enum _spinChunkSourceIDEnums	/*!< Returns the identifier of Source that the image comes from.*/
{
	ChunkSourceID_Source0,	/*!< Image comes from the Source 0.*/
	ChunkSourceID_Source1,	/*!< Image comes from the Source 1.*/
	ChunkSourceID_Source2,	/*!< Image comes from the Source 2.*/
	NUM_CHUNKSOURCEID
} spinChunkSourceIDEnums;

typedef enum _spinChunkRegionIDEnums	/*!< Returns the identifier of Region that the image comes from.*/
{
	ChunkRegionID_Region0,	/*!< Image comes from the Region 0.*/
	ChunkRegionID_Region1,	/*!< Image comes from the Region 1.*/
	ChunkRegionID_Region2,	/*!< Image comes from the Region 2.*/
	NUM_CHUNKREGIONID
} spinChunkRegionIDEnums;

typedef enum _spinChunkTransferStreamIDEnums	/*!< Returns identifier of the stream that generated this block.*/
{
	ChunkTransferStreamID_Stream0,	/*!< Data comes from Stream0.*/
	ChunkTransferStreamID_Stream1,	/*!< Data comes from Stream1.*/
	ChunkTransferStreamID_Stream2,	/*!< Data comes from Stream2.*/
	ChunkTransferStreamID_Stream3,	/*!< Data comes from Stream3.*/
	NUM_CHUNKTRANSFERSTREAMID
} spinChunkTransferStreamIDEnums;

typedef enum _spinChunkScan3dDistanceUnitEnums	/*!< Returns the Distance Unit of the payload image.*/
{
	ChunkScan3dDistanceUnit_Millimeter,	/*!< Default value. Distance values are in millimeter units.*/
	ChunkScan3dDistanceUnit_Inch,	/*!< Distance values are in inch units.*/
	NUM_CHUNKSCAN3DDISTANCEUNIT
} spinChunkScan3dDistanceUnitEnums;

typedef enum _spinChunkScan3dOutputModeEnums	/*!< Returns the Calibrated Mode of the payload image.*/
{
	ChunkScan3dOutputMode_UncalibratedC,	/*!< Uncalibrated 2.5D Depth map. The distance data does not represent a physical unit and may be non-linear. The data is a 2.5D range map only.*/
	ChunkScan3dOutputMode_CalibratedABC_Grid,	/*!< 3 Coordinates in grid organization. The full 3 coordinate data with the grid array organization from the sensor kept.*/
	ChunkScan3dOutputMode_CalibratedABC_PointCloud,	/*!< 3 Coordinates without organization. The full 3 coordinate data without any organization of data points. Typically only valid points transmitted giving varying image size.*/
	ChunkScan3dOutputMode_CalibratedAC,	/*!< 2 Coordinates with fixed B sampling. The data is sent as a A and C coordinates (X,Z or Theta,Rho). The B (Y) axis uses the scale and offset parameters for the B axis.*/
	ChunkScan3dOutputMode_CalibratedAC_Linescan,	/*!< 2 Coordinates with varying sampling. The data is sent as a A and C coordinates (X,Z or Theta,Rho). The B (Y) axis comes from the encoder chunk value.*/
	ChunkScan3dOutputMode_CalibratedC,	/*!< Calibrated 2.5D Depth map. The distance data is expressed in the chosen distance unit. The data is a 2.5D range map. No information on X-Y axes available.*/
	ChunkScan3dOutputMode_CalibratedC_Linescan,	/*!< Depth Map with varying B sampling. The distance data is expressed in the chosen distance unit. The data is a 2.5D range map. The B (Y) axis comes from the encoder chunk value.*/
	ChunkScan3dOutputMode_RectifiedC,	/*!< Rectified 2.5D Depth map. The distance data has been rectified to a uniform sampling pattern in the X and Y direction. The data is a 2.5D range map only. If a complete 3D point cloud is rectified but transmitted as explicit coordinates it should be transmitted as one of the "CalibratedABC" formats.*/
	ChunkScan3dOutputMode_RectifiedC_Linescan,	/*!< Rectified 2.5D Depth map with varying B sampling. The data is sent as rectified 1D profiles using Coord3D_C pixels. The B (Y) axis comes from the encoder chunk value.*/
	ChunkScan3dOutputMode_DisparityC,	/*!< Disparity 2.5D Depth map. The distance is inversely proportional to the pixel (disparity) value.*/
	ChunkScan3dOutputMode_DisparityC_Linescan,	/*!< Disparity 2.5D Depth map with varying B sampling. The distance is inversely proportional to the pixel (disparity) value. The B (Y) axis comes from the encoder chunk value.*/
	NUM_CHUNKSCAN3DOUTPUTMODE
} spinChunkScan3dOutputModeEnums;

typedef enum _spinChunkScan3dCoordinateSystemEnums	/*!< Returns the Coordinate System of the image included in the payload.*/
{
	ChunkScan3dCoordinateSystem_Cartesian,	/*!< Default value. 3-axis orthogonal, right-hand X-Y-Z.*/
	ChunkScan3dCoordinateSystem_Spherical,	/*!< A Theta-Phi-Rho coordinate system.*/
	ChunkScan3dCoordinateSystem_Cylindrical,	/*!< A Theta-Y-Rho coordinate system.*/
	NUM_CHUNKSCAN3DCOORDINATESYSTEM
} spinChunkScan3dCoordinateSystemEnums;

typedef enum _spinChunkScan3dCoordinateSystemReferenceEnums	/*!< Returns the Coordinate System Position of the image included in the payload.*/
{
	ChunkScan3dCoordinateSystemReference_Anchor,	/*!< Default value. Original fixed reference. The coordinate system fixed relative the camera reference point marker is used.*/
	ChunkScan3dCoordinateSystemReference_Transformed,	/*!< Transformed reference system. The transformed coordinate system is used according to the definition in the rotation and translation matrices.*/
	NUM_CHUNKSCAN3DCOORDINATESYSTEMREFERENCE
} spinChunkScan3dCoordinateSystemReferenceEnums;

typedef enum _spinChunkScan3dCoordinateSelectorEnums	/*!< Selects which Coordinate to retrieve data from.*/
{
	ChunkScan3dCoordinateSelector_CoordinateA,	/*!< The first (X or Theta) coordinate*/
	ChunkScan3dCoordinateSelector_CoordinateB,	/*!< The second (Y or Phi) coordinate*/
	ChunkScan3dCoordinateSelector_CoordinateC,	/*!< The third (Z or Rho) coordinate.*/
	NUM_CHUNKSCAN3DCOORDINATESELECTOR
} spinChunkScan3dCoordinateSelectorEnums;

typedef enum _spinChunkScan3dCoordinateTransformSelectorEnums	/*!< Selector for transform values.*/
{
	ChunkScan3dCoordinateTransformSelector_RotationX,	/*!< Rotation around X axis.*/
	ChunkScan3dCoordinateTransformSelector_RotationY,	/*!< Rotation around Y axis.*/
	ChunkScan3dCoordinateTransformSelector_RotationZ,	/*!< Rotation around Z axis.*/
	ChunkScan3dCoordinateTransformSelector_TranslationX,	/*!< Translation along X axis.*/
	ChunkScan3dCoordinateTransformSelector_TranslationY,	/*!< Translation along Y axis.*/
	ChunkScan3dCoordinateTransformSelector_TranslationZ,	/*!< Translation along Z axis.*/
	NUM_CHUNKSCAN3DCOORDINATETRANSFORMSELECTOR
} spinChunkScan3dCoordinateTransformSelectorEnums;

typedef enum _spinChunkScan3dCoordinateReferenceSelectorEnums	/*!< Selector to read a coordinate system reference value defining the transform of a point from one system to the other.*/
{
	ChunkScan3dCoordinateReferenceSelector_RotationX,	/*!< Rotation around X axis.*/
	ChunkScan3dCoordinateReferenceSelector_RotationY,	/*!< Rotation around Y axis.*/
	ChunkScan3dCoordinateReferenceSelector_RotationZ,	/*!< Rotation around Z axis.*/
	ChunkScan3dCoordinateReferenceSelector_TranslationX,	/*!< X axis translation.*/
	ChunkScan3dCoordinateReferenceSelector_TranslationY,	/*!< Y axis translation.*/
	ChunkScan3dCoordinateReferenceSelector_TranslationZ,	/*!< Z axis translation.*/
	NUM_CHUNKSCAN3DCOORDINATEREFERENCESELECTOR
} spinChunkScan3dCoordinateReferenceSelectorEnums;

typedef enum _spinDeviceTapGeometryEnums	/*!< This device tap geometry feature describes the geometrical properties characterizing the taps of a camera as presented at the output of the device.*/
{
	DeviceTapGeometry_Geometry_1X_1Y,	/*!< Geometry_1X_1Y*/
	DeviceTapGeometry_Geometry_1X2_1Y,	/*!< Geometry_1X2_1Y*/
	DeviceTapGeometry_Geometry_1X2_1Y2,	/*!< Geometry_1X2_1Y2*/
	DeviceTapGeometry_Geometry_2X_1Y,	/*!< Geometry_2X_1Y*/
	DeviceTapGeometry_Geometry_2X_1Y2Geometry_2XE_1Y,	/*!< Geometry_2X_1Y2Geometry_2XE_1Y*/
	DeviceTapGeometry_Geometry_2XE_1Y2,	/*!< Geometry_2XE_1Y2*/
	DeviceTapGeometry_Geometry_2XM_1Y,	/*!< Geometry_2XM_1Y*/
	DeviceTapGeometry_Geometry_2XM_1Y2,	/*!< Geometry_2XM_1Y2*/
	DeviceTapGeometry_Geometry_1X_1Y2,	/*!< Geometry_1X_1Y2*/
	DeviceTapGeometry_Geometry_1X_2YE,	/*!< Geometry_1X_2YE*/
	DeviceTapGeometry_Geometry_1X3_1Y,	/*!< Geometry_1X3_1Y*/
	DeviceTapGeometry_Geometry_3X_1Y,	/*!< Geometry_3X_1Y*/
	DeviceTapGeometry_Geometry_1X,	/*!< Geometry_1X*/
	DeviceTapGeometry_Geometry_1X2,	/*!< Geometry_1X2*/
	DeviceTapGeometry_Geometry_2X,	/*!< Geometry_2X*/
	DeviceTapGeometry_Geometry_2XE,	/*!< Geometry_2XE*/
	DeviceTapGeometry_Geometry_2XM,	/*!< Geometry_2XM*/
	DeviceTapGeometry_Geometry_1X3,	/*!< Geometry_1X3*/
	DeviceTapGeometry_Geometry_3X,	/*!< Geometry_3X*/
	DeviceTapGeometry_Geometry_1X4_1Y,	/*!< Geometry_1X4_1Y*/
	DeviceTapGeometry_Geometry_4X_1Y,	/*!< Geometry_4X_1Y*/
	DeviceTapGeometry_Geometry_2X2_1Y,	/*!< Geometry_2X2_1Y*/
	DeviceTapGeometry_Geometry_2X2E_1YGeometry_2X2M_1Y,	/*!< Geometry_2X2E_1YGeometry_2X2M_1Y*/
	DeviceTapGeometry_Geometry_1X2_2YE,	/*!< Geometry_1X2_2YE*/
	DeviceTapGeometry_Geometry_2X_2YE,	/*!< Geometry_2X_2YE*/
	DeviceTapGeometry_Geometry_2XE_2YE,	/*!< Geometry_2XE_2YE*/
	DeviceTapGeometry_Geometry_2XM_2YE,	/*!< Geometry_2XM_2YE*/
	DeviceTapGeometry_Geometry_1X4,	/*!< Geometry_1X4*/
	DeviceTapGeometry_Geometry_4X,	/*!< Geometry_4X*/
	DeviceTapGeometry_Geometry_2X2,	/*!< Geometry_2X2*/
	DeviceTapGeometry_Geometry_2X2E,	/*!< Geometry_2X2E*/
	DeviceTapGeometry_Geometry_2X2M,	/*!< Geometry_2X2M*/
	DeviceTapGeometry_Geometry_1X8_1Y,	/*!< Geometry_1X8_1Y*/
	DeviceTapGeometry_Geometry_8X_1Y,	/*!< Geometry_8X_1Y*/
	DeviceTapGeometry_Geometry_4X2_1Y,	/*!< Geometry_4X2_1Y*/
	DeviceTapGeometry_Geometry_2X2E_2YE,	/*!< Geometry_2X2E_2YE*/
	DeviceTapGeometry_Geometry_1X8,	/*!< Geometry_1X8*/
	DeviceTapGeometry_Geometry_8X,	/*!< Geometry_8X*/
	DeviceTapGeometry_Geometry_4X2,	/*!< Geometry_4X2*/
	DeviceTapGeometry_Geometry_4X2E,	/*!< Geometry_4X2E*/
	DeviceTapGeometry_Geometry_4X2E_1Y,	/*!< Geometry_4X2E_1Y*/
	DeviceTapGeometry_Geometry_1X10_1Y,	/*!< Geometry_1X10_1Y*/
	DeviceTapGeometry_Geometry_10X_1Y,	/*!< Geometry_10X_1Y*/
	DeviceTapGeometry_Geometry_1X10,	/*!< Geometry_1X10*/
	DeviceTapGeometry_Geometry_10X,	/*!< Geometry_10X*/
	NUM_DEVICETAPGEOMETRY
} spinDeviceTapGeometryEnums;

typedef enum _spinGevPhysicalLinkConfigurationEnums	/*!< Controls the principal physical link configuration to use on next restart/power-up of the device.*/
{
	GevPhysicalLinkConfiguration_SingleLink,	/*!< Single Link*/
	GevPhysicalLinkConfiguration_MultiLink,	/*!< Multi Link*/
	GevPhysicalLinkConfiguration_StaticLAG,	/*!< Static LAG*/
	GevPhysicalLinkConfiguration_DynamicLAG,	/*!< Dynamic LAG*/
	NUM_GEVPHYSICALLINKCONFIGURATION
} spinGevPhysicalLinkConfigurationEnums;

typedef enum _spinGevCurrentPhysicalLinkConfigurationEnums	/*!< Indicates the current physical link configuration of the device.*/
{
	GevCurrentPhysicalLinkConfiguration_SingleLink,	/*!< Single Link*/
	GevCurrentPhysicalLinkConfiguration_MultiLink,	/*!< Multi Link*/
	GevCurrentPhysicalLinkConfiguration_StaticLAG,	/*!< Static LAG*/
	GevCurrentPhysicalLinkConfiguration_DynamicLAG,	/*!< Dynamic LAG*/
	NUM_GEVCURRENTPHYSICALLINKCONFIGURATION
} spinGevCurrentPhysicalLinkConfigurationEnums;

typedef enum _spinGevSupportedOptionSelectorEnums	/*!< Selects the GEV option to interrogate for existing support.*/
{
	GevSupportedOptionSelector_SingleLink,	/*!< Single Link*/
	GevSupportedOptionSelector_MultiLink,	/*!< Multi Link*/
	GevSupportedOptionSelector_StaticLAG,	/*!< Static LAG*/
	GevSupportedOptionSelector_DynamicLAG,	/*!< Dynamic LAG*/
	GevSupportedOptionSelector_PAUSEFrameReception,	/*!< PAUSE Frame Reception*/
	GevSupportedOptionSelector_PAUSEFrameGeneration,	/*!< PAUSE Frame Generation*/
	GevSupportedOptionSelector_IPConfigurationLLA,	/*!< IP Configuration LLA*/
	GevSupportedOptionSelector_IPConfigurationDHCP,	/*!< IP Configuration DHCP*/
	GevSupportedOptionSelector_IPConfigurationPersistentIP,	/*!< IP Configuration Persistent IP*/
	GevSupportedOptionSelector_StreamChannelSourceSocket,	/*!< Stream Channel Source Socket*/
	GevSupportedOptionSelector_StandardIDMode,	/*!< Standard ID Mode*/
	GevSupportedOptionSelector_MessageChannelSourceSocket,	/*!< Message Channel Source Socket*/
	GevSupportedOptionSelector_CommandsConcatenation,	/*!< Commands Concatenation*/
	GevSupportedOptionSelector_WriteMem,	/*!< Write Mem*/
	GevSupportedOptionSelector_PacketResend,	/*!< Packet Resend*/
	GevSupportedOptionSelector_Event,	/*!< Event*/
	GevSupportedOptionSelector_EventData,	/*!< Event Data*/
	GevSupportedOptionSelector_PendingAck,	/*!< Pending Ack*/
	GevSupportedOptionSelector_IEEE1588,	/*!< IEEE 1588*/
	GevSupportedOptionSelector_Action,	/*!< Action*/
	GevSupportedOptionSelector_UnconditionalAction,	/*!< Unconditional Action*/
	GevSupportedOptionSelector_ScheduledAction,	/*!< Scheduled Action*/
	GevSupportedOptionSelector_PrimaryApplicationSwitchover,	/*!< Primary Application Switchover*/
	GevSupportedOptionSelector_ExtendedStatusCodes,	/*!< Extended Status Codes*/
	GevSupportedOptionSelector_ExtendedStatusCodesVersion2_0,	/*!< Extended Status Codes Version 2 0*/
	GevSupportedOptionSelector_DiscoveryAckDelay,	/*!< Discovery Ack Delay*/
	GevSupportedOptionSelector_DiscoveryAckDelayWritable,	/*!< Discovery Ack Delay Writable*/
	GevSupportedOptionSelector_TestData,	/*!< Test Data*/
	GevSupportedOptionSelector_ManifestTable,	/*!< Manifest Table*/
	GevSupportedOptionSelector_CCPApplicationSocket,	/*!< CCP Application Socket*/
	GevSupportedOptionSelector_LinkSpeed,	/*!< Link Speed*/
	GevSupportedOptionSelector_HeartbeatDisable,	/*!< Heartbeat Disable*/
	GevSupportedOptionSelector_SerialNumber,	/*!< Serial Number*/
	GevSupportedOptionSelector_UserDefinedName,	/*!< User Defined Name*/
	GevSupportedOptionSelector_StreamChannel0BigAndLittleEndian,	/*!< Stream Channel 0 Big And Little Endian*/
	GevSupportedOptionSelector_StreamChannel0IPReassembly,	/*!< Stream Channel 0 IP Reassembly*/
	GevSupportedOptionSelector_StreamChannel0MultiZone,	/*!< Stream Channel 0 Multi Zone*/
	GevSupportedOptionSelector_StreamChannel0PacketResendDestination,	/*!< Stream Channel 0 Packet Resend Destination*/
	GevSupportedOptionSelector_StreamChannel0AllInTransmission,	/*!< Stream Channel 0 All In Transmission*/
	GevSupportedOptionSelector_StreamChannel0UnconditionalStreaming,	/*!< Stream Channel 0 Unconditional Streaming*/
	GevSupportedOptionSelector_StreamChannel0ExtendedChunkData,	/*!< Stream Channel 0 Extended Chunk Data*/
	GevSupportedOptionSelector_StreamChannel1BigAndLittleEndian,	/*!< Stream Channel 1 Big And Little Endian*/
	GevSupportedOptionSelector_StreamChannel1IPReassembly,	/*!< Stream Channel 1 IP Reassembly*/
	GevSupportedOptionSelector_StreamChannel1MultiZone,	/*!< Stream Channel 1 Multi Zone*/
	GevSupportedOptionSelector_StreamChannel1PacketResendDestination,	/*!< Stream Channel 1 Packet Resend Destination*/
	GevSupportedOptionSelector_StreamChannel1AllInTransmission,	/*!< Stream Channel 1 All In Transmission*/
	GevSupportedOptionSelector_StreamChannel1UnconditionalStreaming,	/*!< Stream Channel 1 Unconditional Streaming*/
	GevSupportedOptionSelector_StreamChannel1ExtendedChunkData,	/*!< Stream Channel 1 Extended Chunk Data*/
	GevSupportedOptionSelector_StreamChannel2BigAndLittleEndian,	/*!< Stream Channel 2 Big And Little Endian*/
	GevSupportedOptionSelector_StreamChannel2IPReassembly,	/*!< Stream Channel 2 IP Reassembly*/
	GevSupportedOptionSelector_StreamChannel2MultiZone,	/*!< Stream Channel 2 Multi Zone*/
	GevSupportedOptionSelector_StreamChannel2PacketResendDestination,	/*!< Stream Channel 2 Packet Resend Destination*/
	GevSupportedOptionSelector_StreamChannel2AllInTransmission,	/*!< Stream Channel 2 All In Transmission*/
	GevSupportedOptionSelector_StreamChannel2UnconditionalStreaming,	/*!< Stream Channel 2 Unconditional Streaming*/
	GevSupportedOptionSelector_StreamChannel2ExtendedChunkData,	/*!< Stream Channel 2 Extended Chunk Data*/
	NUM_GEVSUPPORTEDOPTIONSELECTOR
} spinGevSupportedOptionSelectorEnums;

typedef enum _spinGevIPConfigurationStatusEnums	/*!< Reports the current IP configuration status.*/
{
	GevIPConfigurationStatus_None,	/*!< None*/
	GevIPConfigurationStatus_PersistentIP,	/*!< Persistent IP*/
	GevIPConfigurationStatus_DHCP,	/*!< DHCP*/
	GevIPConfigurationStatus_LLA,	/*!< LLA*/
	GevIPConfigurationStatus_ForceIP,	/*!< Force IP*/
	NUM_GEVIPCONFIGURATIONSTATUS
} spinGevIPConfigurationStatusEnums;

typedef enum _spinGevIEEE1588ClockAccuracyEnums	/*!< Indicates the expected accuracy of the device clock when it is the grandmaster, or in the event it becomes the grandmaster.*/
{
	GevIEEE1588ClockAccuracy_Within25ns,	/*!< Within 25ns*/
	GevIEEE1588ClockAccuracy_Within100ns,	/*!< Within 100ns*/
	GevIEEE1588ClockAccuracy_Within250ns,	/*!< Within 250ns*/
	GevIEEE1588ClockAccuracy_Within1us,	/*!< Within 1us*/
	GevIEEE1588ClockAccuracy_Within2p5u,	/*!< Within 2p 5u*/
	GevIEEE1588ClockAccuracy_Within10us,	/*!< Within 10us*/
	GevIEEE1588ClockAccuracy_Within25us,	/*!< Within 25us*/
	GevIEEE1588ClockAccuracy_Within100us,	/*!< Within 100us*/
	GevIEEE1588ClockAccuracy_Within250us,	/*!< Within 250us*/
	GevIEEE1588ClockAccuracy_Within1ms,	/*!< Within 1ms*/
	GevIEEE1588ClockAccuracy_Within2p5ms,	/*!< Within 2p 5ms*/
	GevIEEE1588ClockAccuracy_Within10ms,	/*!< Within 10ms*/
	GevIEEE1588ClockAccuracy_Within25ms,	/*!< Within 25ms*/
	GevIEEE1588ClockAccuracy_Within100ms,	/*!< Within 100ms*/
	GevIEEE1588ClockAccuracy_Within250ms,	/*!< Within 250ms*/
	GevIEEE1588ClockAccuracy_Within1s,	/*!< Within 1s*/
	GevIEEE1588ClockAccuracy_Within10s,	/*!< Within 10s*/
	GevIEEE1588ClockAccuracy_GreaterThan10s,	/*!< Greater Than 10s*/
	GevIEEE1588ClockAccuracy_AlternatePTPProfile,	/*!< Alternate PTP Profile*/
	GevIEEE1588ClockAccuracy_Unknown,	/*!< Unknown*/
	GevIEEE1588ClockAccuracy_Reserved,	/*!< Reserved*/
	NUM_GEVIEEE1588CLOCKACCURACY
} spinGevIEEE1588ClockAccuracyEnums;

typedef enum _spinGevIEEE1588StatusEnums	/*!< Provides the status of the IEEE 1588 clock.*/
{
	GevIEEE1588Status_Initializing,	/*!< Initializing*/
	GevIEEE1588Status_Faulty,	/*!< Faulty*/
	GevIEEE1588Status_Disabled,	/*!< Disabled*/
	GevIEEE1588Status_Listening,	/*!< Listening*/
	GevIEEE1588Status_PreMaster,	/*!< Pre Master*/
	GevIEEE1588Status_Master,	/*!< Master*/
	GevIEEE1588Status_Passive,	/*!< Passive*/
	GevIEEE1588Status_Uncalibrated,	/*!< Uncalibrated*/
	GevIEEE1588Status_Slave,	/*!< Slave*/
	NUM_GEVIEEE1588STATUS
} spinGevIEEE1588StatusEnums;

typedef enum _spinGevGVCPExtendedStatusCodesSelectorEnums	/*!< Selects the GigE Vision version to control extended status codes for.*/
{
	GevGVCPExtendedStatusCodesSelector_Version1_1,	/*!< Version 1 1*/
	GevGVCPExtendedStatusCodesSelector_Version2_0,	/*!< Version 2 0*/
	NUM_GEVGVCPEXTENDEDSTATUSCODESSELECTOR
} spinGevGVCPExtendedStatusCodesSelectorEnums;

typedef enum _spinGevGVSPExtendedIDModeEnums	/*!< Enables the extended IDs mode.*/
{
	GevGVSPExtendedIDMode_Off,	/*!< Off*/
	GevGVSPExtendedIDMode_On,	/*!< On*/
	NUM_GEVGVSPEXTENDEDIDMODE
} spinGevGVSPExtendedIDModeEnums;

typedef enum _spinGevCCPEnums	/*!< Controls the device access privilege of an application.*/
{
	GevCCP_OpenAccess,	/*!< Open Access*/
	GevCCP_ExclusiveAccess,	/*!< Exclusive Access*/
	GevCCP_ControlAccess,	/*!< Control Access*/
	GevCCP_ControlAccessSwitchoverActive,	/*!< Control Access Switchover Active*/
	NUM_GEVCCP
} spinGevCCPEnums;

typedef enum _spinClConfigurationEnums	/*!< This Camera Link specific feature describes the configuration used by the camera. It helps especially when a camera is capable of operation in a non-standard configuration, and when the features PixelSize, SensorDigitizationTaps, and DeviceTapGeometry do not provide enough information for interpretation of the image data provided by the camera.*/
{
	ClConfiguration_Base,	/*!< Standard base configuration described by the Camera Link standard.*/
	ClConfiguration_Medium,	/*!< Standard medium configuration described by the Camera Link standard.*/
	ClConfiguration_Full,	/*!< Standard full configuration described by the Camera Link standard.*/
	ClConfiguration_DualBase,	/*!< The camera streams the data from multiple taps (that do not fit in the standard base configuration) through two Camera Link base ports. It is responsibility of the application or frame grabber to reconstruct the full image. Only one of the ports (fixed) serves as the "master" for serial communication and triggering.*/
	ClConfiguration_EightyBit,	/*!< Standard 80-bit configuration with 10 taps of 8 bits or 8 taps of 10 bits, as described by the Camera Link standard.*/
	NUM_CLCONFIGURATION
} spinClConfigurationEnums;

typedef enum _spinClTimeSlotsCountEnums	/*!< This Camera Link specific feature describes the time multiplexing of the camera link connection to transfer more than the configuration allows, in one single clock.*/
{
	ClTimeSlotsCount_One,	/*!< One*/
	ClTimeSlotsCount_Two,	/*!< Two*/
	ClTimeSlotsCount_Three,	/*!< Three*/
	NUM_CLTIMESLOTSCOUNT
} spinClTimeSlotsCountEnums;

typedef enum _spinCxpLinkConfigurationStatusEnums	/*!< This feature indicates the current and active Link configuration used by the Device.*/
{
	CxpLinkConfigurationStatus_None,	/*!< The Link configuration of the Device is unknown. Either the configuration operation has failed or there is nothing connected.*/
	CxpLinkConfigurationStatus_Pending,	/*!< The Device is in the process of configuring the Link. The Link cannot be used yet.*/
	CxpLinkConfigurationStatus_CXP1_X1,	/*!< 1 Connection operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfigurationStatus_CXP2_X1,	/*!< 1 Connection operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfigurationStatus_CXP3_X1,	/*!< 1 Connection operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfigurationStatus_CXP5_X1,	/*!< 1 Connection operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfigurationStatus_CXP6_X1,	/*!< 1 Connection operating at CXP-6 speed (6.25 Gbps).*/
	CxpLinkConfigurationStatus_CXP1_X2,	/*!< 2 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfigurationStatus_CXP2_X2,	/*!< 2 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfigurationStatus_CXP3_X2,	/*!< 2 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfigurationStatus_CXP5_X2,	/*!< 2 Connections operating at CXP-4 speed (5.00 Gbps).*/
	CxpLinkConfigurationStatus_CXP6_X2,	/*!< 3 Connections operating at CXP-5 speed (6.25 Gbps).*/
	CxpLinkConfigurationStatus_CXP1_X3,	/*!< 3 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfigurationStatus_CXP2_X3,	/*!< 3 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfigurationStatus_CXP3_X3,	/*!< 3 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfigurationStatus_CXP5_X3,	/*!< 3 Connections operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfigurationStatus_CXP6_X3,	/*!< 3 Connections operating at CXP-6 speed (6.25 Gbps).*/
	CxpLinkConfigurationStatus_CXP1_X4,	/*!< 4 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfigurationStatus_CXP2_X4,	/*!< 4 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfigurationStatus_CXP3_X4,	/*!< 4 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfigurationStatus_CXP5_X4,	/*!< 4 Connections operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfigurationStatus_CXP6_X4,	/*!< 4 Connections operating at CXP-6 speed (6.25 Gbps).*/
	CxpLinkConfigurationStatus_CXP1_X5,	/*!< 5 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfigurationStatus_CXP2_X5,	/*!< 5 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfigurationStatus_CXP3_X5,	/*!< 5 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfigurationStatus_CXP5_X5,	/*!< 5 Connections operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfigurationStatus_CXP6_X5,	/*!< 5 Connections operating at CXP-6 speed (6.25 Gbps).*/
	CxpLinkConfigurationStatus_CXP1_X6,	/*!< 6 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfigurationStatus_CXP2_X6,	/*!< 6 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfigurationStatus_CXP3_X6,	/*!< 6 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfigurationStatus_CXP5_X6,	/*!< 6 Connections operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfigurationStatus_CXP6_X6,	/*!< 6 Connections operating at CXP-6 speed (6.25 Gbps).*/
	NUM_CXPLINKCONFIGURATIONSTATUS
} spinCxpLinkConfigurationStatusEnums;

typedef enum _spinCxpLinkConfigurationPreferredEnums	/*!< Provides the Link configuration that allows the Transmitter Device to operate in its default mode.*/
{
	CxpLinkConfigurationPreferred_CXP1_X1,	/*!< 1 Connection operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfigurationPreferred_CXP2_X1,	/*!< 1 Connection operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfigurationPreferred_CXP3_X1,	/*!< 1 Connection operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfigurationPreferred_CXP5_X1,	/*!< 1 Connection operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfigurationPreferred_CXP6_X1,	/*!< 1 Connection operating at CXP-6 speed (6.25 Gbps).*/
	CxpLinkConfigurationPreferred_CXP1_X2,	/*!< 2 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfigurationPreferred_CXP2_X2,	/*!< 2 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfigurationPreferred_CXP3_X2,	/*!< 2 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfigurationPreferred_CXP5_X2,	/*!< 2 Connections operating at CXP-4 speed (5.00 Gbps).*/
	CxpLinkConfigurationPreferred_CXP6_X2,	/*!< 3 Connections operating at CXP-5 speed (6.25 Gbps).*/
	CxpLinkConfigurationPreferred_CXP1_X3,	/*!< 3 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfigurationPreferred_CXP2_X3,	/*!< 3 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfigurationPreferred_CXP3_X3,	/*!< 3 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfigurationPreferred_CXP5_X3,	/*!< 3 Connections operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfigurationPreferred_CXP6_X3,	/*!< 3 Connections operating at CXP-6 speed (6.25 Gbps).*/
	CxpLinkConfigurationPreferred_CXP1_X4,	/*!< 4 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfigurationPreferred_CXP2_X4,	/*!< 4 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfigurationPreferred_CXP3_X4,	/*!< 4 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfigurationPreferred_CXP5_X4,	/*!< 4 Connections operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfigurationPreferred_CXP6_X4,	/*!< 4 Connections operating at CXP-6 speed (6.25 Gbps).*/
	CxpLinkConfigurationPreferred_CXP1_X5,	/*!< 5 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfigurationPreferred_CXP2_X5,	/*!< 5 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfigurationPreferred_CXP3_X5,	/*!< 5 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfigurationPreferred_CXP5_X5,	/*!< 5 Connections operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfigurationPreferred_CXP6_X5,	/*!< 5 Connections operating at CXP-6 speed (6.25 Gbps).*/
	CxpLinkConfigurationPreferred_CXP1_X6,	/*!< 6 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfigurationPreferred_CXP2_X6,	/*!< 6 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfigurationPreferred_CXP3_X6,	/*!< 6 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfigurationPreferred_CXP5_X6,	/*!< 6 Connections operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfigurationPreferred_CXP6_X6,	/*!< 6 Connections operating at CXP-6 speed (6.25 Gbps).*/
	NUM_CXPLINKCONFIGURATIONPREFERRED
} spinCxpLinkConfigurationPreferredEnums;

typedef enum _spinCxpLinkConfigurationEnums	/*!< This feature allows specifying the Link configuration for the communication between the Receiver and Transmitter Device. In most cases this feature does not need to be written because automatic discovery will set configuration correctly to the value returned by CxpLinkConfigurationPreferred. Note that the currently active configuration of the Link can be read using CxpLinkConfigurationStatus.*/
{
	CxpLinkConfiguration_Auto,	/*!< Sets Automatic discovery for the Link Configuration.*/
	CxpLinkConfiguration_CXP1_X1,	/*!< Force the Link to 1 Connection operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfiguration_CXP2_X1,	/*!< Force the Link to 1 Connection operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfiguration_CXP3_X1,	/*!< Force the Link to 1 Connection operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfiguration_CXP5_X1,	/*!< Force the Link to 1 Connection operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfiguration_CXP6_X1,	/*!< Force the Link to 1 Connection operating at CXP-6 speed (6.25 Gbps).*/
	CxpLinkConfiguration_CXP1_X2,	/*!< Force the Link to 2 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfiguration_CXP2_X2,	/*!< Force the Link to 2 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfiguration_CXP3_X2,	/*!< Force the Link to 2 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfiguration_CXP5_X2,	/*!< Force the Link to 2 Connections operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfiguration_CXP6_X2,	/*!< Force the Link to 3 Connections operating at CXP-6 speed (6.25 Gbps).*/
	CxpLinkConfiguration_CXP1_X3,	/*!< Force the Link to 3 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfiguration_CXP2_X3,	/*!< Force the Link to 3 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfiguration_CXP3_X3,	/*!< Force the Link to 3 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfiguration_CXP5_X3,	/*!< Force the Link to 3 Connections operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfiguration_CXP6_X3,	/*!< Force the Link to 3 Connections operating at CXP-6 speed (6.25 Gbps).*/
	CxpLinkConfiguration_CXP1_X4,	/*!< Force the Link to 4 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfiguration_CXP2_X4,	/*!< Force the Link to 4 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfiguration_CXP3_X4,	/*!< Force the Link to 4 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfiguration_CXP5_X4,	/*!< Force the Link to 4 Connections operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfiguration_CXP6_X4,	/*!< Force the Link to 4 Connections operating at CXP-6 speed (6.25 Gbps).*/
	CxpLinkConfiguration_CXP1_X5,	/*!< Force the Link to 5 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfiguration_CXP2_X5,	/*!< Force the Link to 5 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfiguration_CXP3_X5,	/*!< Force the Link to 5 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfiguration_CXP5_X5,	/*!< Force the Link to 5 Connections operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfiguration_CXP6_X5,	/*!< Force the Link to 5 Connections operating at CXP-6 speed (6.25 Gbps).*/
	CxpLinkConfiguration_CXP1_X6,	/*!< Force the Link to 6 Connections operating at CXP-1 speed (1.25 Gbps).*/
	CxpLinkConfiguration_CXP2_X6,	/*!< Force the Link to 6 Connections operating at CXP-2 speed (2.50 Gbps).*/
	CxpLinkConfiguration_CXP3_X6,	/*!< Force the Link to 6 Connections operating at CXP-3 speed (3.125 Gbps).*/
	CxpLinkConfiguration_CXP5_X6,	/*!< Force the Link to 6 Connections operating at CXP-5 speed (5.00 Gbps).*/
	CxpLinkConfiguration_CXP6_X6,	/*!< Force the Link to 6 Connections operating at CXP-6 speed (6.25 Gbps).*/
	NUM_CXPLINKCONFIGURATION
} spinCxpLinkConfigurationEnums;

typedef enum _spinCxpConnectionTestModeEnums	/*!< Enables the test mode for an individual physical connection of the Device.*/
{
	CxpConnectionTestMode_Off,	/*!< Off*/
	CxpConnectionTestMode_Mode1,	/*!< Mode 1*/
	NUM_CXPCONNECTIONTESTMODE
} spinCxpConnectionTestModeEnums;

typedef enum _spinCxpPoCxpStatusEnums	/*!< Returns the Power over CoaXPress (PoCXP) status of the Device.*/
{
	CxpPoCxpStatus_Auto,	/*!< Normal automatic PoCXP operation.*/
	CxpPoCxpStatus_Off,	/*!< PoCXP is forced off.*/
	CxpPoCxpStatus_Tripped,	/*!< The Link has shut down because of an over-current trip.*/
	NUM_CXPPOCXPSTATUS
} spinCxpPoCxpStatusEnums;

/*@}*/

/*@}*/

#endif // PGR_SPINNAKER_CAMERA_DEFS_C_H