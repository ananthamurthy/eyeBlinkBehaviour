//
// eye-Blink_Conditioning
//
// Trace Eye Blink Conditioning with a simple solenoid driver
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author 		Kambadur Ananthamurthy
//
// Date			04/08/15 1:35 pm
//
// Copyright	© Kambadur Ananthamurthy, 2015
//
// See  NOTES.md for developer notes.
//

//For Profiling Purpose:
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <HardwareSerial.h>

// this can be used to turn profiling on and off
#define PROFILING 0

// this needs to be true in at least ONE .c, .cpp, or .ino file in your sketch
#define PROFILING_MAIN 1

// override the number of bins
#define MAXPROF 30 //number of bins for profiler
#include "Profiling.h"

#define InterruptOff  do{TIMSK2 &= ~(1<<TOIE2)}while(0)
#define InterruptOn  do{TIMSK2 |= (1<<TOIE2)}while(0)

// stuff used for time keeping in our ISR
volatile unsigned int int_counter;
volatile unsigned char seconds, minutes;
unsigned int tcnt2; // used to store timer value

// Include application, user and local libraries
#include "Globals.h"
#include "Initialize.h"
#include "DetectBlinks.h"
#include "Solenoid.h"
#include "ChangePhase.h"
#include "TriggerImaging.h"

#if ENABLE_LCD
#include "LCDRelated.h"
#endif

// Globals:
int blink                      = 0;
const int blink_ai             = A5;        // pin that reads the blinks
const int imagingTrigger_do    = 13;        // pin that triggers imaging
const int puff_do              = 11;
const int tonePin              = 2;         // changed this on 20150807

int blinkCount                 = 0;         // Code
unsigned long startT;
String mouseName               = String(1); // Please enter the name of the mouse
int sessionType_ind            = 1;         // Please specify the Session Type (0: Control, 1: Trace, 2: Delay)
int session                    = 1;
int traceTime                  = 250;       // in ms
int totalTrials                = 100;
int shutterDelay               = 60;        // in ms

boolean profilingDataDump      = 0;         // For dumping profiling data

// Protocol Information
const int preTime              = 5000;      // in ms
const int CSTime               = 350;       // in ms
const int puffTime             = 50;        // in ms //change made on 20151214
const int postTime             = 5000;      // in ms
const int minITI               = 10000;     // in ms
const int randITI              = 5000;      // in ms

// CS+/- frequencies
const int CS_PLUS_ToneFreq     = 2000;
const int CS_MINUS_ToneFreq    = 7000;      // change made on 20151214

// Miscellaneous Initializations
int condition                  = 0;
boolean pause                  = 0 ;
unsigned long startPhaseTime;
unsigned long startTrialTime;
unsigned long currentPhaseTime = 0;
unsigned long lastTime         = 0;
unsigned short sampleInterval  = 10;        // Ten milliseconds for 100 Hz
unsigned int interTrialTime    = 0;

boolean start                  = 0;
boolean trialState             = 0;

void setup()
{
    //Profiling related
#if PROFILING
    PF(0);
    prof_has_dumped = 0;
    clear_profiling_data();
#endif

    // Initialize the serial port
    Serial.begin(38400);

    int_counter = 0;
    seconds = 0;
    minutes = 0;

    // Setup my watchdog.
    watchdog_setup();

    // Set up the trigger pin
    pinMode(imagingTrigger_do, OUTPUT);

    // Set up the puff pin:
    pinMode(puff_do, OUTPUT);

    //Set up the tone pin:
    pinMode(tonePin, OUTPUT);

#ifdef ENABLE_LCD
    // Initialize LCD
    lcd.begin( 16, 2 );

    lcd.setCursor(4, 1);
    lcd.print("PRESS SELECT");
#endif

    //For randomizations
    // uses the exact time of key press (expected to be different every time)
    randomSeed(startT);
}

