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
