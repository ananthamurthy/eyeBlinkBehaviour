"""config.py: 

"""
from __future__ import print_function
    
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
from collections import defaultdict
import time 
import datetime
from multiprocessing import Queue, Process, Value
import logging

# Command line arguments/Other globals.
class Args: pass 
args_ = Args()

def init_logger( filename ):
    # Use this to write to console.
    formatter = logging.Formatter( '%(ascitime)s- %(levelname)s - %(message)s' )
    logging.basicConfig(filename = filename
            , level = logging.DEBUG
            , formatter = formatter
            , filemode = 'a'
            )
    ch = logging.StreamHandler( )
    ch.setLevel( logging.INFO )
    logging.getLogger('').addHandler(ch)

tstart = time.time()

# This is a shared variable for both animation and dumping.

# Initialize with 1 element.
ybuff_, xbuff_ = [ 0 ], [ 1 ]
stary_, startx_ = [], []

DATA_BEGIN_MARKER = '['
DATA_END_MARKER = ']'
COMMENT_MARKER = '#'
TRIAL_DATA_MARKER = '@'
PROFILING_DATA_MARKER = '$'
SESSION_BEGIN_MARKER = '<'
SESSION_END_MARKER = '>'

serial_port_ = None
trial_data_ = []
trial_dict_ = defaultdict(list)
