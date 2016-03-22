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
import pylab
import itertools

#pylab.style.use('ggplot')

# These are the columns in CSV file and these are fixed.
cols_ = [ 'sensor', 'time', 'cs_type', 'session_num' ]

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
    ax = pylab.subplot(3, 1, 1)
    baselineN = 500
    ax.plot(time[:baselineN], sensor[:baselineN], label='baseline')
    ax.plot(time[baselineN:], sensor[baselineN:])
    ax.plot( time,  [np.median( sensor )] * len(time), label= 'median' )
    pylab.xlim( (0, max(time)) )
    pylab.legend(loc='best', framealpha=0.4)
    ax.annotate('Tone', xy=(5000, 300), xytext=(5000, 150) ,
            arrowprops=dict(facecolor='black', shrink=0.05))
    if cstype > 0:
        ax.annotate('Puff', xy=(6000, 300), xytext=(6000, 150) ,
                arrowprops=dict(facecolor='black', shrink=0.05))
    pylab.xlabel( 'Time (ms)' )
    pylab.ylabel( 'Sensor reading' )

    pylab.subplot(3, 1, 2)
    binSize = 100
    areaUnderCurve = []
    bins = np.arange(0, len(sensor), binSize)
    for i, x in enumerate(bins[1:]):
        areaUnderCurve.append( np.sum(sensor[bins[i]:x]) )
    pylab.step( 10*bins[1:], areaUnderCurve, 'o-', where='post'
            ,label = 'Area, bin size = 1000 ms'
            )
    pylab.xlim( (0, max(time)) )
    pylab.legend(loc='best', framealpha=0.4)

    pylab.subplot(3, 1, 3)
    pylab.hist( sensor[:baselineN], bins = 100, alpha = 1 , label = 'baseline')
    pylab.hist( sensor[baselineN:], bins = 100, alpha = 0.5 
            , label = 'post-baseline'
            )
    pylab.title('Histogram of sensor readout')
    pylab.legend(loc='best', framealpha=0.4)
    pylab.suptitle( " ".join(metadata) + ' CS : %s' % cstype, fontsize = 8 )
    pylab.tight_layout()
    outfile = '%s.png' % trialFile
    print('[INFO] Plotting trial to %s' % outfile )
    pylab.savefig( outfile )
    return { 'time' : time, 'sensor' : sensor, 'area' : (bins, areaUnderCurve) }

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
