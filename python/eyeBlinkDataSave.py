#!/usr/bin/env python
#
#  read_save_aduino_data
#  Text
#  ----------------------------------
#  Developed with embedXcode
#
#  Project  eye-Blink_Conditioning
#  Created by   Kambadur Ananthamurthy on 04/08/15
#  Copyright    2015 Kambadur Ananthamurthy
#  License  <#license#>
#

from __future__ import print_function

import os
import sys
import time
import serial
from collections import defaultdict
import datetime
import warnings

DATA_BEGIN_MARKER = "["
DATA_END_MARKER = "]"
COMMENT_MARKER = "#"
TRIAL_DATA_MARKER = "@"
PROFILING_DATA_MARKER = "$"
START_OF_SESSION_MARKER = "<"
END_OF_SESSION_MARKER = ">"

def getSerialPort(portPath = None, baudRate = 9600, timeout = 1):
    ports = [ ]
    if not portPath:
        ports = [ "/dev/ttyACM%s" % x for x in range(5) ]
    else:
        ports = [ portPath ]

    serialPort = None
    while not serialPort:
        print("[INFO] Trying to connect to %s" % ports[-1])
        try:
            serialPort = serial.Serial(ports.pop(), baudRate, timeout =0.5)
        except:
            continue
    
    print("[INFO] Connected to %s" % serialPort)
    return serialPort

def writeTrialData(serialPort, saveDirec, trialsDict = {}):
    runningTrial, csType = serialPort.readline().split()
    while serialPort.readline() != DATA_BEGIN_MARKER:
        continue

    while True:
        line = serialPort.readline()
        if line is DATA_END_MARKER:
            break
        else:
            timeStamp, blinkValue = line.split()
            trialsDict[runningTrial].append((timeStamp, blinkValue))

    outfile = os.path.join(saveDirec, "Trial" + runningTrial + ".csv")
    print("[INFO] Writing to %s" % outfile)
    with open(outfile, 'w') as f:
        f.writeline("# 3rd row values are trial index, cs type.")
        f.writeline("# Actual trial data starts from row 4")
        line = runningTrial + "," + csType
        f.writeline(line)
        data = [ timeStamp + "," + blinkValue
                for (timeStamp, blinkValue) in trialsDict[runningTrial]]
        f.write("\n".join(trialsDict[runningTrial]))
        print("++ Wrote %s, %s" % (line, data))


def writeProfilingData(serialPort, saveDirec, profilingDict = {}):
    while serialPort.readline() != DATA_BEGIN_MARKER:
        continue
    while True:
        line = serialPort.readline()
        print("Line is: %s" % line)
        if line is DATA_END_MARKER:
            break
        else:
            bin, counts = line.split()
            profilingDict[bin] = counts

    with open(os.path.join(saveDirec, "profilingData.csv"), 'w') as f:
        data = profilingDict.items()
        data = [bin + "," + count for (bin, count) in data]
        f.write("\n".join(data))

def writeData(serialPort, saveDirec, trialsDict, profilingDict):
    operationMap = { TRIAL_DATA_MARKER : lambda port, direc: writeTrialData(port, direc, trialsDict)
        , PROFILING_DATA_MARKER : lambda port, direc: writeProfilingData(port, direc, profilingDict)
        }
    print("A")
    print("AA: %s" % serialPort.readline())
    arduinoData = serialPort.readline()
    while not arduinoData.strip():
        print("[WARN] Nothing is read from serial port. Waiting for data ... ")
        time.sleep(0.1)
        arduinoData = serialPort.readline()

    # FIXME: Don't know what it does.
    #while serialPort.readline() != START_OF_SESSION_MARKER:
    #    continue

    while True:
        arduinoData = serialPort.readline()
        print("C: %s" % arduinoData)
        if END_OF_SESSION_MARKER == arduinoData:
            return
        elif arduinoData.startswith(COMMENT_MARKER):
            print("[DEBUG] Inside writeData: %s" % arduinoData)
            operationMap[arduinoData](serialPort, saveDirec)
        else:
            print("B %s" % arduinoData)

def main():
    serialPort = getSerialPort( )
    serialPort.write(sys.argv[1])
    serialPort.write(sys.argv[2])
    serialPort.write(sys.argv[3])
    timeStamp = datetime.datetime.now().isoformat()
    if len(sys.argv) <= 1:
        outfile = os.path.join( timeStamp
                               , "raw_data")
    else:
        outfile = "MouseK" + sys.argv[1] + "_SessionType" + sys.argv[2] + "_Session" + sys.argv[3]

    saveDirec = os.path.join("/tmp", outfile)
    if not os.path.exists(saveDirec):
        os.makedirs(saveDirec)
    saveDirec = os.path.join(saveDirec, timeStamp)

    os.mkdir(saveDirec) #does not mkdir recursively

    trialsDict = defaultdict(list)
    profilingDict = {}
    print ("[INFO] Saving data to " + saveDirec)
    writeData(serialPort, saveDirec, trialsDict, profilingDict)
    print("[INFO] The session is complete and will now terminate")
    serialPort.close()

if __name__ == "__main__":
    main()
