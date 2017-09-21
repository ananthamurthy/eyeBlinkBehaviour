//=============================================================================
// Copyright © 2016 Point Grey Research, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of Point
// Grey Research, Inc. ("Confidential Information").  You shall not
// disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with Point Grey Research, Inc. (PGR).
//
// PGR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. PGR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
/*!
\file
\brief   Definition of PortRecorder
\ingroup Spinnaker_GenApi_PublicInterface
*/

#ifndef SPINNAKER_GENAPI_PORTRECORDER_H
#define SPINNAKER_GENAPI_PORTRECORDER_H

#include "SpinnakerPlatform.h"
#include "Types.h"

#include "IPortRecorder.h"
#include "PortNode.h"
#include "PortReplay.h"
#include "PortWriteList.h"

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{
	namespace GenApi
	{
		/**
		\brief Interface for recording write commands on a port
		\ingroup Spinnaker_GenApi_PublicInterface
		*/
		class SPINNAKER_API PortRecorder : virtual public IPortRecorder, virtual public PortReplay
		{
		public:
			PortRecorder();

			virtual ~PortRecorder();

			//! starts logging all WriteRegister commands to a list
			virtual void StartRecording(IPortWriteList *pPortRecorder);

			//! stops recording
			virtual void StopRecording();
			
			//! Get the access mode of the node
			virtual EAccessMode GetAccessMode() const;

			//! overload SetReference for Value
			virtual void SetReference(IPort* pBase );

		private:
			void* m_pPortRecorder;
		};

		//! Reference to an IPortRecorder pointer
		//! \ingroup Spinnaker_GenApi_PublicImpl
		typedef PortRecorder CPortRecorderRef;
	}
}

#pragma warning ( pop )

#endif // ifndef SPINNAKER_GENAPI_IPORTRECORDER_H
