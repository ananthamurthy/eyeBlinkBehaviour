//
// ChangePhase.cpp
// C++ code
// ----------------------------------
// Developed with embedXcode
// http://embedXcode.weebly.com
//
// Project 		eye-Blink_Conditioning
//
// Created by 	Kambadur Ananthamurthy, 13/09/15 11:15 am
// 				Kambadur Ananthamurthy
//
// Copyright	© Kambadur Ananthamurthy, 2015
// Licence   	<#license#>
//
// See 			ChangePhase.h and ReadMe.txt for references
//

#include "Arduino.h"

// Code
#include "Globals.h"

#ifdef ENABLE_LCD
#include "LCDRelated.h"
#endif

#include "ChangePhase.h"

extern int condition;
extern int trialNum;
extern unsigned long startPhaseTime;

void changePhase( int cond, int status )
{
    condition = cond;
#ifdef ENABLE_LCD
    printStatus(status, trialNum);
#endif
    lastTime = 0;
    startPhaseTime = millis();
}
