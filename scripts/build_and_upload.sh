#!/bin/bash
# First argument is optional. It is path to serial port. If not given, a port is
# detected automatically for you.

MAKE=`which make`
MAKE_PARAMS=""
case "$(uname -s)" in 
    Darwin)
        echo "Using mac"
        ;;
    Linux)
        echo "On Linux"
        ;;
    CYGWIN)
        echo "Cygwin+Windows";
        ;;
    *)
        echo "Unknown.Quitting";
        exit
        ;;
esac

if [ $1 ]; then
    echo "Using user input for serial: $1"
    MAKE_PARAMS="$MAKE_PARAMS MONITOR_PORT=$1"
fi
$MAKE $MAKE_PARAMS
$MAKE $MAKE_PARAMS upload
