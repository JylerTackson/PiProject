#!/bin/bash

#This bash script only needs to be ran once on the raspberry pi.
#This bash script initalizes the pi with the necessary dependencies, sets up the camera, and tests the camera.
#

echo "1) Updating system apt..."
sudo apt update && sudo apt upgrade -y

echo "2) Installing libcamera and OpenCV..."
sudo apt install -y libcamera-apps libopencv-dev cmake g++ git

echo "3) Enabling camera interface in raspi-config..."
sudo raspi-config nonint do_camera 0

echo "4) Testing camera with libcamera-hello..."
libcamera-hello -t 3000                         #Run camera for 3000ms

echo "✅ Arducam OV5647 (CSI) camera setup complete."


#How to run the bash script from the Ubuntu Terminal:
#   1) In Shell navitage to scripts folder
#   2) chmod +x setup_camera.sh     --This changes the .sh files permissions to allow it to run like a program.
#   3) Run the script:      ./setup_camera.sh