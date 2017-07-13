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
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatch
import itertools
import random 
import logging
import pandas

try:
    plt.style.use( 'ggplot' )
except Exception as e:
    pass

plt.rcParams.update({'font.size': 8})
# These are the columns in CSV file and these are fixed.
cols_ = { 'time' : 0 , 'sensor' : 1 , 'trial_count' : 2
        , 'tone' : 3 , 'puff' : 4 , 'led' : 5 , 'status' : 6 }

            
columns_ = [ 'time', 'sensor', 'trial_count', 'tone', 'puff', 'led', 'status']

aN, bN = 0, 0
toneBeginN, toneEndN = 0, 0
puffBeginN, puffEndN = 0, 0
data = None
tone = None
puff = None
led = None
status = None
cstype = 1              # Always 1 for this branch
trial_type = 'CS_P'     # cs+, distraction, or probe
time = None
newtime = None
sensor = None
trialFile = None
args_ = None


def straighten_time( time ):
    # if time is not in ascending order, straighten it.
    tDiff = np.diff( time )
    wherePastBegins = np.where(tDiff < 0)[0]
    nTimesTimeWrapBack = 0
    for x in wherePastBegins:
        nTimesTimeWrapBack += 1
        diff = time[x] - time[x+1]
        time[x+1:] += diff
    return time, nTimesTimeWrapBack

def add_puff_and_tone_labels( ax, time ):
    global tone, puff, led
    global toneBeginN, toneEndN
    global puffBeginN, puffEndN
    toneN = get_status_ids( 'CS_P' )
    toneBeginN, toneEndN = toneN[0], toneN[-1]
    toneW = time[ toneEndN ] - time[ toneBeginN ]
    ax.add_patch( mpatch.Rectangle( 
        (time[toneBeginN], min(400,sensor.mean()-200)), toneW, 50, lw=0)
        )
    ax.annotate('Tone', xy=(time[toneEndN], sensor.mean() )
            , xytext=(time[toneBeginN], min(300,sensor.mean()-300))
            )
    try:
        puffN = get_status_ids( 'PUFF' )
        puffBeginN, puffEndN = puffN[0], puffN[-1]
        puffW = time[ puffEndN ] - time[ puffBeginN ]
        ax.add_patch( 
                mpatch.Rectangle( (time[puffBeginN],
                    min(400,sensor.mean()-200))
                    , puffW, 50,lw=0)
                )
        ax.annotate('Puff', xy=(time[puffBeginN], sensor.mean())
                , xytext=(time[puffBeginN], min(300,sensor.mean()-300)))
    except Exception as e:
        logging.info( 'This trial does not have PUFF' )

def get_status_ids( status_id ):
    global status
    return [i for i,x in enumerate( status ) if x == status_id ]

def plot_raw_trace( ax, data ):
    time, sensor = data['time'], data['sensor'] 
    preData = data[ data['status'] == 'PRE_' ]
    postData = data[ data['status'] == 'POST' ]
    ax.plot( time, sensor )
    ax.plot( preData['time'], preData['sensor'], label = 'PRE')
    ax.plot( postData['time'], postData['sensor' ], label = 'POST' )
    ax.legend( )
    plt.xlim( (0, max(time)) )
    plt.ylim( (sensor.min()-100, sensor.max() + 200 ) )
    plt.xlabel( 'Time (ms)' )
    plt.ylabel( 'Sensor readout' )

def plot_zoomedin_raw_trace( ax ):
    global time, newtime
    global puff, tone, led
    global puffBeginN, puffEndN
    global toneBeginN, toneEndN
    global aN, bN
    scaleT = 0.1
    time0A = time[:aN] * scaleT 
    timeAB = time[aN:bN] -  time[aN] + time[int(scaleT*aN)]
    timeBX = timeAB[-1] + (time[bN:] - time[bN]) * scaleT
    newtime = np.concatenate( ( time0A, timeAB, timeBX ) )
    plt.plot( newtime[:aN], sensor[:aN] , color = 'b')
    plt.plot( newtime[aN-1:bN], sensor[aN-1:bN], color = 'r')
    plt.plot( newtime[bN:], sensor[bN:] , color = 'b')
    plt.xticks( [0, newtime[aN], newtime[bN], max(newtime) ]
            , [0, time[aN], time[bN], int(max(time)) ] 
            )
    ax.set_xlim(( 0, max(newtime) ))
    ax.set_ylim(( max(0,min(sensor)-200) , max(sensor)+100))
    add_puff_and_tone_labels( ax, newtime)
    plt.xlabel( 'Time (ms)' )
    plt.ylabel( 'Sensor readout' )

