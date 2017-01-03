#!/usr/bin/env bash

sudo apt install -y  libopencv-*
sudo apt install -y  libboost-dev 
sudo apt install -y  cmake
sudo apt install -y  python-numpy 
sudo apt install -y  python-opencv 
sudo apt install -y  arduino
sudo apt install -y  python-pip
sudo apt install -y  gnuplot 
sudo apt install -y  python-tifffile python-pillow  python-matplotlib
sudo -E pip install gnuplotlib readchar  

echo "Now adding user to all the cool groups"
sudo gpasswd -a $USER dialout
if [ ! -f /etc/udev/rules.d/40-pgr.rules ]; then
    echo "Configuring for camera"
    bash ./PointGreyCamera/external/spin-conf
fi
echo "All done. You may like to reboot/logout"
