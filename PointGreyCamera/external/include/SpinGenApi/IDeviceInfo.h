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
/*!
\file
\brief   Definition of interface INodeMap
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_DEVICEINFO_H
#define SPINNAKER_GENAPI_DEVICEINFO_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "GCString.h"
#include "GCTypes.h"

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{
	namespace GenApi
	{

		//*************************************************************
		// IDeviceInfo interface
		//*************************************************************

		/**
		\brief Interface to get information about the device (= nodemap)
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		interface SPINNAKER_API_ABSTRACT IDeviceInfo
		{
			//! Get the model name
			virtual GenICam::gcstring GetModelName() = 0;

			//! Get the vendor name
			virtual GenICam::gcstring GetVendorName() = 0;

			//! Get tool tip
			virtual GenICam::gcstring GetToolTip() = 0;

			//! Get the standard name space
			virtual GenICam::gcstring GetStandardNameSpace() = 0;

			//! Get the version of the DLL's GenApi implementation
			virtual void GetGenApiVersion(GenICam::Version_t &Version, uint16_t &Build) = 0;

			//! Get the schema version number
			virtual void GetSchemaVersion(GenICam::Version_t &Version) = 0;

			//! Get the version of the device description file
			virtual void GetDeviceVersion(GenICam::Version_t &Version) = 0;

			//! Get the Guid describing the product
			virtual GenICam::gcstring GetProductGuid() = 0;

			//! Get the Guid describing the product version
			virtual GenICam::gcstring GetVersionGuid() = 0;
		};
	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_IDEVICEINFO_H
