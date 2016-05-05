/*
 * =====================================================================================
 *
 *       Filename:  Distractor.h
 *
 *    Description:  Distractor
 *
 *        Version:  1.0
 *        Created:  05/03/2016 03:34:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  NCBS Bangalore
 *
 * =====================================================================================
 */


#ifndef  Distractor_INC
#define  Distractor_INC

#include "Globals.h"

void switchOnDistractor( unsigned long current_time, const int pin )
{
    digitalWrite( pin, HIGH );
    delay( distractorOnTime );
    digitalWrite( pin, LOW );
    delay( distractorOffTime );
}

#endif   /* ----- #ifndef Distractor_INC  ----- */
