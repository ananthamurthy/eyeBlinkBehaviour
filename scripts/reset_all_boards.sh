#!/bin/bash
PORTS=`python ./config/get_serial_ports.py`
for p in $PORTS; do
    echo "Resetting $p"
    ./reset_board $p
done
