# Scripts - GNSS and Camera Streaming Launcher

This directory contains command-line and automation scripts  
used to run the **GNSS localization pipeline**, **Flask web visualization**, and **camera streaming service**  
for the GNSS-based remote steering and variable-wheel robot project.

---

## Overview

The scripts in this folder are designed to start the following components:

1. **GNSS Data Node (ROS2)**
2. **GNSS Visualization Web Server (Flask)**
3. **Camera Streaming Service (mjpg-streamer)**
4. **ngrok Multi-Tunnel (remote access)**

All commands can be executed manually from the terminal  
or automated later via `.sh` or `.bat` launcher files.

---

## Terminal 1 – GNSS Driver Node

```bash
source ~/ros2_ws/install/setup.bash
ros2 run nmea_navsat_driver nmea_serial_driver \
--ros-args -p port:=/dev/ttyACM0 -p baud:=115200
Purpose:
Reads NMEA GNSS messages from the ZED-F9P module and publishes them as sensor_msgs/NavSatFix.

Terminal 2 – GNSS Listener Node
source ~/ros2_ws/install/setup.bash
ros2 run gnss_tools ros2_gnss_listener
Purpose:
Subscribes to GNSS topics and prints position data for verification.

Terminal 3 – Flask Web Map Server
cd ~/gnss_map
python3 app.py
Purpose:
Starts the Flask-based web visualization that displays GNSS coordinates
from /tmp/gnss_data.json on a real-time map at http://localhost:5000.

Camera Streaming Service
cd mjpg-streamer/mjpg-streamer-experimental
./mjpg_streamer -i "./input_uvc.so -r 480x240 -f 15" -o "./output_http.so -w ./www"
Purpose:
Launches a lightweight MJPG-Streamer server to provide live video feed from the robot’s camera
at http://<device_ip>:8080.

Parameters:

-r 480x240 → video resolution

-f 15 → frame rate (fps)

-w ./www → default web UI directory

ngrok Tunnel (Remote Access)
ngrok start --all
Purpose:
Opens secure remote access tunnels for both the Flask GNSS map and the camera stream,
allowing control and visualization from outside the local network.

Suggested Launch Order
Step	Action	Terminal
1	Run GNSS serial driver (nmea_serial_driver)	Terminal 1
2	Run GNSS listener (ros2_gnss_listener)	Terminal 2
3	Run Flask map server (app.py)	Terminal 3
4	Start camera streaming (mjpg_streamer)	Terminal 4 (optional)
5	Run ngrok tunnels (ngrok start --all)	Terminal 5

Automation Note
To simplify repeated launches, create a shell script (e.g., launch_all.sh):

#!/bin/bash
gnome-terminal -- bash -c "source ~/ros2_ws/install/setup.bash && ros2 run nmea_navsat_driver nmea_serial_driver --ros-args -p port:=/dev/ttyACM0 -p baud:=115200"
sleep 2
gnome-terminal -- bash -c "source ~/ros2_ws/install/setup.bash && ros2 run gnss_tools ros2_gnss_listener"
sleep 2
gnome-terminal -- bash -c "cd ~/gnss_map && python3 app.py"
sleep 2
gnome-terminal -- bash -c "cd mjpg-streamer/mjpg-streamer-experimental && ./mjpg_streamer -i './input_uvc.so -r 480x240 -f 15' -o './output_http.so -w ./www'"
sleep 2
gnome-terminal -- bash -c "ngrok start --all"
Make the file executable:

chmod +x launch_all.sh
Then run:

./launch_all.sh
Maintained as part of the GNSS-Based Variable-Wheel Robot Project.
Module: System Launch Scripts
Last updated: 2025-10-11