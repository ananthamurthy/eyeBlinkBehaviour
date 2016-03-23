"""analyze_dir.py: 

Analyze a given directory. All trials are accumulated and plotted.

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
import numpy as np
import dateutil
import dateutil.parser
import matplotlib
import matplotlib.pyplot as plt
from collections import defaultdict
import logging
import analyze_trial as at

args_ = None
csplus = []
csminus = []
aN, bN = at.aN, at.bN

def main(  ):
    global args_
    files = []
    for d, sd, fs in os.walk( args_.dir ):
        for f in fs:
            if 'Trial0.csv' in f or 'Trial101.csv' in f:
                continue
            ext = f.split('.')[-1]
            if ext == 'csv':
                filepath = os.path.join(d, f)
                files.append( filepath )
    tVec = []
    data = []
    for f in files:
        result = at.main( { 'input' : f } )
        tVec = result['time']
        row = result['sensor']
        if len(row) > 100:
            if result['cstype'] == 0:
                csminus.append( row[aN:bN] )
            else:
                csplus.append( row[aN:bN] )
        plt.close()

    plt.figure()
    csplusData = np.vstack( csplus ) 
    csminusData = np.vstack( csminus )
    plt.style.use('classic')
    plt.subplot(2, 1, 1)
    plt.imshow( csminusData, cmap = "jet", extent = [10*aN, 10*bN, 0, 100]  
            , vmin = 0, vmax = 1000
            ,interpolation = 'none', aspect='auto' )
    plt.xlabel( 'Time (ms)' )
    plt.ylabel( '# Trial ')
    plt.title( 'CS-' )
    plt.legend( )
    plt.colorbar( )
    plt.subplot(2, 1, 2)
    plt.imshow( csplusData, cmap = "jet", extent = [10*aN, 10*bN, 0, 100]  
            , vmin = 0, vmax = 1000
            ,interpolation = 'none', aspect='auto' )
    plt.xlabel( 'Time (ms)' )
    plt.ylabel( '# Trial' )
    plt.title( 'CS+' )
    plt.legend( )
    plt.colorbar( )
    if not args_.result_dir:
        args_.result_dir = args_.dir

    outfile = '%s/summary.png' % args_.result_dir
    print('[INFO] Saving file to %s' % outfile )
    plt.tight_layout( )
    plt.savefig( outfile )

if __name__ == '__main__':
    import argparse
    # Argument parser.
    description = '''Summaries data in one directory'''
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('--dir', '-d'
        , required = True
        , help = 'Directory to seach for behaviour data '
        )
    parser.add_argument('--max', '-m'
            , required = False
            , default = -1
            , help = 'Max number of trials to be plotted. Default all'
            )
    parser.add_argument('--subplots', '-s'
        , action = 'store_true'
        , help = 'Each trial in subplot.'
        )
    parser.add_argument('--result_dir', '-o'
        , required = False
        , default = False
        , help = 'Directory to save restults.'
        )
    parser.add_argument('--analysis', '-a'
        , required = False
        , default = 'heatmap'
        , help = 'heatmap, default = heatmap'
        )
    class Args: pass 
    args_ = Args()
    parser.parse_args(namespace=args_)
    main(  )
