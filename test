#!/bin/bash - 
#===============================================================================
#
#          FILE: test.sh
# 
#         USAGE: ./test.sh 
# 
#   DESCRIPTION:  test model.
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Dilawar Singh (), dilawars@ncbs.res.in
#  ORGANIZATION: NCBS Bangalore
#       CREATED: 09/29/2016 04:38:58 PM
#      REVISION:  ---
#===============================================================================

set -x
set -e
set -o nounset                              # Treat unset variables as an error

#make  upload
#miniterm.py -p /dev/ttyACM0 -b  38400

./reset_all_boards.sh 
./build_and_upload.sh
rm -rf *.log
#miniterm.py -p /dev/ttyACM0 -b  38400
~/Scripts/miniterm.hs /dev/ttyACM0 38400 
#./record_and_plot.sh -n 1 -st 1 -sn 1
