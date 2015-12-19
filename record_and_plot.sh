#!/bin/bash
if [ $# -lt 1 ]; then
    python ./python/arduino_live -h 
    exit
fi
(
    python ./python/arduino_live "$@"  
)
