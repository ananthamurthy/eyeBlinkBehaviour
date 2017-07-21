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
import cPickle as pickle
import numpy as np
import config

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

    resdir = os.path.join( trialdir, '_analysis' )
    if not os.path.exists( resdir ):
        os.makedirs( resdir )

    for f in sorted( tiffs ):
        pickleFile = os.path.join(resdir, os.path.basename( '%s.pickle' % f))
        if not os.path.exists( pickleFile ):
            res = analyze_trial_video.process( f, plot = True )
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
        duration = 1000 * (tvec[-1] - tvec[0])
        if duration < 900:
            print( 
                '[WARN] %s was shorter than 900 ms. Duration %d' % (f,duration) 
                )
        times.append( tvec )
        allBlinks.append( d['blinks'] )

    tmins, tmaxs = [ ], [ ]
    for t in times:
        tmins.append( t[0] )
        tmaxs.append( t[-1] )

    minT, maxT = np.mean(tmins), np.mean(tmaxs)
    #minT, maxT = -0.500, 0.850
    newTVec = np.linspace( minT, maxT, len(allBlinks[-1]) )

    allLens = [ len(x) for x in allBlinks ]
    minL = min( allLens )
    img = [ ]

    alignedData = [ ]
    for tvec, yvec in zip(times, allBlinks):
        row = np.interp( newTVec, tvec, yvec )
        img.append( row )
        alignedData.append( zip(newTVec,row) )

    numTicks = 10
    stepSize = (len(newTVec) / numTicks)
    xlabels = [ '%d' % int(1000 * x) for x in newTVec[::stepSize] ]

    plt.subplot( 211 )
    plt.imshow( img, interpolation = 'none', aspect = 'auto' )
    plt.xticks( range(0, len(newTVec), stepSize), xlabels, fontsize=10)

    plt.xlabel( 'Time (ms)' )
    plt.colorbar( )

    trialName = filter(None, trialdir.split( '/' ))[-1]

    # Compute performance index.
    perfs = compute_performance( alignedData )
    pI, piList = compute_performance_index( perfs )
    plt.subplot( 212 )
    plt.plot( map( lambda x: x[0], perfs ), label = 'learning' )
    plt.xlabel( '# Trial' )
    plt.legend( framealpha=0.4)

    plt.title( "Performance Index %.3f" % pI )
    outfile = os.path.join( resdir, 'summary.png' )

    plt.tight_layout( pad = 3 )

    plt.suptitle( 'Trial: %s' % trialName )
    plt.savefig( outfile )
    print( 'Wrote summary to %s' % outfile )

def compute_performance_index( perfs ):
    yesOrNoList = [ ]
    yesTrial = 0.0
    for p in perfs:
        if p[0] > config.thres_:
            yesOrNoList.append( True )
            yesTrial += 1.0
        else:
            yesOrNoList.append( False )
    return yesTrial / len(yesOrNoList), yesOrNoList


def compute_baseline( d ):
    baseline = filter( lambda x : x[0] < 0 and x[0] > -0.200, d )
    signal = map( lambda x: x[1], baseline )
    return np.mean( signal ), np.std( signal )

def compute_learning( d, baseline ):
    tsignal = filter( lambda x : x[0] > 0.0 and x[0] < 0.300, d )
    # Subtract mean of baseline i.e. baseline.
    signal = map( lambda x: abs(x[1] - baseline[0]), tsignal )
    # Return mean and std of signal and variance of baseline.
    return max( signal ), np.std( signal ), baseline[1]

def compute_performance( data ):
    learnings = [ ]
    for d in data:
        baseline = compute_baseline( d )
        learning = compute_learning( d, baseline )
        learnings.append( learning )
    return learnings

def main( ):
    datadir = sys.argv[1]
    print( '[INFO] Processing %s' % datadir )
    process( datadir )


if __name__ == '__main__':
    main()