void loop()
{
    // Press "Select" to start Session
    if (start != 1)
    {
        reboot_ = false;
        status = "001";
        initialize();
        reset_watchdog( );
    }

    while (start == 1)
    {
        status = "111";
        reset_watchdog( );

        // Seding rr will reset the arduino
        if( is_command_read( RESET_COMMAND,  true ))
        {
            reboot_ = true;
            Serial.println("+++ Software RESET in 2 seconds, puny human!");
            Serial.println("And there is nothing you can do. Ha Ha!");
        }

        if (trialNum == 0)
        {
            startPhaseTime = millis();
            startTrialTime = millis();
            trialNum = 1;
            // Switch ON the imaging trigger
            triggerImaging(imagingTrigger_do, HIGH);
#if ENABLE_LCD
            printStatus(START_PRE, trialNum);
#endif
        }
        else
        {
            // has to be calculated for every loop
            currentPhaseTime = millis() - startPhaseTime;
            // has to be calculated for every loop; not being used anywhere
            unsigned long currentTime = millis() - startTrialTime;

#ifdef ENABLE_LCD
            int lcd_key = read_lcd_button();
            if (lcd_key == btnRIGHT)
            {
                pause = 1;
            }
#endif

            switch ( condition )
            {
            // PRE
            case 0:
                PF((condition+1));
                detectBlinks();
                if (currentPhaseTime >= preTime)
                {
                    // start the next phase
                    if (CS_plus == 1)
                    {
                        tone( tonePin, CS_PLUS_ToneFreq);
#if ENABLE_LCD
                        changePhase( 1, START_CS_PLUS );           // CS+
#endif
                    }
                    else
                    {
                        tone( tonePin, CS_MINUS_ToneFreq );
#if ENABLE_LCD
                        changePhase( 2, START_CS_MINUS );          // CS-
#endif
                    }
                }
                break;

            case 1:                                                // CS+
                PF((condition+1));
                detectBlinks();
                if (currentPhaseTime >= CSTime)
                {
                    // start the next phase
                    noTone(tonePin);
#if ENABLE_LCD
                    changePhase( 3, START_TRACE );                 // Trace
#endif
                }
                break;

            case 2:                                                // CS-
                PF((condition+1));
                detectBlinks();
                if (currentPhaseTime >= CSTime)
                {
                    noTone(tonePin);
#if ENABLE_LCD
                    changePhase( 3, START_TRACE );                 // Trace
#endif
                }
                break;

            case 3:                                                // trace
                PF((condition+1));
                detectBlinks();
                if (currentPhaseTime >= traceTime)
                {
                    // start the next phase
                    if (sessionType_ind != 0)
                    {
                        if (CS_plus == 1)
                        {
                            playPuff(puff_do, HIGH);
                            condition = 4;                 // US: Air-Puff
#if ENABLE_LCD
                            changePhase( 4, START_US );    // US: Air-puff
#endif
                        }
                        else
                        {
                            playPuff(puff_do, LOW);
                            // US: Air- no puff
#if ENABLE_LCD
                            changePhase( 5, START_US_NO_PUFF );
#endif
                        }
                    }
                    else
                    {
                        // control case (No-Puff)
                        playPuff(puff_do, LOW);
                        // US: Air- no puff
#if ENABLE_LCD
                        changePhase( 5, START_US_NO_PUFF );
#endif
                    }
                }
                break;

            case 4:                                                // Puff (US)
                PF((condition+1));
                detectBlinks();
                if (currentPhaseTime >= puffTime)
                {
                    // start the next phase
                    playPuff(puff_do, LOW);
                    // Post pairing/stimuli
#if ENABLE_LCD
                    changePhase( 6, START_POST );
#endif
                }
                break;

            case 5:                                                // No-Puff
                PF((condition+1));
                detectBlinks();
                if (currentPhaseTime >= puffTime)
                {
                    // start the next phase
                    playPuff(puff_do, LOW);
                    // Post pairing/stimuli
#if ENABLE_LCD
                    changePhase( 6, START_POST );
#endif
                }
                break;

            case 6:
                // Post Pairing/Stimuli
                PF((condition+1));
                detectBlinks();
                if (currentPhaseTime >= postTime)
                {
                    interTrialTime = minITI + random( randITI );
#if ENABLE_LCD
                    changePhase( 7, START_ITI );                   // ITI
#endif

                    // Switch OFF the imaging trigger
                    triggerImaging(imagingTrigger_do, LOW);
                }
                break;

            case 7:
                // Inter trial interval
                PF((condition+1));
                if (pause == 1)
                {
#if ENABLE_LCD 
                    changePhase( 9, PAUSE );                       // PAUSE
#endif
                    break;
                }
                else
                {
                    if (currentPhaseTime >= interTrialTime)
                    {
                        trialNum++;
                        blinkCount = 0;
                        if (trialNum > totalTrials)
                        {
#if ENABLE_LCD
                            changePhase( 8, END );                 // END of session
#endif
                            break;
                        }
                        else
                        {
                            if (random(10) >= 5)
                                CS_plus = 1;                       // play CS+
                            else
                                CS_plus = 0;                       // play CS-

#ifdef ENABLE_LCD
                            printStatus(START_PRE, trialNum);
                            changePhase( 0, START_PRE );           // Next cycle
#endif

                            // Switch ON the imaging trigger
                            triggerImaging(imagingTrigger_do, HIGH);

                            startTrialTime = millis();
                        }
                    }
                    break;
                }

            // End of session
            case 8:                                                
                if (profilingDataDump == 1)
                {
                    profilingDataDump = 0;
                }
                // has the microcontroller on indefinite hold
                while(1);                                          
                break;

#ifdef ENABLE_LCD
            case 9:                                              
                int unpause_key = read_lcd_button();
                if (unpause_key == btnLEFT)
                {
                    pause = 0;
#if ENABLE_LCD
                    changePhase( 7, START_ITI );                   
#endif
                    break;                                        
                }
                break;                                             
#endif
            }                                                      

        }       

    }          

}             
