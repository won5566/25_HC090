# ROS2 System - GNSS JSON Bridge & Web Server Integration

This directory contains the **ROS2 components** used for GNSS data handling and web visualization  
in the GNSS-based remote steering and variable-wheel all-terrain robot project.

---

## Overview

The ROS2 layer performs two primary functions:

| Module | Role | Description |
|---------|------|-------------|
| `gnss_json_bridge` | GNSS → JSON Converter | Reads GNSS NavSatFix messages and saves them to `/tmp/gnss_data.json` |
| `Web_Server` | Flask-based Web Visualization | Provides `/position` API and renders the GNSS marker on a real-time map |

These two modules work together to provide **end-to-end GNSS telemetry visualization**,  
bridging the robot’s onboard sensors to a web-based interface.

---

## Folder Structure

ros2/
├─ gnss_json_bridge/ # ROS2 Python node (NavSatFix → JSON)
└─ Web_Server/ # Flask server (JSON → Web UI)


---

## GNSS → Web Visualization Data Flow

<pre>
[ZED-F9P GNSS Sensor]
        ↓  (ROS2 NavSatFix message)
[gnss_json_bridge/gnss_to_json.py]
        ↓  (writes JSON)
[/tmp/gnss_data.json]
        ↓
[Web_Server/app.py]
        ↓
[/position API]
        ↓
[index.html + main.js]
        ↓
[Real-time GNSS marker displayed on map]
</pre>

---

## How It Works

1. **GNSS Data Node (`gnss_json_bridge`)**
   - Subscribes to `/fix` or `/gnss` topic (`sensor_msgs/NavSatFix`)
   - Converts latitude, longitude, altitude, and timestamp into JSON
   - Saves JSON data to `/tmp/gnss_data.json` whenever a new message is received  

2. **Web Server (`Web_Server`)**
   - Flask-based web application running on port `5000`
   - Reads `/tmp/gnss_data.json` and serves it through the `/position` endpoint  
   - Uses `index.html` and `main.js` to visualize GNSS coordinates on an interactive map  

---

## Example Commands

### 1. Build and Source the ROS2 Workspace
```bash
cd ~/ros2_ws
colcon build
source install/setup.bash
2. Run the GNSS Node
ros2 run gnss_json_bridge gnss_to_json
3. Run the Flask Web Server
cd Web_Server
python app.py
Then open your browser and go to:

http://<device_ip>:5000
You will see the GNSS marker updating on the map in real time.

Notes
/tmp/gnss_data.json acts as a bridge file between the ROS2 node and Flask web server.

Both modules can later be launched together using a single ROS2 .launch.py file.

Designed for use on Jetson Orin Nano / Ubuntu 22.04 / ROS2 Humble.

Flask visualization is optimized for lightweight rendering on embedded systems.

Maintained as part of the GNSS-Based Variable-Wheel Robot Project.
Module: ROS2 GNSS & Web Integration
Last updated: 2025-10-11