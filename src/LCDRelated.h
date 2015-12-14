//
// File			LCDRelated.h
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
// Date			04/08/15 1:39 pm
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

#ifndef LCDRelated_h
#define LCDRelated_h

// NOTE: Include it in ino file

// This is an Arduino Library
#include <LiquidCrystal.h>

// Initialize LC library with # of interface pins
extern LiquidCrystal lcd;

static const char* sessionType[] = {"Cntrl", "Trace", "Delay"};

// Use these variables with the function "printStatus(value)" to
const int START_PRE = 0;
const int START_CS_PLUS = 1; // paired CS
const int START_CS_MINUS = 2;
const int START_TRACE = 3;
const int START_US = 4; //puff is on
const int START_US_NO_PUFF = 5; //puff is off
const int START_POST = 6;
const int START_ITI = 7;
const int END = 8;
const int PAUSE = 9;

// all values should have 7 letters/spaces between quotes
static const char* printStr[] = {
    "    Pre", "    CS+", "    CS-"
    , "  Trace", "     US", "No-Puff", "   POST"
    , "    ITI", "    END", " Pause "
};

/**
 @description Updates the lcd screen with the Trial Number, Phase, and Session Duration (mins)
 @params value Is the index being used with printStr
 @params trialNum Is the current Trial Number
 */
void printStatus(int value, int trialNum);

const int lcdButton_ai = A0; //pin that the pause button is read from

// Pause/Unpause Buttons
//int adc_key_in = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
/**
 @description Analog reads which buttons on the LCD screen have been pressed
 */
int read_lcd_button();

#endif
