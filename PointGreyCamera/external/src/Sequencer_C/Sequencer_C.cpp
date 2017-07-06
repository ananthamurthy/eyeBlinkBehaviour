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

/**
 *	@example Sequencer_C.cpp
 *
 *	@brief Sequencer_C.cpp shows how to use the sequencer to grab images with
 *	various settings. It relies on information provided in the Enumeration_C,
 *	Acquisition_C, and NodeMapInfo_C examples.
 *
 *	It can also be helpful to familiarize yourself with the
 *	ImageFormatControl_C and Exposure_C examples as these provide a strong
 *	introduction to camera customization.
 *
 *	The sequencer is another very powerful tool that can be used to create and
 *	store multiple sets of customized image settings. A very useful 
 *	application of the sequencer is creating high dynamic range images.
 *
 *	This example is probably the most complex and definitely the longest. As
 *	such, the configuration has been split between three functions. The first
 *	prepares the camera to set the sequences, the second sets the settings for
 *	a single sequence (it is run five times), and the third configures the 
 *	camera to use the sequencer when it acquires images.
 */

#include "SpinnakerC.h"
#include "stdio.h"
#include "string.h"

// Compiler warning C4996 suppressed due to deprecated strcpy() and sprintf() 
// functions on Windows platform.
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64 
	#pragma warning(disable : 4996)
#endif

// This macro helps with C-strings.
#define MAX_BUFF_LEN 256

