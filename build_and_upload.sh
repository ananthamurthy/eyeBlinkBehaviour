#!/bin/bash
# First argument is optional. It is path to serial port. If not given, a port is
# detected automatically for you.
MAKE=make
if [ $1 ]; then
    echo "Using user input for serial: $1"
    MAKE="make MONITOR_PORT=$1"
else
    MAKE=make
fi
$MAKE 
$MAKE upload
