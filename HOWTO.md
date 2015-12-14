# To build and upload code 

If your device is connected to serial port `/dev/ttyACM0` 

    $ ./build_and_upload.sh /dev/ttyACM0 

Will build and upload the code to device.

# To just build the code 

    $ make 

And you are done 

# To reboot boards

    $ ./reset_all_boards.sh 

It will reset all the boards connected to any serial port.

# To start new session, call

    $ ./record_and_plot.sh -n <mouse_index> -st <session_type> -sn <session_num>
    -p <port> 


