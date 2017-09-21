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
\brief   Definition of ICommand interface
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_ICOMMAND_H
#define SPINNAKER_GENAPI_ICOMMAND_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "IValue.h"

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{
	namespace GenApi
	{
		//*************************************************************
		// ICommand interface
		//*************************************************************

		//! Interface for command like  properties
		//! \ingroup Spinnaker_GenApi_PublicInterface
		interface SPINNAKER_API_ABSTRACT ICommand : virtual public IValue
		{
		public:

			//! Execute the command
			/*!
			\param Verify Enables AccessMode and Range verification (default = true)
			*/
			virtual void Execute(bool Verify = true) = 0;

			//! Execute the command
			virtual void operator()() = 0;

			//! Query whether the command is executed
			/*!
			\param Verify Enables Range verification (default = false). The AccessMode is always checked
			\return True if the Execute command has finished; false otherwise
			*/
			virtual bool IsDone(bool Verify = true) = 0;


		};

	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_ICOMMAND_H