def plot_histogram( ax, data):
    """Here we take the data from ROI (between aN and bN). A 100 ms window (size
    = 10) slides over it. At each step, we get min and max of window, store
    these values in a list. 

    We plot histogram of the list
    """
    time, sensor = data['time'], data['sensor']

    preData = data[ data['status'] == 'PRE_' ]
    postData = data[ data['status'] == 'POST' ]

    ax.hist( preData['sensor'].values
            , normed = True, label = 'PRE'
            , alpha = 0.7, bins = 50
            )
    ax.hist( postData['sensor'].values
            , normed = True, label = 'POST'
            , alpha = 0.7, bins = 50
            )
    ax.legend(loc='best', framealpha=0.4)

def determine_trial_type( last_column ):
    assert len( last_column ) > 50, 'Few entries %s' % len( last_column )
    if 'DIST' in last_column:
        return 'DIST'
    elif ('CS_P' in last_column) and ('PUFF' not in last_column ):
        return 'PROB'
    else:
        return 'CS_P'

def parse_csv_file( filename ):
    global trial_type
    print( '[DEBUG] Reading %s' % filename )
    data = pandas.read_table( filename
            , names = columns_
            , sep = ',', comment = '#', skiprows = 5 )
    return "", data


def find_zeros( y ):
    posEdge, negEdge = [], []
    if y[0] < 0:
        negEdge.append( 0 )
    else:
        posEdge.append( 0 )

    for i, x in enumerate(y[1:]):
        # y[i] is previous value if x in current value
        if y[i] >= 0 and x < 0:
            negEdge.append( i )
        elif y[i] <= 0 and x > 0:
            posEdge.append( i )
    return (negEdge, posEdge)

def compute_area_under_curve( y, t, a, b ):
    global trialFile
    offset = 0
    yStart = np.where( t >= a )[0][0] - offset
    yEnd = np.where( t >= b )[0][0] + offset
    yTime = t[yStart:yEnd]
    ySignal = y[yStart:yEnd] - y.mean()
    yAbsSignal = [ abs(x) for x in ySignal ]
    negE, posE = find_zeros( ySignal )
    zs = sorted( negE + posE )
    if len(zs) < 2:
        return np.sum( yAbsSignal )

    area = 0.0 
    for i, x in enumerate( zs[1:] ):
        start, end =  zs[i]+1, x+1
        area += abs( np.sum( ySignal[start:end] ) )
    return area

def main( args ):
    global cstype, trialFile
    global tone, puff, led
    global data, sensor, time
    global status
    global trial_type
    trialFile = args['input']
    plot = args.get('plot', True)
    logging.debug('Processing file %s' % trialFile )
    metadata, data = parse_csv_file( trialFile )
    print( data )
    if len( data ) <= 10:
        logging.debug( 'Few or no entry in this trial' )
        return 
    if plot:
        ax = plt.subplot(2, 1, 1)
        plot_raw_trace( ax, data )

    # In this subplot, we scale down the pre and post baseline by a factor of
    # 10. The newtime vector is transformation of time vector to achive this.
    if plot:
        ax = plt.subplot(2, 1, 2)
        try:
            plot_histogram( ax, data )
        except Exception as e:
            logging.warn( 'Failed to plot histogram' )
            logging.warn( '\t Error was %s' % e )

        plt.suptitle( os.path.basename(trialFile) )
        outfile = args.get('output', False) or '%s%s.png' % (trialFile, '')
        logging.warn('Plotting trial to %s' % outfile )
        plt.savefig( outfile )
        plt.close()

    return { 'time' : data['time'] , 'sensor' : data['sensor']
            #, 'puff_area' : puffArea
            #, 'tone_area' : toneArea
            #, 'area_in_bins' : areaInBins
            #, 'cstype' : 2
            #, 'aNbN' : (aN, bN )
            , 'trial_type' : trial_type
            }

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
