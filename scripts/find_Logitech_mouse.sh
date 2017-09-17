#!/usr/bin/env bash
MOUSE=$(readlink -f /dev/input/by-id/usb-Logitech_*-mouse | grep mouse | head -n 1)
echo $MOUSE
