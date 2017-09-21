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

#ifndef PGR_SPINNAKER_H
#define PGR_SPINNAKER_H

/**
*  @defgroup SpinnakerHeaders Spinnaker Headers
*/

/*@{*/

/**
 *  @defgroup Spinnaker_h Spinnaker.h
 *
 *  Global header file for Spinnaker.
 *
 *  By including this file, all required header files for full Spinnaker
 *  operation will be included automatically. It is recommended that this file
 *  be used instead of manually including individual header files.
 *
 *  We welcome your bug reports, suggestions, and comments:
 *  http://www.ptgrey.com/support/contact-us
 */

/*@{*/

/**
 * SpinnakerPlatform Include
 */
#include "SpinnakerPlatform.h"

/**
 * Spinnaker Definitions Include
 */
#include "SpinnakerDefs.h"

/** 
*  Spinnaker GenICam Wrapper Includes
*/
#include "SpinGenApi/GCBase.h"

#include "SpinGenApi/SpinnakerGenApi.h"

/**
 * Spinnaker Class Includes
 */
#include "System.h"
#include "SystemPtr.h"
#include "Exception.h"
#include "Interface.h"
#include "InterfaceList.h"
#include "InterfacePtr.h"
#include "CameraBase.h"
#include "CameraList.h"
#include "Camera.h"
#include "CameraPtr.h"
#include "Image.h"
#include "ImagePtr.h"
#include "ImageStatistics.h"

/**
 * Spinnaker Event Class Includes
 */
#include "Event.h"
#include "InterfaceEvent.h"
#include "ArrivalEvent.h"
#include "RemovalEvent.h"
#include "DeviceEvent.h"
#include "ImageEvent.h"
#include "LoggingEvent.h"
#include "LoggingEventDataPtr.h"

/*@}*/

/*@}*/

#endif // PGR_SPINNAKER_H