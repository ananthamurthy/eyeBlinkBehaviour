"""mouse.py: 
Track wheel motion with MOUSE.
"""
    
__author__           = "DoraBabu, Dilawar Singh"
__copyright__        = "Copyright 2017-, Dilawar Singh"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import sys
import time
import pyautogui

x0, y0 = (960, 540)

def main( ):
    t0 = time.time( )
    try:
        while True:
            pyautogui.moveTo( x0, y0 )
            t = time.time( )
            dt = t - t0
            t0 = time.time( )
            x, y = pyautogui.position()
            print( dt, x, y )
    except KeyboardInterrupt:
        print( 'Received interrupt' )
        quit(1)

if __name__ == '__main__':
    main()
