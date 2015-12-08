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

q_ = Queue()

try:
    matplotlib.use('GTKAgg') 
except Exception as e:
    print("Cant load GTKAgg. Using default")

import logging
logging.basicConfig(level=logging.DEBUG,
    format='%(asctime)s -- %(message)s',
    datefmt='%m-%d %H:%M',
    filename='blink.log',
    filemode='w')
_logger = logging.getLogger('')


import matplotlib.pyplot as plt
from matplotlib import animation

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

def writeTrialData(serial_port_, saveDirec, trialsDict = {}, arduinoData =[]):
    #The first line after '@' will give us
    runningTrial, csType = getLine(serial_port_).split()
    trialsDict[runningTrial] = []
    print('[INFO] Trial: %s' %runningTrial)
    
    #Then, wait indefinitely for the DATA_BEGIN_MARKER from the next line
    while True:
        line = getLine( serial_port_ )
        if DATA_BEGIN_MARKER in line:
            break

    #Once the DATA_BEGIN_MARKER is caught,
    while True:
        line = getLine(serial_port_)
        if DATA_END_MARKER in line:
            break
        elif not line:
            pass
        else:
            blinkValue, timeStamp = line.split()
            trialsDict[runningTrial].append((blinkValue, timeStamp))

    with open(os.path.join(saveDirec, "Trial" + runningTrial + ".csv"), 'w') as f:
        f.write("# 3rd row values are trial index, cs type.\n")
        f.write("# Actual trial data starts from row 4\n")
        f.write(runningTrial + "," + csType + "\n")
        for (blinkValue, timeStamp) in trialsDict[runningTrial]:
            data = blinkValue + "," + timeStamp
            f.write("%s\n" % data)


#     filename = os.path.join(saveDirec,'Trial' + runningTrial + '.csv')
#     fields = ['BlinkValue', 'TimeStamp']
#     saveDict2csv(filename, fields, trialsDict)

def writeProfilingData(serial_port_, saveDirec, profilingDict = {}, arduinoData = []):
    
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
    
        with open(os.path.join(saveDirec, "profilingData.csv"), 'w') as f:
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
    return txtLine

def dump_to_console(serial_port_, saveDirec, trialsDict, profilingDict):
    line = getLine( serial_port_ )
    while SESSION_BEGIN_MARKER not in line:
        line = getLine( serial_port_ )
        line = line.strip()
        if line:
            y, x = line_to_yx( line )
            lline_.set_data(y, x)

    #Once the SESSION_BEGIN_MARKER is caught,
    while True:
        arduinoData = getLine(serial_port_)
        if arduinoData:
            q_.put(arduinoData)
        if SESSION_END_MARKER in arduinoData:
            return
        elif not arduinoData:
            continue
        elif COMMENT_MARKER in arduinoData:
            pass
        elif TRIAL_DATA_MARKER in arduinoData:
            writeTrialData(serial_port_, saveDirec)
        elif PROFILING_DATA_MARKER in arduinoData:
            writeProfilingData(serial_port_, saveDirec)
        else:
            print("[WARNING] No instructions for %s defined in dump_to_console()" %arduinoData)

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
    saveDirec = os.path.join( save_dir_, outfile )
    if os.path.exists(saveDirec):
        saveDirec = os.path.join(saveDirec, timeStamp)
        os.makedirs(saveDirec)
    else:
        os.makedirs(saveDirec) 
    # update the global to reflect the changes.
    save_dir_ = saveDirec

def produce_data():
    # Here we dump the data onto console/cursed console.
    global save_dir_
    global q_
    while True:
        line = getLine( serial_port_ )
        y, x = line_to_yx( line )
        if x and y:
            try:
                x, y = float(x), int(y)
                q_.put((y,x))
            except Exception as e:
                _logger.info("Could not convert: %s, %s" % (y, x))

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

def get_data():
    global q_, lline_
    while True:
        item =  q_.get()
        y, x = line_to_yx( item )
        if x:
            lline_.set_data(y, x)
            fig_.canvas.draw()

def sanitize_data( xvec, yvec):
    data = zip(xvec, yvec)
    return zip(*data)

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
    # data = sanitize_data(xbuff_, ybuff_)
    # lline_.set_data(data[0][-1000:], data[1][-1000:])
    lline_.set_data(xbuff_[-1000:], ybuff_[-1000:])
    text = 'TIME: %.3f' % (time.time() - tstart)
    text += ' MOUSE: %s' % mouse_
    text += ' SERIAL: %s' % serial_
    text_.set_text(text)
    return lline_, gline_, gline1_, text_

def main():
    start()
    p = Process( target = produce_data )
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
