#!/usr/bin/env python2

"""

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
import datetime
import cPickle as pickle 
from libtiff import TIFF
import matplotlib as mpl
import matplotlib.pyplot as plt

try:
    mpl.style.use( 'seaborn-poster' )
except Exception as e:
    pass
#mpl.rcParams['axes.linewidth'] = 0.1
plt.rc('font', family='serif')

fmt_ =  "%Y-%m-%dT%H:%M:%S.%f"

def parse_timestamp( tstamp ):
    global fmt_
    return datetime.datetime.strptime( tstamp, fmt_ )

def get_status_timeslice( data, status ):
    status = filter( lambda x: x[-2] == status, data )
    if len( status ) > 2:
        startTime = parse_timestamp( status[0][1] )
        endTime = parse_timestamp( status[-1][1] ) 
    else:
        startTime, endTime = 0.0, 0.0
    return startTime, endTime

def process( tifffile, plot = True ):
    print( '[INFO] Processing %s' % tifffile )
    tf = TIFF.open( tifffile )
    frames = tf.iter_images( )
    datafile = "%s_data.dat" % tifffile
    datalines = [ ]
    arduinoData = [ ]
    for fi, frame in enumerate( frames ):
        # print( frame.shape )
        binline = frame[0,:]
        txtline = (''.join(( [ chr( x ) for x in binline ] ))).rstrip()
        data = txtline.split( ',' )
        if len( data ) > 1:
            datalines.append( data )
        if len( data ) > 2:
            arduinoData.append( data )
        else:
            pass
            #print( 'x Frame %d has no arduino data' % fi )

    tvec, blinkVec = [ ], [ ] 
    for l in datalines:
        tvec.append( parse_timestamp( l[0] ) )
        blinkVec.append( float( l[-1] ) )
    mean_,min_,max_ = sum(blinkVec)/len(blinkVec), min( blinkVec ), max(blinkVec)

    cspST, cspET = get_status_timeslice( arduinoData, 'CS+' )
    usST, usET = get_status_timeslice( arduinoData, 'PUFF' )


    datadir = os.path.join( os.path.dirname( tifffile ), '_analysis' )
    if not os.path.isdir( datadir ):
        os.makedirs( datadir )

    if plot:
        ax = plt.subplot( 111 )

        if cspET > cspST:
            ax.plot( [cspST, cspET] , [mean_, mean_] )

        if usET > usST:
            ax.plot( [usST, usET] , [mean_, mean_] )

        ax.plot( tvec, blinkVec )
        plt.xticks( rotation = 'vertical' )
        ax.set_title( os.path.basename( sys.argv[1] ), fontsize = 8)

        outfile = os.path.join( datadir, '%s.png' % os.path.basename(tifffile))
        plt.tight_layout( pad = 0.2 )
        plt.savefig( outfile )
        plt.close( )
        print( 'Saved to %s' % outfile )

    # Write processed data to pickle.
    res = dict( time = tvec
            , blinks = blinkVec
            , cs = [ cspST, cspET ]
            , us = [ usST, usET ]
            )

    pickleFile = os.path.join( datadir, '%s.pickle' %
            os.path.basename(tifffile))
    with open( pickleFile, 'wb' ) as pF:
        pickle.dump( res, pF )
    print( '[INFO] Wrote pickle %s' % pickleFile )
    return res


def main( ):
    tiff = sys.argv[1]
    process( tiff )

if __name__ == '__main__':
    main()
