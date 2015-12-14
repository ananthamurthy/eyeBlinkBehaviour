//
// DetectBlinks.cpp
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
// See 			DetectBlinks.h and ReadMe.txt for references
//

// Code
#include "Globals.h"
#include "DetectBlinks.h"

void detectBlinks() //(unsigned long currentTime)
{

    if ( currentPhaseTime - lastTime > sampleInterval )
    {
        blink = analogRead(blink_ai);
        write_data_line( blink, currentPhaseTime % 10000 );
        lastTime += sampleInterval;
    }
}
