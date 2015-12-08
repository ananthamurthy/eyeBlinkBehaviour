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
import curses
import signal
import codecs
import numpy as np

# logger
import logging
logging.basicConfig(level=logging.DEBUG,
    format='%(asctime)s -- %(message)s',
    datefmt='%m-%d %H:%M',
    filename='blink.log',
    filemode='w')
logger_ = logging.getLogger('')

enable_curses_ = True
if not enable_curses_:
    print("[INFO] not cursed")

# Implement signal handler. If some interrupted arise from, cleanup and quit.
def handler(signum, frame):
    add_log("Intruppted")
    cleanup()
    quit()
signal.signal( signal.SIGINT, handler )

## curses windows.
logWin_ = None
plotWin_ = None
statusWin_ = None
ymax_ = 0
xmax_ = 0
startTime_ = time.time()

def refresh():
    global logWin_, plotWin_, statusWin_
    if not enable_curses_:
        return
    logWin_.refresh()
    plotWin_.refresh()
    statusWin_.refresh()

def cleanup():
    if not enable_curses_:
        return
    curses.endwin()

def initCurses():
    global logWin_, plotWin_, statusWin_
    global width_
    scr = curses.initscr()
    curses.echo()
    curses.cbreak()
    curses.curs_set(False)
    ymax_, xmax_ = scr.getmaxyx()

    statusWin_ = curses.newwin(3, xmax_, 0, 0)

    plotWin_ = curses.newwin(ymax_-20, xmax_, 4, 0)
    plotWin_.scrollok(1)
    plotWin_.box()

    logWin_ = curses.newwin(15, xmax_, ymax_-15, 0)
    logWin_.scrollok(1)
    curses.start_color()
    refresh()

def add_log(msg, end='\n', overwrite = False):
    global logWin_
    # IT servers two purpose, a) it introduce a healthy delay before we write to
    # the curses console, and b) we get the raw data into debug file.
    if not enable_curses_:
        return
    logger_.info(msg)
    if overwrite:
        y, x = logWin_.getyx()
        if x < len(msg): xloc = x
        else: xloc = x - len(msg) 
        logWin_.addstr(int(y), xloc, '.'+msg  )
    else:
        logWin_.addstr( msg + end)
    refresh()

def add_time_status( ):
    global statusWin_
    global startTime_
    if not enable_curses_:
        return

    curses.init_pair(2, curses.COLOR_WHITE, curses.COLOR_BLUE)
    statusWin_.addstr(1, 1, 'Time %s\n' % (time.time() - startTime_)
            , curses.color_pair(2)
            )
    refresh()

def add_status( status ):
    global statusWin_ 
    if not enable_curses_:
        return
    statusWin_.erase()
    add_time_status()
    y,x = statusWin_.getyx()
    statusWin_.addstr(y, 2+max(x-len(status), 1), status)
    refresh()


def line2xy( line ):
    if not line.strip():
        return [1, -1]
    l = filter(None, line.split())
    if len(l) == 1:
        l.append(-1)
    assert len(l) == 2, l
    return l

xvec_ = [ 0 ]
yvec_ = [ 0 ]

def xyplot( line, index, stride=10, end = '' ):
    global plotWin_, statusWin_  
    global xvec_, yvec_

    scaleX = 10
    scaleY = 20
    if not enable_curses_:
        return
    ymax, xmax = plotWin_.getmaxyx()

    y, x = line2xy( line )
    try:
        y, x = int(y), int(x)
    except Exception as e:
        return None

    if x < 0: 
        x = scaleX * len(xvec_) 
    xvec_.append( int(x) )
    yvec_.append( int(y) )

    # append the data at each call into buffer, but do not plot unless stride is
    # satisfied.
    if index % stride != 0:
        return None

    dmax = max(xvec_)
    shiftx = xmax - (dmax / scaleX) - 5
    add_log("raw: %s, %s" % (xvec_[-1], yvec_[-1]))

    xdataToPlot = np.array(xvec_[max(-5*scaleX, -40):]) / (scaleX)
    ydataToPlot = np.array(yvec_[max(-5*scaleX, -40):]) / scaleY

    logger_.info("x buff: %s" % xdataToPlot)
    logger_.info("y buff: %s" % ydataToPlot)

    if xdataToPlot.max() > xmax:
        xdataToPlot = xdataToPlot + shiftx

    # There values can be negative after shifting. We are ignore them when
    # plotting. DO NOT WORRY about negative values!
    # assert (xdataToPlot <= xmax).all(), xdataToPlot

    # assert (ydataToPlot >= 0).all(), ydataToPlot
    # assert (ydataToPlot <= ymax).all(), ydataToPlot

    logger_.info("To plot (xs) : %s" % str(xdataToPlot))
    logger_.info("To plot (ys) : %s" % str(ydataToPlot))


    plotWin_.erase()
    plotWin_.refresh()

    for i, x in enumerate(xdataToPlot):
        y = ydataToPlot[i]
        add_log("Plotting %s, %s" % (y, x))
        logger_.info("Plotting: %s, %s" % (y, x))

        # NOTE TO SELF: Doing it here make life simpler, DO NOT TRY to be too
        # smart, you will end up wasting lot of time of a script which is not
        # other use.
        if x <= 0:
            continue
        try:
            plotWin_.addstr(min(y, ymax-1), x, '*')
        except Exception as e:
            msg = "%s: Tried y=%s, x=%s" % (e, y, x)
            add_log(msg)
            logger_.warning(msg)

    refresh()

