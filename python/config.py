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


import gnuplotlib as gp
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

# Fig using gnuplot
gfig_ = gp.gnuplotlib(title = 'Eyeblink Behaviour')

class Logger():

    def __init__(self, name = ''):
        if not name: 
            name = 'eyeblink.log'
        self.filename = os.path.join( os.curdir,  name+'.log')
        with open(self.filename, 'w') as f:
            f.write('\n')

    def log(self, msg):
        with open(self.filename, 'a') as f:
            stamp = datetime.datetime.now().isoformat()
            f.write('%s - %s\n' % (stamp, msg))

    def set_name(self, name):
        self.__init__(name)

_logger = Logger( )

tstart = time.time()

# Our shared queue used in multiprocessing
q_ = Queue()
running_trial_ = Value('d', 0)

# This is a shared variable for both animation and dumping.

# Initialize with 1 element.
ybuff_, xbuff_ = [ 0 ], [ 1 ]
stary_, startx_ = [], []

save_dir_ = os.path.join( 
        os.environ['HOME']
        , 'Desktop'
        , 'Work'
        , 'Behaviour'
        )

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
