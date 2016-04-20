#include "Globals.h"
#include <avr/wdt.h>

bool reboot_ = false;
bool paused_ = false;
bool flipped_ = false;

// This must be default to 0. It is set to 1 with some probablity (most likely
// to be 0.5).
bool CS_plus = 0;
int trialNum = 0;
int prevTwoTrials[2] = { 0, 0 };
int nextProbeIn = 0;
unsigned int CS_fraction = 8;

String status = "000";

// Only reset watchdog when glob reset_ is false. Else let watchdog reboot the
// board.
void reset_watchdog( )
{
    if( not reboot_ )
        wdt_reset();
}

void write_data_line( int data, unsigned long timestamp )
{
    char msg[40];

    prevTwoTrials[0] = prevTwoTrials[1];
    prevTwoTrials[1] = trialNum;
    
    // If a new trial starts and CS_plus is true, then reduce the nextProbeIn by
    // 1.
    if( prevTwoTrials[1] > prevTwoTrials[0] && CS_plus )
        nextProbeIn -= 1;

    sprintf(msg, "%6lu,%5d,%3d,%3d,%2d,%2d", timestamp, data, trialNum
            , totalTrials , CS_plus, nextProbeIn
            );
    Serial.println(msg);
    //Serial.print(status + ":" + msg);
}

/**
 * @brief Returns true if a given command is on serial port. All commands must
 * be prefix-free.
 *
 * @param command
 *
 * @return  true if command is found else false.
 */
bool is_command_read( char* command, bool consume )
{
    // Peek for the first character.
    int firstChar = command[0];
    if( ! Serial.available() )
        return false;

    // Serial.println( "Expected " + String( firstChar ));
    // Serial.println( "Got " + String(Serial.peek()) );
    if( firstChar == Serial.peek( ) )
    {
        // If character exists, then find the whole command.
        if( Serial.find( command ) )
            return true;
    }
    
    // consume the character. We must consume the character when there is no
    // alternate rule matching.
    if(consume)
        Serial.read();
    return false;
}

/**
 * @brief Check if the pause is recieved.
 */
void check_for_pause( void )
{
    if ( is_command_read( PAUSE_COMMAND, true ) )
    {
        Serial.println("COMMAND: Pause");
        paused_ = true;
    }
}

void shutoff_cs( unsigned tonePin, unsigned ledPin )
{
    // start the next phase
    noTone(tonePin);
    digitalWrite( ledPin, LOW);
}

