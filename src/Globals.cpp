#include "Globals.h"
#include <avr/wdt.h>

bool reboot_ = false;
// This must be default to 0. It is set to 1 with some probablity (most likely
// to be 0.5).
bool CS_plus = 0;
int trialNum = 0;

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
    sprintf(msg, "%6lu,%5d,%3d,%2d", timestamp, data, trialNum, CS_plus);
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

    if( firstChar == Serial.peek( ) )
    {
        // If character exists, the find the whole command.
        if( Serial.find( command ) )
            return true;
    }
    
    // consume the character. We must consume the character when there is no
    // optional parsing.
    if(consume)
        Serial.read();
    return false;
}
