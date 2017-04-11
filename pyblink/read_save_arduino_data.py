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
baudRate = 38400
for t in ttyoptions:
    try:
        tty = serial.Serial(t, baudRate, timeout = 1)
        ttyName = ("/dev/tty.usbmodem1411")
        time.sleep(2)
        tty.write(sys.argv[1])
        tty.write(sys.argv[2])
        tty.write(sys.argv[3])
    except Exception as e:
        print("[WARNING] Failed to connect to %s with error %s" % (t, e))
        continue

def writeToTrialFile(line):
    global newTrialFile
    global runningTrial
    sessionTrialTypes = os.path.join(save_direc, "sessionTrialTypes")
    if "@" in line.lower():
        newTrialFile = os.path.join(save_direc, "Trial%s" % runningTrial)
        print("[TRIAL-INFO] Writing Trial %s to %s" % (runningTrial, newTrialFile))
        with open(newTrialFile, "w") as tf:
            tf.write("".join(trialsDict[runningTrial]))
    elif "blink count = " in line.lower():
        print(line.lower())
    elif "mouse" in line.lower():
        mouse = line.lower()
    elif "session" in line.lower():
        session = ''.join(x for x in line if x.isdigit()) #string
    elif "trial no." in line.lower():
        runningTrial = ''.join(x for x in line if x.isdigit()) #string
        with open(sessionTrialTypes,"a") as stt:
            if "+" in line:
                stt.write("Trial %s is cs 1\n" % runningTrial)
            else:
                stt.write("Trial %s is cs 0\n" % runningTrial)
        print("[TRIAL-INFO] Trial %s has started" % runningTrial)
    elif "profiling" in line.lower():
        print("[INFO] Profiling data being acquired")
        with open (os.join(outfile, "profile.txt") as f:
            line.lower().startswith("profiling done"):
            f.write("%s" % line)
            # if no data for x amount of time"
            saveProfilingData = 0
    else:
        blinkProfile.append(line)
        trialsDict[runningTrial].append(line)

print("[INFO] Connecting to %s" % ttyName)
with open(os.path.join(save_direc, outfile), 'w') as f:
    print("[SESSION-INFO] Session data will be written to file %s" % outfile)
    while(True):
        line = tty.readline() #readline automatically confirms "\n"
        #print("%s" % line.strip(' '), end='')
        f.write("%s" % line)
        writeToTrialFile(line)
