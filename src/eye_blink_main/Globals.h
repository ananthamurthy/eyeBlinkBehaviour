//
// File			Globals.h
// Header
//
// Details		<#details#>
//
// Project		 eye-Blink_Conditioning
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author		Kambadur Ananthamurthy
// 				Kambadur Ananthamurthy
//
// Date			04/08/15 1:38 pm
// Version		<#version#>
//
// Copyright	© Kambadur Ananthamurthy, 2015
// Licence    <#license#>
//
// See			ReadMe.txt for references
//

#include "Arduino.h"

#ifndef Globals_h
#define Globals_h
#define DEBUG  1

// #define ENABLE_LCD

// Define command characters.

#define RESET_COMMAND       "rr"
#define SELECT_COMMAND      "ss"
#define CS_PLUS_COMMAND     "11"
#define CS_MINUS_COMMAND    "22"
#define PUFF_COMMAND        "pp"
#define PAUSE_COMMAND       "ww"
#define UNPAUSE_COMMAND     "cc"

#define DATA_BEGIN_MARKER "["
#define DATA_END_MARKER "]"
#define COMMENT_MARKER "#"
#define TRIAL_DATA_MARKER "@"
#define PROFILING_DATA_MARKER "$"
#define SESSION_BEGIN_MARKER "<"
#define SESSION_END_MARKER ">"

extern int blink;
extern const int blink_ai;    // pin that reads the blinks
extern int blinkCount;
extern const int puff_do; // pin that drives the eye-puff solenoid
extern const int tonePin;
extern const int ledPin;
extern unsigned long startT;
extern unsigned long currentPhaseTime;
extern unsigned long currentTime; 
extern unsigned long lastTime;
extern unsigned short sampleInterval;
extern int shutterDelay;
extern int totalTrials;
extern int trialNum;
extern long int trialTime;

extern int sessionType_ind;

extern const int puffTime;
extern int CSTime;
extern int traceTime;

// Time of distractor / LED or tone.
extern int distractorOnTime;
extern int distractorOffTime;

/**
 * @brief What fraction of all CS is CS+. Value between 0 and 10.
 */
extern unsigned int CS_fraction;

extern unsigned int CS_TONE_1;
extern unsigned int CS_TONE_2;

// reset the arduino within 1 seconds.
extern bool reboot_;
extern bool paused_;

/**
 * @brief If true, the CS_plus and CS_minus are flipped.
 */
extern bool flipped_;

extern bool CS_plus;

// A two character status of arduino board.
extern String status; 

void reset_watchdog( );

void write_data_line( int analog_read, unsigned long timestamp );

bool is_command_read( char* command , bool consume = false);

void shutoff_cs( unsigned tonePin, unsigned ledPin );

// Check for the pause
void check_for_pause( );

extern int nextProbeIn;
extern int prevTwoTrials[2];

/**
 * @brief Status of the experiment: PRE_, TONE, TRAC, DIST, POST etc.
 */
extern char status_[5];
#endif
