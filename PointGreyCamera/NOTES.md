                                        Tuesday 06 December 2016 11:27:46 AM IST

With maximum resolution of 1280x1028, maximum frame rate achievavle was about 40
to 55 FPS. Reduced the resolution to half and FPS went upto 60 FPS.

To increase FPS further, I turn off auto-exposure and set it to 2000 uS. At this
value, I get FPS ~77. Reducing auto-exposure futher does not imporve FPS. With
lighterning condition of my desk, the picture acquired was decent.

Making socket NONBLOCKING reduces the FPS to 10. Don't know why. Need to know in
detail what O_NON_BLOCK actually do. I suspected that this just make socket
read/write non-blocking and should improve the speed of socket.

Reading frame in chunks of 4096 gives speed of 60 FPS.  Increasing it to ten
times more gives FPS of 66. Increasing it further to frame size does not improve
it any more  Increasing it to ten times more gives FPS of 66. Increasing it
further to frame size does not improve it. Should I create a socket in RAM after
mounting a slice of RAM in filesystem? No. It didn't help at all. The buffers
are already in RAM.

commit c48808e7e0b34185ec785e6c24464574650708a0 achieves 100 FPS.

