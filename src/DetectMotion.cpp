//
// DetectMotion.cpp
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
#include "DetectMotion.h"

void detectMotion() //(unsigned long currentTime)
{
    if ( currentPhaseTime - lastTime > sampleInterval )
    {        
        write_data_line( 0,currentPhaseTime % 10000 );
        lastTime += sampleInterval;
    }
}
