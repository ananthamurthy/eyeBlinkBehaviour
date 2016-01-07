#!/bin/bash
set -e
if [ $# -lt 1 ]; then
    echo "USAGE: $0 data_dir"
    exit
fi

RESDIR=_results
mkdir -p $RESDIR
DIRS=`find $1 -type d -name "*SessionType*Session*"`
for d in $DIRS; do
    echo "Processing $d"
    python ./analyze_data.py -d $d  -o `pwd`/_results/`basename $d`
    find $d -type f -name "*.png" -or -name "*.svg" | xargs -I file cp file $RESDIR
done
echo "All results files are also copied to $RESDIR"

