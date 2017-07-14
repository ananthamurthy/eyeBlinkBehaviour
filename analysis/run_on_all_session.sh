#!/bin/bash
# Arg 1 : The name of directory where all data is stored.
# Arg 2 : Pattern to filter. This is optional. If not given, all sessions are
# processed.
set -e
if [ $# -lt 1 ]; then
    echo "USAGE: $0 data_dir"
    exit
fi

PAT=${2:-*_?_*}
echo "Using pattern: $PAT"

DIRS=`find $1 -type d -name "${PAT}"`
for d in $DIRS; do
    echo "Processing $d"
    python ./analyze_trial.py  $d 
done
