#!/usr/bin/evn python2

"""analyze_trial.py: 

Analyze each trial.

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2016, Dilawar Singh "
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import os
import sys
import analyze_trial_video 
import glob
import cPickle as pickle
import numpy as np

import matplotlib as mpl
import matplotlib.pyplot as plt
try:
    mpl.style.use( 'seaborn-talk' )
except Exception as e:
    pass
mpl.rcParams['axes.linewidth'] = 0.1
plt.rc('font', family='serif')


trial_data_ = [ ]

def process( trialdir ):
    global trial_data_
    tiffs = [ ]
    for d, sd, fs in os.walk( trialdir ):
        for f in fs:
            ext = f.split( '.' )[-1]
            if ext in [ 'tiff', 'tif' ]:
                tiffs.append( os.path.join( d, f ) )

    
    datadir = os.path.join( trialdir, '_analysis' )
    for f in sorted( tiffs ):
        pickleFile = os.path.join(datadir, os.path.basename( '%s.pickle' % f))
        if not os.path.exists( pickleFile ):
            res = analyze_trial_video.process( f, plot = False )
            trial_data_.append( (f, res) )
        else:
            print( 'Pickle file is found. Reusing it' )
            with open( pickleFile, 'rb' ) as pF:
                res = pickle.load( pF )
                trial_data_.append( (f, res) )

    times, allBlinks = [ ], [ ]
    for (f, d) in trial_data_:
        blinks = d[ 'blinks' ]
        tvec = d['time']
        cs = d['cs']
        tvec = map(lambda x: (x - cs[0]).total_seconds( ), tvec)
        times.append( tvec )
        allBlinks.append( d['blinks'] )

    tmins, tmaxs = [ ], [ ]
    for t in times:
        tmins.append( min(t) )
        tmaxs.append( max(t) )

    minT, maxT = max(tmins), min(tmaxs)
    newTVec = np.linspace( minT, maxT, len(allBlinks) )

    allLens = [ len(x) for x in allBlinks ]
    minL = min( allLens )
    img = [ ]
    for tvec, yvec in zip(times, allBlinks):
        row = np.interp( newTVec, tvec, yvec )
        img.append( row )

    numTicks = 10
    stepSize = len(newTVec) / (1+numTicks)
    xlabels = [ '%d' % int(1000 * x) for x in newTVec[::stepSize] ]

    plt.imshow( img, interpolation = 'none', aspect = 'auto' )
    plt.xticks( range(0, len(newTVec), stepSize), xlabels, fontsize=10)
    plt.xlabel( 'Time (ms)' )

    plt.colorbar( )

    trialName = filter(None, trialdir.split( '/' ))[-1]
    plt.title( 'Trial: %s' % trialName )

    outfile = os.path.join( datadir, 'summary.png' )
    plt.savefig( outfile )
    print( 'Wrote summary to %s' % outfile )


def main( ):
    datadir = sys.argv[1]
    print( '[INFO] Processing %s' % datadir )
    process( datadir )


if __name__ == '__main__':
    main()

