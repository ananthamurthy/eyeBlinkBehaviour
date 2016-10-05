set datafile separator ","
plot "< tail -n 10000 ./sensor.dat" using 2 with lines
pause 1
reread
