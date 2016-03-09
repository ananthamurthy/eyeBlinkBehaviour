//
// File			Initialize.h
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
// Date			13/09/15 11:06 am
// Version		<#version#>
//
// Copyright	© Kambadur Ananthamurthy, 2015
// Licence    <#license#>
//
// See			ReadMe.txt for references
//


#ifndef Initialize_h
#define Initialize_h

#include "Arduino.h"
#include "Globals.h"

/**
 @description Read details passed as inputs over the serial communication and use this to set protocol parameters, LCD update, etc.
 */

int initialize();

void watchdog_setup( );

#endif
