#!/bin/bash
set -e
if [ $# -lt 1 ]; then
    echo "USAGE: $0 data_dir"
    exit
fi

DIRS=`find $1 -type d -name "*SessionType*Session*"`
for d in $DIRS; do
    echo "Processing $d"
    python ./analyze_data.py -d $d  -o `pwd`/_results/`basename $d` | tee ${d}/log.log
done

