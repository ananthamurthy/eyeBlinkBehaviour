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
#include "LCDRelated.h"

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
#include "Distractor.h"

#ifdef ENABLE_LCD
#include "LCDRelated.h"
#endif

// Globals:
int blink                      = 0;
const int blink_ai             = A5;        // pin that reads the blinks
const int imagingTrigger_do    = 13;        // pin that triggers imaging
const int puff_do              = 11;
const int tonePin              = 2;         // changed this on 20150807
const int ledPin               = 3;         // added on 20160127

int blinkCount                 = 0;         // Code
unsigned long startT;
String mouseName               = String(1); // Please enter the name of the mouse

int session                    = 1;
extern int traceTime;                       // in ms
int totalTrials                = 100;
int shutterDelay               = 60;        // in ms

boolean profilingDataDump      = 0;         // For dumping profiling data

// Protocol Information
const int preTime              = 5000;      // in ms
int CSTime                     = 100;       // in ms //changed on 20160423, for Distractor training where one needs 50ms CS times.
const int puffTime             = 50;        // in ms //change made on 20151214
const int postTime             = 5000;      // in ms
const int minITI               = 15000;     // in ms
const int randITI              = 5000;      // in ms

// Time of distractor / LED or tone.
int distractorOnTime     = 100;
int distractorOffTime    = 250;

////For session 12
//
//if (sessionType_ind == 12)
//{  CSTime = 50;                            // in ms
//}


// Miscellaneous Initialisations
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

    //Set up the LED pin:
    pinMode(ledPin, OUTPUT);

#ifdef ENABLE_LCD
    // Initialize LCD
    lcd.begin( 16, 2 );

    lcd.setCursor(4, 1);
    lcd.print("PRESS SELECT");
