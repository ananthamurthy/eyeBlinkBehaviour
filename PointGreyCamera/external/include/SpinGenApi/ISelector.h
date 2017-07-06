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

#ifndef SPINNAKER_GENAPI_ISELECTOR_H
#define SPINNAKER_GENAPI_ISELECTOR_H

#if defined (_MSC_VER) && (_MSC_VER > 1200)
#pragma once
#endif // _MSC_VER > 1200

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "Container.h"

#pragma warning ( push )
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{

	namespace GenApi
	{
		/**
		\brief Interface for groups of features selected by a single one
		\ingroup Spinnaker_GenApi_PublicImpl
		*/
		interface SPINNAKER_API_ABSTRACT ISelector : virtual public IBase
		{
			//! true if this feature selects a group of features
			virtual bool IsSelector() const = 0;

			//! retrieve the group of selected features
			virtual void GetSelectedFeatures(FeatureList_t&) const = 0;

			//! retrieve the group of features selecting this node
			virtual void GetSelectingFeatures(FeatureList_t&) const = 0;
		};
	}

}

#pragma warning ( pop )


#endif // SPINNAKER_GENAPI_ISELECTOR_H
