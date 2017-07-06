#!/usr/bin/env bash

# Reset the camera by vendor id = 1e10 (Point Grey).
for X in /sys/bus/usb/devices/*
do
    if [ -e "$X/idVendor" ] && [ -e "$X/idProduct" ]
    then
        # Only reset the given vendor
        VENDOR=$(cat "$X/idVendor" )
        PRODUCT=$(cat "$X/idProduct" )
        if [ $VENDOR == "1e10" ]; then
            echo "Resetting $X"
            echo 0 > "$X/authorized"
            sleep 0.5
            echo 1 > "$X/authorized"
        fi
    fi
done

