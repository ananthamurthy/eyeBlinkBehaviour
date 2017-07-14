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

    allBlinks = [ ]
    for (f, d) in trial_data_:
        blinks = d[ 'blinks' ]
        allBlinks.append( d['blinks'] )

    allLens = [ len(x) for x in allBlinks ]
    minL = min( allLens )
    img = [ ]
    for row in allBlinks:
        img.append( row[:minL] )

    plt.imshow( img, interpolation = 'none', aspect = 'auto' )
    plt.colorbar( )

    plt.title( 'Trial: %s' % trialdir, fontsize = 10 )

    outfile = os.path.join( datadir, 'summary.png' )
    plt.savefig( outfile )
    print( 'Wrote summary to %s' % outfile )


def main( ):
    datadir = sys.argv[1]
    print( '[INFO] Processing %s' % datadir )
    process( datadir )

if __name__ == '__main__':
    main()

