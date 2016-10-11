//
// VideoTrigger.cpp
// C++ code
// ----------------------------------
// Developed with embedXcode
// http://embedXcode.weebly.com
//
// Project 		eye-Blink_Conditioning
//
// Created by 	Kambadur Ananthamurthy, 04/08/15 1:45 pm
// 				Kambadur Ananthamurthy
//
// Copyright	© Kambadur Ananthamurthy, 2015
// Licence   	<#license#>
//
// See 			VideoTrigger.h and ReadMe.txt for references
//

//Code
#include "Globals.h"
#include "VideoTrigger.h"

void videoTrigger()
{
    if (currentPhaseTime - lastTime <= sampleInterval)
    {
        Serial.println("x");
        if ( currentPhaseTime - lastTime <= sampleInterval/2 )
        {
            Serial.println("x1");
            digitalWrite(videoTrigger_do, HIGH);
        }
	    else
        {   
            Serial.println("x2");
	        digitalWrite(videoTrigger_do, LOW);
        }
    }
    else
    {
        Serial.println("y");
        lastTime += sampleInterval;
    }
}
