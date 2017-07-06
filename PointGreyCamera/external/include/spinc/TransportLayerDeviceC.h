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
/* Generated Fri Aug 19 10:27:35 2016 */

#include "QuickSpinC.h"

#ifndef PGR_SPINNAKERC_TLDEVICE_H
#define PGR_SPINNAKERC_TLDEVICE_H

/**	
* @defgroup TLDeviceC_h TLDevice Structures
* @ingroup CQuickSpin
*/
/*@{*/

typedef struct _quickSpinTLDevice
{
	quickSpinStringNode DeviceID;
	quickSpinStringNode DeviceSerialNumber;
	quickSpinStringNode DeviceVendorName;
	quickSpinStringNode DeviceModelName;
	quickSpinEnumerationNode DeviceType;
	quickSpinStringNode DeviceDisplayName;
	quickSpinEnumerationNode DeviceAccessStatus;
	quickSpinEnumerationNode GUIXMLLocation;
	quickSpinStringNode GUIXMLPath;
	quickSpinEnumerationNode GenICamXMLLocation;
	quickSpinStringNode GenICamXMLPath;
	quickSpinEnumerationNode GevCCP;
	quickSpinIntegerNode GevDeviceIPAddress;
	quickSpinIntegerNode GevDeviceSubnetMask;
	quickSpinIntegerNode GevDeviceMACAddress;
	quickSpinIntegerNode GevDeviceGateway;
	quickSpinIntegerNode DeviceLinkSpeed;
	quickSpinStringNode DeviceVersion;
	quickSpinStringNode DeviceDriverVersion;
	quickSpinStringNode DeviceUserID;
	quickSpinIntegerNode GevVersionMajor;
	quickSpinIntegerNode GevVersionMinor;
	quickSpinBooleanNode GevDeviceModeIsBigEndian;
	quickSpinIntegerNode GevDeviceReadAndWriteTimeout;
	quickSpinIntegerNode GevDeviceMaximumRetryCount;
	quickSpinBooleanNode DeviceMulticastMonitorMode;
	quickSpinEnumerationNode DeviceEndianessMechanism;
	quickSpinStringNode DeviceInstanceId;
	quickSpinEnumerationNode DeviceCurrentSpeed;
} quickSpinTLDevice;

/*@}*/

#endif // PGR_SPINNAKERC_TLDEVICE_H