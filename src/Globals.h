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


// Core library for code-sense - IDE-based
#if defined(WIRING) // Wiring specific
#   include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#   include "WProgram.h"
#elif defined(MPIDE) // chipKIT specific
#   include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#   include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad specific
#   include "Energia.h"
#elif defined(LITTLEROBOTFRIENDS) // LittleRobotFriends specific
#   include "LRF.h"
#elif defined(MICRODUINO) // Microduino specific
#   include "Arduino.h"
#elif defined(TEENSYDUINO) // Teensy specific
#   include "Arduino.h"
#elif defined(REDBEARLAB) // RedBearLab specific
#   include "Arduino.h"
#elif defined(SPARK) // Spark specific
#   include "application.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#   include "Arduino.h"
#else // error
#   error Platform not defined
#endif // end IDE

#ifndef Globals_h
#define Globals_h


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
void reset_watchdog( );

#endif
