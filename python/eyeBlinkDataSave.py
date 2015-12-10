#!/usr/bin/env python2

from __future__ import print_function

"""
Created on Sat Nov  7 15:38:48 2015

@author: Dilawar, Ananth, Shriya
"""
import os
import sys
import time

import serial
import io

import serial.tools.list_ports

from collections import defaultdict
import datetime
import csv
import numpy as np
import codecs
from multiprocessing  import Process, Queue, Value

import matplotlib
try:
    matplotlib.use('GTKAgg') 
except Exception as e:
    print("Cant load GTKAgg. Using default")

import matplotlib.pyplot as plt
from matplotlib import animation
import logging

logging.basicConfig(level=logging.DEBUG,
    format='%(asctime)s -- %(message)s',
    datefmt='%m-%d %H:%M',
    filename='blink.log',
    filemode='w')
_logger = logging.getLogger('')

tstart = time.time()

import sqlite3 as sql

class BlinkDb():
    """Keep raw data in sqlite3. Write every 3 seconds"""
    def __init__(self, path):
        self.table = datetime.date.today().strftime('data_%H%M%d')
        self.conn = sql.connect( path )
        self.cur = self.conn.cursor()

    def query(self, q, commit = False):
        self.cur.execute( q )
        if commit:
            self.conn.commit()
        # Commit after every 3 seconds
        if int(time.time() - tstart) % 3 == 0:
            self.conn.commit()

    def init(self):
        self.query("""
                CREATE TABLE IF NOT EXISTS {0} (timestamp, line) 
                """.format( self.table ) , commit = True
                )

    def insert( self, line):
        if not line:
            return
        self.query( """INSERT INTO {0} VALUES ( 'now()', '{1}' )""".format(
            self.table, line))

    def cleanup(self):
        self.conn.close()

db_ = BlinkDb( 'blink.sqlite' )
db_.init()

def cleanup():
    db_.cleanup()

# Create a class to handle serial port.
class ArduinoPort( ):

    def __init__(self, path, baud_rate = 9600, **kwargs):
        self.path = path
        self.baudRate = kwargs.get('baud_rate', 9600)
        self.port = None

    def open(self, wait = True):
        # ATTN: timeout is essential else realine will block.
        try:
            self.port = serial.serial_for_url(args_.port, self.baudRate, timeout = 1)
        except OSError as e:
            # Most like to be a busy resourse. Wait till it opens.
            print("[FATAL] Could not connect")
            print(e)
            if wait:
                print("[INFO] Device seems to be busy. I'll try to reconnect"
                        " after  some time..."
                        )
                time.sleep(1)
                self.open( True )
            else:
                quit()
        except Exception as e:
            print("[FATAL] Failed to connect to port. Error %s" % e)
            quit()
        if wait:
            print("[INFO] Waiting for port %s to open" % self.path, end='')
            while not self.port.isOpen():
                if (time.time() - tstart) % 2 == 0:
                    print('.', end='')
                    sys.stdout.flush()
        print(" ... OPEN")

    def read_line(self, **kwargs):
        line = self.port.readline()
        return line.strip()

    def write_msg(self, msg):
        print('[INFO] Writing %s to serial port' % msg)
        sys.stdout.flush()
        self.port.write(b'%s' % msg)
        time.sleep(1)


# Command line arguments/Other globals.
args_ = None 

# Our shared queue used in multiprocessing
q_ = Queue()
running_trial_ = Value('d', 0)

# This is a shared variable for both animation and dumping.

fig_ = plt.figure( )
fig_.title = 'Overall profile'

global_ = plt.subplot(2,1,1)
local_ = plt.subplot(2,1,2)

gax_ = plt.subplot(2, 1, 1)
gax_.set_xlim([0, 1000])
gax_.set_ylim([0, 1000])
gax_.axes.get_xaxis().set_visible(False)
text_ = gax_.text(0.02, 0.95, '', transform=gax_.transAxes)

lax_ = plt.subplot(2, 1, 2)
lax_.set_xlim([0, 1000])
lax_.set_ylim([0, 1000])
text_l_ = lax_.text(0.02, 0.95, '', transform=lax_.transAxes)

# ax.set_autoscalex_on(True)
lline_, = lax_.plot([], [], lw=0.5)
gline_, = gax_.plot([], [])
gline1_, = gax_.plot(0, 0, 'r*')

ybuff_, xbuff_ = [], []
stary_, startx_ = [], []

save_dir_ = os.path.join( 
        os.environ['HOME']
        , 'Desktop'
        , 'Work'
        , 'Behaviour'
        )

# not blocking in pylab


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

def get_default_serial_port( ):
    # If port part is not given from command line, find a serial port by
    # default.
    print("[WARN] Searching for ARDUINO port since no --port/-p is given")
    print("       Only listing ports with VENDOR ID ")
    coms = list(serial.tools.list_ports.grep( 'PID' ))
    return coms[-1][0]

def init_serial( baudRate = 9600):
    global serial_port_
    global args_
    if args_.port is None:
        args_.port = get_default_serial_port( )
    print("[INFO] Using port: %s" % args_.port)
    serial_port_ = ArduinoPort( args_.port, baudRate )
    serial_port_.open( wait = True )

def writeTrialData( runningTrial, csType ):
    #The first line after '@' will give us
    global save_dir_
    global trial_dict_
    
    outfile = os.path.join( save_dir_, 'Trial%s.csv' % runningTrial )
    print("[INFO] Writing trial data to : %s" % outfile)
    with open(outfile, 'w') as f:
        f.write("# 3rd row values are trial index, cs type.\n")
        f.write("# Actual trial data starts from row 4\n")
        f.write( "%s,%s\n" % (runningTrial, csType))
        for (blinkValue, timeStamp) in trial_dict_[runningTrial]:
            f.write("%s,%s\n" % (blinkValue, timeStamp))

