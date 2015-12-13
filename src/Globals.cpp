#include "Globals.h"
#include <avr/wdt.h>

bool reboot_ = false;
bool CS_plus = 1;

// Only reset watchdog when glob reset_ is false. Else let watchdog reboot the
// board.
void reset_watchdog( )
{
    if( not reboot_ )
        wdt_reset();
}

void write_data_line( int data, unsigned long timestamp )
{
    char msg[30];
    sprintf(msg, "%4d,V=%4d,T=%2d,CS=%2d\n", timestamp, data, trialNum, CS_plus); 
    Serial.print(msg);
}
