"""read_mouse_delta.py: 

"""
from __future__ import print_function
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2017-, Dilawar Singh"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import struct
import os
import time
import math
import threading
import Queue

user_ = os.environ.get( 'USER', ' ' )

user_interrupt_ = False
cur_, prev_ = (0,0,0), (0,0,0)

def getMouseEvent( mouseF, q ):
    global user_interrupt_
    while True:
        if user_interrupt_:
            break 
        buf = mouseF.read(3);
        x,y = struct.unpack( "bb", buf[1:] );
        t = time.time( )
        q.put( (t, x, y) )

def printMouse( q ):
    global user_interrupt_
    global prev_, cur_
    while True:
        if user_interrupt_:
            break 
        if not q.empty( ):
            val = q.get( )
            prev_, cur_ = cur_, val 
            dx, dy = (cur_[1] - prev_[1]),  (cur_[2]-prev_[2]) 
	    dist = ( dx ** 2.0 + dy ** 2.0 ) ** 0.5
            v = dist / (cur_[0] - prev_[0])
	    theta = math.atan( dx / max(1e-6,dy) )
            print( 'velocity = % 8.3f, % 8.3f' % (v, theta) )



def main( ):
    global user_interrupt_
    q = Queue.Queue( )
    f = open( "/dev/input/mouse1", "rb" ) 
    readT = threading.Thread( name = 'get_mouse', target=getMouseEvent, args=(f,q))
    writeT = threading.Thread( name = 'print_mouse', target=printMouse, args=(q,) )
    readT.daemon = True
    writeT.daemon = True
    readT.start( )
    writeT.start( )

    # Main thread, just to catch interrupts.
    try:
        while 1:
            time.sleep( 0.1 )
    except KeyboardInterrupt as e:
        user_interrupt_ = True 
    except Exception as e:
        user_interrupt_ = True
    print( '> All done' )

if __name__ == '__main__':
    main()

