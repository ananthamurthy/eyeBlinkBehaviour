//=============================================================================
// Copyright © 2016 Point Grey Research, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of Point
// Grey Research, Inc. ("Confidential Information").  You shall not
// disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with PGR.
//
// PGR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. PGR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

#ifndef _PTGREY_VIDEOENCODER_H /* Include guard. */
#define _PTGREY_VIDEOENCODER_H

#include "PtGreyVideoEncoderPlatform.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int BOOL;

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

/*******************************************************************************
 * Preprocessor directives.
 ******************************************************************************/
#include <stdio.h>
#ifndef FILENAME_MAX
#define FILENAME_MAX	(4096)
#endif
#define PTGREY_BUF_LEN	(FILENAME_MAX)
#define PTGREY_BR_MIN	(10)


/*******************************************************************************
 * Classes and abstract data types.
 ******************************************************************************/
/**
 * @brief	Video formats supported for conversion.
 */
enum PtGreyVideoCodecFormat {
	PTGREY_VIDEO_UNCOMPRESSED = 0,
	PTGREY_VIDEO_MJPG,
	PTGREY_VIDEO_H264,
	PTGREY_VIDEO_MAX
};

/**
 * @brief	Image conversion algorithms supported for re-scaling images.
 */
enum PtGreyVideoScalerMode {
	PTGREY_SCALER_FAST_BILINEAR = 0,
	PTGREY_SCALER_BILINEAR,
	PTGREY_SCALER_BICUBIC,
	PTGREY_SCALER_MAX
};


/**
 * @brief	Opaque struct/handle used to communicate with internal library.
 */
struct PtGreyHandle;

/**
 * @brief	Encoding options provided by the user.
 */
struct PtGreyVideoEncoderOptions {
	enum PtGreyVideoCodecFormat fmt;	/* Video codec to use for output video file. */
	enum PtGreyVideoScalerMode mode;	/* Image scaling algorithm to use. */
	char filename[PTGREY_BUF_LEN];		/* NULL-terminated short name (not including full path) of the output file. */
	int srcHeight;						/* Height of the input image. */
	int srcWidth;						/* Width of the input image. */
	int dstHeight;						/* Height of the output image. Must be an integer multiple of 2. */
	int dstWidth;						/* Width of the output image. Must be an integer multiple of 2. */
	int FPS_NUM;						/* Desired frame rate (frames per second) numerator. */
	int FPS_DEN;						/* Desired frame rate (frames per second) denominator. */
	int GOB;							/* Number of I-frames per P frame. Increasing this value
										 * improves quality at the expense of increased file size. */
	int frames;							/* Number of frames to encode. */
	int BR;								/* Desired bit rate (bits per second). Minimum is PTGREY_BR_MIN. */
	int stride;							/* Stride of pixel data (ie: number of bytes per pixel, assuming no
										 * padding bits.
										 */
};


/*******************************************************************************
 * Function prototypes.
 ******************************************************************************/
/**
 * @file	PtGreyVideoEncoder.h
 * @brief	The API functions within this library are re-entrant, as each video
 * 			encoding session is expected to use a unique handle acquire via
 * 			PtGreyCreateVideoEncoder(). The code is not thread safe, as there is
 * 			not internal mutex to prevent the user from attempting to close an
 * 			encoding session while in progress. The library can be completely
 * 			thread safe by wrapping each API call for a given handle with a
 * 			unique mutex.
 */


/*******************************************************************************
 * @brief	Create a valid handle to the encoding engine.
 * @return	Status of the operation. On faliure, all resources allocated
 * 			internally by this function are automatically cleaned up, so
 * 			there is no need to call PtGreyDestroyVideoEncoder(). If the
 * 			destroy function is called anyways, it has no effect
 * 			(idempotent).
 *				0:		Success.
 *				<0:		Failure.
 * @param:	pHandle
 *			Pointer to an uninitialized 'struct PtGreyHandle'.
 * @param:	pOpts
 *			Pointer to a pre-populated 'struct PtGreyVideoEncoderOptions'.
 ******************************************************************************/
PTGREY_VIDEO_ENCODER_API int PtGreyCreateVideoEncoder(
		struct PtGreyHandle** pHandle,
		struct PtGreyVideoEncoderOptions *pOpts);

/*******************************************************************************
 * @brief	Cleanup and destroy an existing valid handle to the encoding engine.
 * @return	Status of the operation.
 *				0:		Success.
 *				<0:		Failure.
 * @param:	pHandle
 *			Pointer to an initialized 'struct PtGreyHandle'.
 ******************************************************************************/
PTGREY_VIDEO_ENCODER_API int PtGreyDestroyVideoEncoder(
		struct PtGreyHandle** pHandle);

/*******************************************************************************
 * @brief	Write a frame of image data to an existing video stream.
 * @return	Status of the operation.
 *				0:		Success.
 *				<0:		Failure.
 * @param:	pHandle
 *			Pointer to an initialized 'struct PtGreyHandle'.
 * @param:	pFrame
 *			Pointer to a raw image data of length and width as defined in the
 *			pHandle used with PtGreyCreateVideoEncoder(). Image data is expected
 *			to be in RGB24 (packed) format. Spinnaker and FlyCapture2 can
 *			convert raw image data (ie: Bayer tiled) to this format via the
 *			::Image::Convert functionality built into the respective libraries.
 ******************************************************************************/
PTGREY_VIDEO_ENCODER_API int PtGreyWriteFrame(
		struct PtGreyHandle* pHandle,
		const unsigned char* pFrame);

#ifdef __cplusplus
}
#endif

#endif //_PTGREY_VIDEOENCODER_H

