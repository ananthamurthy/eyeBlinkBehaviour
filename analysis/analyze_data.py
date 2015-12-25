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
logging.basicConfig( filename = '__analyze__.log'
        , level = logging.DEBUG
        , filemode = 'w'
        )

files_ = defaultdict(list)
data_ = defaultdict(list)
args_ = None

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
    elif args_.analysis == 'raster':
        # plt.figure( figsize = (20, 0.1*len(data_)), frameon=False)
        pass
    else:
        plt.figure()
    matplotlib.rcParams.update( {
        'font.size' : 10
        })

def data_components( data ):
    # first column is values.
    # Second column is time vector and third vector is cstype vector. Only one
    # value from cstype vector is sufficient to indicate the type of vector.
    if data.shape[1] != 3:
        logging.warn("Seems like old data format with 2 columns. Not using it")
        return None, None, None
    values, time, cstype = data[:,0], data[:,1], data[:,2]
    time = get_linear_time_vec( time )
    cstype = cstype[0]
    return values, time, cstype

def plot_raw_data( ):
    global args_
    modify_canvas( )
    plt.title('Raw plots of arduino values')
    plt.xlabel('TIme (ms)')
    for i, trial in enumerate(data_):
        tid = os.path.split( trial )[-1]
        print("Processing %s" % trial)
        data, metadata = data_[trial]
        values, time, cstype = data_components( data )
        if values is None:
            continue
        if args_.subplots:
            ax = plt.subplot( len(data_), 1, i, frameon = False)
        plt.plot(values, label = '%s' % tid )
        plt.legend( frameon = False)
    plt.ylabel( '# Trial')

    if not args_.outfile:
        args_.outfile = '%s/%s.svg' % (args_.dir, args_.analysis)

    print("[INFO] Saving to %s" % args_.outfile)
    plt.savefig( '%s' % args_.outfile, transparent = True)

def plot_cs_summary( yvec, xvec = None, label = ' ', bin_size = 10):
    # If bin_size is more than one, use it to smooth the curse.
    logging.info("Smoothing the curve using window size %s" % bin_size)
    window = np.ones( bin_size ) / bin_size
    yvec = np.convolve( yvec, window, 'same' )

    if xvec is None:
        plt.plot( yvec , label = label)
    else:
        plt.plot( xvec, yvec, label = label)
    if label.strip():
        plt.legend(loc='best', framealpha=0.4)

def plot_raster( ):
    global args_
    global data_
    modify_canvas()
    plt.xlabel('TIme (ms)')
    scale = 1.0
    # One plot of cs+ and one for cs-
    csPosPlots = []
    csMinusPlots = []

    maxTimeLen = 0
    for i, trial in enumerate(data_):
        data, metadata = data_[trial]
        # Threshold 
        yvec, time, cstype = data_components( data )
        if len(time) > maxTimeLen:
            maxTimeLen = len(time)
        vlineVec = np.where( yvec >= yvec.mean() + 2*yvec.std())
        if cstype == 0:
            csMinusPlots.append((vlineVec, time))
        else:
            csPosPlots.append((vlineVec, time))

    # Now compare both cs+ and cs- rasters.
    csMinusCount = np.zeros( maxTimeLen )
    for c, time in csMinusPlots:
        count = np.zeros( maxTimeLen )
        count[ c ] = 1
        csMinusCount += count

    csPosCount = np.zeros( maxTimeLen )
    for c, time in csPosPlots:
        count = np.zeros( maxTimeLen )
        count[ c ] = 1
        csPosCount += count 


    plt.subplot(2, 1, 1)
    for i, (yvec, time) in enumerate(csMinusPlots):
        plt.vlines(yvec, scale*(i+0.5), scale*(i+1.5) , color='r')
    plot_cs_summary( csMinusCount ) #, label = 'cs-')
    plt.ylim(0, scale*len(csMinusPlots)+scale)
    plt.title('%s\nThreshold = mean + 2 * std' % args_.dir, fontsize=10)
    plt.ylabel( '# Trial (CS-)')

    plt.subplot(2, 1, 2)
    for i, (yvec, time) in enumerate(csPosPlots):
        plt.vlines(yvec, scale*(i+0.5), scale*(i+1.5) , color='r')
    plot_cs_summary( csPosCount) #, label = 'cs+')
    plt.ylim(0, scale*len(csPosPlots)+scale)
    plt.ylabel( '# Trial (CS+)')

    if not args_.outfile:
        args_.outfile = '%s/%s.svg' % (args_.dir, args_.analysis)

    print("[INFO] Saving to %s" % args_.outfile)
    plt.savefig( '%s' % args_.outfile, transparent = True)

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
            data = np.genfromtxt(f,delimiter=',')
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

def main(  ):
    global args_
    for d, sd, fs in os.walk( args_.dir ):
        for f in fs:
            if 'Trial0.csv' in f:
                continue
            if '.csv' in f:
                filepath = os.path.join(d, f)
                files_[d].append( filepath )

    collect_valid_data() 
    print("="*80)
    print("| Collected all valid data")
    print(". Total entries = %s" % len(data_))

    if args_.analysis == 'plot':
        plot_raw_data( )
    elif args_.analysis == 'raster':
        print("[INFO] Plotting raster plots")
        plot_raster( )
    else:
        print('[WARN] Unknown analysis %s' % args_.analysis)
        print("[WARN] Currently 'plot' and 'raster' supported")
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
    parser.add_argument('--outfile', '-o'
        , required = False
        , help = 'File to store you plot.'
        )
    parser.add_argument('--analysis', '-a'
        , required = False
        , default = 'raster'
        , help = 'plot|raster, default = raster'
        )
    class Args: pass 
    args_ = Args()
    parser.parse_args(namespace=args_)
    main(  )
