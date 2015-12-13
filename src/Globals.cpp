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
    Serial.println("@" + String(timestamp) 
            + ",V=" + String(data) 
            + ",T=" + trialNum 
            + ",CS=" + String(CS_plus)
            ); 
}
