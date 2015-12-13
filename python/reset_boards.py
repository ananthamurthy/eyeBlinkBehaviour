#!/usr/bin/env python2

import serial
import time
import serial.tools.list_ports

def get_default_serial_port( ):
    # If port part is not given from command line, find a serial port by
    # default.
    coms = list(serial.tools.list_ports.grep( 'PID' ))
    return [ x[0] for x in coms ]

def reset_port( portname ):
    p = serial.serial_for_url( portname )
    assert p
    for i in range(5):
        l = p.readline()
        if 'Please' in l:
            print('+ Seems like board is reqesting answers')
            print('|- No need to reset port %s' % p.name)
            return 
    print('+ Writing RESET to port %s' % p.name)
    p.write(b'```\r')
    time.sleep(1)
    p.write(b'``````')
    time.sleep(1)
    print('Waiting for reset')
    while  True:
        line = p.readline()
        print(line)
        if 'Software RESET' in p.readline():
            break
    return 

def main( ):
    coms = get_default_serial_port()
    for c in coms:
        reset_port( c )

if __name__ == '__main__':
    main()

