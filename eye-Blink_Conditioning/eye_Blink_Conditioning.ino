//
// eye-Blink_Conditioning
//
// Trace Eye Blink Conditioning with a simple solenoid driver
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author 		Kambadur Ananthamurthy
// 				Kambadur Ananthamurthy
//
// Date			04/08/15 1:35 pm
// Version		<#version#>
//
// Copyright	© Kambadur Ananthamurthy, 2015
// Licence		<#license#>
//
// See         ReadMe.txt for references
//


// Core library for code-sense - IDE-based
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(LITTLEROBOTFRIENDS) // LittleRobotFriends specific
#include "LRF.h"
#elif defined(MICRODUINO) // Microduino specific
#include "Arduino.h"
#elif defined(SPARK) || defined(PARTICLE) // Particle / Spark specific
#include "application.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(REDBEARLAB) // RedBearLab specific
#include "Arduino.h"
#elif defined(ESP8266) // ESP8266 specific
#include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

/*
 INSTRUCTIONS: (Skip 1 and 2 if already performed)
 1. Hook the arduino up to a usb port
 2. Verify/Compile the code and upload to the arduino
 3. Run the python code to send in the session details and start reading data
 4. ONLY THEN, press SELECT on the Arduino's LCD to begin the session.
 NOTE: Pressing SELECT is going to start the trial whether or not the session details or data have been read
 */

/*
 GENERAL NOTE: All codes to be uploaded to the Arduino, cycle through "void loop()" at some refresh rate.
 Basically calculations, assignments, etc. can be executed every cycle, if specified as such.
 */

/*
 TRACE EYE-BLINK CONDITIONING:
 >> Associate a tone with the eye-blink response.
 >> The US is an air-puff to the eye.
 >> 5 s Pre-tone, 350 ms CS+/-, 100 ms US/No-US, Post-stim (till 20s trial).
 >> ITI (randomized between 20-30 s). // Will have to check if randomization
 is the best option.
 
 The following is the trainning logic for running behaviour with head-fixed
 mice, using assorted solenoids and an eye-blink sensor.
 The code reports the current state on LCD screen, pushes output through a
 simple solenoid driver circuit and transfers data to a serial port.
 */

//For Profiling Purpose:
#include <avr/interrupt.h>
#include <avr/io.h>
#include <HardwareSerial.h>

// this can be used to turn profiling on and off
#define PROFILING 1
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

// Arduino runs at 16 Mhz, so we have 1000 overflows per second...
// this ISR will get hit once a millisecond
ISR(TIMER2_OVF_vect) {
    
    int_counter++;
    if (int_counter == 1000) {
        seconds++;
        int_counter = 0;
        if(seconds == 60) {
            seconds = 0;
            minutes++;
        }
    }
#if PROFILING
    prof_array[prof_line]++;
#endif
    TCNT2 = tcnt2;  // reset the timer for next time
}

// Timer setup code borrowed from Sebastian Wallin
// http://popdevelop.com/2010/04/mastering-timer-interrupts-on-the-arduino/
// further borrowed from: http://www.desert-home.com/p/super-thermostat.html
void setupTimer (void) {
    //Timer2 Settings:  Timer Prescaler /1024
    // First disable the timer overflow interrupt while we're configuring
    TIMSK2 &= ~(1<<TOIE2);
    // Configure timer2 in normal mode (pure counting, no PWM etc.)
    TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
    // Select clock source: internal I/O clock
    ASSR &= ~(1<<AS2);
    // Disable Compare Match A interrupt enable (only want overflow)
    TIMSK2 &= ~(1<<OCIE2A);
    
    // Now configure the prescaler to CPU clock divided by 128
    TCCR2B |= (1<<CS22)  | (1<<CS20); // Set bits
    TCCR2B &= ~(1<<CS21);             // Clear bit
    
    /* We need to calculate a proper value to load the timer counter.
     * The following loads the value 131 into the Timer 2 counter register
     * The math behind this is:
     * (CPU frequency) / (prescaler value) = 125000 Hz = 8us.
     * (desired period) / 8us = 125.
     * MAX(uint8) - 125 = 131;
     */
    /* Save value globally for later reload in ISR */
    tcnt2 = 131;
    
    /* Finally load end enable the timer */
    TCNT2 = tcnt2;
    TIMSK2 |= (1<<TOIE2);
    sei();
}

// Include application, user and local libraries
#include "Globals.h"
#include "LCDRelated.h"
#include "DetectBlinks.h"
#include "Solenoid.h"

//Globals:
int blink = 0;
const int blink_ai = A5;    // pin that reads the blinks
const int puff_do = 11;
int blinkCount = 0;// Code
unsigned long startT;

