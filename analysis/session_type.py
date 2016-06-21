# Analyze each session.

import os
import sys
import re
import pylab
import logging
import numpy as np
from collections import defaultdict

import analyze_trial as at

def get_trial_files( session_dir ):
    files = []
    for fid  in range(1, 101 ):
        fPath = os.path.join( session_dir, 'Trial%s.csv' % fid  )
        if os.path.exists( fPath ):
            files.append( fPath )
    return files

def reshape_session_data( s_data ):
    """Flatten array of sensor into a matrix for whole session. 
    Merge all tvec arrays in one tvec array since all trial share the same time.
    Collect area under the curves into another list.

    In short if there were N, N, N arrays of time, sensor, and area list, we
    return 1 time vec, 1 matrix of N x len(sensor), and N array of area list.
    """
    tList, vList, areaList = [], [], []
    lengths = []
    for t, v, area in s_data:
        tList.append( t )
        vList.append( v )
        areaList.append( area )
        lengths += [ len(t), len( v ) ]
    # Reshapes all entries the minimum length
    tList = [ x[0:min(lengths)] for x in tList ]
    vList = [ x[0:min(lengths)] for x in vList ]
    tVec = np.mean(tList, axis=0)
    sensorImg = np.vstack( vList )
    return tVec, sensorImg, areaList
    

def session_data( session_dir ):
    print( '[INFO] Analysing session stored in %s' % session_dir )
    trialFiles = get_trial_files( session_dir )
    sessionData = defaultdict( list )
    for tF in trialFiles:
        # set plot = True if you want to plot each trial data as well.
        tRes = at.main( { 'input' : tF, 'plot' : False } )
        if tRes is None:
            print( '[WARN] Files %s has no data ' % tF )
            continue
        tVec, sensor = tRes['time'], tRes['sensor']
        area = ( tRes['tone_area'], tRes['puff_area'] )
        if len( tVec ) < 10 or len( sensor) < 10:
            print( "[WARN] No data in file %s" % tF )
            continue
        trialType = tRes['trial_type']
        sessionData[trialType].append( (tVec, sensor, area) )

    data = {}
    for k in sessionData:
        data[k] = reshape_session_data( sessionData[k] )
    return data
