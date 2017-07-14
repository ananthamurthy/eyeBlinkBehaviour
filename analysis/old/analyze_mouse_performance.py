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
import session_type as st
import math

matplotlib.rcParams.update( {'font.size' : 10} )
try:
    plt.style.use('classic')
except Exception as e:
    pass

args_ = None

csplus, csminus = [], []
csplusIdx, csminusIdx = [], []

distraction = []
distractionIdx = []

probes = []
probesIdx = []

def plot_subplot( ax, data, idx, tVec, aN, bN, title ):
    csplusData = np.vstack( data ) 
    plt.imshow( csplusData, cmap = "jet"
            , extent = [tVec[aN], tVec[bN], len(idx), 0]  
            , vmin = data.min(), vmax = data.max()
            , interpolation = 'none', aspect='auto' 
            )
    # ax.set_xticks( range(0,len(idx),2), idx[::2] )
    ax.set_xlabel( 'Time (ms)' )
    ax.set_ylabel( '# Trial' )
    ax.set_title( title )
    ax.legend( )
    # ax.colorbar( )

def accept( subdir_name, reject_list ):
    for l in reject_list:
        if l in subdir_name:
            print( '[INFO] Dir %s is rejected' % subdir_name )
            return False
    return True

def plot_area_under_curve( cspData, normalised = True ):
    if normalised:
        outfile = os.path.join( args_.dir, 'area_under_tone_puff_normalised.png' )
    else:
        outfile = os.path.join( args_.dir, 'area_under_tone_puff_raw.png' )

    for i, (t, sense, area) in enumerate(cspData):
        ax = plt.subplot( math.ceil( len(cspData)/ 2.0 ), 2, i + 1 )
        area = zip(*area)
        if not normalised:
            plt.scatter( area[0] , area[1] )
            ax.set_xlim( 0, 3000 )
            ax.set_ylim( 0, 3000 )
        else:
            plt.scatter( area[0] / np.max( area[0] ) , area[1] / np.max( area[1]))

    plt.xlabel( 'Tone AOC' )
    plt.ylabel( 'Puff AOC' )

    plt.savefig( outfile  )
    print('[INFO] Saved tone/puff area scatter for all session to %s' % outfile)


def plot_performance( cspData ):
    global args_
    outfile = os.path.join( args_.dir, 'performance.png' )
    sessions, performances = [], []
    for i, (t, sense, area) in enumerate( cspData ):
        sessions.append( i + 1 )
        area = zip( *area )
        tone, puff = area 
        performances.append( np.mean(tone) / np.mean( puff) )

    plt.plot( sessions, performances , '-*')
    plt.xlabel( '# Session ' )
    plt.ylabel( 'Performance = tone / puff ' )
    plt.savefig( outfile )
    print( '[INFO] Performance is save to %s' % outfile )


def plot_csp_data( cspData ):
    """Plot CS_P type of trials from each session """
    global args_
    allSession = []
    allArea = []
    for t, sense, area in cspData:
        allSession.append( np.mean(sense, axis=0) )
    for i, sens in enumerate(allSession):
        plt.subplot( len(allSession), 1, i + 1 )
        plt.plot( sens, label = 'Session %s' % (i + 1) )
        plt.legend( )
    # plt.colorbar( )
    outfile = os.path.join( args_.dir, 'all_cs_p.png' )
    plt.savefig( outfile )
    print( '[INFO] Saved all CS_P to %s' % outfile )

    plt.figure( )
    plot_area_under_curve( cspData, False )
    plt.figure( )
    plot_area_under_curve( cspData, True )

    # Final performace.
    plt.figure( )
    plot_performance( cspData )


def rank_behaviour( session_type_dirs ):
    """Rank the behaviour of a given mouse. The directory session_type_dirs 
    contains all the data related to this mouse.
    """
    
    cspData = []
    areaData = []
    for sd in session_type_dirs:
        sessionData = st.session_data( sd )
        cspData.append( sessionData['CS_P'] )

    plot_csp_data( cspData )

def get_sessions( dir_name, **kwargs ):
    ignoreSessionTypeList = kwargs.get( 'ignore_session_types', [] )
    files = {}
    validSubDirs = []
    for d, sd, fs in os.walk( dir_name ):
        stPat = re.compile( r'SessionType\d+' )
        for sdd in sd:
            if stPat.search( sdd ):
                if accept( sdd, ignoreSessionTypeList ):
                    validSubDirs.append( os.path.join(d, sdd) )
    rank_behaviour( validSubDirs )


def main(  ):
    global args_
    if not args_.output_dir:
        args_.output_dir = os.path.join(args_.dir, '_plots')
    if not os.path.isdir( args_.output_dir):
        os.makedirs( args_.output_dir )

    sessions = get_sessions( args_.dir, ignore_session_types=[ 'SessionType12'] )


if __name__ == '__main__':
    import argparse
    # Argument parser.
    description = '''Scoring mouse performance'''
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('--dir', '-d'
        , required = True
        , help = 'Directory to seach for behaviour data for a mouse'
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
    class Args: pass 
    args_ = Args()
    parser.parse_args(namespace=args_)
    main(  )