//Locals:
//Some Initialization: To get Session Details - These will all get edited if there is serial input
int userInput[3];
String mouseName = String(1); //Please enter the name of the mouse
int sessionType_ind = 1; //Please specify the Session Type (0: Control, 1: Trace, 2: Delay)
int session = 1;
int traceTime = 250; //in ms

const int tonePin = 3; //changed this on 20150807

boolean profilingDataDump = 0; // For dumping profiling data

//Protocol Information
const int totalTrials = 10;
const int preTime = 1000; //in ms
const int CSTime = 1000; //in ms
const int puffTime = 1000; //in ms
const int postTime = 1000; //in ms
const int minITI = 1000; //in ms
const int randITI = 1000; //in ms

// CS+/- frequencies
const int CS_PLUS_ToneFreq = 9500;
const int CS_MINUS_ToneFreq = 4000; //change made on 20150826

// Miscellaneous Initializations
int condition = 0;
boolean pause = 0 ;
unsigned long startPhaseTime;
unsigned long startTrialTime;
unsigned long currentPhaseTime = 0;
int interTrialTime = 0;
int trialNum = 0;
boolean CS_plus = 1;
boolean start = 0;

void setup()
{
    //Profiling related
#if PROFILING
    PF(0);
    prof_has_dumped = 0;
    clear_profiling_data();
#endif
    
    // Initialize the serial port
    Serial.begin(9600);
//    Serial.println("#setup()");
    
    int_counter = 0;
    seconds = 0;
    minutes = 0;
    
//    Serial.println("#setupTimer()");
    setupTimer();
    
    // Set up the puff port:
    pinMode(puff_do, OUTPUT);
    
    // Initialize LCD
    lcd.begin( 16, 2 );
    
    //     lcd.setCursor( 0, 0 );
    //     lcd.print("Press SELECT");
    //     lcd.setCursor( 0, 1 );
    //     lcd.print(" to start");
    //
    //     lcd.setCursor( 0, 1 );
    //     lcd.print("S");
    //     lcd.setCursor(1, 1);
    //     lcd.print(session);
    //     lcd.setCursor( 4, 1 );
    //     lcd.print("T");
    //
    //     lcd.setCursor( 0, 0 );
    //     lcd.print(mouseName);
    //
    //     lcd.setCursor(8, 0);
    //     lcd.print(sessionType[sessionType_ind]);
    
    lcd.setCursor(4, 1);
    lcd.print("PRESS SELECT");
}