#endif

    //For randomizations
    randomSeed( analogRead( blink_ai ) ); // 0 -> use system clock to generate random seed the CS type for trials

    nextProbeIn = (int) random(8,13); //NOTE: the "(int)" only truncates
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

        // Lookout for the pause button.
        if( ! paused_ )
        {
            if( is_command_read( PAUSE_COMMAND, true))
            {
                Serial.println("COMMAND: Pause");
                paused_ = true;
            }
        }



        if (trialNum == 0)
        {
            startPhaseTime = millis();
            startTrialTime = millis();
            trialNum = 1;
            // Switch ON the imaging trigger
            triggerImaging(imagingTrigger_do, HIGH);
#ifdef ENABLE_LCD
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


            // Shriya's session types.
            if (sessionType_ind >= 12 && sessionType_ind <= 18) 
            {

              //All the session types involving a distractor. 
              //The first 20 trials are always CS+ to establish learning and baseline. From trial 21, it is randomized to play distractors in 80% of the trials.
              
                if (sessionType_ind >= 16)   
                {
                }
                else
                    CS_plus = 1;

              
                //To expand or minimize the trace interval after the 20th trial.
                
                if (trialNum > 20)  
                {
                    if (sessionType_ind == 14)
                        traceTime = 250;

                    if (sessionType_ind == 15)
                        traceTime = 500;
                }
            }

            switch ( condition )
            {
            // PRE
            case 0:
                sprintf(status_, "PRE_");
                PF((condition+1));
                detectBlinks();
                //Serial.println("StartPre");


                // The distractoor switched on in the Pre-tone Phase and remains on till Trace begins.
                // Session Type 17 and 18 and Distractor sessions.
                
                if ((sessionType_ind == 17) && (CS_plus == 1))
                  {
                    switchOnDistractor( currentTime, tonePin );
                  }

                else if ((sessionType_ind == 18) && (CS_plus == 1))
                  {
                     switchOnDistractor( currentTime, ledPin  );
                  }
                            
                if (currentPhaseTime >= preTime)
                
                {  //Serial.println("EndPre");

                    if (sessionType_ind == 17)
                    { digitalWrite(ledPin, HIGH);
                    }
                    else if (sessionType_ind >= 12 && sessionType_ind <= 18) 
                    {
                        tone( tonePin, CS_TONE_1);
                                //digitalWrite( tonePin, HIGH );
                                //Serial.print("even ST: CS-=Tone1");
                     }
                        changePhase(1, START_CS_PLUS);
                 }
                break;

            //CS+
            case 1:
                sprintf(status_, "CS_P")
                PF((condition+1));
                detectBlinks();
                //Serial.println("StartCS+");

                if (currentPhaseTime >= CSTime)
                { //Serial.println("EndCS+");
                    shutoff_cs( tonePin, ledPin );

                    
                   //Session Type 16 is where CS and Distractor are both tones. Not using this right now.
                   
                    if( sessionType_ind == 16 && CS_plus == 1)
                    {
                         {
                            delay (100);
                            tone (tonePin, CS_TONE_1);
                            status_="DIST";
                            //Serial.println("Distractor!");             //For verification
                            delay (CSTime);
                            shutoff_cs(tonePin, ledPin);
                        }
                    }

                    changePhase( 3, START_TRACE );
                }
                break;

            //CS-
            case 2:
                sprintf(status_,  "CS_M");
                PF((condition+1));
                detectBlinks();
                //Serial.println("StartCS-");

                if (currentPhaseTime >= CSTime)
                { //Serial.println("EndCS-");
                    shutoff_cs( tonePin, ledPin );
                    changePhase( 3, START_TRACE );
                }
                break;

            //Trace
            case 3:
                sprintf(status_, "TRAC");
                PF((condition+1));
                detectBlinks();

//                if ((sessionType_ind == 17) && (CS_plus == 1))
//                  digitalWrite (ledPin, LOW);
//                else if ((sessionType_ind == 18) && (CS_plus == 1))  
//                  digitalWrite (ledPin, LOW);

                  
                //Serial.println("StartTrace");

                if (currentPhaseTime >= traceTime)
                {   //Serial.println("EndTrace");
                    //Serial.print("Trace=");                              //For verification
                    //Serial.println(traceTime);
                    // start the next phase
                    if ((sessionType_ind >= 6) && (sessionType_ind != 12))
                    {
                        if ((CS_plus == 1) || (sessionType_ind == 16))
                        {
                            if (nextProbeIn != 0)
                            {
                                playPuff(puff_do, HIGH);
                                //Serial.println("PuffON");
                                changePhase( 4, START_US );    // US: Air-puff
                            }
                            else
                            {
                                playPuff(puff_do, LOW);
                                nextProbeIn = (int) random(8,13); //NOTE: the "(int)" only truncates
                                changePhase(5, START_US_NO_PUFF);
                            }
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
                        //Serial.println("NoPuff");
                        // US: Air- no puff
                        changePhase( 5, START_US_NO_PUFF );
                    }
                }
                break;

            //Puff
            case 4:
                sprintf( status_, "PUFF" );
                PF((condition+1));
                detectBlinks();
                if (currentPhaseTime >= puffTime)
                {
                    // start the next phase
                    playPuff(puff_do, LOW);
                    //Serial.println("PuffOFF");
                    // Post pairing/stimuli
                    changePhase( 6, START_POST );
                }
                break;

            //No-Puff
            case 5:
                sprintf(status_, "NPUF");
                PF((condition+1));
                detectBlinks();
                if (currentPhaseTime >= puffTime)
                {   //Serial.println("NONOPuff");
                    // start the next phase
                    playPuff(puff_do, LOW);
                    // Post pairing/stimuli
                    changePhase( 6, START_POST );
                }
                break;

            //Post-Stim
            case 6:
                sprintf(status_, "POST");
                // Post Pairing/Stimuli
                PF((condition+1));
                detectBlinks();
                //Serial.println("StartPost");
                if (currentPhaseTime >= postTime)
                {
                    interTrialTime = minITI + random( randITI );
                    //Serial.println("EndPost");
                    changePhase( 7, START_ITI );

                    // Switch OFF the imaging trigger
                    triggerImaging(imagingTrigger_do, LOW);
                }
                break;

            //ITI
            case 7:
                // Inter trial interval
                sprintf(status_, "ITI_");
                PF((condition+1));
                //Serial.println("StartITI");
                if (paused_)
                {
                    changePhase( 9, PAUSE );
                    break;
                }
                else
                {
                    if (currentPhaseTime >= interTrialTime)
                    {   //Serial.println("EndITI");
                        Serial.println(trialNum);
                        trialNum++;
                        trialTime = 0;
                        blinkCount = 0;
                        if (trialNum > totalTrials)
                        {
                            changePhase( 8, END );                 // END of session
                            break;
                        }
                        else
                        {
                            if (random(10) <= CS_fraction)         // function random is exclusive, meaning, to generate random numbers between 0 to 10, one should use random(11).
                                CS_plus = 1;                       // play CS+
                            else
                                CS_plus = 0;                       // play CS-

#ifdef ENABLE_LCD
                            printStatus(START_PRE, trialNum);
#endif
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
                sprintf(status_, "EOS_");
                if (profilingDataDump == 1)
                {
                    profilingDataDump = 0;
                }
                // has the microcontroller on indefinite hold
                while(1);
                break;

            case 9:
#ifdef ENABLE_LCD
                //PAUSE
                int unpause_key = read_lcd_button();
                if (unpause_key == btnLEFT)
                {
                    pause = 0;
                    changePhase( 7, PAUSE );
                    break;
                }
#else
                if( is_command_read( UNPAUSE_COMMAND, true) )
                {
                    paused_ = false;
                    Serial.println("COMMAND: Unpause");
                    changePhase( 7, START_ITI );
                }
#endif
                break;
            }

        }

    }

}
