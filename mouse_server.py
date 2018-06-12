#!/usr/bin/python

from __future__ import print_function
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2017-, Dilawar Singh"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import sys
import struct
import os
import time
import math
import io
import fcntl 
import datetime
import socket

def close( ):
    global conn_, sock_
    if conn_:
        sock_.close( )
        conn_.close( )

sock_, conn_ = None, None
sockName_ = '/tmp/__MY_MOUSE_SOCKET__' 

def create_socket( ):
    global sock_, conn_
    conn_ = None
    if os.path.exists( sockName_ ):
        os.remove( sockName_ )

    sock_ = socket.socket( socket.AF_UNIX, socket.SOCK_STREAM )
    sock_.settimeout( 1.0 )     # wait for a second.
    sock_.bind( sockName_ )

    connected = False
    while not connected:
        try:
            print( '.', end = '' )
            sys.stdout.flush()
            sock_.listen( 1 )
            conn_, addr = sock_.accept( )
            connected = True
        except Exception as e:
            pass

user_interrupt_ = False
trajs = [ (datetime.datetime.now(),0,0)  for i in range(20) ] 
lastT_ = datetime.datetime.now()

f_ = None
q_ = [ (0,0,0) ]


def getMouseEvent( mouseF, q ):
    global user_interrupt_

    if user_interrupt_:
        return 

    # This is too fast. Probably not a good idea. Use os.read( ).
    fd = mouseF.fileno()
    flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, flag | os.O_NONBLOCK)
    flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    buf = mouseF.read(3);
    t = time.time( )
    if buf:
        x,y = struct.unpack( "bb", buf[1:] );
        q.append( (t, x, y) )
    else:
        q.append( (t,0,0) )
    # Essential to sleep for some time.
    time.sleep( 1e-3 )

def getMousePos( q ):
    global user_interrupt_
    global lastT_

    if user_interrupt_:
        sock_.close( )
        return

    t1 = datetime.datetime.now()
    tignore, dx, dy = q.pop( )
    t0, x0, y0= trajs[-1]
    trajs.append( (t1, x0 + dx, y0 + dy) )
    trajs.pop( 0 )
    res = compute_velocity_and_dir( trajs )
    if (t1 - lastT_).microseconds > 1000:
        lastT_ = t1
        return '%s,%.4f,%.4f' % (t1,res[0],res[1])

def compute_velocity_and_dir( trajs ):
    vels, dirs, dt = [ ], [ ], []
    for i, (t, x, y) in enumerate(trajs[1:]):
        t0, x0, y0 = trajs[i]
        print( x0, y0 )
        if t > t0:
            # per second.
            v = 1e6*((x-x0)**2.0+(y-y0)**2.0)**0.5/(t-t0).microseconds
            dt.append(t-t0)
            theta = (y-y0)/max(1e-12, (x - x0))
            d = math.atan( theta )
            vels.append( v )
            dirs.append( d )
        else:
            vels.append( 0 )
            dirs.append( 0 )
            dt.append( 0 )
    # average direction
    return sum(vels)/len(vels), sum(dirs)/len(dirs)

def process( path ):
    global user_interrupt_
    global conn_
    global f_, q_
    global mouseFile_

    if user_interrupt_:
        return False

    if f_ is None:
        f_ = io.open( path, "rb" ) 

    getMouseEvent(f_, q_)
    now = datetime.datetime.now().isoformat()
    r = getMousePos( q_ )
    if r is not None:
        txt = now + ',' + r
        if conn_:
            conn_.sendall( txt + '\n' )

def main( path ):
    create_socket( )
    print( 'CONNECTED' )
    while 1:
        x = process( path )

if __name__ == '__main__':
    path = sys.argv[1]
    try:
        main( path )
        close( )
    except KeyboardInterrupt as e:
        print( 'User pressed Ctrl+C' )
        close( )
