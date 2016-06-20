# Analyze each session.

import os
import sys
import re

def get_trial_files( session_dir ):
    files = set()
    for d, sd, fs in os.walk( session_dir ):
        for f in fs:
            if re.search( 'Trial\d+.csv', f ):
                files.add( os.path.join( d, f ) )
    return files


def rank_session( session_dir ):
    print( '[INFO] Analysing session stored in %s' % session_dir )
    trialFiles = get_trial_files( session_dir )
    print trialFiles


