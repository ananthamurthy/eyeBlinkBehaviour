"""analyze_speed_dir_data.py: 

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2017-, Dilawar Singh"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import sys
import os
import numpy as np
import pandas as pd
import scipy.signal as sig
import matplotlib as mpl
import matplotlib.pyplot as plt
try:
    mpl.style.use( 'seaborn-talk' )
except Exception as e:
    pass
mpl.rcParams['axes.linewidth'] = 0.1
plt.rc('font', family='serif')

def smooth( vec, N = 20 ):
    return np.convolve( vec, np.ones( N ) / N, 'same' )


def main( ):
    df = pd.read_csv( sys.argv[1], sep =  ' ' )
    
    plt.subplot( 311 )
    plt.plot( df[ 'time' ], df[ 's1' ] )
    plt.plot( df[ 'time' ], df[ 's2' ] )
    plt.ylim( [-1, 2] )

    plt.subplot( 312 )
    s1, s2 = df['v1'].values, df['v2'].values
    tvec, corrVec = [ ], [ ]
    N = 20
    for i, x in enumerate( s1[N:] ):
        x1 = smooth( s1[i:i+N] )
        x2 = smooth( s1[i:i+N] )
        cr = sig.correlate( x1, x2 )
        tvec.append( df['time'][i+N] )
        corrVec.append( np.argmax(cr) - N )

    plt.plot( tvec, corrVec )

    plt.subplot( 313 )
    plt.plot( df[ 'time' ], smooth( df[ 'v1' ] ) )
    plt.plot( df[ 'time' ], smooth( df[ 'v2' ] ) )
    plt.show( )

if __name__ == '__main__':
    main()
