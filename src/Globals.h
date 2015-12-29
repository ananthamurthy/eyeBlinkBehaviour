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
#define CS_PLUS_COMMAND     "++"
#define CS_MINUS_COMMAND    "--"
#define PUFF_COMMAND        "pp"

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
extern unsigned long startT;
extern unsigned long currentPhaseTime;
extern unsigned long lastTime;
extern unsigned short sampleInterval;
extern int shutterDelay;
extern int totalTrials;
extern int trialNum;
extern const int puffTime;
extern const int CSTime;
extern const int CS_PLUS_ToneFreq;
extern const int CS_MINUS_ToneFreq;

// reset the arduino within 1 seconds.
extern bool reboot_;
extern bool CS_plus;

// A two character status of arduino board.
extern String status; 

void reset_watchdog( );

void write_data_line( int analog_read, unsigned long timestamp );

bool is_command_read( char* command , bool consume = false);

#endif
