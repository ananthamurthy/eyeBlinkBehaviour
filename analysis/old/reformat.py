import os
import sys
import numpy as np
import re

tone1Start = 5000
tone1End = 5100

def straighten_time( time ):
    # if time is not in ascending order, straighten it.
    tDiff = np.diff( time )
    wherePastBegins = np.where(tDiff < 0)[0]
    nTimesTimeWrapBack = 0
    for x in wherePastBegins:
        nTimesTimeWrapBack += 1
        diff = time[x] - time[x+1]
        time[x+1:] += diff
    return time, nTimesTimeWrapBack


def reformat( in_path ):
    d, f = os.path.split( in_path )
    newD = os.path.join( '__reformatted__', d )
    if not os.path.isdir( newD ):
        os.makedirs( newD )
    outpath = os.path.join( newD, f )
    print( '[INFO] Reformatting path %s ->  %s' % (in_path, outpath) )
    with open( in_path, "r") as f:
        lines = f.read().split( '\n' )
        header = lines[:4]
        data = lines[5:]
    data = np.genfromtxt( in_path, delimiter = ',')
    if len(data) == 0:
        return
    tvec, nWraps =  straighten_time( data[:,1] )
    sessionType =  int(header[2].split(':')[-1].strip())
    m = re.search( r'.*Trial(?P<name>\d+)\.csv', in_path)
    trailNum = m.group('name')
    tone1Vec = np.zeros( len( tvec ) )
    tone2Vec = np.zeros( len( tvec ) )
    puffVec = np.zeros( len( tvec ) )
    ledVec = np.zeros( len( tvec ) )
    for i, t in enumerate(tvec):
        if t >= 5000 and t <= 5100:
            tone1Vec[i] =  5.0
        if sessionType == 13:
            if t >= 5450 and t <= 5500:
                puffVec[i] = 5.0

    data = np.c_[ data, tone1Vec + tone2Vec, puffVec, ledVec  ]
    np.savetxt( outpath, data, header = "\n".join(header), delimiter=',' )


def main( ):
    for d, sd, fs in os.walk( '.' ):
        for f in fs:
            ext = f.split('.')[-1]
            if '__reformatted__' in d:
                continue
            if ext != 'csv':
                continue
            path = os.path.join( d, f )
            reformat( path )

if __name__ == '__main__':
    main()
