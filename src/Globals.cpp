#include "Globals.h"
#include <avr/wdt.h>

bool reboot_ = false;
// This must be default to 0. It is set to 1 with some probablity (most likely
// to be 0.5).
bool CS_plus = 0;
int trialNum = 0;

// Only reset watchdog when glob reset_ is false. Else let watchdog reboot the
// board.
void reset_watchdog( )
{
    if( not reboot_ )
        wdt_reset();
}

void write_data_line( int data, unsigned long timestamp )
{

#if 1
    char msg[40];
    sprintf(msg, "%6lu,%5d,%3d,%2d\n", timestamp, data, trialNum, CS_plus);
    Serial.print(msg);
#else
    // This always works as expected. But many call to print. Above is better
    // (make sure to pass correct arguments.
    Serial.print( String(timestamp));
    Serial.print("," + String(data));
    Serial.print("," + String(trialNum));
    Serial.print("," + String(CS_plus));
    Serial.print("\n");
#endif

}
