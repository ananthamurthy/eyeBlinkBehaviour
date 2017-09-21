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

#ifndef PGR_SPINNAKER_AVIRECORDER_H
#define PGR_SPINNAKER_AVIRECORDER_H

#include "SpinnakerPlatform.h"
#include "SpinnakerDefs.h"

namespace Spinnaker
{
	class ImagePtr;

	/**
	*  @defgroup SpinnakerClasses Spinnaker Classes
	*/
	/*@{*/

	/**
	*  @defgroup AVIRecorder_h AVI Recorder Class
	*/
	/*@{*/
	
	/**
	* @brief Provides the functionality for the user to record images to an AVI file.
	*/
    
    class SPINNAKER_API AVIRecorder
    {
    public:

        /**
         * Default constructor.
         */
        AVIRecorder();

        /**
         * Default destructor.
         */
        virtual ~AVIRecorder();

        /**
         * Open an AVI file in preparation for writing Images to disk.
         * The size of AVI files is limited to 2GB. The filenames are
         * automatically generated using the filename specified.
         *
         * @param pFileName The filename of the AVI file.
         * @param pOption Options to apply to the AVI file.
         *
         * @see AVIClose()
         *
         */
        virtual void AVIOpen(
            const char* pFileName,
            AVIOption &  pOption );

        /**
         * Open an MJPEG AVI file in preparation for writing Images to disk.
         * The size of AVI files is limited to 2GB. The filenames are
         * automatically generated using the filename specified.
         *
         * @param pFileName The filename of the AVI file.
         * @param pOption MJPEG options to apply to the AVI file.
         *
         * @see AVIClose()
		 * @see MJPGOption
         *
         */
        virtual void AVIOpen(
            const char* pFileName,
            MJPGOption &  pOption );


		 /**
         * Open an H264 MP4 file in preparation for writing Images to disk.
         * The size of MP4 files is limited to 2GB. The filenames are
         * automatically generated using the filename specified.
         *
         * @param pFileName The filename of the MP4 file.
         * @param pOption H264 options to apply to the MP4 file.
         *
         * @see AVIClose()
		 * @see H264Option
         *
         */
        virtual void AVIOpen(
            const char* pFileName,
            H264Option &  pOption );


        /**
         * Append an image to the AVI/MP4 file.
         *
         * @param pImage The image to append.
         *
         */
        virtual void AVIAppend( ImagePtr pImage);

        /**
         * Close the AVI/MP4 file.
         *
         * @see AVIOpen()
         *
         */
        virtual void AVIClose( );

    private:

        AVIRecorder( const AVIRecorder& );
        AVIRecorder& operator=( const AVIRecorder& );

        struct AVIRecorderData; // Forward declaration

        AVIRecorderData* m_pAVIRecorderData;
    };

	/*@}*/

    /*@}*/
}

#endif //PGR_FC2_AVIRECORDER_H