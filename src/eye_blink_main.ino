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

// some handy macros for printing debugging values
#define DL(x) Serial.print(x)
#define DLn(x) Serial.println(x)
#define DV(m, v) do{Serial.print(m);Serial.print(v);Serial.print(" ");}while(0)
#define DVn(m, v) do{Serial.print(m);Serial.println(v);}while(0)

// more handy macros but unused in this example
#define InterruptOff  do{TIMSK2 &= ~(1<<TOIE2)}while(0)
#define InterruptOn  do{TIMSK2 |= (1<<TOIE2)}while(0)

// stuff used for time keeping in our ISR
volatile unsigned int int_counter;
volatile unsigned char seconds, minutes;
unsigned int tcnt2; // used to store timer value

// Include application, user and local libraries
#include "Globals.h"
#include "Initialize.h"
#include "LCDRelated.h"
#include "DetectBlinks.h"
#include "Solenoid.h"
#include "ChangePhase.h"
#include "TriggerImaging.h"

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

    // Initialize LCD
    lcd.begin( 16, 2 );

    lcd.setCursor(4, 1);
    lcd.print("PRESS SELECT");

    //For randomizations
    // uses the exact time of key press (expected to be different every time)
    randomSeed(startT);
}

void loop()
{
    // Press "Select" to start Session
    if (start != 1)
    {
        initialize();
        reset_watchdog( );
    }

    // Reset reboot_ flag.
    reboot_ = false;

    while (start == 1)
    {
        // Seding rr will reset the arduino
        if( Serial.available() )
        {
            if( 114 == Serial.peek() )
            {
                if( Serial.find("rr") )
                {
                    reboot_ = true;
                    Serial.println("+++ Software RESET in 2 seconds, puny human!");
                    Serial.println("And there is nothing you can do. Ha Ha!");
                    break;
                }
            }
        }
        else
            reset_watchdog();

        if (trialNum == 0)
        {
            startPhaseTime = millis();
            startTrialTime = millis();
            trialNum = 1;
            // Switch ON the imaging trigger
            triggerImaging(imagingTrigger_do, HIGH);
            printStatus(START_PRE, trialNum);
        }
        else
        {
            // has to be calculated for every loop
            currentPhaseTime = millis() - startPhaseTime;
            // has to be calculated for every loop; not being used anywhere
            unsigned long currentTime = millis() - startTrialTime;

            int lcd_key = read_lcd_button();
            if (lcd_key == btnRIGHT)
            {
                pause = 1;
            }

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
                        changePhase( 1, START_CS_PLUS );           // CS+
                    }
                    else
                    {
                        tone( tonePin, CS_MINUS_ToneFreq );
                        changePhase( 2, START_CS_MINUS );          // CS-
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
                    changePhase( 3, START_TRACE );                 // Trace
                }
                break;

            case 2:                                                // CS-
                PF((condition+1));
                detectBlinks();
                if (currentPhaseTime >= CSTime)
                {
                    noTone(tonePin);
                    changePhase( 3, START_TRACE );                 // Trace
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
                            changePhase( 4, START_US );    // US: Air-puff
                        }
                        else
                        {
                            playPuff(puff_do, LOW);
                            // US: Air- no puff
                            changePhase( 5, START_US_NO_PUFF );
                        }
                    }
                    else
                    {
                        // control case (No-Puff)
                        playPuff(puff_do, LOW);
                        // US: Air- no puff
                        changePhase( 5, START_US_NO_PUFF );
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
                    changePhase( 6, START_POST );
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
                    changePhase( 6, START_POST );
                }
                break;

            case 6:
                // Post Pairing/Stimuli
                PF((condition+1));
                detectBlinks();
                if (currentPhaseTime >= postTime)
                {
                    interTrialTime = minITI + random( randITI );
                    changePhase( 7, START_ITI );                   // ITI

                    // Switch OFF the imaging trigger
                    triggerImaging(imagingTrigger_do, LOW);
                }
                break;

            case 7:
                // Inter trial interval
                PF((condition+1));
                if (pause == 1)
                {
                    changePhase( 9, PAUSE );                       // PAUSE
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
                            changePhase( 8, END );                 // END of session
                            break;
                        }
                        else
                        {
                            if (random(10) >= 5)
                                CS_plus = 1;                       // play CS+
                            else
                                CS_plus = 0;                       // play CS-

                            printStatus(START_PRE, trialNum);
                            changePhase( 0, START_PRE );           // Next cycle

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

            case 9:                                              
                int unpause_key = read_lcd_button();
                if (unpause_key == btnLEFT)
                {
                    pause = 0;
                    changePhase( 7, START_ITI );                   
                    break;                                        
                }
                break;                                             
            }                                                      

        }       

    }          

}             
