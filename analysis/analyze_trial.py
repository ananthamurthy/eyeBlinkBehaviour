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
import logging

#style = random.choice( plt.style.available )
style = 'seaborn-darkgrid' 
try:
    plt.style.use( style )
except Exception as e:
    pass

plt.rcParams.update({'font.size': 8})
# These are the columns in CSV file and these are fixed.
cols_ = [ 'time', 'sensor', 'trial_num', 'total_trials'
        , 'cs_type', 'next_probe_in', 'tone', 'puff', 'led' 
        , 'status'
        ]

aN, bN = 0, 0
toneBeginN, toneEndN = 0, 0
puffBeginN, puffEndN = 0, 0
data = None
tone = None
puff = None
led = None
status = None
cstype = 1              # Always 1 for this branch
trial_type = 'csplus'   # cs+, distraction, or probe
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

def plot_raw_trace( ax ):
    global cstype, data, time, sensor
    global status
    global aN, bN
    aN = get_status_ids('CS_P' )[0]
    bN = get_status_ids('POST')[0] + 10

    ax.plot(time, sensor)
    ax.plot(time[aN], sensor[aN], color = 'b')
    ax.plot(time[aN:bN], sensor[aN:bN], color = 'r')
    ax.plot(time[bN:], sensor[bN:], color = 'b')
    # ax.plot( time,  [np.median( sensor )] * len(time))
    plt.xlim( (0, max(time)) )
    plt.ylim( (0, sensor.max() + 100 ) )
    plt.legend( framealpha=0.4)
    add_puff_and_tone_labels( ax, time )
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

def plot_histogram( ax ):
    """Here we take the data from ROI (between aN and bN). A 100 ms window (size
    = 10) slides over it. At each step, we get min and max of window, store
    these values in a list. 

    We plot histogram of the list
    """
    global newtime, time
    roiData = sensor[aN:bN]
    baselineData = np.concatenate( (sensor[:aN], sensor[bN:]) )
    windowSize = 10
    histdataRoi = []
    for i in range( len(roiData) ):
        window = roiData[i:i+windowSize]
        histdataRoi.append( np.ptp( window ) ) # peak to peak

    histdataBaseline = []
    for i in range( len(baselineData) ):
        window = baselineData[i:i+windowSize]
        histdataBaseline.append( np.ptp( window ) )

    plt.hist( histdataBaseline
            , bins = np.arange( min(histdataBaseline), max(histdataBaseline), 5)
            , normed = True, label = 'baseline (peak to peak)'
            , alpha = 0.7
            )
    plt.hist( histdataRoi
            , bins = np.arange( min(histdataRoi), max(histdataRoi), 5)
            , normed = True , label = 'ROI (peak to peak)'
            , alpha = 0.7
            )
    # plt.title('Histogram of sensor readout')
    plt.legend(loc='best', framealpha=0.4)

def get_colums( data, n ):
    column = []
    for d in data:
        column.append( d[n] )
    try:
        column = np.array( column )
    except Exception as e:
        pass
    return column

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
    with open( filename, 'r' ) as f:
        lines = f.read().split( '\n' )
    if len(lines) < 10:
        return [], []

    metadata, data = [], []
    for l in lines:
        if not l:
            continue
        if '#' == l[0]:
            metadata.append( l )
            continue
        dd = []
        l = l.split(',')
        for x in l:
            try:
                dd.append( float( x.strip() ) )
            except Exception as e:
                dd.append( x.strip() )
        data.append( dd )
    trial_type = determine_trial_type( get_colums( data, 9) )
    logging.debug('\t Trial type %s' % trial_type )
    return metadata, data

def find_zeros( y ):
    posEdge, negEdge = [], []
    for i, x in enumerate(y[1:]):
        # y[i] is previous value if x in current value
        if y[i] >= 0 and x < 0:
            negEdge.append( i )
        elif y[i] <= 0 and x > 0:
            posEdge.append( i )
    return (negEdge, posEdge)

def compute_area_under_curve( y, t ):
    print( '[DEBUG] Computing area under the curve for trial' )
    # Get the window in which puff is most-likely. It starts when puff singal is
    # ON, with maximum width of 300 ms.
    offset = 0
    puffStart = np.where( t >= 5450 )[0][0] - offset
    puffEnd = np.where( t >= 5850 )[0][0] + offset
    puffTime = t[puffStart:puffEnd]
    puffSignal = y[puffStart:puffEnd] - y.mean()
    negE, posE = find_zeros( puffSignal )
    zs = sorted( negE + posE )

    assert len(zs) >= 2, 'Must have at least 2 pairs of zeros: %s' % zs
    area = 0.0 
    for i, x in enumerate( zs[1:] ):
        start, end =  zs[i]+1, x+1
        area += abs( np.sum( puffSignal[start:end] ) )
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
    if len( data ) <= 10:
        logging.debug( 'Few or no entry in this trial' )
        return 

    time, sensor = get_colums(data, 0), get_colums(data, 1)
    time = time - time.min() 
    tone, puff, led = get_colums(data,6), get_colums(data,7), get_colums(data,8)
    cstype = get_colums( data, 4 )[0]
    status = get_colums( data, 9 )
    if plot:
        ax = plt.subplot(3, 1, 1)
        plot_raw_trace( ax )

    area = compute_area_under_curve( sensor, time )

    binSize = 100
    areaInBins = []
    bins = np.arange(0, len(sensor), binSize)
    for i, x in enumerate(bins[1:]):
        areaInBins.append( np.sum(sensor[bins[i]:x]) )

    ######
    # In this subplot, we scale down the pre and post baseline by a factor of
    # 10. The newtime vector is transformation of time vector to achive this.
    if plot:
        ax = plt.subplot(3, 1, 2)
        plot_zoomedin_raw_trace( ax )
        ax = plt.subplot(3, 1, 3)
        try:
            plot_histogram( ax )
        except Exception as e:
            logging.warn( 'Failed to plot histogram' )
            logging.warn( '\t Error was %s' % e )

        plt.suptitle( " ".join(metadata) + ' CS : %s' % cstype, fontsize = 8 )
        plt.tight_layout()
        outfile = args['output'] or '%s%s.png' % (trialFile, '')
        logging.warn('Plotting trial to %s' % outfile )
        plt.savefig( outfile )
        plt.close()

    return { 'time' : time, 'sensor' : sensor
            , 'newtime' : newtime
            , 'area' : area
            , 'area_in_bins' : areaInBins
            , 'cstype' : int(cstype)
            , 'aNbN' : (aN, bN )
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