DATA_BEGIN_MARKER = '['
DATA_END_MARKER = ']'
COMMENT_MARKER = '#'
TRIAL_DATA_MARKER = '@'
PROFILING_DATA_MARKER = '$'
SESSION_BEGIN_MARKER = '<'
SESSION_END_MARKER = '>'

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
    try:
        serialPort = serial.Serial(portPath, baudRate)
    except Exception as e:
        add_log("failed to connect to serial port") 
        add_log("%s" % e)
        cleanup()

    add_log('[INFO] Connected to %s' % serialPort)
    return serialPort

def writeTrialData(serialPort, saveDirec, trialsDict = {}, arduinoData =[]):
    #The first line after '@' will give us
    try:
        runningTrial, csType = getLine(serialPort).split()
    except Exception as e:
        logger_.info("failed to split: %s" % e)
        add_log("Fatal error, check log")
        quit()

    trialsDict[runningTrial] = []
    add_log('[INFO] Trial: %s' %runningTrial)
    
    #Then, wait indefinitely for the DATA_BEGIN_MARKER from the next line
    i = 0
    while True:
        i += 1
        line = getLine( serialPort )
        if DATA_BEGIN_MARKER in line:
            break
        add_status("Waiting for START", overwrite=True)
        xyplot( line )

    #Once the DATA_BEGIN_MARKER is caught,
    while True:
        line = getLine(serialPort)
        if DATA_END_MARKER in line:
            break
        elif not line:
            pass
        else:
            blinkValue, timeStamp = line.split()
            add_status('Trial No: %s' % runningTrial)
            xyplot( line )
            # add_log( "Data: %s" % line)
            trialsDict[runningTrial].append((blinkValue, timeStamp))

    with open(os.path.join(saveDirec, "Trial" + runningTrial + ".csv"), 'w') as f:
        f.write("# 3rd row values are trial index, cs type.\n")
        f.write("# Actual trial data starts from row 4\n")
        f.write(runningTrial + "," + csType + "\n")
        for (blinkValue, timeStamp) in trialsDict[runningTrial]:
            data = blinkValue + "," + timeStamp
            f.write("%s\n" % data)


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
                add_log('[INFO-WARNING] No instructions for %s defined in writeProfilingData()' %line)
    
        with open(os.path.join(saveDirec, "profilingData.csv"), 'w') as f:
            data = profilingDict.items()
            data = [bin + "," + count for (bin, count) in data]
            f.write("\n".join(data))

def getLine(serialPort):
    #line  =  serialPort.readline()
    #return line.strip()
    line, txtLine = [], ""
    while True:
        c = serialPort.read( 1 )
        if c: 
            if c == '\r' or c == '\n' or c == '\r\n':
                for x in line:
                    txtLine += str(x)
                break
            else:
                line.append(c)
    return txtLine.decode('ascii', 'ignore')

def dump_to_console(serialPort, saveDirec, trialsDict, profilingDict):
    line = getLine( serialPort )
    i = 0
    while SESSION_BEGIN_MARKER not in line:
        i += 1
        line = getLine( serialPort )
        add_status('Waiting for you to press SELECT')
        line = line.strip()
        if line.strip():
            logger_.info("Got arduino line: %s" % line)
            xyplot( line, index = i, stride=20 )

    #Once the SESSION_BEGIN_MARKER is caught,
    add_log('[INFO] A new session has begun')
    while True:
        arduinoData = getLine(serialPort)
        if arduinoData:
            add_log( "Data: %s" % arduinoData )
        if SESSION_END_MARKER in arduinoData:
            return
        elif not arduinoData:
            continue
        elif COMMENT_MARKER in arduinoData:
            add_log(arduinoData)
        elif TRIAL_DATA_MARKER in arduinoData:
            writeTrialData(serialPort, saveDirec)
        elif PROFILING_DATA_MARKER in arduinoData:
            writeProfilingData(serialPort, saveDirec)
        else:
            add_log("[WARNING] No instructions for %s defined in dump_to_console()" %arduinoData)

def start():
    serialPort = getSerialPort()
    serialPort.write(sys.argv[1])
    serialPort.write(sys.argv[2])
    serialPort.write(sys.argv[3])
    timeStamp = datetime.datetime.now().isoformat()
    if len(sys.argv) <= 1:
        outfile = os.path.join( timeStamp , 'raw_data')
    else:
        outfile = 'MouseK' + sys.argv[1] + '_SessionType' + sys.argv[2] + '_Session' + sys.argv[3]    
    saveDirec = os.path.join(os.environ['HOME'], 'Desktop/Work/Behaviour', outfile)
    if os.path.exists(saveDirec):
        saveDirec = os.path.join(saveDirec, timeStamp)
        os.makedirs(saveDirec)
    else:
        os.makedirs(saveDirec) 
    
    trialsDict = defaultdict(list)
    profilingDict = {}
    add_log('+ Saving data to ' + saveDirec)
    add_log('+ Press the SELECT button to begin')

    # Here we dump the data onto console/cursed console.
    dump_to_console(serialPort, saveDirec, trialsDict, profilingDict)

    add_log('+ The session is complete and will now terminate')
    serialPort.close()
    
def main( ):
    if enable_curses_:
        initCurses()
    start()
    cleanup()
    quit()

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
        xyplot(d)


if __name__ == '__main__':
    main()
    # test()
