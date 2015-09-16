#!/usr/bin/env python
#
#  read_save_aduino_data
#  Text
#  ----------------------------------
#  Developed with embedXcode
#
#  Project 	eye-Blink_Conditioning
#  Created by 	Kambadur Ananthamurthy on 04/08/15
#  Copyright 	2015 Kambadur Ananthamurthy
#  License	<#license#>
#

from __future__ import print_function

import os
import sys
import time
import serial
from collections import defaultdict
import datetime

DATA_BEGIN_MARKER = "["
DATA_END_MARKER = "]"
COMMENT_MARKER = "#"
TRIAL_DATA_MARKER = "@"
PROFILING_DATA_MARKER = "$"
START_OF_SESSION_MARKER = "<"
END_OF_SESSION_MARKER = ">"

def getSerialPort(portPath = "/dev/tty.usbmodem1411", baudRate = 9600, timeout = 1):
    serialPort = serial.Serial(portPath, baudRate, timeout = 1)
    time.sleep(2)
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

    with open(os.path.join(save_direc, "Trial" + runningTrial + ".csv"), 'w') as f:
        f.writeline("# 3rd row values are trial index, cs type.")
        f.writeline("# Actual trial data starts from row 4")
        f.writeline(runningTrial + "," + csType)
        data = [ timeStamp + "," + blinkValue
                for (timeStamp, blinkValue) in trialsDict[runningTrial]]
        f.write("\n".join(trialsDict[runningTrial]))

def writeProfilingData(serialPort, saveDirec, profilingDict = {}):
    while serialPort.readline() != DATA_BEGIN_MARKER:
        continue
    while True:
        line = serialPort.readline()
        if line is DATA_END_MARKER:
            break
        else:
            bin, counts = line.split()
            pofilingDict[bin] = counts

    with open(os.path.join(save_direc, "profilingData.csv"), 'w') as f:
        data = profilingDict.items()
        data = [bin + "," + count for (bin, count) in data]
        f.write("\n".join(data))

def writeData(serialPort, saveDirec, trialsDict, profilingDict):
    operationMap = { TRIAL_DATA_MARKER : lambda port, direc: writeTrialData(port, direc, trialsDict)
        , PROFILING_DATA_MARKER : lambda port, direc: writeProfilingData(port, direc, profilingDict)
        }
    while serialPort.readline() != START_OF_SESSION_MARKER:
        continue
    
    while True:
        arduinoData = serialPort.readline()
        if END_OF_SESSION_MARKER == arduinoData:
            return
        elif arduinoData.startswith(COMMENT_MARKER):
            print (arduinoData)
            operationMap[arduinoData](serialPort, saveDirec)
        else:
            print(arduinoData)

def main():
    serialPort = getSerialPort()
    serialPort.write(sys.argv[1])
    serialPort.write(sys.argv[2])
    serialPort.write(sys.argv[3])
    timeStamp = datetime.datetime.now().isoformat()
    if len(sys.argv) <= 1:
        outfile = os.path.join( timeStamp
                               , "raw_data")
    else:
        outfile = "MouseK" + sys.argv[1] + "_SessionType" + sys.argv[2] + "_Session" + sys.argv[3]

    saveDirec = os.path.join("/Users/ananth/Desktop/Work/Data/", outfile)

if os.path.exists(saveDirec):
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
