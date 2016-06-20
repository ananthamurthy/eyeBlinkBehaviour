# Analyze each session.

import os
import sys
import re
import pylab
import logging
from collections import defaultdict

import analyze_trial as at

def get_trial_files( session_dir ):
    files = []
    for fid  in range(1, 101 ):
        fPath = os.path.join( session_dir, 'Trial%s.csv' % fid  )
        if os.path.exists( fPath ):
            files.append( fPath )
    return files


def rank_session( session_dir ):
    print( '[INFO] Analysing session stored in %s' % session_dir )
    trialFiles = get_trial_files( session_dir )
    sessionData = defaultdict( list )
    for tF in trialFiles:
        tRes = at.main( { 'input' : tF, 'plot' : False } )
        if tRes is None:
            print( '[WARN] Files %s has no data ' % tF )
            continue
        tVec, sensor = tRes['time'], tRes['sensor']
        if len( tVec ) < 10 or len( sensor) < 10:
            print( "[WARN] No data in file %s" % tF )
            continue
        trialType = tRes['trial_type']
        sessionData[trialType].append( (tVec, sensor) )
    print len( sessionData['CS_P'] )
    return sessionData
