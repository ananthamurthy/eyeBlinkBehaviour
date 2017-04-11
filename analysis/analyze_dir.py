#!/usr/bin/env python

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
import matplotlib.cm as cm
from scipy.interpolate import interp1d

#matplotlib.rcParams.update( {'font.size' : 10} )

args_ = None

csplus, csminus = [], []
csplusIdx, csminusIdx = [], []

distraction = []
distractionIdx = []
probes = []
probesIdx = []

# This is the valid trial time.
min_trial_time_ = 17500      # ms

def plot_subplot( ax, data, idx, tvecs, title ):
    assert len( data ) > 2
    assert len(tvecs) == len(data)
    # Dimention mismatch, use histogram2d
    newImg = []
    for i, tvec in enumerate( tvecs ):
        t = tvec.values
        d = data[i].values
        # Nearest gives the best fit.
        f = interp1d( t, d, kind='nearest' )
        tnew = np.arange( 200, min_trial_time_, 5 )
        dnew = f( tnew )

        meanErr = abs(np.mean( dnew ) - np.mean( d ))
        stdErr = abs(np.std( dnew ) - np.std( d )) 
        if meanErr > 1.0:
            print( '[Warn] Got error in mean after resampling %f' % meanErr )
        if stdErr > 2.0:
            print( '[WARN] Got error in std  %f' % stdErr )
        newImg.append( dnew )

    plt.imshow( np.vstack(newImg), cmap = "jet"
            , interpolation = 'none', aspect='auto' 
            )

    # ax.set_xticks( range(0,len(idx),2), idx[::2] )
    ax.set_xlabel( 'Time (ms)' )
    ax.set_ylabel( '# Trial' )
    ax.set_title( title )
    ax.legend( )


def main(  ):
    global args_
    if not args_.output_dir:
        args_.output_dir = os.path.join(args_.dir, '_plots')
    if not os.path.isdir( args_.output_dir):
        os.makedirs( args_.output_dir )

    files = {}
    print( '[INFO] Searching in %s' % args_.dir )
    for d, sd, fs in os.walk( args_.dir ):
        for f in fs:
            ext = f.split('.')[-1]
            if ext == 'csv':
                filepath = os.path.join(d, f)
                trialIndex = re.search('Trial(?P<index>\d+)\.csv', filepath) 
                if trialIndex:
                    index = int(trialIndex.groupdict()['index'])
                    files[index] = (filepath, f)

    # Sort the trials according to trial number
    fileIdx = sorted( files )
    if len(fileIdx) == 0:
        print('[WARN] No files found' )
        quit()

    cstvecs, probetvecs = [], []
    for idx  in fileIdx:
        f, fname = files[idx]
        result = None
        try:
            result = at.main( { 'input' : f
                , 'output' : os.path.join(args_.output_dir, fname+'.png') 
                , 'plot' : False }
                )
        except Exception as e:
            result = None
            print( '[WARN] Failed to process file %s' % f )

        if not result:
            continue

        tVec = result['time']
        if tVec.max()  < min_trial_time_:
            print( '[WARN] Ignoring file %s' % fname )
            continue


        row = result['sensor']
        if len(row) > 100:
            r = row
            if idx % 10 == 0:
                probetvecs.append( tVec )
                probes.append( r )
                probesIdx.append( idx )
            else:
                csplus.append( r )
                csplusIdx.append( idx )
                cstvecs.append( tVec )

    if csplus:
        ax = plt.subplot(2, 1, 1)
        print( 'Plotting csplus' )
        plot_subplot( ax, csplus, csplusIdx, cstvecs, 'CS+' )
        plt.colorbar()
    if probes:
        ax = plt.subplot(2, 1, 2)
        print( 'Plotting probes' )
        plot_subplot( ax, probes, probesIdx, probetvecs, 'PROBES' )
        plt.colorbar( )

    outfile = '%s/summary.png' % args_.output_dir
    print('[INFO] Saving file to %s' % outfile )
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
