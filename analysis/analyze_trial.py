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

def process( datadir ):
    tiffs = [ ]
    for d, sd, fs in os.walk( datadir ):
        for f in fs:
            ext = f.split( '.' )[-1]
            if ext in [ 'tiff', 'tif' ]:
                tiffs.append( os.path.join( d, f ) )

    for f in sorted( tiffs ):
        analyze_trial_video.process( f )

def main( ):
    datadir = sys.argv[1]
    print( '[INFO] Processing %s' % datadir )
    process( datadir )

if __name__ == '__main__':
    main()

