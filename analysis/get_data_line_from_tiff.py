#!/usr/bin/env python

"""get_data_line_from_tiff.py: 

    Extract dataline from tiff.

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2016, Dilawar Singh"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import sys
import os
import math
import numpy as np
from libtiff import TIFF
import datetime

fmt_ = "%Y-%m-%dT%H:%M:%S.%f"
cmPerPixel_ = 1/37.8

def toTime( string ):
    return datetime.datetime.strptime( string, fmt_)

def plotFile( filename ):
    import matplotlib as mpl
    import matplotlib.pyplot as plt
    try:
        mpl.style.use( 'ggplot' )
    except Exception as e:
        pass
    mpl.rcParams['axes.linewidth'] = 0.1
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')
    
    with open( filename, 'r' ) as f:
        text = f.read( )
    lines = text.split( '\n' )
    datalines = [ ]
    for l in lines:
        print(l)
        fs = l.split( ',' )
        if len(fs) < 8:
            continue
        datalines.append( fs )

    x1, x2, x3, blink = [],[],[],[]
    speed = []
    for l in datalines:
        if len(l) < 12:
            continue
        t1, t2, t3 = list( map( toTime, [l[0], l[1], l[12]] ) )
        x1.append( t1 )
        x2.append( t2 )
        x3.append( t3 )
        blink.append(float(l[-1]))
        speed.append( cmPerPixel_ * float(l[-2]))

    print( 'Plotting' )
    plt.figure()
    plt.subplot( 211 )
    plt.plot( x1, blink )
    plt.ylabel( 'Blink readout' )

    # speed and direction
    ax1 = plt.subplot( 212 )
    ax2 = ax1.twinx()
    ax1.plot( x3, speed, color='blue', label = 'speed' )
    ax1.set_title( 'Speed+Direction' )

    outfile = '%s_raw.png' % sys.argv[1]

    plt.tight_layout()
    plt.savefig( outfile )
    print( '[INFO] Written to %s' % outfile )

def process( tifffile, plot = True ):
    print( '[INFO] Processing %s' % tifffile )
    tf = TIFF.open( tifffile )
    frames = tf.iter_images( )
    datafile = "%s_data.dat" % tifffile
    datalines = [ ]
    for fi, frame in enumerate( frames ):
        # print( frame.shape )
        binline = frame[0,:]
        txtline = (''.join(( [ chr( x ) for x in binline ] ))).rstrip()
        print(txtline)
        data = txtline.split( ',' )
        if len( data ) > 1:
            datalines.append( txtline )
        else:
            print( 'x Frame %d has no arduino data' % fi )

    with open( datafile, "w" ) as f:
        f.write( "\n".join( datalines ) )
        print( "[INFO] Wrote all data to %s" % datafile )

    if plot:
        plotFile( datafile )

def main( ):
    if len(sys.argv) < 2:
        print( "[ERROR] USAGE: %s tifffile" % sys.argv[0] )
        quit(1)
        
    tiff = sys.argv[1]
    process( tiff )


if __name__ == '__main__':
    main()