// This function prepares the sequencer to accept custom configurations by 
// ensuring sequencer mode is off (this is a requirement to the enabling of 
// sequencer configuration mode), disabling automatic gain and exposure, and 
// turning sequencer configuration mode on.
spinError ConfigureSequencerPartOne(spinNodeMapHandle hNodeMap)
{
	spinError err = SPINNAKER_ERR_SUCCESS;
	unsigned int i = 0;

	printf("\n\n*** SEQUENCER CONFIGURATION ***\n\n");

	//
	// Ensure sequencer is off for configuration
	//
	// *** NOTES ***
	// In order to set a new sequencer configuration, sequencer mode must
	// be disabled and sequencer configuration mode must be enabled. In 
	// order to manually disable sequencer mode, the sequencer configuration 
	// must be valid; otherwise, we know that sequencer mode is off, but an 
	// exception will be raised when we try to manually disable it.
	//
	// Therefore, in order to ensure that sequencer mode is off, we first
	// check whether the current sequencer configuration is valid. If it
	// isn't, then we know that sequencer mode is off and we can move on; 
	// however, if it is, then we know it is safe to manually disable
	// sequencer mode.
	//
	// Also note that sequencer configuration mode needs to be off in order
	// to manually disable sequencer mode. It should be off by default, so
	// the example skips checking this.
	//
	spinNodeHandle hSequencerConfigurationValid = NULL;
	spinNodeHandle hSequencerConfigurationValidCurrent = NULL;
	spinNodeHandle hSequencerConfigurationValidYes = NULL;
	spinNodeHandle hSequencerMode = NULL;
	spinNodeHandle hSequencerModeOff = NULL;
	int64_t sequencerModeOff = 0;

	// Validate sequencer configuration
	err = spinNodeMapGetNode(hNodeMap, "SequencerConfigurationValid", &hSequencerConfigurationValid);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to validate sequencer configuration (node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetCurrentEntry(hSequencerConfigurationValid, &hSequencerConfigurationValidCurrent);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to validate sequencer configuration (current entry retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hSequencerConfigurationValid, "Yes", &hSequencerConfigurationValidYes);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to validate sequencer configuration ('yes' entry retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	// If valid, disable sequencer mode; otherwise, do nothing
	if (hSequencerConfigurationValidCurrent == hSequencerConfigurationValidYes)
	{
		err = spinNodeMapGetNode(hNodeMap, "SequencerMode", &hSequencerMode);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to disable sequencer mode (node retrieval). Aborting with error %d...\n\n", err);
			return err;
		}

		err = spinEnumerationGetEntryByName(hSequencerMode, "Off", &hSequencerModeOff);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to disable sequencer mode ('on' entry retrieval). Aborting with error %d...\n\n", err);
			return err;
		}

		err = spinEnumerationEntryGetIntValue(hSequencerModeOff, &sequencerModeOff);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to disable sequencer mode (entry int value retrieval). Aborting with error %d...\n\n", err);
			return err;
		}

		err = spinEnumerationSetIntValue(hSequencerMode, sequencerModeOff);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to disable sequencer mode (entry int value setting). Aborting with error %d...\n\n", err);
			return err;
		}	
	}

	printf("Sequencer mode disabled...\n");

	//
	// Turn off automatic exposure mode
	//
	// *** NOTES ***
	// Automatic exposure prevents the manual configuration of exposure 
	// times and needs to be turned off for this example.
	//
	// *** LATER ***
	// If exposure time is not being manually set for a specific reason, it 
	// is best to let the camera take care of exposure time automatically.
	//
	spinNodeHandle hExposureAuto = NULL;
	spinNodeHandle hExposureAutoOff = NULL;
	int64_t exposureAutoOff;
	
	err = spinNodeMapGetNode(hNodeMap, "ExposureAuto", &hExposureAuto);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable automatic exposure (node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hExposureAuto, "Off", &hExposureAutoOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable automatic exposure ('off' entry retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hExposureAutoOff, &exposureAutoOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable automatic exposure (entry int value retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationSetIntValue(hExposureAuto, exposureAutoOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable automatic exposure (entry int value setting). Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Automatic exposure disabled...\n");

	//
	// Turn off automatic gain
	//
	// *** NOTES ***
	// Automatic gain prevents the manual configuration of gain and needs to
	// be turned off for this example.
	//
	// *** LATER ***
	// If gain is not being manually set for a specific reason, it is best
	// to let the camera take care of gain automatically.
	//
	spinNodeHandle hGainAuto = NULL;
	spinNodeHandle hGainAutoOff = NULL;
	int64_t gainAutoOff;

	err = spinNodeMapGetNode(hNodeMap, "GainAuto", &hGainAuto);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable automatic gain. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hGainAuto, "Off", &hGainAutoOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable automatic gain. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hGainAutoOff, &gainAutoOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable automatic gain. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationSetIntValue(hGainAuto, gainAutoOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable automatic gain. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Automatic gain disabled...\n");

	//
	// Turn configuration mode on
	//
	// *** NOTES ***
	// Once sequencer mode is off, enabling sequencer configuration mode 
	// allows for the setting of individual sequences.
	// 
	// *** LATER ***
	// Before sequencer mode is turned back on, sequencer configuration
	// mode must be turned off.
	//
	spinNodeHandle hSequencerConfigurationMode = NULL;
	spinNodeHandle hSequencerConfigurationModeOn = NULL;
	int64_t sequencerConfigurationModeOn = 0;

	err = spinNodeMapGetNode(hNodeMap, "SequencerConfigurationMode", &hSequencerConfigurationMode);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable sequencer configuration mode. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hSequencerConfigurationMode, "On", &hSequencerConfigurationModeOn);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable sequencer configuration mode. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hSequencerConfigurationModeOn, &sequencerConfigurationModeOn);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable sequencer configuration mode. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationSetIntValue(hSequencerConfigurationMode, sequencerConfigurationModeOn);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable sequencer configuration mode. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Sequencer configuration mode enabled...\n\n");

	return err;
}

// This function sets a single state. It sets the sequence number, applies 
// custom settings, selects the trigger type and next state number, and saves 
// the state. The custom values that are applied are all calculated in the 
// function that calls this one, RunSingleCamera().
spinError SetSingleState(spinNodeMapHandle hNodeMap, unsigned int sequenceNumber, int64_t widthToSet, int64_t heightToSet, double exposureTimeToSet, double gainToSet)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	//
	// Select the sequence number
	//
	// *** NOTES ***
	// Select the index of the state to be set.
	//
	// *** LATER ***
	// The next state - i.e. the state to be linked to -
	// also needs to be set before saving the current state.
	//
	spinNodeHandle hSequencerSetSelector = NULL;

	err = spinNodeMapGetNode(hNodeMap, "SequencerSetSelector", &hSequencerSetSelector);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to select current sequence. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinIntegerSetValue(hSequencerSetSelector, sequenceNumber);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to select current sequence. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Customizing sequence %d...\n", sequenceNumber);

	//
	// Set desired settings for the current state
	//
	// *** NOTES ***
	// Width, height, exposure time, and gain are set in this example. If
	// the sequencer isn't working properly, it may be important to ensure
	// that each feature is enabled on the sequencer. Features are enabled
	// by default, so this is not explored in this example.
	//
	// Changing the height and width for the sequencer is not available
	// for all camera models.
	//
	// Set width; width recorded in pixels
	spinNodeHandle hWidth = NULL;
	int64_t widthInc = 0;
	bool8_t isAvailableWidth = False;
	bool8_t isWritableWidth = False;

	err = spinNodeMapGetNode(hNodeMap, "Width", &hWidth);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set width. Aborting with error %d...\n\n");
		return err;
	}

	err = spinNodeIsAvailable(hWidth, &isAvailableWidth);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set width. Aborting with error %d...\n\n");
		return err;
	}

	err = spinNodeIsWritable(hWidth, &isWritableWidth);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set width. Aborting with error %d...\n\n");
		return err;
	}
	
	if (isAvailableWidth && isWritableWidth)
	{
		err = spinIntegerGetInc(hWidth, &widthInc);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to set width. Aborting with error %d...\n\n", err);
			return err;
		}

		if (widthToSet % widthInc != 0)
		{
			widthToSet = (widthToSet / widthInc) * widthInc;
		}

		err = spinIntegerSetValue(hWidth, widthToSet);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to set width. Aborting with error %d...\n\n", err);
			return err;
		}

		printf("\tWidth set to %d...\n", (int)widthToSet);
	}
	else
	{
		printf("\tUnable to set width; width for sequencer not available on all camera models...\n");
	}
	
	// Set height; height recorded in pixels
	spinNodeHandle hHeight = NULL;
	int64_t heightInc = 0;
	bool8_t isAvailableHeight = False;
	bool8_t isWritableHeight = False;

	err = spinNodeMapGetNode(hNodeMap, "Height", &hHeight);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set height. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinNodeIsAvailable(hWidth, &isAvailableHeight);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set width. Aborting with error %d...\n\n");
		return err;
	}

	err = spinNodeIsWritable(hWidth, &isWritableHeight);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set width. Aborting with error %d...\n\n");
		return err;
	}

	if (isAvailableHeight && isWritableHeight)
	{
		err = spinIntegerGetInc(hHeight, &heightInc);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to set height. Aborting with error %d...\n\n", err);
			return err;
		}

		if (heightToSet % heightInc != 0)
		{
			heightToSet = (heightToSet / heightInc) * heightInc;
		}

		err = spinIntegerSetValue(hHeight, heightToSet);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to set height. Aborting with error %d...\n\n", err);
			return err;
		}

		printf("\tHeight set to %d...\n", (int)heightToSet);
	}
	else
	{
		printf("\tUnable to set height; height for sequencer not available on all camera models...\n");
	}

	// Set exposure time; exposure time recorded in microseconds
	spinNodeHandle hExposureTime = NULL;
	
	err = spinNodeMapGetNode(hNodeMap, "ExposureTime", &hExposureTime);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set exposure. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinFloatSetValue(hExposureTime, exposureTimeToSet);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set exposure. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("\tExposure time set to %f...\n", exposureTimeToSet);

	// Set gain; gain recorded in decibels
	spinNodeHandle hGain = NULL;

	err = spinNodeMapGetNode(hNodeMap, "Gain", &hGain);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set gain. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinFloatSetValue(hGain, gainToSet);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set gain. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("\tGain set to %f...\n", gainToSet);

	//
	// Set the trigger type for the current sequence
	//
	// *** NOTES ***
	// It is a requirement of every state to have its trigger source set.
	// The trigger source refers to the moment when the sequencer changes 
	// from one state to the next.
	//
	spinNodeHandle hSequencerTriggerSource = NULL;
	spinNodeHandle hSequencerTriggerSourceFrameStart = NULL;
	int64_t sequencerTriggerSourceFrameStart = 0;

	err = spinNodeMapGetNode(hNodeMap, "SequencerTriggerSource", &hSequencerTriggerSource);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set trigger source. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hSequencerTriggerSource, "FrameStart", &hSequencerTriggerSourceFrameStart);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set trigger source. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hSequencerTriggerSourceFrameStart, &sequencerTriggerSourceFrameStart);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set trigger source. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationSetIntValue(hSequencerTriggerSource, sequencerTriggerSourceFrameStart);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set trigger source. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("\tTrigger source set to start of frame...\n");

	//
	// Set the next state in the sequence
	//
	// *** NOTES ***
	// When setting the next state in the sequence, ensure it does not 
	// exceed the maximum and that the states loop appropriately.
	//
	spinNodeHandle hSequencerSetNext = NULL;
	const unsigned int finalSequenceIndex = 4;
	unsigned int nextSequence = 0;

	err = spinNodeMapGetNode(hNodeMap, "SequencerSetNext", &hSequencerSetNext);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set next sequence. Aborting with err %d...\n\n", err);
		return err;
	}

	if (sequenceNumber != finalSequenceIndex)
	{
		nextSequence = sequenceNumber + 1;
	}

	err = spinIntegerSetValue(hSequencerSetNext, nextSequence);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set next sequence. Aborting with err %d...\n\n", err);
		return err;
	}

	printf("\tNext sequence set to %d...\n", nextSequence);

	//
	// Save current state
	//
	// *** NOTES ***
	// Once all appropriate settings have been configured, make sure to 
	// save the state to the sequence. Notice that these settings will be 
	// lost when the camera is power-cycled.
	//
	spinNodeHandle hSequencerSetSave = NULL;
	
	err = spinNodeMapGetNode(hNodeMap, "SequencerSetSave", &hSequencerSetSave);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to save sequence. Aborting with err %d...\n\n", err);
		return err;
	}

	err = spinCommandExecute(hSequencerSetSave);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to save sequence. Aborting with err %d...\n\n", err);
		return err;
	}

	printf("\tSequence %d saved...\n\n", sequenceNumber);

	return err;
}

