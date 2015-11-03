#!/usr/bin/env python
#
#  read_save_aduino_data
#  Text
#  ----------------------------------
#  Developed with embedXcode
#
#  Project     eye-Blink_Conditioning
#  Created by     Kambadur Ananthamurthy on 04/08/15
#  Copyright     2015 Kambadur Ananthamurthy
#  License    <#license#>
#

from __future__ import print_function

import os
import sys
import time
import serial
from collections import defaultdict
import datetime
import csv

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

def getSerialPort(portPath = '/dev/tty.usbmodem1411', baudRate = 9600, timeout = 1):
    serialPort = serial.Serial(portPath, baudRate, timeout = 1)
    time.sleep(2)
    print('[INFO] Connected to %s' % serialPort)
    return serialPort

def writeTrialData(serialPort, saveDirec, trialsDict = {}, arduinoData =[]):
    #The first line after '@' will give us
    runningTrial, csType = getLine(serialPort).split()
    trialsDict[runningTrial] = []
    print ('[INFO] Trial: %s' %runningTrial)
    
    #Then, wait indefinitely for the DATA_BEGIN_MARKER from the next line
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
            blinkValue, timeStamp = line.split()
            #print('runningTrial: ', runningTrial)
            trialsDict[runningTrial].append((blinkValue, timeStamp))

with open(os.path.join(saveDirec, "Trial" + runningTrial + ".csv"), 'w') as f:
    f.write("# 3rd row values are trial index, cs type.\n")
        f.write("# Actual trial data starts from row 4\n")
        f.write(runningTrial + "," + csType + "\n")
        data = [timeStamp + "," + blinkValue
                for (timeStamp, blinkValue) in trialsDict[runningTrial]]
        f.write("\n".join(data))


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

#     filename = os.path.join(saveDirec, 'profilingData.csv')
#     fields = ['Bin', 'Counts']
#     saveDict2csv(filename, fields, profilingDict)

def getLine(serialPort):
    line = serialPort.readline()
    print(line)
    return line.strip()

def writeData(serialPort, saveDirec, trialsDict, profilingDict):
#    operationMap = { TRIAL_DATA_MARKER : lambda port, direc: writeTrialData(port, direc, trialsDict)
#        , PROFILING_DATA_MARKER : lambda port, direc: writeProfilingData(port, direc, profilingDict)
#        }
    #Wait indefinitely for the SESSION_BEGIN_MARKER
    while SESSION_BEGIN_MARKER not in getLine(serialPort):
        continue
    
    #Once the SESSION_BEGIN_MARKER is caught,
    print('[INFO] A new session has begun')
    while True:
        arduinoData = getLine(serialPort)
        if SESSION_END_MARKER in arduinoData:
            return
        elif not arduinoData:
            continue
        elif COMMENT_MARKER in arduinoData:
            # print(arduinoData)
            pass
        elif TRIAL_DATA_MARKER in arduinoData:
            writeTrialData(serialPort, saveDirec)
        elif PROFILING_DATA_MARKER in arduinoData:
            writeProfilingData(serialPort, saveDirec)
        else:
            print ("[INFO-WARNING] No instructions for %s defined in writeData()" %arduinoData)

def main():
    serialPort = getSerialPort()
    serialPort.write(sys.argv[1])
    time.sleep(1)
    serialPort.write(sys.argv[2])
    time.sleep(1)
    serialPort.write(sys.argv[3])
    timeStamp = datetime.datetime.now().isoformat()
    if len(sys.argv) <= 1:
        outfile = os.path.join( timeStamp
                               , 'raw_data')
    else:
        outfile = 'MouseK' + sys.argv[1] + '_SessionType' + sys.argv[2] + '_Session' + sys.argv[3]
    
    saveDirec = os.path.join('/Users/ananth/Desktop/Work/Behaviour/', outfile)

if os.path.exists(saveDirec):
    saveDirec = os.path.join(saveDirec, timeStamp)
    os.mkdir(saveDirec) #does not mkdir recursively
    
    trialsDict = defaultdict(list)
    profilingDict = {}
    print ('[INFO] Saving data to ' + saveDirec)
    print ('[INFO] Press the SELECT button to begin')
    writeData(serialPort, saveDirec, trialsDict, profilingDict)
    print('[INFO] The session is complete and will now terminate')
    serialPort.close()

if __name__ == '__main__':
    main()
