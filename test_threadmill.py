"""test_threadmill.py: 

Read the data from thread-mill and analyze it.

"""
from __future__ import print_function

    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2017-, Dilawar Singh"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import sys
import logging
import os
import numpy as np
import time
import datetime
import scipy.signal as sig
import gnuplotlib as gpl
sys.path.append( 'pyblink' )
import arduino

res_file_ = '__results__tmp__.csv' 


def stamp( ):
    return datetime.datetime.now().isoformat( )

def line_to_data(line):
    """First element is timestamp, rest the data etc.
    """
    if '>' in line:
        return [ ]

    line = filter(None, line.split(',') )
    data = [ ]
    for x in line:
        try:
            data.append( int(x) )
        except ValueError as e:
            data.append( x )
    return data

def _readline( ser ):
    eol = b'\n'
    leneol = len(eol)
    line = bytearray()
    while True:
        c = ser.read(1)
        if c:
            line += c
            if line[-leneol:] == eol:
                break
        else:
            break

        if( len(line) > 100 ):
            break

    return bytes(line)

def compute_speed( tvec, yvec ):
    """Compute speed """
    ydiff = np.diff( yvec )
    minus1Ps = np.where( ydiff == -1 )
    minus1Ts = tvec[ minus1Ps ]
    tps = np.diff( minus1Ts )
    velocity = np.mean( 100 * 4.5 / tps )    # m / sec
    if np.isnan( velocity ):
        velocity = 0.0
    return velocity


def calculate_motion( t, s1, s2 ):
    """Caculate speed and direction of motion """
    t, s1, s2 = [ np.array( x ) for x in [ t, s1, s2] ]
    s1H = sig.hilbert( s1 )
    s2H = sig.hilbert( s2 )
    theta1 = np.unwrap( np.angle( s1H ) )
    theta2 = np.unwrap( np.angle( s2H ) )
    direction = theta1 - theta2
    v1 = compute_speed( t, s1 )
    v2 = compute_speed( t, s2 )
    # gpl.plot( (t, s1), (t, s2), terminal = 'X11' )
    speed, dire = (v1+v2)/2.0, np.mean(direction)
    with open( res_file_, 'a' ) as f:
        f.write( '%g %g %g %g %g %g\n' % (t[-1], s1[-1], s1[-2], v1, v2, dire ) )

    return speed, dire

def calculate_direction( s1, s2 ):
    d = -1
    if s1 > s2:
        d = 1
    else:
        d = -1
    return d

def main( port, baud ):
    print( '[INFO] Using port %s baudrate %d' % (port, baud ) )
    tvec, motion1, motion2 = [ ], [ ], [ ]
    ar = arduino.ArduinoPort( port )
    ar.open( )
    speed, direction = 0.0, 0
    N = 20
    with open( res_file_, 'w' ) as f:
        f.write( "time s1 s2 v1 v2 dir\n" )

    while True:
        line = ar.read_line( )
        data = line_to_data( line )
        if len( data ) < 7:
            continue

        tvec.append( data[0] )
        motion1.append( data[5] )
        motion2.append( data[6] )
        try:
            speed,direction = calculate_motion( tvec[-N:], motion1[-N:], motion2[-N:] )
        except Exception as e:
            speed = 0.0
            direction = 0
            print( e )
        print( '%.5f %s' % (speed, direction))

if __name__ == '__main__':
    port = sys.argv[1]
    baud = 38400
    main( port, baud )