// Now that the states have all been set, this function readies the camera 
// to use the sequencer during image acquisition.
spinError ConfigureSequencerPartTwo(spinNodeMapHandle hNodeMap)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	//
	// Turn configuration mode off
	//
	// *** NOTES ***
	// Once all desired states have been set, turn sequencer 
	// configuration mode off in order to turn sequencer mode on.
	//
	spinNodeHandle hSequencerConfigurationMode = NULL;
	spinNodeHandle hSequencerConfigurationModeOff = NULL;
	int64_t sequencerConfigurationModeOff = 0; 

	err = spinNodeMapGetNode(hNodeMap, "SequencerConfigurationMode", &hSequencerConfigurationMode);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable sequencer configuration mode. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hSequencerConfigurationMode, "Off", &hSequencerConfigurationModeOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable sequencer configuration mode. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hSequencerConfigurationModeOff, &sequencerConfigurationModeOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable sequencer configuration mode. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationSetIntValue(hSequencerConfigurationMode, sequencerConfigurationModeOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to disable sequencer configuration mode. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Sequencer configuration mode disabled...\n");

	//
	// Turn sequencer mode on
	// 
	// *** NOTES ***
	// Once sequencer mode is turned on, the camera will begin using the 
	// saved states in the order that they were set. 
	//
	// *** LATER ***
	// Once all images have been captured, disable the sequencer in order 
	// to restore the camera to its initial state.
	//
	spinNodeHandle hSequencerMode = NULL;
	spinNodeHandle hSequencerModeOn = NULL;
	int64_t sequencerModeOn = 0;

	err = spinNodeMapGetNode(hNodeMap, "SequencerMode", &hSequencerMode);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable sequencer mode. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hSequencerMode, "On", &hSequencerModeOn);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable sequencer mode. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hSequencerModeOn, &sequencerModeOn);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable sequencer mode. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationSetIntValue(hSequencerMode, sequencerModeOn);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable sequencer mode. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Sequencer mode enabled...\n");

	//
	// Validate sequencer settings
	//
	// *** NOTES ***
	// Once all states have been set, it is a good idea to 
	// validate them. Although this node cannot ensure that the states
	// have been set up correctly, it does ensure that the states have 
	// been set up in such a way that the camera can function.
	//
	spinNodeHandle hSequencerConfigurationValid = NULL;
	spinNodeHandle hSequencerConfigurationValidCurrent = NULL;
	spinNodeHandle hSequencerConfigurationValidYes = NULL;
	int64_t sequencerConfigurationValidCurrent = 0;
	int64_t sequencerConfigurationValidYes = 0;

	err = spinNodeMapGetNode(hNodeMap, "SequencerConfigurationValid", &hSequencerConfigurationValid);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to validate sequencer configuration (node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetCurrentEntry(hSequencerConfigurationValid, &hSequencerConfigurationValidCurrent);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to validate sequencer configuration (current node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hSequencerConfigurationValid, "Yes", &hSequencerConfigurationValidYes);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to validate sequencer configuration ('yes' node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hSequencerConfigurationValidCurrent, &sequencerConfigurationValidCurrent);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to validate sequencer configuration ('current' value retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hSequencerConfigurationValidYes, &sequencerConfigurationValidYes);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to validate sequencer configuration ('yes' value retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	if (sequencerConfigurationValidCurrent != sequencerConfigurationValidYes)
	{
		err = SPINNAKER_ERR_ERROR;
		printf("Sequencer configuration not valid. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Sequencer configuration valid...\n\n");

	return err;
}

// This function restores the camera to its default state by turning sequencer
// mode off and re-enabling automatic exposure and gain.
spinError ResetSequencer(spinNodeMapHandle hNodeMap)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	//
	// Turn sequencer mode back off
	//
	// *** NOTES ***
	// The sequencer is turned off in order to return the camera to its default
	// state.
	//
	spinNodeHandle hSequencerMode = NULL;
	spinNodeHandle hSequencerModeOff = NULL;
	int64_t sequencerModeOff = 0;

	err = spinNodeMapGetNode(hNodeMap, "SequencerMode", &hSequencerMode);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable sequencer mode. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hSequencerMode, "Off", &hSequencerModeOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable sequencer mode. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hSequencerModeOff, &sequencerModeOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable sequencer mode. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationSetIntValue(hSequencerMode, sequencerModeOff);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable sequencer mode. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Sequencer mode disabled...\n");

	// 
	// Turn automatic exposure back on
	//
	// *** NOTES ***
	// Automatic exposure is turned on in order to return the camera to its 
	// default state.
	//
	spinNodeHandle hExposureAuto = NULL;
	spinNodeHandle hExposureAutoContinuous = NULL;
	int64_t exposureAutoContinuous;

	err = spinNodeMapGetNode(hNodeMap, "ExposureAuto", &hExposureAuto);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable automatic exposure. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hExposureAuto, "Continuous", &hExposureAutoContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable automatic exposure. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hExposureAutoContinuous, &exposureAutoContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable automatic exposure. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationSetIntValue(hExposureAuto, exposureAutoContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable automatic exposure. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Automatic exposure enabled...\n");

	// 
	// Turn automatic gain back on
	//
	// *** NOTES ***
	// Automatic gain is turned on in order to return the camera to its 
	// default state.
	//
	spinNodeHandle hGainAuto = NULL;
	spinNodeHandle hGainAutoContinuous = NULL;
	int64_t gainAutoContinuous;

	err = spinNodeMapGetNode(hNodeMap, "GainAuto", &hGainAuto);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable automatic gain. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hGainAuto, "Continuous", &hGainAutoContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable automatic gain. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hGainAutoContinuous, &gainAutoContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable automatic gain. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationSetIntValue(hGainAuto, gainAutoContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to enable automatic gain. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Automatic gain enabled...\n\n");

	return err;
}

// This function prints the device information of the camera from the transport
// layer; please see NodeMapInfo_C example for more in-depth comments on 
// printing device information from the nodemap.
spinError PrintDeviceInfo(spinNodeMapHandle hNodeMap)
{
	spinError err = SPINNAKER_ERR_SUCCESS;
	unsigned int i = 0;

	printf("\n*** DEVICE INFORMATION ***\n\n");

	// Retrieve device information category node
	spinNodeHandle hDeviceInformation = NULL;

	err = spinNodeMapGetNode(hNodeMap, "DeviceInformation", &hDeviceInformation);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve node. Non-fatal error %d...\n\n", err);
		return err;
	}

	// Retrieve number of nodes within device information node
	size_t numFeatures = 0;

	err = spinCategoryGetNumFeatures(hDeviceInformation, &numFeatures);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve number of nodes. Non-fatal error %d...\n\n", err);
		return err;
	}

	// Iterate through nodes and print information
	for (i = 0; i < numFeatures; i++)
	{
		spinNodeHandle hFeatureNode = NULL;

		err = spinCategoryGetFeatureByIndex(hDeviceInformation, i, &hFeatureNode);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve node. Non-fatal error %d...\n\n", err);
			continue;
		}

		spinNodeType featureType = UnknownNode;

		err = spinNodeGetType(hFeatureNode, &featureType);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve node type. Non-fatal error %d...\n\n", err);
			continue;
		}

		char featureName[MAX_BUFF_LEN];
		size_t lenFeatureName = MAX_BUFF_LEN;
		char featureValue[MAX_BUFF_LEN];
		size_t lenFeatureValue = MAX_BUFF_LEN;

		err = spinNodeGetName(hFeatureNode, featureName, &lenFeatureName);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			strcpy(featureName, "Unknown name");
		}

		err = spinNodeToString(hFeatureNode, featureValue, &lenFeatureValue);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			strcpy(featureValue, "Unknown value");
		}

		printf("%s: %s\n", featureName, featureValue);
	}

	return err;
}

