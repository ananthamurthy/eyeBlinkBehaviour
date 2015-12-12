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


import matplotlib
try:
    matplotlib.use('GTKAgg') 
except Exception as e:
    print("Cant load GTKAgg. Using default")

import matplotlib.pyplot as plt
import os 
import sys
from collections import defaultdict
import time 
import datetime
from multiprocessing import Queue, Process, Value


# Command line arguments/Other globals.
class Args: pass 
args_ = Args()

_logger = None

tstart = time.time()

# Our shared queue used in multiprocessing
q_ = Queue()
running_trial_ = Value('d', 0)

# This is a shared variable for both animation and dumping.

fig_ = plt.figure( )
fig_.title = 'Overall profile'

gax_ = plt.subplot(1, 1, 1)
gax_.set_xlim([0, 3000])
gax_.set_ylim([0, 1000])
gax_.axes.get_xaxis().set_visible(False)
text_ = gax_.text(0.02, 0.95, '', transform=gax_.transAxes)

# ax.set_autoscalex_on(True)
gline_, = gax_.plot([], [])
gline1_, = gax_.plot(0, 0, 'r*')

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
