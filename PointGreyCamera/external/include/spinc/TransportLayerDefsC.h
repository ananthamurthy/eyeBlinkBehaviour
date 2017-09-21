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
/* Generated Fri Aug 19 10:27:30 2016 */

#ifndef PGR_SPINNAKERC_TRANSPORTLAYERDEFSC_H
#define PGR_SPINNAKERC_TRANSPORTLAYERDEFSC_H

/**
* @defgroup CQuickSpin Spinnaker C QuickSpin API
*/
/*@{*/

/**	
* @defgroup TransportLayerDefsC_h Transport Layer Enumerations
*/
/*@{*/

/**
*@brief The enumeration definitions for transport layer nodes.
*/

typedef enum _spinTLStreamTypeEnums	/*!< Stream type of the device.*/
{
	StreamType_Mixed,/*!< Stream Type - Mixed*/
	StreamType_Custom,/*!< Stream Type - Custom*/
	StreamType_GEV,/*!< Stream Type - GEV*/
	StreamType_CL,/*!< Stream Type - CL*/
	StreamType_IIDC,/*!< Stream Type - IIDC*/
	StreamType_UVC,/*!< Stream Type - UVC*/
	StreamType_CXP,/*!< Stream Type - CXP*/
	StreamType_CLHS,/*!< Stream Type - CLHS*/
	StreamType_U3V,/*!< Stream Type - U3V*/
	StreamType_ETHERNET,/*!< Stream Type - ETHERNET*/
	StreamType_PCI,/*!< Stream Type - PCI*/
	NUMSTREAMTYPE
} spinTLStreamTypeEnums;

typedef enum _spinTLStreamDefaultBufferCountModeEnums	/*!< Controls the number of buffers used for the stream.*/
{
	StreamDefaultBufferCountMode_Manual,/*!< Controls the number of buffers used for the stream.*/
	StreamDefaultBufferCountMode_Auto,/*!< The number of buffers used for the stream is automatically calculated based on the device bandwidth.*/
	NUMSTREAMDEFAULTBUFFERCOUNTMODE
} spinTLStreamDefaultBufferCountModeEnums;

typedef enum _spinTLStreamBufferHandlingModeEnums	/*!< Available buffer handling modes of this data stream:*/
{
	StreamBufferHandlingMode_OldestFirst,/*!< The application always gets the buffer from the head of the output buffer queue (thus, the oldest available one). If the output buffer queue is empty, the application waits for a newly acquired buffer until the timeout expires.*/
	StreamBufferHandlingMode_OldestFirstOverwrite,/*!< The application always gets the buffer from the head of the output buffer queue (thus, the oldest available one). If the output buffer queue is empty, the application waits for a newly acquired buffer until the timeout expires. If a new buffer arrives it will overwrite the existing buffer from the head of the queue (behaves like a circular buffer).*/
	StreamBufferHandlingMode_NewestFirst,/*!< The application always gets the buffer from the tail of the output buffer queue (thus, the newest available one). If the output buffer queue is empty, the application waits for a newly acquired buffer until the timeout expires.*/
	StreamBufferHandlingMode_NewestFirstOverwrite,/*!< The application always gets the buffer from the tail of the output buffer queue (thus, the newest available one). If the output buffer queue is empty, the application waits for a newly acquired buffer until the timeout expires. If a new buffer arrives it will overwrite the existing buffer from the tail of the queue.*/
	NUMSTREAMBUFFERHANDLINGMODE
} spinTLStreamBufferHandlingModeEnums;

