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
import matplotlib.pyplot as plt
from matplotlib import animation

# Two threaded queue. One thread writes to queue, other consume it to plot it.
# globals.
fig_ = plt.figure()
ax_ = plt.axes(xlim=(0,1000), ylim=(0, 1000))
# ax.set_autoscalex_on(True)
line_, = ax_.plot([], [], '*')

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

serialPort = None

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
    global serialPort
    serialPort = serial.Serial(portPath, baudRate)
    print('[INFO] Connected to %s' % serialPort)
    return serialPort

def writeTrialData(serialPort, saveDirec, trialsDict = {}, arduinoData =[]):
    #The first line after '@' will give us
    runningTrial, csType = getLine(serialPort).split()
    trialsDict[runningTrial] = []
    print('[INFO] Trial: %s' %runningTrial)
    
    #Then, wait indefinitely for the DATA_BEGIN_MARKER from the next line
    while True:
        line = getLine( serialPort )
        if DATA_BEGIN_MARKER in line:
            break

    #Once the DATA_BEGIN_MARKER is caught,
    while True:
        line = getLine(serialPort)
        if DATA_END_MARKER in line:
            break
        elif not line:
            pass
        else:
            blinkValue, timeStamp = line.split()
            # print( "Data: %s" % line)
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

def writeProfilingData(serialPort, saveDirec, profilingDict = {}, arduinoData = []):
    
    #Wait indefinitely for the DATA_BEGIN_MARKER
    while DATA_BEGIN_MARKER not in getLine(serialPort):
        continue
    
    #Once the DATA_BEGIN_MARKER is caught,
    while True:
        line = getLine(serialPort)
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
    global serialPort
    if not port:
        port = serialPort
    line = []
    txtLine = u''
    while True:
        c = port.read( 1 )
        if c: 
            if c == '\r' or c == '\n' or c == '\r\n':
                for x in line:
                    try:
                        txtLine += x.decode('ascii')
                    except:
                        return ""
                break
            else:
                line.append(c)
    return txtLine

def dump_to_console(serialPort, saveDirec, trialsDict, profilingDict):
    line = getLine( serialPort )
    while SESSION_BEGIN_MARKER not in line:
        line = getLine( serialPort )
        line = line.strip()
        if line:
            y, x = line_to_yx( line )
            line_.set_data(y, x)
            fig_.canvas.draw()

    #Once the SESSION_BEGIN_MARKER is caught,
    while True:
        arduinoData = getLine(serialPort)
        if arduinoData:
            q_.put(arduinoData)
        if SESSION_END_MARKER in arduinoData:
            return
        elif not arduinoData:
            continue
        elif COMMENT_MARKER in arduinoData:
            pass
        elif TRIAL_DATA_MARKER in arduinoData:
            writeTrialData(serialPort, saveDirec)
        elif PROFILING_DATA_MARKER in arduinoData:
            writeProfilingData(serialPort, saveDirec)
        else:
            print("[WARNING] No instructions for %s defined in dump_to_console()" %arduinoData)

def start():
    global serialPort
    global save_dir_
    serialPort = getSerialPort()
    serialPort.write(sys.argv[1])
    time.sleep(1)
    serialPort.write(sys.argv[2])
    time.sleep(1)
    serialPort.write(sys.argv[3])
    timeStamp = datetime.datetime.now().isoformat()
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
    profilingDict = {}
    trialsDict = defaultdict(list)
    dump_to_console(serialPort, save_dir_, trialsDict, profilingDict)
    serialPort.close()

def get_lines_for_half_second( serialPort ):
    startT = time.time()
    xdata, ydata = [], []
    while time.time() - startT < 0.5:
        l = getLine( serialPort )
        if not l.strip():
            continue
        l = l.split(' ')
        if not l:
            continue
        if len(l) == 1: 
            l.append( len(xdata) + 2 )
        y, x = l
        xdata.append(float(x))
        ydata.append(float(y))
    return (xdata, ydata)

def line_to_yx( line ):
    if not line.strip():
        return (None, None)
    l = line.split(' ')
    if not l:
        return (None, None)
    if len(l) == 1: 
        l.append( time.time() - tstart )
    return l

def get_data():
    global q_, line_
    while True:
        item =  q_.get()
        y, x = line_to_yx( item )
        if x:
            print(y, x)
            line_.set_data(y, x)
            fig_.canvas.draw()

def init():
    line_.set_data([], [])
    return line_,

def animate(i):
    global line_
    line = getLine()
    y, x = line_to_yx(line)
    if x and i % 100 == 0:
        xmax = ax_.get_xlim()
        if float(x) + 1 > xmax:
            ax_.set_xlim((xmax-500, xmax+500))
        line_.set_data( float(x)+1, y )
    return line_,

def main():
    start()
    anim = animation.FuncAnimation(fig_
            , animate
            , init_func = init
            , frames=20
            , interval = 1
            , blit = True
            )
    plt.show()


def test():
    filename = None
    for d, ds, fs in os.walk(os.environ['HOME']+"/Desktop/Work/Behaviour/"): 
        for f in fs:
            if "Trial1.csv" in f:
                filename = os.path.join(d, f)
                break
    with open(filename, "r") as f:
        lines = f.read().split('\n')
    data = lines[3:]
    initCurses()
    for d in data:
        d = d.replace(',',  ' ')

if __name__ == '__main__':
    main()
    # test()
