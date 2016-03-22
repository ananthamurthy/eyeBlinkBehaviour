#!/usr/bin/env python

"""analyze_trial.py: 

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2016, Dilawar Singh "
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatch
import itertools
import random 

#style = random.choice( plt.style.available )
style = 'seaborn-darkgrid' 
try:
    plt.style.use( style )
except Exception as e:
    pass

plt.rcParams.update({'font.size': 8})
# These are the columns in CSV file and these are fixed.
cols_ = [ 'sensor', 'time', 'cs_type', 'session_num' ]
aN, bN = 450, 650
toneBeginN, toneEndN = 500, 535
puffBeginN, puffEndN = 570, 575

def straighten_time( time ):
    # if time is not in ascending order, straighten it.
    tDiff = np.diff( time )
    wherePastBegins = np.where(tDiff < 0)[0]
    for x in wherePastBegins:
        diff = time[x] - time[x+1]
        time[x+1:] += diff
    return time

def get_data_to_plot( mat ):
    return mat

def main( args ):
    trialFile = args['input']
    plot = args.get('plot', True)
    print('[INFO] Processing file %s' % trialFile )
    with open( trialFile, 'r') as f:
        lines = f.read().split('\n')
    metadata = itertools.takewhile( lambda x: '#' in x, lines)
    metadata = [ x[1:] for x in metadata ]
    # rest is data
    data = np.genfromtxt( trialFile, delimiter=',' )
    print( '[DEBUG] Metadata :%s' % metadata )
    time, sensor = data[:,1], data[:,0]
    cstype = data[1,2]
    time = straighten_time( time )
    assert (np.sort(time) == time).all(), "Time must be ascending order"
    if plot:
        ax = plt.subplot(3, 1, 1)
        baselineN = 500
        ax.plot(time, sensor)
        ax.plot(time[aN], sensor[aN], color = 'b')
        ax.plot(time[aN:bN], sensor[aN:bN], color = 'r')
        ax.plot(time[bN:], sensor[bN:], color = 'b')
        # ax.plot( time,  [np.median( sensor )] * len(time))
        plt.xlim( (0, max(time)) )
        plt.ylim( (0, 2 * sensor.mean() ) )
        plt.legend( framealpha=0.4)
        ax.add_patch( mpatch.Rectangle( 
            (time[toneBeginN], min(sensor)+30), 350, 50, lw=0)
            )
        ax.annotate('Tone', xy=(time[toneEndN], min(sensor))
                , xytext=(time[toneBeginN], min(sensor)-20)
                )
        if cstype > 0:
            ax.add_patch( mpatch.Rectangle( (time[puffBeginN], min(sensor)+30), 50, 50,lw=0))
            ax.annotate('Puff', xy=(time[puffBeginN], min(sensor)), xytext=(time[puffBeginN],
                min(sensor)-20))
        plt.xlabel( 'Time (ms)' )
        plt.ylabel( 'Sensor readout' )

    binSize = 100
    areaUnderCurve = []
    bins = np.arange(0, len(sensor), binSize)
    for i, x in enumerate(bins[1:]):
        areaUnderCurve.append( np.sum(sensor[bins[i]:x]) )

    ax = plt.subplot(3, 1, 2)
    scaleT = 0.1
    time0A = time[:aN] * scaleT 
    timeAB = time[aN:bN] -  time[aN] + time[scaleT*aN]
    timeBX = timeAB[-1] + (time[bN:] - time[bN]) * scaleT
    newTime = np.concatenate( ( time0A, timeAB, timeBX ) )
    if plot:
        plt.plot( newTime[:aN], sensor[:aN] , color = 'b')
        plt.plot( newTime[aN-1:bN], sensor[aN-1:bN], color = 'r')
        plt.plot( newTime[bN:], sensor[bN:] , color = 'b')
        plt.xticks( [0, newTime[aN], newTime[bN], max(newTime) ]
                , [0, aN*10, bN*10, int(max(time)) ] 
                )
        plt.xlim(( 0, max(newTime) ))
        ax.add_patch( mpatch.Rectangle( 
            (newTime[toneBeginN], min(sensor)+30), 350, 50, lw=0)
            )
        plt.annotate('Tone', xy=(newTime[toneEndN], min(sensor))
                , xytext=(newTime[toneBeginN], min(sensor)-20)
                )
        if cstype > 0:
            ax.add_patch( mpatch.Rectangle( (newTime[puffBeginN], min(sensor)+30), 50, 50,lw=0))
            plt.annotate('Puff', xy=(newTime[puffBeginN], min(sensor)), xytext=(newTime[puffBeginN],
                min(sensor)-20))
        plt.xlabel( 'Time (ms)' )
        plt.ylabel( 'Sensor readout' )

        plt.subplot(3, 1, 3)
        yval = sensor[:baselineN]
        plt.hist( yval, bins = int(max(yval) - min(yval))/10, alpha = 0.8, lw = 0
                , label = 'baseline')
        yval = sensor[baselineN:]
        plt.hist( yval, bins = int(max(yval)-min(yval))/10, alpha = 0.5, lw = 0
                , label = 'post-baseline'
                )
        plt.title('Histogram of sensor readout')
        plt.legend(loc='best', framealpha=0.4)
        plt.suptitle( " ".join(metadata) + ' CS : %s' % cstype, fontsize = 8 )
        plt.tight_layout()
        outfile = '%s%s.png' % (trialFile, style)
        print('[INFO] Plotting trial to %s' % outfile )
        plt.savefig( outfile )

    return { 'time' : time, 'sensor' : sensor
            , 'newtime' : newTime
            , 'area' : (bins, areaUnderCurve) }

if __name__ == '__main__':
    import argparse
    # Argument parser.
    description = '''description'''
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('--input', '-i'
        , required = True
        , help = 'Input file'
        )
    parser.add_argument('--output', '-o'
        , required = False
        , help = 'Output file'
        )
    parser.add_argument( '--debug', '-d'
        , required = False
        , default = 0
        , type = int
        , help = 'Enable debug mode. Default 0, debug level'
        )
    class Args: pass 
    args = Args()
    parser.parse_args(namespace=args)
    main( vars(args) )
