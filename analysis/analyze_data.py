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
import matplotlib.pyplot as plt
from collections import defaultdict
import logging

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


def analize_trials( ):
    global args_
    print("="*80)
    print("| Collected all valid data")
    print(". Total entries = %s" % len(data_))
    if args_.subplots:
        plt.figure( figsize = (20, 1.5*len(data_)))
    for i, trial in enumerate(data_):
        tid = os.path.split( trial )[-1]
        print("Processing %s" % trial)
        data, metadata = data_[trial]
        values, time = data[:,0], data[:,1]
        time = get_linear_time_vec( time )
        if args_.subplots:
            ax = plt.subplot( len(data_), 1, i)
            # ax.set_ylim( [ values.mean() - 100, values.mean() + 100 ] )
        plt.plot(values, label = '%s' % tid )
        plt.legend(loc='best')

    if args_.outfile:
        print("[INFO] Saving to %s" % args_.outfile)
        plt.savefig( '%s' % args_.outfile)
    else:
        plt.show()

def collect_valid_data( direc ):
    global data_ 
    global args_
    metadata = get_metadata( direc )
    print("| Processing %s" % direc)
    print(".. Timestamp (YY-DD-MM), Time: %s" % metadata['timestamp'])
    for f in files_[direc]:
        data = np.genfromtxt(f,delimiter=',')
        if data.shape[0] < 500:
            print("... [FATAL] Only (%s) entries in file. Ignoring" % data.shape[0]
                    )
        else:
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

    [ collect_valid_data(d)  for d in files_ ]
    analize_trials( )

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
    class Args: pass 
    args_ = Args()
    parser.parse_args(namespace=args_)
    main(  )
