# eyeBlinkBehaviour

Camera server (PointGrey) and arduino based behaviour setup. Everything is
automated using cmake. Both arduino and camera must be connected to compute
before doing the following.

To build and upload to arduino   

    $ mkdir _build 
    $ cd _build
    $ cmake -DANIMAL_NAME=k2 -DSESSION_NUM=1 -DSESSION_TYPE=2 ..
    $ make run              # to run the whole setup, (arduino and camera both must be connected)or
    $ make miniterm         # Just to test arduino board. (camera need to be connected)

Press `CTRL+C` in terminal to close the session. If just running `make
miniterm`, press `CTRL+]` to come out of miniterm (scrolling text).


# Dependencies

Most of them are in source.

- cmake 
- gnuplot-x11
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
