# Running ./read_mouse_delta.py

To test the mouse:

    $ python ./read_mouse_delta.py 

You will get velocity and direction; direction is not well tested yet.

## Notes

By default it reads the second mouse `/dev/input/mouse1`. It should be
sufficient for most purpose.

Before you run this script, you need to add user to group `input`. If you are
not in user group input, then do the following

    $ gpasswd -a USER input

Logout and login again and run the script. 