def collect_data( ):
    global serial_port_
    global trial_dict_
    global running_trial_
    global cur_

    # Used to ignore garbage data in the begining.
    anyTrialHasStarted = False
    runningTrial = 0
    csType = None
    while True:
        arduinoData = serial_port_.read_line()
        _logger.info('RX< %s' % arduinoData)
        db_.insert( arduinoData )

        y, x = line_to_yx(arduinoData)
        if x and y:
            q_.put((y,x))

        if not arduinoData:
            continue

        # When TRIAL_DATA_MARKER is found, collect trial data and write the
        # previous non-zero trial.
        if TRIAL_DATA_MARKER in arduinoData:
            anyTrialHasStarted = True
            print("[INFO] New trial starts")
            runningTrial += 1

            # global copy for display on matplotlib
            running_trial_.value = runningTrial  

            if int(runningTrial) >= 2:
                print("[INFO] Writing previous trial %s" % ( int(runningTrial) - 1 ))
                writeTrialData( runningTrial - 1, csType )
                # Reset csType to None
                csType = None
        elif anyTrialHasStarted:
            if not csType:
                runningTrial, csType = arduinoData.split()
                runningTrial = int(runningTrial)
                print("[INFO] Trial: %s, CSType: %s" % (runningTrial, csType))
            else:
                if x and y:
                    trial_dict_[runningTrial].append((y,x))
                
        else:
            pass

def init_arduino():
    global serial_port_
    global save_dir_
    global args_

    _logger.info('RX< %s' % serial_port_.read_line())
    serial_port_.write_msg('%s\r' % args_.name )
    _logger.info('RX< %s' % serial_port_.read_line())
    serial_port_.write_msg('%s\r' % args_.session_num )
    _logger.info('RX< %s' % serial_port_.read_line())
    serial_port_.write_msg( '%s\r' % args_.session_type )

    timeStamp = datetime.datetime.now().strftime('%Y-%m-%d_%H-%M')
    mouseName = 'MouseK%s' % args_.name
    outfile = os.path.join( mouseName
            , '%s_SessionType%s_Session%s' % ( 
                args_.name, args_.session_type, args_.session_num)
            )
    save_dir_ = os.path.join( save_dir_, outfile )
    if os.path.exists(save_dir_):
        save_dir_ = os.path.join(save_dir_, timeStamp)
        os.makedirs(save_dir_)
    else:
        os.makedirs(save_dir_) 

def line_to_yx( line ):
    if not line.strip():
        return (None, None)
    l = line.split(' ')
    if not l:
        return (None, None)
    if len(l) == 1: 
        l.append( time.time() - tstart )
    try:
        return (float(l[0]), float(l[1]))
    except Exception as e:
        return (None, None)
    return l


def init():
    lline_.set_data([], [])
    text_.set_text('')
    return lline_, gline_, gline1_, text_, text_l_

def animate(i):
    global lline_
    global xbuff_, ybuff_
    global q_
    global running_trial_
    global args_

    # Get 20 elements from queue and plot them.
    for i in range(20):
        y, x = q_.get()
        ybuff_.append(y)
        xbuff_.append( len(ybuff_) + 1 )

    _logger.info("Got from queue: %s, %s" % (xbuff_[-20:], ybuff_[-20:]))
    xmin, xmax = lax_.get_xlim()
    if len(xbuff_) >= xmax:
        _logger.info("Updating axes")
        lax_.set_xlim((xmax-1000, xmax+1000))
        gax_.set_xlim((xmax-3000, xmax))
        xbuff_ = xbuff_[-3000:]
        ybuff_ = ybuff_[-3000:]
        gline_.set_data(xbuff_, ybuff_)
        startx_.append(xbuff_[-1])
        stary_.append(50)
        gline1_.set_data(startx_, stary_)
    lline_.set_data(xbuff_[-1000:], ybuff_[-1000:])
    text = 'TIME: %.3f' % (time.time() - tstart)
    text += ' MOUSE: %s' % args_.name
    text += ' SERIAL: %s' % args_.port
    text_.set_text(text)
    text_l_.set_text('Running trial: %d' % running_trial_.value)
    return lline_, gline_, gline1_, text_, text_l_

def main():
    global args_
    init_serial( )
    init_arduino( )
    p = Process( target = collect_data )
    p.start()
    anim = animation.FuncAnimation(fig_
            , animate
            , init_func = init
            , frames=1
            , interval = 1
            , blit = True
            )
    plt.show()
    p.join()

if __name__ == '__main__':
    import argparse
    # Argument parser.
    description = '''Arduino reader.'''
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('--name', '-n'
        , required = True
        , type = int
        , help = 'Mouse index (positive integers)'
        )
    parser.add_argument('--session-type', '-st'
        , required = True
        , type = int
        , help = 'Seession Type [0,1,2]'
        )
    parser.add_argument('--session-num', '-sn'
        , required = True
        , type = int
        , help = 'Session number (positive integer)'
        )
    parser.add_argument('--port', '-p'
        , required = False
        , default = None
        , help = 'Serial port [full path]'
        )
    class Args: pass 
    args_ = Args()
    parser.parse_args( namespace=args_ )
    try:
        main( )
    except KeyboardInterrupt as e:
        print("[WARN] Interrupt from keyboard.... Quitting after cleanup.")
        cleanup()
        quit()