// This function acquires and saves 10 images from a device; please see
// Acquisition_C example for more in-depth comments on the acquisition of
// images.
spinError AcquireImages(spinCamera hCam, spinNodeMapHandle hNodeMap, spinNodeMapHandle hNodeMapTLDevice)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	printf("\n*** IMAGE ACQUISITION ***\n\n");

	// Set acquisition mode to continuous
	spinNodeHandle hAcquisitionMode = NULL;
	spinNodeHandle hAcquisitionModeContinuous = NULL;
	int64_t acquisitionModeContinuous = 0;

	err = spinNodeMapGetNode(hNodeMap, "AcquisitionMode", &hAcquisitionMode);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set acquisition mode to continuous (node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationGetEntryByName(hAcquisitionMode, "Continuous", &hAcquisitionModeContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set acquisition mode to continuous (entry 'continuous' retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationEntryGetIntValue(hAcquisitionModeContinuous, &acquisitionModeContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set acquisition mode to continuous (entry int value retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinEnumerationSetIntValue(hAcquisitionMode, acquisitionModeContinuous);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to set acquisition mode to continuous (entry int value setting). Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Acquisition mode set to continuous...\n");

	// Begin acquiring images
	err = spinCameraBeginAcquisition(hCam);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to begin image acquisition. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Acquiring images...\n");

	// Retrieve device serial number for filename
	spinNodeHandle hDeviceSerialNumber = NULL;
	char deviceSerialNumber[MAX_BUFF_LEN];
	size_t lenDeviceSerialNumber = MAX_BUFF_LEN;

	err = spinNodeMapGetNode(hNodeMapTLDevice, "DeviceSerialNumber", &hDeviceSerialNumber);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		strcpy(deviceSerialNumber, "");
		lenDeviceSerialNumber = 0;
	}
	else
	{
		err = spinStringGetValue(hDeviceSerialNumber, deviceSerialNumber, &lenDeviceSerialNumber);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			strcpy(deviceSerialNumber, "");
			lenDeviceSerialNumber = 0;
		}

		printf("Device serial number retrieved as %s...\n", deviceSerialNumber);
	}
	printf("\n");

	// Retrieve, convert, and save images
	const unsigned int k_numImages = 10;
	unsigned int imageCnt = 0;

	for (imageCnt = 0; imageCnt < k_numImages; imageCnt++)
	{
		// Retrieve next received image 
		spinImage hResultImage = NULL;
		
		err = spinCameraGetNextImage(hCam, &hResultImage);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to get next image. Non-fatal error %d...\n\n", err);
			continue;
		}

		// Ensure image completion
		bool8_t isIncomplete = False;
		bool8_t hasFailed = False;

		err = spinImageIsIncomplete(hResultImage, &isIncomplete);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to determine image completion. Non-fatal error %d...\n\n", err);
			hasFailed = True;
		}

		if (isIncomplete)
		{
			spinImageStatus imageStatus = IMAGE_NO_ERROR;

			err = spinImageGetStatus(hResultImage, &imageStatus);
			if (err != SPINNAKER_ERR_SUCCESS)
			{
				printf("Unable to retrieve image status. Non-fatal error %d...\n\n", err);
			}
			else
			{
				printf("Image incomplete with image status %d...\n", imageStatus);
			}

			hasFailed = True;
		}

		// Release incomplete or failed image
		if (hasFailed)
		{
			err = spinImageRelease(hResultImage);
			if (err != SPINNAKER_ERR_SUCCESS)
			{
				printf("Unable to release image. Non-fatal error %d...\n\n", err);
			}

			continue;
		}

		// Print image information
		size_t width = 0;
		size_t height = 0;

		err = spinImageGetWidth(hResultImage, &width);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve image width. Non-fatal error %d...\n", err);
		}

		err = spinImageGetHeight(hResultImage, &height);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve image height. Non-fatal error %d...\n", err);
		}

		printf("Grabbed image %u, width = %u, height = %u\n", imageCnt, (unsigned int)width, (unsigned int)height);

		// Convert image to mono 8
		spinImage hConvertedImage = NULL;

		err = spinImageCreateEmpty(&hConvertedImage);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to create image. Non-fatal error %d...\n\n", err);
			hasFailed = True;
		}

		err = spinImageConvert(hResultImage, PixelFormat_Mono8, hConvertedImage);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to convert image. Non-fatal error %d...\n\n", err);
			hasFailed = True;
		}

		// Create unique file name
		char filename[MAX_BUFF_LEN];

		if (lenDeviceSerialNumber == 0)
		{
			sprintf(filename, "Sequencer-C-%d.jpg", imageCnt);
		}
		else
		{
			sprintf(filename, "Sequencer-C-%s-%d.jpg", deviceSerialNumber, imageCnt);
		}

		// Save image
		err = spinImageSave(hConvertedImage, filename, JPEG);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to save image. Non-fatal error %d...\n", err);
		}
		else
		{
			printf("Image saved at %s\n\n", filename);
		}

		// Destroy converted image
		err = spinImageDestroy(hConvertedImage);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to destroy image. Non-fatal error %d...\n\n", err);
		}

		// Release image
		err = spinImageRelease(hResultImage);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to release image. Non-fatal error %d...\n\n", err);
		}
	}

	// End acquisition
	err = spinCameraEndAcquisition(hCam);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to end acquisition. Non-fatal error %d...\n\n", err);
	}

	return err;
}

