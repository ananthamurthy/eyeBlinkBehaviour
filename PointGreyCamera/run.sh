#!/bin/bash - 
#===============================================================================
#
#          FILE: run.sh
# 
#         USAGE: ./run.sh 
# 
#   DESCRIPTION:  This script run the acquisition.
#                 On user unterrupt, we send SIGINT to C++ binary which is the
#                 best way to cleaup the camera before shutting down.
# 
#        AUTHOR: Dilawar Singh (), dilawars@ncbs.res.in
#  ORGANIZATION: NCBS Bangalore
#       CREATED: Tuesday 06 December 2016 03:05:41  IST
#===============================================================================


set -o nounset                              # Treat unset variables as an error
set -e 
set -x

COMMAND=`pwd`/cam_server

# Call 
function kill_process( ) 
{
    PID=$1
    echo "Trying to kill $PID"
    CMD=`ps -p $PID -o comm=`
    echo "\tCommand: $CMD"

    kill -9 $PID

    if ps -p $PID > /dev/null; then
        printf "\tWARN: Process with PID %d is still running\n", $PID
    else
        printf "\tSucessfully killed %d\n", $PID
    fi

    # Just to be sure. Remove other process as well.
    killall -9 $COMMAND
}

# Handle Ctrl+C 
function kill_acquition_from_point_grey( )
{
    echo "Ctrl+c pressed. Terminating processes  $1"
    kill_process $1
}


# First, we execute the binary file acquition_from_point_grey  in background and
# save its PID. We can use the PID to kill this process.

$COMMAND &
ACQ_PID=`echo $!`
trap 'kill_acquition_from_point_grey ${ACQ_PID}' INT
echo "Running acquition app , PID = ${ACQ_PID}"

# Sleep for a second before launching python script.
sleep 1;

# Now run python script to acquire data. If user press Ctrl+c to stop it, we
# must send ctrl+c to PID acquition_from_point_grey app as well.
python ./camera_client.py 

# If we have come here successfully, cleanup.
kill_process( ${ACQ_PID} )
