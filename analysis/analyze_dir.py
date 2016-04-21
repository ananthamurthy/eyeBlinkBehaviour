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
import re
import analyze_trial as at

matplotlib.rcParams.update( {'font.size' : 10} )

args_ = None
csplus = []
csplusIdx, csminusIdx = [], []
csminus = []
aN, bN = at.aN, at.bN

def main(  ):
    global args_
    if not args_.output_dir:
        args_.output_dir = os.path.join(args_.dir, '_plots')
    if not os.path.isdir( args_.output_dir):
        os.makedirs( args_.output_dir )

    files = {}
    for d, sd, fs in os.walk( args_.dir ):
        for f in fs:
            ext = f.split('.')[-1]
            if ext == 'csv':
                filepath = os.path.join(d, f)
                trialIndex = re.search('Trial(?P<index>\d+)\.csv', filepath) 
                index = int(trialIndex.groupdict()['index'])
                files[index] = (filepath, f)
    tVec = []
    # Sort the trials according to trial number
    fileIdx = sorted( files )
    for idx  in fileIdx:
        f, fname = files[idx]
        result = at.main( { 'input' : f
            , 'output' : os.path.join(args_.output_dir, fname+'.png') } 
            )
        if not result:
            continue
        tVec = result['time']
        row = result['sensor']
        if len(row) > 100:
            if result['cstype'] == 0: 
                csminus.append( row[aN:bN] )
                csminusIdx.append( idx )
            else: 
                csplus.append( row[aN:bN] )
                csplusIdx.append( idx )

    plt.figure()
    csplusData = np.vstack( csplus ) 
    csminusData = np.vstack( csminus )
    try:
        plt.style.use('classic')
    except Exception as e:
        pass
    plt.subplot(2, 1, 1)
    plt.imshow( csminusData, cmap = "jet"
            , extent = [10*aN, 10*bN, len(csminusIdx), 0]  
            , vmin = csplusData.min(), vmax = csplusData.max()
            , interpolation = 'none', aspect='auto' 
            )
    plt.xlabel( 'Time (ms)' )
    plt.ylabel( '# Trial ')
    plt.yticks( range(0,len(csminusIdx),2), csminusIdx[::2], fontsize = 6 )
    plt.title( 'CS- Trials' )
    plt.legend( )
    plt.colorbar( )
    plt.subplot(2, 1, 2)
    plt.imshow( csplusData, cmap = "jet"
            , extent = [10*aN, 10*bN, len(csplusIdx), 0]  
            , vmin = csplusData.min(), vmax = csplusData.max()
            , interpolation = 'none', aspect='auto' 
            )
    plt.yticks( range(0,len(csplusIdx),2), csplusIdx[::2] , fontsize = 6)
    plt.xlabel( 'Time (ms)' )
    plt.ylabel( '# Trial' )
    plt.title( 'CS+ Trials' )
    plt.legend( )
    plt.colorbar( )

    outfile = '%s/summary.png' % args_.output_dir
    print('[INFO] Saving file to %s' % outfile )
    plt.tight_layout( )
    plt.suptitle( args_.dir.split('/')[-1].replace('_', ', ')
            , horizontalalignment = 'left'
            , fontsize = 9 )
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
    parser.add_argument('--output_dir', '-o'
        , required = False
        , default = ''
        , help = 'Directory to save results.'
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