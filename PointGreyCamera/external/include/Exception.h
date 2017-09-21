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

#ifndef PGR_SPINNAKER_EXCEPTION_H
#define PGR_SPINNAKER_EXCEPTION_H

#include "SpinnakerPlatform.h"
#include "SpinnakerDefs.h"
#include <stdio.h>
#include <exception>

namespace Spinnaker
{
	/**
	 *  @defgroup SpinnakerClasses Spinnaker Classes
	 */

	/*@{*/

	/**
	 *  @defgroup Exception_h Exception Class
	 */

	/*@{*/

    /**
    * @brief The Exception object represents an error that is returned from the library.
    *        Overloaded operators allow comparisons against other Exception objects.
    */

    class SPINNAKER_API Exception : public virtual std::exception
    {

    public:

        /**
         * Default constructor.
         */
        Exception();

		/**
         * Message constructor.
         *
         * @param line Line number where the exception is thrown
		 * @param fileName Name of the file called
		 * @param funcName Name of the function called
		 * @param buildDate Build date
		 * @param buildTime Build time
		 * @param errMsg A pointer to the exception message string
		 * @param err Error code
         */
		Exception( int line,
			const char * fileName,
			const char * funcName,
			const char * buildDate,
			const char * buildTime,
			const char * errMsg,
			Error	err);

        /**
         * Copy constructor.
         */
        Exception( const Exception& except );

        /**
         * Default destructor.
         */
        virtual ~Exception() throw() ;

		/**
         * Assignment operator.
         */
		Exception&	operator=( const Exception& except );

		/**
         * Equality operator.
         */
		bool operator==( const Error err) const;

		/**
         * Inequality operator.
         */
		bool operator!=( const Error err) const;

		/**
         * virtual override for what().
		 * Gets the error code and error message.
         */
		virtual const char * what() const throw (); //add throw() to avoid looser throw specifier error

		/**
         * Gets the error code and full error message including the line, file, function, build date, and time.
         */
		const char * GetFullErrorMessage() const;

		/**
         * Accessor Functions.
         */
		const char *	GetErrorMessage() const;
		const char *	GetFileName() const;
		const char *	GetFunctionName() const;
		const char *	GetBuildDate() const;
		const char *	GetBuildTime() const;
		int				GetLineNumber() const;
		Error	GetError() const;


    protected:

    private:

		struct ExceptionData;
        ExceptionData* m_pImpl;
    };

	/*@}*/

	/*@}*/
}

#endif // PGR_SPINNAKER_EXCEPTION_H