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

const int tonePin = 10;

//Protocol Information
const int totalTrials = 10;
const int preTime = 5000; //in ms
const int CSTime = 350; //in ms
const int puffTime = 100; //in ms
const int postTime = 9300; //in ms
const int minITI = 15000; //in ms
const int randITI = 15000; //in ms

// CS+/- frequencies
const int CS_PLUS_ToneFreq = 9500;
const int CS_MINUS_ToneFreq = 15000;

// Miscellaneous Initializations
int condition = 0;
bool pause = 0 ;
unsigned long startPhaseTime;
unsigned long startTrialTime;
unsigned long currentPhaseTime = 0;
int interTrialTime = 0;
int trialNum = 0;
bool CS_plus = 1;
bool start = 0;

void setup()
{
    // Set up the puff port:
    pinMode(puff_do, OUTPUT);
    
    // Initialize serial communications:
    Serial.begin(9600);
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
        //Get session details
        for (int i = 0; i < 3; i++)
        {
            if (Serial.available() > 0)
            { // Checks for a character in the serial monitor
                userInput[i] = Serial.parseInt();
            }
        }
        mouseName = "MouseK" + String(userInput[0]);
        sessionType_ind = userInput[1];
        session = userInput[2];
        
        
        //        Serial.println(mouseName);
        //        Serial.println(sessionType_ind);
        //        Serial.println(session);
        
        // From here, the Arduino will start running the behaviour
        int startButton = read_lcd_button();
        if (startButton == btnSELECT)
        {
            startT = millis();
            start = 1;
            //Serial.println("Let's Go!");
            //delay(1);
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
            Serial.println(mouseName);
            Serial.print("Session");
            Serial.print(session);
            Serial.print(": ");
            Serial.println(sessionType[sessionType_ind]);
            Serial.println("@");
            Serial.print("Trial No. ");
            Serial.print("1"); // Just to not confuse data saving
            Serial.print(" :");
            Serial.println(" CS+ ");
            
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
        else
        {
            start = 0;
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
                    //Serial.println("Case7");
                    printStatus(START_ITI, trialNum);
                    //      Serial.print(currentPhaseTime);
                    //      Serial.print('\t');
                    //      Serial.println(interTrialTime);
                    if (currentPhaseTime >= interTrialTime)
                    {
                        trialNum++;
                        Serial.print("Blink Count = ");
                        Serial.println(blinkCount);
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
                            Serial.println("@");
                            
                            if (random(10) >= 6)
                            {
                                CS_plus = 1; //play CS+
                                Serial.print("Trial No. ");
                                Serial.print(trialNum);
                                Serial.print(":");
                                Serial.println(" CS+ ");
                            }
                            else
                            {
                                CS_plus = 0; //play CS-
                                Serial.print("Trial No. ");
                                Serial.print(trialNum);
                                Serial.print(":");
                                Serial.println(" CS- ");
                            }
                            
                            if (pause == 1)
                            {
                                printStatus(PAUSE, trialNum);
                                condition = 9;
                                break;
                            }
                            startPhaseTime = millis();
                            startTrialTime = millis();
                        }
                    }
                    break;
                    
                case 8: // End of session
                    //Serial.println("Case8");
                    printStatus(END, (trialNum-1)); // No need to change the trial number on LCD screen
                    break;
                    
                case 9:  // Pause
                    //Serial.println("Case9");
                    int unpause_key = read_lcd_button();
                    if (unpause_key == btnLEFT)
                    {
                        pause = 0;
                        condition = 0; // Goes to Pre-Tone
                        break; // Might be redundant
                    }
                    break; // goes to the specified phase and trial number
            } // ends "switch (condition)"
            
        } // Ends actual Trial 1 to Total Trials
        
    } // ends "while (start == 1)"
    
} // ends void loop()
