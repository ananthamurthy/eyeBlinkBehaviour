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

#ifndef PGR_LOGGINGEVENTDATA_H
#define PGR_LOGGINGEVENTDATA_H

#include "Spinnaker.h"

namespace Spinnaker
{
	/**
	*  @defgroup SpinnakerEventClasses Spinnaker Event Classes
	*/

	/*@{*/

	/**
	*  @defgroup LoggingEventData_h Logging Event Class
	*/

	/*@{*/

    /**
    * @brief The LoggingEventData object.
    */

	class SPINNAKER_API LoggingEventData
	{
	public:
			/**
			* Default Destructor
			*/
			~LoggingEventData();

			/**
			* Gets the logging event category name.
			*
			* @return The category name
			*/
			const char* GetCategoryName();

			/**
			* Gets the logging event message.
			*
			* @return The log message
			*/
			const char* GetLogMessage();

			/**
			* Gets the logging event's Nested Diagnostic Context (NDC).
			*
			* @return The log event's NDC
			*/
			const char* GetNDC();

			/**
			* Gets the logging event priority.
			*
			* @return The log priority
			*/
			const int	GetPriority();

			/**
			* Gets the logging event thread name.
			*
			* @return The thread name
			*/
			const char* GetThreadName();

			/**
			* Gets the logging event time stamp.
			*
			* @return The time stamp of the log
			*/
			const char* GetTimestamp();

			/**
			* Gets the logging event priority name.
			*
			* @return The priority name of the log
			*/
			const char* GetPriorityName();
	protected:
		friend class SystemImpl;

		/**
		* Default Constructor
		*/
		LoggingEventData(void* data);
		

		private:
			struct LoggingEventDataInternal; // Forward declaration

			LoggingEventDataInternal* m_pLoggingEventData;
	};

	/*@}*/

	/*@}*/
}

#endif // PGR_LoggingEventData_H