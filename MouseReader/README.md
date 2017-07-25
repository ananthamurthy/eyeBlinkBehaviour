# Running ./read_mouse_delta.py

To be able to run this script, you must be in group `input`. Make sure that
you are in this group https://stackoverflow.com/questions/350141/how-to-find-out-what-group-a-given-user-has. If 
you are not in `input` group, add yourself [https://askubuntu.com/questions/79565/how-to-add-existing-user-to-an-existing-group].

To run,
    $ python ./read_mouse_delta.py 

You will get velocity and direction.

## Notes

By default it reads the second mouse `/dev/input/mouse1`. It should be
sufficient for most purpose.