typedef enum _spinTLDeviceTypeEnums	/*!< Transport layer type of the device.*/
{
	DeviceType_Mixed,/*!< TL - Mixed*/
	DeviceType_Custom,/*!< TL - Custom*/
	DeviceType_GEV,/*!< TL - GEV*/
	DeviceType_CL,/*!< TL - CL*/
	DeviceType_IIDC,/*!< TL - IIDC*/
	DeviceType_UVC,/*!< TL - UVC*/
	DeviceType_CXP,/*!< TL - CXP*/
	DeviceType_CLHS,/*!< TL - CLHS*/
	DeviceType_U3V,/*!< TL - U3V*/
	DeviceType_ETHERNET,/*!< TL - ETHERNET*/
	DeviceType_PCI,/*!< TL - PCI*/
	NUMDEVICETYPE
} spinTLDeviceTypeEnums;

typedef enum _spinTLDeviceAccessStatusEnums	/*!< Gets the access status the transport layer Producer has on the device.*/
{
	DeviceAccessStatus_Unknown,/*!< Unknown status*/
	DeviceAccessStatus_ReadWrite,/*!< Full access*/
	DeviceAccessStatus_ReadOnly,/*!< Read-only access*/
	DeviceAccessStatus_NoAccess,/*!< Non-available devices*/
	NUMDEVICEACCESSSTATUS
} spinTLDeviceAccessStatusEnums;

typedef enum _spinTLGUIXMLLocationEnums	/*!< Sets the location to load GUI XML.*/
{
	GUIXMLLocation_Device,/*!< Load XML from device*/
	GUIXMLLocation_Host,/*!< Load XML from host*/
	NUMGUIXMLLOCATION
} spinTLGUIXMLLocationEnums;

typedef enum _spinTLGenICamXMLLocationEnums	/*!< Sets the location to load GenICam XML.*/
{
	GenICamXMLLocation_Device,/*!< Load GenICam XML from device*/
	GenICamXMLLocation_Host,/*!< Load GenICam XML from host*/
	NUMGENICAMXMLLOCATION
} spinTLGenICamXMLLocationEnums;

typedef enum _spinTLGevCCPEnums	/*!< Controls the device access privilege of an application.*/
{
	GevCCP_EnumEntry_GevCCP_OpenAccess,/*!< Open access privilege.*/
	GevCCP_EnumEntry_GevCCP_ExclusiveAccess,/*!< Exclusive access privilege.*/
	GevCCP_EnumEntry_GevCCP_ControlAccess,/*!< Control access privilege.*/
	NUMGEVCCP
} spinTLGevCCPEnums;

typedef enum _spinTLDeviceEndianessMechanismEnums	/*!< Identifies the endianness handling mode.*/
{
	DeviceEndianessMechanism_Legacy,/*!< Handling the device endianness according to GenICam Schema 1.0*/
	DeviceEndianessMechanism_Standard,/*!< Handling the device endianness according to GenICam Schema 1.1 and later*/
	NUMDEVICEENDIANESSMECHANISM
} spinTLDeviceEndianessMechanismEnums;

typedef enum _spinTLDeviceCurrentSpeedEnums	/*!< The USB Speed that the device is currently operating at.*/
{
	DeviceCurrentSpeed_UnknownSpeed,/*!< Unknown-Speed.*/
	DeviceCurrentSpeed_LowSpeed,/*!< Low-Speed.*/
	DeviceCurrentSpeed_FullSpeed,/*!< Full-Speed.*/
	DeviceCurrentSpeed_HighSpeed,/*!< High-Speed.*/
	DeviceCurrentSpeed_SuperSpeed,/*!< Super-Speed.*/
	NUMDEVICECURRENTSPEED
} spinTLDeviceCurrentSpeedEnums;

typedef enum _spinTLPOEStatusEnums	/*!< Reports and controls the interface's power over Ethernet status.*/
{
	POEStatus_NotSupported,/*!< Not Supported*/
	POEStatus_PowerOff,/*!< Power is Off*/
	POEStatus_PowerOn,/*!< Power is On*/
	NUMPOESTATUS
} spinTLPOEStatusEnums;

/*@}*/

/*@}*/

#endif // PGR_SPINNAKER_TRANSPORTLAYERDEFSC_H