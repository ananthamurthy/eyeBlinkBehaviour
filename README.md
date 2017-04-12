# eyeBlinkBehaviour

Camera server (PointGrey) and arduino based behaviour setup. Everything is
automated using cmake.

To build and upload to arduino   

    $ mkdir _build 
    $ cd _build
    $ cmake ..
    $ make run              # to run the whole setup, or
    $ make miniterm         # Just to test arduino board. 


# Dependencies

- cmake 
- gnuplot-x11
- pip install readchar


# Commands

- __Puff__ : p
- __Tone__ : t
- __Led__ : l
- __Select__ : s 
- __Reboot__ : ctrl+c
