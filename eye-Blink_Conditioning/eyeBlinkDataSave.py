#!/usr/bin/env python
#
#  read_save_aduino_data
#  Text
#  ----------------------------------
#  Developed with embedXcode
#
#  Project 	eye-Blink_Conditioning
#  Created by 	Kambadur Ananthamurthy on 04/08/15
#  Copyright 	© 2015 Kambadur Ananthamurthy
#  License	<#license#>
#

from __future__ import print_function

import os
import sys
import time
import serial

from collections import defaultdict

import datetime
stamp = datetime.datetime.now().isoformat()

# - Get all options for acmports
#acmports = range(5)
#ttyoptions = [ "/dev/tty.usbmodem%s" % x for x in acmports ]
ttyoptions = ["/dev/tty.usbmodem1411"]
ttyName = '/dev/cu.usbmodem'

runningTrial = "1"
trialsDict = defaultdict(list)
trialsDict[runningTrial] = [] #give keys as strings

if len(sys.argv) <= 1:
    outfile = os.path.join(stamp, "raw_data")
else:
    outfile = "MouseK" + sys.argv[1] + "_SessionType" + sys.argv[2] + "_Session" + sys.argv[3]

#print(sys.argv)
save_direc = ("/Users/ananth/Desktop/Work/Data/%s" % outfile)
if not os.path.isdir(save_direc):
    os.mkdir(save_direc) #does not mkdir recursively

if os.path.exists(os.path.join(save_direc, outfile)):
    outfile = outfile + stamp

tty = None
baudRate = 9600
for t in ttyoptions:
    try:
        tty = serial.Serial(t, baudRate, timeout = 1)
        ttyName = ("/dev/tty.usbmodem1411")
        time.sleep(2)
        tty.write(sys.argv[1])
        tty.write(sys.argv[2])
        tty.write(sys.argv[3])
    except Exception as e:
        print("[WARN] Failed to connect to %s with error %s" % (t, e))
        continue

def writeTrialData(save_direc):
    runningTrial = int(tty.readline())
    dataBegin = tty.readline()
    while True:
        line = tty.readline()
        if line is "]":
            break
        else:
            timeStamp, blinkValue = line.split()
            trialsDict[runningTrial].append((timeStamp, blinkValue))

    with open(os.path.join(save_direc, "Trial" + str(runningTrial) + ".csv")) as f:
        data = [timeStamp + "," + blinkValue for (timeStamp, blinkValue) in trialsDict[runningTrial]]
        f.write("\n".join(trialsDict[runningTrial]))

def writeProfilingData(save_direc):
    dataBegin = tty.readline()
    while True:
        line = tty.readline()
        if line is "]":
            break
        else:
            bin, counts = line.split()
            pofilingData[bin] = counts

    with open(os.path.join(save_direc, "profiling_data.csv") as f:
        data = profilingData.items()
        data = [bin + "," + count for (bin, count) in data]
        f.write("\n".join(data))

def writeData(save_direc):
    line = tty.readline()
    while line.startswith("@"):
        writeTrialData(save_direc)
    while line.startswith("$"):
        writeProfilingData(save_direc)