#!/usr/bin/env python2

"""get_data_line_from_tiff.py: 

    Extract dataline from tiff.

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2016, Dilawar Singh"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import sys
import os
import numpy as np
from libtiff import TIFF

def process( tifffile ):
    print( '[INFO] Processing %s' % tifffile )
    tf = TIFF.open( tifffile )
    frames = tf.iter_images( )
    datafile = "%s_data.dat" % tifffile
    datalines = [ ]
    for fi, frame in enumerate( frames ):
        # print( frame.shape )
        binline = frame[0,:]
        txtline = (''.join(( [ chr( x ) for x in binline ] ))).rstrip()
        data = txtline.split( ',' )
        if len( data ) > 1:
            datalines.append( txtline )
        else:
            print( 'x Frame %d has no arduino data' % fi )

    with open( datafile, "w" ) as f:
        f.write( "\n".join( datalines ) )
        print( "[INFO] Wrote all data to %s" % datafile )


def main( ):
    tiff = sys.argv[1]
    process( tiff )


if __name__ == '__main__':
    main()
