#!/usr/bin/env python
from __future__ import print_function

"""
Created on Sat Nov  7 15:38:48 2015

@author: Dilawar, Ananth, Shriya
"""
import os
import sys
import time
import serial
from collections import defaultdict
import datetime
import csv
import numpy as np
import codecs
import matplotlib
from multiprocessing  import Process, Queue

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


q_ = Queue()
mouse_ = None
serial_ = None

fig_ = plt.figure( )
fig_.title = 'Overall profile'

global_ = plt.subplot(2,1,1)
local_ = plt.subplot(2,1,2)

gax_ = plt.subplot(2, 1, 1)
gax_.set_xlim([0, 1000])
gax_.set_ylim([0, 1000])
gax_.axes.get_xaxis().set_visible(False)

lax_ = plt.subplot(2, 1, 2)
lax_.set_xlim([0, 1000])
lax_.set_ylim([0, 1000])
text_ = gax_.text(0.02, 0.95, '', transform=gax_.transAxes)

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

tstart = time.time()

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
def saveDict2csv(filename, fieldnames=[], dictionary={}):
    with open (filename, 'a') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames)
        writer.writeheader()
        for key in dictionary:
            writer.writerow(dictionary[key])

# NOTE: Keep the timeout 0 or leave it to default value. Else small lines wont
# be read completely from serial-port.
def getSerialPort(portPath = '/dev/ttyACM'+ str(sys.argv[4]), baudRate = 9600):
    global logWin_
    global serial_port_
    global serial_
    serial_port_ = serial.Serial(portPath, baudRate)
    print('[INFO] Connected to %s' % serial_port_)
    serial_ = '%s' % portPath.split('/')[-1]
    return serial_port_

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


def writeProfilingData(profilingDict = {}, arduinoData = []):
    
    global serial_port_
    global save_dir_
    #Wait indefinitely for the DATA_BEGIN_MARKER
    while DATA_BEGIN_MARKER not in getLine(serial_port_):
        continue
    
    #Once the DATA_BEGIN_MARKER is caught,
    while True:
        line = getLine(serial_port_)
        if DATA_END_MARKER in line:
            break
        elif not line:
            pass
        else:
            try:
                bin, counts = line.split()
                profilingDict[bin] = counts
            except:
                print('[INFO-WARNING] No instructions for %s defined in writeProfilingData()' %line)
    
    outfile = os.path.join( save_dir_, 'profilingData.csv')
    print("[INFO] Writing profiling data to : %s" % outfile)
    with open(outfile, 'w') as f:
        data = profilingDict.items()
        data = [bin + "," + count for (bin, count) in data]
        f.write("\n".join(data))

def getLine(port = None):
    global serial_port_
    if not port:
        port = serial_port_
    line = []
    txtLine = u''
    while True:
        c = port.read( 1 )
        if c: 
            if c == '\r' or c == '\n' or c == '\r\n':
                for x in line:
                    try:
                        txtLine += x
                    except:
                        return ""
                break
            else:
                line.append(c)
    return txtLine.decode('ascii', 'ignore')

def collect_data( ):
    global serial_port_
    global trial_dict_
    line = getLine( serial_port_ )
    print("Line: %s" % line)
    #Once the SESSION_BEGIN_MARKER is caught,
    while True:
        line = getLine( serial_port_ ).strip()
        if SESSION_BEGIN_MARKER  in line:
            break
        if line:
            y, x = line_to_yx( line )
            if x and y:
                q_.put((y,x))

    runningTrial = None
    csType = None
    while True:
        arduinoData = getLine(serial_port_)
        if not arduinoData:
            continue

        y, x = line_to_yx(arduinoData)

        # Put all legal arduinoData into queue.
        if x and y: q_.put((y,x))

        # When TRIAL_DATA_MARKER is found, collect trial data and write the
        # previous non-zero trial.
        if TRIAL_DATA_MARKER in arduinoData:
            print("[INFO] Trial starts")
            if x and y:
                trial_dict_[runningTrial].append((y,x))
            if runningTrial > 1:
                print("Writing previous trial %s" % ( runningTrial ))
                writeTrialData( runningTrial, csType )
        else:
            if not (csType and runningTrial):
                runningTrial, csType = arduinoData.split()
                print("[INFO] Trial, CSType: %s, %s" % (runningTrial, csType))
            else:
                if x and y:
                    trial_dict_[runningTrial].append((y,x))

def start():
    global serial_port_
    global save_dir_
    global serial_, mouse_
    serial_port_ = getSerialPort()
    serial_port_.write(sys.argv[1])
    time.sleep(1)
    serial_port_.write(sys.argv[2])
    time.sleep(1)
    serial_port_.write(sys.argv[3])
    timeStamp = datetime.datetime.now().isoformat()
    mouse_ = sys.argv[1]
    if len(sys.argv) <= 1:
        outfile = os.path.join( timeStamp , 'raw_data')
    else:
        outfile = 'MouseK' + sys.argv[1] + '_SessionType' + sys.argv[2] + '_Session' + sys.argv[3]    
    save_dir_ = os.path.join( save_dir_, outfile )
    if os.path.exists(save_dir_):
        save_dir_ = os.path.join(save_dir_, timeStamp)
        os.makedirs(save_dir_)
    else:
        os.makedirs(save_dir_) 
    # update the global to reflect the changes.
    save_dir_ = save_dir_

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
    return lline_, gline_, gline1_, text_

def animate(i):
    global lline_
    global serial_, mouse_
    global xbuff_, ybuff_
    global q_

    # Get 20 elements from queue and plot them.
    for i in range(20):
        y, x = q_.get()
        ybuff_.append(y)
        xbuff_.append( len(ybuff_) + 1 )

    _logger.info("Got from queue: %s, %s" % (xbuff_[-20:], ybuff_[-20:]))
    xmin, xmax = lax_.get_xlim()
    if len(xbuff_) >= xmax:
        print("+ Updating axes")
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
    text += ' MOUSE: %s' % mouse_
    text += ' SERIAL: %s' % serial_
    text_.set_text(text)
    return lline_, gline_, gline1_, text_

def main():
    start()
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
    main()
    # test()