void loop()
{
    // Press "Select" to start Session
    if (start == 1)
    {
    }
    else
    {
        Serial.print("#Mouse Name: ");
        while(!Serial.available());
        mouseName = "MouseK" + String(Serial.readString().toInt());
        Serial.println(mouseName);
        
        Serial.print("#Session Type Index: ");
        while(!Serial.available());
        sessionType_ind = Serial.readString().toInt();
        Serial.println(sessionType_ind);

        Serial.print("#Session: ");
        while(!Serial.available());
        session = Serial.readString().toInt();
        Serial.println(session);
        
        Serial.println("#Press the SELECT buttbon!");
        
        // From here, the Arduino will start running the behaviour
        while(read_lcd_button() != btnSELECT);

        startT = millis();
        start = 1;
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
        Serial.println("@");
        //Serial.print(trialNum);
        Serial.println("1 1"); // Just to not confuse data saving
        Serial.println("[");
        
        // Get traceTime based on the Session Type
        if (sessionType_ind == 2)
        {
            traceTime = 0; //in ms
        }
        else
        {
            traceTime = 250; //in ms
        }
        
        
    }
    while (start == 1)
    {
        if (trialNum == 0)
        {
            startPhaseTime = millis();
            startTrialTime = millis();
            trialNum = 1;
        }
        else
        {
            unsigned long currentPhaseTime = millis() - startPhaseTime; // has to be calculated for every loop
            unsigned long currentTime = millis() - startTrialTime; // has to be calculated for every loop
            
            // Pause //
            int lcd_key = read_lcd_button();
            if (lcd_key == btnRIGHT)
            {
                pause = 1;
            }
            switch ( condition )
            {
                case 0: // PRE
                    PF((condition+1));
                    //Serial.println("Case0");
                    detectBlinks();
                    printStatus(START_PRE, trialNum);
                    if (currentPhaseTime >= preTime)
                    {
                        //start the next phase
                        if (CS_plus == 1)
                        {
                            condition = 1; //CS+
                            tone( tonePin, CS_PLUS_ToneFreq );
                        }
                        else
                        {
                            condition = 2; //CS-
                            tone( tonePin, CS_MINUS_ToneFreq );
                        }
                        startPhaseTime = millis();
                    }
                    break;
                    
                case 1: // CS+
                    PF((condition+1));
                    //Serial.println("Case1");
                    detectBlinks();
                    printStatus(START_CS_PLUS, trialNum);
                    if (currentPhaseTime >= CSTime)
                    {
                        //start the next phase
                        condition = 3; //Trace
                        noTone(tonePin);
                        startPhaseTime = millis();
                    }
                    break;
                    
                case 2: // CS-
                    PF((condition+1));
                    //Serial.println("Case2");
                    detectBlinks();
                    printStatus(START_CS_MINUS, trialNum);
                    if (currentPhaseTime >= CSTime)
                    {
                        condition = 3; //Trace
                        noTone(tonePin);
                        startPhaseTime = millis();
                    }
                    break;
                    
                case 3: // trace
                    PF((condition+1));
                    //Serial.println("Case3");
                    detectBlinks();
                    printStatus(START_TRACE, trialNum);
                    
                    if (currentPhaseTime >= traceTime)
                    {
                        //start the next phase
                        if (sessionType_ind != 0)
                        {
                            if (CS_plus == 1)
                            {
                                playPuff(puff_do, HIGH);
                                condition = 4; //US: Air-Puff
                                startPhaseTime = millis();
                            }
                            else
                            {
                                playPuff(puff_do, LOW);
                                condition = 5; //US: Air-Puff
                                startPhaseTime = millis();
                            }
                        }
                        else
                        { //control case (No-Puff)
                            playPuff(puff_do, LOW);
                            condition = 5; //US: Air-Puff
                            startPhaseTime = millis();
                        }
                    }
                    break;
                    
                case 4: // Puff (US)
                    PF((condition+1));
                    //Serial.println("Case4");
                    detectBlinks();
                    printStatus(START_US, trialNum);
                    if (currentPhaseTime >= puffTime)
                    {
                        //start the next phase
                        playPuff(puff_do, LOW);
                        condition = 6; //Post Pairing/Stimuli
                        startPhaseTime = millis();
                    }
                    break;
                    
                case 5: // No-Puff
                    PF((condition+1));
                    //Serial.println("Case5");
                    detectBlinks();
                    printStatus(START_US_NO_PUFF, trialNum);
                    if (currentPhaseTime >= puffTime)
                    {
                        //start the next phase
                        playPuff(puff_do, LOW);
                        condition = 6; //Post Pairing/Stimuli
                        startPhaseTime = millis();
                    }
                    break;
                    
                case 6: // Post Pairing/Stimuli
                    PF((condition+1));
                    //Serial.println("Case6");
                    detectBlinks();
                    printStatus(START_POST, trialNum);
                    if (currentPhaseTime >= postTime)
                    {
                        condition = 7; //ITI
                        interTrialTime = minITI + random( randITI );
                        startPhaseTime = millis();
                    }
                    break;
                    
                case 7:// Inter trial interval
                    PF((condition+1));
                    if (pause == 1)
                    {
                        printStatus(PAUSE, trialNum);
                        condition = 9;
                        break;
                    }
                    else
                    {
                        //Serial.println("Case7");
                        printStatus(START_ITI, trialNum);

                        if (currentPhaseTime >= interTrialTime)
                        {
                            trialNum++;
//                            Serial.print("Blink Count = ");
//                            Serial.println(blinkCount);
                            blinkCount = 0;
                            if (trialNum > totalTrials)
                            {
                                condition = 8; //End of Session
                                Serial.println("@");
                                break;
                            }
                            else
                            {
                                condition = 0;
                                Serial.println("]")
                                Serial.println("@");
                                
                                if (random(10) >= 5) //change made on 20150826
                                {
                                    CS_plus = 1; //play CS+
                                    Serial.print(trialNum)
                                    Serial.println(" 1")
                                }
                                else
                                {
                                    CS_plus = 0; //play CS-
                                    Serial.print(trialNum)
                                    Serial.println(" 0")
                                }
                                
                                startPhaseTime = millis();
                                startTrialTime = millis();
                            }
                        }
                        break;
                    }
                    
                case 8: // End of session
                    //Serial.println("Case8");
                    printStatus(END, (trialNum-1)); // No need to change the trial number on LCD screen
                    if (profilingDataDump == 0)
                    {
                        Serial.println("$");
                        Serial.println("[");
                        dump_profiling_data();
                        Serial.println("]");
                        profilingDataDump = 1;
                        
                        Serial.println(";"); //tells data saving to close everything.
                    }
                    break;
                    
                case 9:  // Pause
                    //Serial.println("Case9");
                    int unpause_key = read_lcd_button();
                    if (unpause_key == btnLEFT)
                    {
                        pause = 0;
                        condition = 7; // Goes to Pre-Tone
                        break; // Might be redundant
                        startPhaseTime = millis();
                    }
                    break; // goes to the specified phase and trial number
                    
            } // ends "switch (condition)"
            
        } // Ends actual Trial 1 to Total Trials
        
    } // ends "while (start == 1)"
    
} // ends void loop()
