//
// Initialize.cpp
// C++ code
// ----------------------------------
// Developed with embedXcode
// http://embedXcode.weebly.com
//
// Project 		eye-Blink_Conditioning
//
// Created by 	Kambadur Ananthamurthy, 13/09/15 11:07 am
// 				Kambadur Ananthamurthy
//
// Copyright	© Kambadur Ananthamurthy, 2015
// Licence   	<#license#>
//
// See 			Initialize.h and ReadMe.txt for references
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
#include "Initialize.h"

extern String mouseName;
extern int sessionType_ind;
extern int session;
extern boolean start;
extern int traceTime;
extern int totalTrials;

void initialize()
{
  Serial.print("#Please enter the mouse ID number: ");
  while (!Serial.available());
  mouseName = "MouseK" + String(Serial.readString().toInt());
  Serial.println("#" + mouseName);

  delay(1);
  Serial.print("#Please enter the session type index: ");
  while (!Serial.available());
  sessionType_ind = Serial.readString().toInt();
  Serial.println("#Session Type " + String(sessionType_ind));

  delay(1);
  Serial.print("#Please enter the session number: ");
  while (!Serial.available());
  session = Serial.readString().toInt();
  Serial.println("#Session " + String(session));

  delay(1);
  Serial.println("#Please press the SELECT button to begin!");

  while (read_lcd_button() != btnSELECT);

  // From here, the Arduino will start running the behaviour
  startT = millis();
  start = 1;
  lcd.setCursor( 0, 1 );
  lcd.print("S");
  lcd.setCursor(1, 1);
  lcd.print(session);
  lcd.setCursor( 4, 1 );
  lcd.print("T");

  lcd.setCursor( 0, 0 );
  lcd.print(mouseName);

  lcd.setCursor(8, 0);
  lcd.print(sessionType[sessionType_ind]);
  lcd.setCursor(6, 1);
  lcd.print("          ");
  Serial.println(SESSION_BEGIN_MARKER);
  Serial.println(TRIAL_DATA_MARKER);
  //Serial.print(trialNum);
  Serial.println("1 1"); // Just to not confuse data saving; NOTE: we always start the session with a CS+ trial
  Serial.println(DATA_BEGIN_MARKER);

  // Get totalTrials and traceTime based on the Session Type
  if (sessionType_ind == 2)
  {
    traceTime = 0; //in ms
    totalTrials = 100;
  }
  else
  {
    traceTime = 250; //in ms
    if (sessionType_ind == 0)
    {
      totalTrials = 50;
    }
    else
    {
      totalTrials = 100;
    }
  }
}
