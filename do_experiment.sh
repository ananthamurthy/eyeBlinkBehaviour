#!/bin/bash - 
#===============================================================================
#
#          FILE: do_experiment.sh
# 
#         USAGE: ./do_experiment.sh  mouse_name session_name session_type
# 
#   DESCRIPTION: 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Dilawar Singh (), dilawars@ncbs.res.in
#  ORGANIZATION: NCBS Bangalore
#       CREATED: 12/16/2016 05:58:14 PM
#      REVISION:  ---
#===============================================================================

set -o nounset                              # Treat unset variables as an error


if [ $# -lt 3 ]; then
    echo "USAGE: $0 mouse_name session_num session_type"
    exit
fi

mkdir -p _build

( 
    echo "Building everything"
    cd _build 
    cmake -DANIMAL_NAME=$1 -DSESSION_NUM=$2 -DSESSION_TYPE=$3 ..
    make
    make upload 
)

echo "Running everything"
cd _build && make run
