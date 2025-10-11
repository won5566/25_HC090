# ROS2 System — GNSS JSON Bridge & Web Server Integration

This directory contains the **ROS2 components** used for GNSS data handling and web visualization  
in the GNSS-based remote steering and variable-wheel all-terrain robot project.

---

## 🧠 Overview

The ROS2 layer performs two main functions:

| Module | Role | Description |
|---------|------|-------------|
| **gnss_json_bridge** | GNSS → JSON Converter | Reads GNSS NavSatFix messages and saves them to `/tmp/gnss_data.json` |
| **Web_Server** | Flask-based Web Visualization | Provides `/position` API and renders GNSS marker on a real-time map |

These two modules work together to provide **end-to-end GNSS telemetry visualization**  
from the robot’s onboard sensors to a web-based interface.

---

## ⚙️ Folder Structure

ros2/
├── gnss_json_bridge/ # ROS2 Python node (NavSatFix → JSON)
└── Web_Server/ # Flask server (JSON → Web UI)


---

## 🛰️ GNSS → Web Visualization Data Flow

[ZED-F9P GNSS Sensor]
↓ (ROS2 NavSatFix message)
[gnss_json_bridge/gnss_to_json.py]
↓ (writes JSON)
[/tmp/gnss_data.json]
↓
[Web_Server/app.py]
↓
[/position API]
↓
[index.html + main.js]
↓
[Real-time GNSS marker on map]


---

## 🧩 How It Works

1. **GNSS Data Node (`gnss_json_bridge`)**
   - Subscribes to `/fix` or `/gnss` topic (sensor_msgs/NavSatFix)
   - Converts latitude, longitude, altitude, and timestamp to JSON
   - Saves to `/tmp/gnss_data.json` every time a new message arrives

2. **Web Server (`Web_Server`)**
   - Flask server running on port `5000`
   - Reads `/tmp/gnss_data.json` and serves it via `/position` endpoint
   - Uses `index.html` + `main.js` to visualize GNSS location on a map

---

## ⚙️ Example Commands

### 1️⃣ Build and Source Workspace
```bash
cd ~/ros2_ws
colcon build
source install/setup.bash

2️⃣ Run GNSS Node
ros2 run gnss_json_bridge gnss_to_json

3️⃣ Run Web Server
cd Web_Server
python app.py
Then open your browser and go to:

http://<device_ip>:5000
You’ll see the GNSS marker updating on the map in real time.

🧱 Notes
/tmp/gnss_data.json acts as the bridge file between ROS2 and Flask

Both modules can be launched together later using a single ROS2 launch file

Designed for use on Jetson Orin / Ubuntu 22.04 / ROS2 Humble

👨‍💻 Maintainer
Team L&K — Korea University of Technology and Education (KOREATECH)
ROS2 GNSS & Web Integration: 김형준


---