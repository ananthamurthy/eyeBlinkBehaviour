# To build and upload code 

    $ mkdir _build
    $ cd _build 
    $ cmake .. # options if any in -DOPTION=val format
    $ make 

To run the whole setup.

    $ make run
    
# Spefifying session type 

CMake option `-DSESSION_TYPE=S` specify `SOUND` trial. `-DSESSION_TYPE=L` is for 
`LIGHT` trial. `-DSESSION_TYPE=M` is for `MIXED` trials.

# To analyze the data post-behaviour

Lets assume your data is stored in `~/DATA/k3_1_1/`, you need to do the
following

    $ cd analysis 
    $ python analyze_trial.py ~/DATA/k3_1_1/

In directory `~/DATA/k3_1_1/`, it will generate `_analysis` folder where all
plots are stored.