// This function acts very similarly to the RunSingleCamera() functions of other
// examples, except that the values for the sequences are also calculated here; 
// please see NodeMapInfo example for additional information on the steps in 
// this function. 
spinError RunSingleCamera(spinCamera hCam)
{
	spinError err = SPINNAKER_ERR_SUCCESS;

	// Retrieve TL device nodemap and print device information
	spinNodeMapHandle hNodeMapTLDevice = NULL;

	err = spinCameraGetTLDeviceNodeMap(hCam, &hNodeMapTLDevice);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve TL device nodemap. Non-fatal error %d...\n\n", err);
	}
	else
	{
		err = PrintDeviceInfo(hNodeMapTLDevice);
	}

	// Initialize camera
	err = spinCameraInit(hCam);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to initialize camera. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve GenICam nodemap
	spinNodeMapHandle hNodeMap = NULL;

	err = spinCameraGetNodeMap(hCam, &hNodeMap);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve GenICam nodemap. Aborting with error %d...\n\n", err);
		return err;
	}

	// Configure sequencer to be ready to set sequences
	err = ConfigureSequencerPartOne(hNodeMap);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}
	
	//
	// Set sequences
	//
	// *** NOTES ***
	// In the following section, the sequencer values are calculated. This
	// section does not appear in the configuration, as the values 
	// calculated are somewhat arbitrary: width and height are both set to
	// 25% of their maximum values, incrementing by 10%; exposure time is
	// set to its minimum, also incrementing by 10% of its maximum; and gain
	// is set to its minimum, incrementing by 2% of its maximum.
	//
	const unsigned int k_numSequences = 5;

	// Retrieve maximum width; width recorded in pixels
	spinNodeHandle hWidth = NULL;
	int64_t widthMax = 0;

	err = spinNodeMapGetNode(hNodeMap, "Width", &hWidth);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to get max width (node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinIntegerGetMax(hWidth, &widthMax);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to get max width (max retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve maximum height; height recorded in pixels
	spinNodeHandle hHeight = NULL;
	int64_t heightMax = 0;

	err = spinNodeMapGetNode(hNodeMap, "Height", &hHeight);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to get max height (node retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinIntegerGetMax(hHeight, &heightMax);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to get max height (max retrieval). Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve maximum exposure time; exposure time recorded in microseconds
	spinNodeHandle hExposureTime = NULL;
	const double exposureTimeMaxToSet = 5000000.0;
	double exposureTimeMax = 0.0;
	double exposureTimeMin = 0.0;

	err = spinNodeMapGetNode(hNodeMap, "ExposureTime", &hExposureTime);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve exposure time node. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinFloatGetMax(hExposureTime, &exposureTimeMax);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve maximum exposure time. Aborting with error %d...\n\n", err);
		return err;
	}

	if (exposureTimeMax > exposureTimeMaxToSet)
	{
		exposureTimeMax = exposureTimeMaxToSet;
	}

	err = spinFloatGetMin(hExposureTime, &exposureTimeMin);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve minimum exposure time. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve maximum and minimum gain; gain recorded in decibels
	spinNodeHandle hGain = NULL;
	double gainMax = 0.0;
	double gainMin = 0.0;

	err = spinNodeMapGetNode(hNodeMap, "Gain", &hGain);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve gain node. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinFloatGetMax(hGain, &gainMax);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve maximum gain. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinFloatGetMin(hGain, &gainMin);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve minimum gain. Aborting with error %d...\n\n", err);
		return err;
	}

	// Set individual sequences
	unsigned int sequenceNumber;
	int64_t widthToSet = widthMax / 4;
	int64_t heightToSet = heightMax / 4;
	double exposureTimeToSet = exposureTimeMin;
	double gainToSet = gainMin;

	for (sequenceNumber = 0; sequenceNumber < k_numSequences; sequenceNumber++)
	{
		err = SetSingleState(hNodeMap, sequenceNumber, widthToSet, heightToSet, exposureTimeToSet, gainToSet);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			return err;
		}

		widthToSet += widthMax / 10;
		heightToSet += heightMax / 10;
		exposureTimeToSet += exposureTimeMax / 10.0;
		gainToSet += gainMax / 50.0;
	}


	// Configure sequencer to acquire images
	err = ConfigureSequencerPartTwo(hNodeMap);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Acquire images
	err = AcquireImages(hCam, hNodeMap, hNodeMapTLDevice);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Reset sequencer
	err = ResetSequencer(hNodeMap);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		return err;
	}

	// Deinitialize camera
	err = spinCameraDeInit(hCam);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to deinitialize camera. Non-fatal error %d...\n\n", err);
	}

	return err;
}

