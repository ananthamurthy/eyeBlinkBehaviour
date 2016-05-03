//
// LCDRelated.cpp
// C++ code
// ----------------------------------
// Developed with embedXcode
// http://embedXcode.weebly.com
//
// Project 		eye-Blink_Conditioning
//
// Created by 	Kambadur Ananthamurthy, 04/08/15 1:44 pm
// 				Kambadur Ananthamurthy
//
// Copyright	© Kambadur Ananthamurthy, 2015
// Licence   	<#license#>
//
// See 			LCDRelated.h and ReadMe.txt for references
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

// Code
#include "Globals.h"

#include "LCDRelated.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // changed this on 20150807

// Code

//*** LCD UPDATE ***

//the following function updates the LCD with the current info
void printStatus( int value , int trialNum)
{
    unsigned long dt = millis() - startT;
    int time_min = dt / 60000;

    //Serial.print( dt );
    //Serial.print( '\t' );

    //Serial.print( '\t' );
    //Serial.print( currTime );
    //Serial.println( value );

    lcd.setCursor( 14, 0 );
    lcd.print( time_min );
    lcd.setCursor( 5, 1 );
    if (value == 8) //Hack to have the LCD Update for the last time, with the right trialNum
    {
        lcd.print( trialNum-1 );
    }
    else
    {
        lcd.print( trialNum );
    }
    lcd.setCursor( 9, 1 );
    lcd.print( printStr[value] );
    /*
     lcd.setCursor( 5, 1);
     lcd.print( numpuffs );
     */
}

//*** LCD BUTTONS ***

// The following function reads and finds out if the LCD buttons have been pressed or not
// currently the only configurations are for the Pause and Unpause buttons. Other buttons not specified
// but look at commented section

int lcd_input_key = 0;
int read_lcd_button()
{
    lcd_input_key = analogRead(lcdButton_ai); // read the value from the sensor
    if (lcd_input_key > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
    if (lcd_input_key < 98)   return btnRIGHT;  //Pause
    if (lcd_input_key < 254)  return btnUP;
    if (lcd_input_key < 408)  return btnDOWN;
    if (lcd_input_key < 600)  return btnLEFT; //Unpause
    if (lcd_input_key < 900)  return btnSELECT; // assuming we never get 1000.
}
