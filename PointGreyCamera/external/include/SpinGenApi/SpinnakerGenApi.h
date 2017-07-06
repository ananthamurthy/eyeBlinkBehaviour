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

#ifndef SPINNAKER_GENAPI_H
#define SPINNAKER_GENAPI_H

#include "Node.h"
#include "NodeMap.h"
#include "NodeCallback.h"
#include "Types.h"
#include "Synch.h"
#include "ValueNode.h"
#include "EnumClasses.h"
#include "EnumNode.h"
#include "EnumEntryNode.h"
#include "EnumNodeT.h"
#include "IntegerNode.h"
#include "FloatNode.h"
#include "StringNode.h"
#include "BooleanNode.h"
#include "CategoryNode.h"
#include "CommandNode.h"
#include "RegisterNode.h"
#include "ChunkAdapter.h"
#include "ChunkAdapterGeneric.h"
#include "ChunkAdapterDcam.h"
#include "ChunkAdapterU3V.h"
#include "ChunkAdapterGEV.h"
#include "ChunkPort.h"
#include "EventAdapter.h"
#include "EventAdapterGeneric.h"
#include "EventAdapter1394.h"
#include "EventAdapterU3V.h"
#include "EventAdapterGEV.h"
#include "EventPort.h"
#include "IntRegNode.h"
#include "StringRegNode.h"
#include "Synch.h"
#include "FloatRegNode.h"
#include "Pointer.h"
#include "PortWriteList.h"
#include "PortNode.h"
#include "Persistence.h"
#include "GCString.h"
#include "GCStringVector.h"
#include "GCTypes.h"

#pragma warning( push )
#pragma warning( disable: 4244 ) // conversion from 'std::streamsize' to 'size_t'
#include "Filestream.h"
#pragma warning( pop )

#include "IPort.h"
#include "IDeviceInfo.h"
//GenApi Warnings
#pragma warning ( disable : 4068 ) // unknown pragma; refers to BullsEyeCoverage
#pragma warning ( disable : 4251 ) // XXX needs to have dll-interface to be used by clients of class YYY
#pragma warning( disable: 4702 ) // unreachable code in <list>,...
#pragma warning( disable: 4275 ) // non dll-interface structXXX used as base
#pragma warning( disable: 4312 ) // 'type cast' : conversion from 'uintptr_t' to 'void *' of greater size

#endif // SPINNAKER_GENAPI_H