// Example entry point; please see Enumeration_C example for more in-depth
// comments on preparing and cleaning up the system.
int main(/*int argc, char** argv*/)
{
	spinError errReturn = SPINNAKER_ERR_SUCCESS;
	spinError err = SPINNAKER_ERR_SUCCESS;
	unsigned int i = 0;

	// Print application build information
	printf("Application build date: %s %s \n\n", __DATE__, __TIME__);

	// Retrieve singleton reference to system object
	spinSystem hSystem = NULL;

	err = spinSystemGetInstance(&hSystem);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve system instance. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve list of cameras from the system
	spinCameraList hCameraList = NULL;

	err = spinCameraListCreateEmpty(&hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to create camera list. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinSystemGetCameras(hSystem, hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve camera list. Aborting with error %d...\n\n", err);
		return err;
	}

	// Retrieve number of cameras
	size_t numCameras = 0;

	err = spinCameraListGetSize(hCameraList, &numCameras);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to retrieve number of cameras. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("Number of cameras detected: %u\n\n", (unsigned int)numCameras);

	// Finish if there are no cameras
	if (numCameras == 0)
	{
		// Clear and destroy camera list before releasing system
		err = spinCameraListClear(hCameraList);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to clear camera list. Aborting with error %d...\n\n", err);
			return err;
		}

		err = spinCameraListDestroy(hCameraList);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to destroy camera list. Aborting with error %d...\n\n", err);
			return err;
		}

		// Release system
		err = spinSystemReleaseInstance(hSystem);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to release system instance. Aborting with error %d...\n\n", err);
			return err;
		}

		printf("Not enough cameras!\n");
		printf("Done! Press Enter to exit...\n");
		getchar();

		return -1;
	}

	// Run example on each camera
	for (i = 0; i < numCameras; i++)
	{
		printf("\nRunning example for camera %d...\n", i);

		// Select camera
		spinCamera hCamera = NULL;

		err = spinCameraListGet(hCameraList, i, &hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			printf("Unable to retrieve camera from list. Aborting with error %d...\n\n", err);
			errReturn = err;
		}
		else
		{
			// Run example
			err = RunSingleCamera(hCamera);
			if (err != SPINNAKER_ERR_SUCCESS)
			{
				errReturn = err;
			}
		}

		// Release camera
		err = spinCameraRelease(hCamera);
		if (err != SPINNAKER_ERR_SUCCESS)
		{
			errReturn = err;
		}

		printf("Camera %d example complete...\n\n", i);
	}

	// Clear and destroy camera list before releasing system
	err = spinCameraListClear(hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to clear camera list. Aborting with error %d...\n\n", err);
		return err;
	}

	err = spinCameraListDestroy(hCameraList);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to destroy camera list. Aborting with error %d...\n\n", err);
		return err;
	}

	// Release system
	err = spinSystemReleaseInstance(hSystem);
	if (err != SPINNAKER_ERR_SUCCESS)
	{
		printf("Unable to release system instance. Aborting with error %d...\n\n", err);
		return err;
	}

	printf("\nDone! Press Enter to exit...\n");
	getchar();

	return errReturn;
}
