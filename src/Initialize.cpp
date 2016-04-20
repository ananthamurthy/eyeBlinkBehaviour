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

// Code
#include "Globals.h"
#include "LCDRelated.h"
#include "Initialize.h"
#include "Solenoid.h"
#include <avr/wdt.h>


extern String mouseName;
extern int session;
extern boolean start;
extern int totalTrials;

int traceTime;
int sessionType_ind;

/**
 * @brief Wait for delay milliseconds for read. If no data appears in this time,
 * return.
 *
 * NOTE: This means the if writing to a serial port, always put delay less than a
 * second. Probably 0.1 second is a good value (see write_msg in python script).
 *
 * @param delay, unsigned int. For that much time we should wait.
 */
bool wait_for_read( unsigned long delay )
{
    unsigned long tstart = millis();
    while( ! Serial.available() )
    {
        if( (millis() - tstart) > delay )
            return false;
    }
    // Got something within delay.
    return true;
}

/**
 * @brief Initialize watchdog timer.
 */
void watchdog_setup( void )
{
    // Set the timer to 2 sec.
    wdt_enable( WDTO_2S );
    wdt_reset();
}

/**
 * @brief Interrupt serviving routine.
 *
 * @param _vect
 */
ISR(WDT_vect)
{
    // Handle interuppts here.
    // Nothing to handle.
}

int initialize()
{
    reboot_ = false;

    /*
     * Keep sending question onto serial port every second.
     */
    while(true)
    {
        reset_watchdog();
        Serial.println("?? Please enter the mouse ID number: ");
        if( wait_for_read( 1000 ))
        {
            // Probably answer to our question.
            String answer = Serial.readString();
            if( answer.toInt() == 0 ) // Mouse name can't be zero
                Serial.println("!! Expected a positive interger.");
            else
            {
                mouseName = "MouseK" + answer;
                Serial.println("-> Got mouse name: #" + mouseName);
                break;
            }
        }
    }

    while(true)
    {
        reset_watchdog();
        Serial.println("?? Please enter the session type index: ");
        if( wait_for_read( 1000 ))
        {
            // Probably answer to our question.
            String answer = Serial.readString();
            sessionType_ind = answer.toInt();
            Serial.println("-> Got session Type: " + String(sessionType_ind));
            break;
        }
    }

    while(true)
    {
        reset_watchdog();
        Serial.println("?? Please enter the session number: ");
        if( wait_for_read( 1000 ))
        {
            // Probably answer to our question.
            String answer = Serial.readString();
            if( answer.toInt() == 0 ) // Session number can't be zero
                Serial.println("!! Expected a positive interger.");
            else
            {
                session = answer.toInt();
                Serial.println("-> Got session :" + answer);
                break;
            }
        }
    }

    while(true)
    {
        reset_watchdog();
        Serial.println("?? Please specify if you want to flip CS+/CS- (0/1): ");
        if( wait_for_read( 1000 ) )
        {
            String answer = Serial.readString();
            if( answer.toInt() == 0)
            {
                flipped_ = false;
                Serial.println("-> Got flipped = false");
            }
            else
            {
                flipped_ = true;
                Serial.println("-> Got flipped = true");
            }
            break;
        }
    }

    while(true)
    {
        reset_watchdog();
        Serial.println("?? Please specify CS Fraction (0, 10): ");
        if( wait_for_read( 1000 ) )
        {
            CS_fraction = Serial.readString().toInt();
            Serial.println("-> CS Fraction = " + String(CS_fraction) );
        }
        break;
    }

    Serial.println("|| Please press the SELECT button to begin!");
    startT = millis();

    // I should also be able to trigger that loop by writing START to serial
    // port.
#ifdef ENABLE_LCD
    while (read_lcd_button() != btnSELECT)
#else
    while(true)
#endif
    {
        reset_watchdog();

        if (startT > sampleInterval)
        {
            blink = analogRead(blink_ai);
            // Since this is not timestamped data, send 0 as timestamp.
            // NOTE: Can't use -1 since it is unsigned long.
            write_data_line( blink, 0 );
            startT = millis();
        }
        // Read the character and decide what to do.
        if( is_command_read( CS_PLUS_COMMAND , false) )
        {
            Serial.println("COMMAND: Play CS1");
            tone( tonePin, CS_TONE_1);
            delay( CSTime );
            noTone( tonePin );
        }
        else if( is_command_read( CS_MINUS_COMMAND, false) )
        {
            Serial.println("COMMAND: Play CS2");
            if( sessionType_ind % 2 == 0 )
            {
		tone( tonePin, CS_TONE_2);
                delay( CSTime );
                noTone( tonePin );
 	    }
            else
            {
		digitalWrite( ledPin, HIGH);
                delay( CSTime );
                digitalWrite( ledPin, LOW );                
            }
        }
        else if( is_command_read( PUFF_COMMAND, false ) ) // Puff
        {
            Serial.println("COMMAND: Play puff");
            playPuff(puff_do, HIGH);
            delay(puffTime);
            playPuff(puff_do, LOW);
        }
        else if( is_command_read( SELECT_COMMAND, true ) )
        {
            Serial.println("COMMAND: SELECT");
            break;
        }

    }

    // From here, the Arduino will start running the behaviour
    startT = millis();
    start = 1;

#ifdef ENABLE_LCD
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
#endif

    // Get totalTrials and traceTime based on the Session Type
    
   // if ((sessionType_ind == 0) || (sessionType_ind == 1) || (sessionType == 2) || (sessionType == 3) || (sessionType_ind == 4) || (sessionType_ind == 5)) //control (no-puff)
    if (sessionType_ind <= 5)
    {
        totalTrials = 41;
        if ((sessionType_ind == 0) || (sessionType_ind == 1))
            traceTime = 0;
        else if ((sessionType_ind == 2) || (sessionType_ind == 3))
            traceTime = 250;
        else
            traceTime = 500;
    }
    else
    {
        totalTrials = 101;
       // if ((sessionType_ind == 6) || (sessionType_ind == 7) ) //delay
        if (sessionType_ind <=7)
            traceTime = 0; //in ms
        //else if ((sessionType_ind == 8) || (sessionType_ind == 9)) //trace = 350 ms
        else if (sessionType_ind >7 && sessionType_ind <=9)
            traceTime = 250; //in ms
        else //(sessionType_ind>9 && sessionType_ind<=11) //trace = 350 ms
            traceTime = 500; //in ms
    }
    return sessionType_ind;
    return traceTime;
}
