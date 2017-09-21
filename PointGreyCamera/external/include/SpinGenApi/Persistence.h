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
\brief   Definition of interface IPersistScript and class CFeatureBag
\ingroup Spinnaker_GenApi_PublicUtilities
*/

#ifndef SPINNAKER_GENAPI_PERSISTENCE_H
#define SPINNAKER_GENAPI_PERSISTENCE_H

#include "Types.h"
#include "Pointer.h"
#include "ISelectorDigit.h"
#include "GCString.h"
#include "GCStringVector.h"
#include <list>
#include <iostream>

namespace Spinnaker
{

	namespace GenApi
	{

		//! Basic interface to persist values to
		interface SPINNAKER_API_ABSTRACT IPersistScript
		{
			//! sets information about the node map
			virtual void SetInfo(GenICam::gcstring &Info) = 0;

			//! Stores a feature
			virtual void PersistFeature(IValue& item) = 0;
		};

		//! Bag holding streamable features of a nodetree
		class SPINNAKER_API CFeatureBag : public IPersistScript
		{
		public:
			CFeatureBag();
			virtual ~CFeatureBag();

			//! sets information about the node map
			virtual void SetInfo(GenICam::gcstring &Info);

			//! Stores a feature
			virtual void PersistFeature(IValue& item);

			//! Loads the features from the bag to the node tree
			//! \param pNodeMap  The node map
			//! \param Verify If true, all streamable features are read back
			//! \param pErrorList If an error occurs during loading the error message is stored in the list and the loading continues
			/*! For Verify=true the list of names in the feature bag is replayed again.
				If a node is a selector it's value is set to the value from the feature bag
				If not the value is read from the camera and compared with the value from the feature bag.
			*/
			bool LoadFromBag(INodeMap *pNodeMap, bool Verify = true, GenICam::gcstring_vector *pErrorList = NULL);

			/*! \brief Stores the streamable nodes to this feature bag
				\param pNodeMap The node map to persist
				\param MaxNumPersistSkriptEntries The max number of entries in the container; -1 means unlimited
				\return number of entries in the bag
			*/
			int64_t StoreToBag(INodeMap *pNodeMap, const int MaxNumPersistSkriptEntries = -1 );

			//! compares the content of two feature bags
			bool operator==(const CFeatureBag &FeatureBag) const;

			friend SPINNAKER_API std::istream& EatComments(std::istream &is);

			//! fills the bag from a stream
			friend SPINNAKER_API std::istream& operator >>(std::istream &is, CFeatureBag &FeatureBag);

			//! puts the bag into a stream
			friend SPINNAKER_API std::ostream& operator <<(std::ostream &os, const CFeatureBag &FeatureBag);

			void* GetFeatureBagHandle();

		private:
			
			void* m_featureBag;
		};
	}
}

#endif //SPINNAKER_GENAPI_PERSISTENCE_H
