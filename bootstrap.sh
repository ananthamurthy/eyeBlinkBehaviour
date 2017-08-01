#!/usr/bin/env bash
set +x 
set -e

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
    sudo bash ./PointGreyCamera/external/spin-conf
fi

sudo mkdir -p /mnt/ramdisk
sudo chmod a+w /mnt/ramdisk

#echo "You may like mount a slice of ram to /mnt/ramdisk"
#echo "Something like the following needs to be added to /etc/fstab"
#printf "\ttmpfs /mnt/ramdisk tmpfs nosuid,size=1024M 0 0\n"
#printf "To make it permanent\n"

LINE="tmpfs /mnt/randisk tmpfs nosuid,size=1024M 0 0"
if grep -Fxq "$LINE" /etc/fstab; then
    echo "RAMDISK already configured in /etc/fstab"
else
    echo "$LINE" | sudo tee --append /etc/fstab 
fi
echo "All done. You may like to reboot/logout"
