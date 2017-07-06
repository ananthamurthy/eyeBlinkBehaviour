Camera server (PointGrey) and arduino based behaviour setup. Everything is
automated using cmake. Both arduino and camera must be connected to compute
before doing the following.

# Download and setup 

To download the code from a particular branch

     $ git clone --recursive -b bhumika https://github.com/ananthamurthy/eyeBlinkBehaviour 
     $ cd eyeBlinkBehaviour 
     $ ./bootstap.sh    # To setup your Ubuntu system.
     
The script `bootstap.sh` will try to configure your system. You must have `sudo` permissions. And you
must be using `Ubuntu` since the camera server only compiles on Ubuntu. In case, something odd happens, 
raise an issue on github.

Once bootstrap is successful, to build and upload to arduino   

    $ mkdir _build 
    $ cd _build
    $ cmake -DANIMAL_NAME=k2 -DSESSION_NUM=1 -DSESSION_TYPE=2 ..
    $ make run              # to run the whole setup, (arduino and camera both must be connected)or
    $ make miniterm         # Just to test arduino board. (camera need to be connected)

Press `CTRL+C` in terminal to close the session. If just running `make
miniterm`, press `CTRL+]` to come out of miniterm (scrolling text).

## CMake options

### Port

If you need to change the arduino port, pass `-DPORT=/path/to/port` option to cmake. On a linux system, e.g.

     $ cmake -DPORT=/dev/ttyACM1 -DANIMAL_NAME=k2 -DSESSION_NUM=1 -DSESSION_TYPE=2 ..

# Dependencies

Most of them are in source.

- cmake 
- gnuplot-x11
- python-serial
- pip install readchar
- pip install gnuplotlib


# Commands

- __Puff__ : p
- __Tone__ : t
- __Led__ : l
- __Select__ : s 
- __Reboot__ : ctrl+c

# What is being prinited.

See function `write_data_line` in file `src/main.ino`.
