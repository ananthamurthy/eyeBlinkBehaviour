#!/usr/bin/env python2

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

def toTime( string ):
    return datetime.datetime.strptime( string, fmt_)

def plotFile( filename ):
    import matplotlib as mpl
    import matplotlib.pyplot as plt
    try:
        mpl.style.use( 'seaborn-talk' )
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
        fs = l.split( ',' )
        if len(fs) < 8:
            continue
        datalines.append( fs )

    x1, x2, x3, y1, y2, y3 = [],[],[],[],[],[]
    for l in datalines:
        if len(l) < 12:
            continue
        t1, t2, t3 = list( map( toTime, [l[0], l[1], l[12]] ) )
        x1.append( t1 )
        x2.append( t2 )
        x3.append( t3 )
        y1.append( float(l[-1]) )
        y2.append( math.copysign( float(l[-3]), float(l[-2])) )

    print( 'Plotting' )
    plt.figure()
    plt.subplot( 211 )
    plt.plot( x1, y1 )
    plt.ylabel( 'Blink readout' )
    plt.subplot( 212 )
    plt.plot( x2, y2 )
    plt.ylabel( 'Pixel per sec' )
    outfile = '%s_raw.png' % sys.argv[1]
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
    tiff = sys.argv[1]
    process( tiff )


if __name__ == '__main__':
    main()
