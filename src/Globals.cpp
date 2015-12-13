#include "Globals.h"
#include <avr/wdt.h>

bool reboot_ = false;

// Only reset watchdog when glob reset_ is false. Else let watchdog reboot the
// board.
void reset_watchdog( )
{
    if( not reboot_ )
        wdt_reset();
}
