#!/usr/bin/env python

"""analyze_data

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2015, Dilawar Singh and NCBS Bangalore"
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

logging.basicConfig( filename = '__analyze__.log'
        , level = logging.DEBUG
        , filemode = 'a'
        )

files_ = defaultdict(list)
data_ = defaultdict(list)
args_ = None

def subdir( dirname ):
    d, subdirname = os.path.split( dirname )
    if not subdirname.strip():
        return subdir( d )
    return subdirname 

def get_timestamp( date_string, tried = 0 ):
    if '_' in date_string:
        try:
            date, time = date_string.split('_')
            time = time.replace('-', ':')
            date_string = date + ' ' + time
        except:
            pass
    try:
        return dateutil.parser.parse( date_string )
    except Exception as e:
        return None

def get_metadata( directory ):
    meta = {}
    x, timestamp = os.path.split( directory )
    ts = get_timestamp( timestamp )
    meta['timestamp'] = ts
    return meta

def get_linear_time_vec( vec ):
    vDiff = np.diff( vec )
    partitionIds = list(np.where( vDiff <= 0 )[0])

    if len(partitionIds) == 0:
        return vec

    partitionIds.append(len(vec) - 1)
    prevIndex, offset = 0, 0
    newVec = np.array([])
    for i, v in enumerate( partitionIds ):
        logging.debug("-- %s to %s, + %s" % (prevIndex, v, offset))
        newVec = np.append( newVec, offset + vec[prevIndex:v+1] )
        prevIndex = v+1
        offset = newVec.max()
    assert len(newVec) == len(vec), "Expected %s, got %s" % (len(vec),
            len(newVec)
            )

    return newVec 

def modify_canvas( ):
    global args_
    if args_.analysis == 'plot':
        if args_.subplots:
            plt.figure( figsize = (20, 1.5*len(data_)), frameon=False)
    else:
        plt.figure()

    matplotlib.rcParams.update( {
        'font.size' : 10
        })

def data_components( data ):
    # first column is values.
    # Second column is time vector and third vector is cstype vector. Only one
    # value from cstype vector is sufficient to indicate the type of vector.
    if data.shape[1] < 3:
        print("[WARN] Seems like old data format with 2 columns. Not using it")
        return None, None, None
    values, time, cstype = data[:,0], data[:,1], data[:,2]
    time = get_linear_time_vec( time )
    cstype = cstype[0]
    return values, time, cstype

def threshold( vec ):
    # Compute the threshold of the vector
    result = np.zeros( shape = vec.shape )
    result[ vec > vec.mean() + 2 * vec.std() ] = 1
    return result

def partition_data( ):
    """ get csplus and csminus vectors along with max length of time in any of
    these trials.
    """
    global data_, args_
    print('[INFO] Partitioning data into CS+ and CS-')
    cspos = []
    csminus = []
    times = []
    lengthOfTime = 10**6
    for i, trial in enumerate(data_):
        data, metadata = data_[trial]
        # Threshold 
        yvec, time, cstype = data_components( data )
        if time is None:
            continue
        if lengthOfTime > time.shape[0]:
            lengthOfTile = time.shape[0]
        res = threshold( yvec )
        if cstype == 0:
            csminus.append(res)
            times.append(time)
        else:
            cspos.append(res)
            times.append(time)
    # Some rows have n elements while other n-1. Use reshape function to make
    # each row n-1.
    print('[INFO] Resizing trial data to remove length mismatch')
    print('\t|- Using minimum of any time vector')
    for i, x in enumerate(cspos):
        cspos[i] = np.resize( cspos[i], lengthOfTile )
    for i, x in enumerate(csminus):
        csminus[i] = np.resize(csminus[i], lengthOfTile)
    for i, x in enumerate(times):
        times[i] = np.resize(times[i], lengthOfTile)
    return cspos, csminus, times

def plot_heatmap( ):
    global args_
    global data_
    csPosPlots, csMinusPlots, times = partition_data( )
    csposfile = '%s_cspos.csv' % args_.result_dir
    csminusfile = '%s_csminus.csv' % args_.result_dir
    timefile = '%s_time.csv' % args_.result_dir
    np.savetxt(csposfile, csPosPlots)
    np.savetxt(csminusfile, csMinusPlots)
    np.savetxt(timefile, times)
    print('[INFO] Wrote {0}'.format("\n\t".join([csposfile, csminusfile,
        timefile])))
    fig, axes = plt.subplots(4, 1, sharex=True)
    axes[0].imshow( np.vstack(csMinusPlots), aspect = 'auto' )
    axes[0].set_title( 'CS- Trials' )
    axes[1].plot(  np.sum(csMinusPlots, axis = 0), label = 'Total binks' )
    axes[2].imshow( csPosPlots, aspect = 'auto' )
    axes[2].set_title( 'CS+ Trials' )
    axes[3].plot(  np.sum(csPosPlots, axis = 0), label = 'Total binks'  )
    plt.xlim( [0, csMinusPlots[0].shape[0] ] )
    fig.suptitle( '%s' % args_.dir, fontsize = 8 )
    plt.legend(loc='best', framealpha=0.4)
    plt.xlabel( ' # Time (x10 ms)' )
    outfile =  '%s_blink_result.png' % args_.result_dir
    print('[INFO] Saved figure to %s' % outfile)
    plt.savefig( outfile )

def reformat_to_3cols( data ):
    # First row has the cstype
    trialNum, csType = data[0]
    data = data[1:] 
    newData = np.zeros( shape=(data.shape[0], 3) )
    if int(csType) == 0:
        newData = np.zeros( shape=(data.shape[0], 3) )
    else:
        newData = np.ones( shape=(data.shape[0], 3) )
    newData[:,:2] = data
    return newData

def collect_valid_data(  ):
    global data_ 
    global files_
    global args_
    for direc in files_:
        metadata = get_metadata( direc )
        print("| Processing %s" % direc)
        print(".. Timestamp (YY-DD-MM), Time: %s" % metadata['timestamp'])
        for f in files_[direc]:
            logging.info("Processing %s" % f)
            data = np.genfromtxt(f, delimiter=',', comments='#')
            assert data.shape > (0, 0), "Empty/corrupted file"
            if data.shape[0] < 500:
                logging.warn(". (%s) entries in file. Ignoring" % data.shape[0])
                continue
            if data.shape[1] < 3:
                logging.info("Less than 3 columns in data file. reformating ..")
                data= reformat_to_3cols( data )
            data_[f] = (data, metadata)
            if args_.max != -1:
                if len(data_) == int(args_.max):
                    print("[INFO] Total %s trails" % len(data_))
                    return

def init( ):
    global args_ 
    if not os.path.isdir( args_.result_dir ):
        os.makedirs( args_.result_dir )

def main(  ):
    global args_
    init( )
    for d, sd, fs in os.walk( args_.dir ):
        for f in fs:
            if 'Trial0.csv' in f or 'Trial101.csv' in f:
                continue
            if '.csv' in f:
                filepath = os.path.join(d, f)
                files_[d].append( filepath )

    try:
        collect_valid_data() 
        print("="*80)
        print("| Collected all valid data")
        print(". Total entries = %s" % len(data_))
    except Exception as e:
        print('[ERR] Could not collect data from %s' % args_.dir )
        print('\t|- Error was %s' % e)
        quit()

    if args_.analysis == 'heatmap':
        print('[INFO] Plotting heatmap')
        try:
            plot_heatmap( )
        except Exception as e:
            print('[ERR] Failed to plot heatmap')
            print('\t|- Error was %s' % e )
    else:
        print('[WARN] Unknown analysis %s' % args_.analysis)
        print("[WARN] Currently 'plot' and 'heatmap' supported")
        quit()

if __name__ == '__main__':
    import argparse
    # Argument parser.
    description = '''description'''
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
        , default = os.getcwd()
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
