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
    digitalWrite(videoTrigger_do, LOW);
    if ( currentPhaseTime - lastTime > sampleInterval )
    {
        digitalWrite(videoTrigger_do, HIGH);
        lastTime += sampleInterval;
    }
}
