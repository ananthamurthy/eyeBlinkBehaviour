#include "Globals.h"
#include "VideoTrigger.h"

void videoTrigger()
{
    digitalWrite(videoTrigger_do, HIGH)
    if ( currentPhaseTime - lastTime > sampleInterval )
    {
        digitalWrite(triggerPin, LOW)
        lastTime += sampleInterval;
    }
}
