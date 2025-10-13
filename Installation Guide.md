# Installation Guide - GNSS-Based Remote Steering & Variable-Wheel Robot

This guide provides step-by-step instructions to install, configure, and run  
the complete software and hardware system for the GNSS-based remote-steering robot.

---

## 1. System Requirements

| Category | Specification |
|-----------|----------------|
| OS | Ubuntu 22.04 LTS (Jetson Orin Nano recommended) |
| ROS2 | Humble Hawksbill |
| Python | 3.10 or higher |
| Hardware | STM32F429ZIT6, ESP32 Dev Module, Arduino Mega 2560 |
| Network | Wi-Fi for Flask ↔ ESP32 communication |
| Camera | USB webcam (MJPG-Streamer compatible) |

---

## 2. Directory Structure

<pre>
project/
├─ ros2/ # GNSS + Flask visualization system
├─ server/ # Flask TCP bridge and control API
├─ esp32/ # TCP–UART bridge firmware
├─ stm32/ # Motor and servo control firmware
├─ appinventor/ # Android joystick application (.aia)
├─ scripts/ # Launch and automation scripts
└─ docs/ # Reports and reference documents
</pre>

---

## 3. ROS2 Environment Setup

### 3.1 Install ROS2 Humble (Ubuntu 22.04)

```bash
sudo apt update && sudo apt upgrade -y
sudo apt install curl gnupg lsb-release -y
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key \
  -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] \
http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | \
sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
sudo apt update
sudo apt install ros-humble-desktop python3-colcon-common-extensions -y
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
source ~/.bashrc
3.2 Build ROS2 Workspace
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws
colcon build
source install/setup.bash
4. Flask Server Setup
4.1 Create and Activate Virtual Environment
cd server
python -m venv .venv
source .venv/bin/activate       # Linux/Mac
# OR
.\.venv\Scripts\activate        # Windows PowerShell
pip install -r requirements.txt
4.2 Run Flask Server
python app/GNSS_SERVER.py
Access the control API at:

http://<SERVER_IP>:8080
5. ESP32 Firmware Setup
5.1 Environment
Arduino IDE (latest version)

Add ESP32 board package
URL: https://dl.espressif.com/dl/package_esp32_index.json

Select Board: ESP32 Dev Module

Set Port: COMx or /dev/ttyUSBx

5.2 Flash Firmware
Open esp32/GNSS_ESP32.ino
Update Wi-Fi credentials:
const char* ssid = "YOUR_SSID";
const char* pass = "YOUR_PASS";
Upload (Ctrl + U)
6. STM32 Firmware Setup
6.1 Requirements
STM32CubeIDE v1.14.0 or higher

ST-Link Programmer

NUCLEO-F429ZI board

6.2 Build and Flash
Open stm32/GNSS_STM32 project in CubeIDE

Connect board via ST-Link

Select Build → Debug/Run

Firmware will handle UART5 input and control BLDC + servos.

7. App Inventor Mobile Controller
Import appinventor/joystick.aia into MIT App Inventor 2

Update Flask endpoint IP (http://<SERVER_IP>:8080)

Build and install .apk on Android device

Use joystick and mode buttons to control the robot

8. Camera Streaming Setup
8.1 Install MJPG-Streamer
sudo apt install cmake libjpeg-dev build-essential
git clone https://github.com/jacksonliam/mjpg-streamer.git
cd mjpg-streamer/mjpg-streamer-experimental
make
8.2 Start Streaming
./mjpg_streamer -i "./input_uvc.so -r 480x240 -f 15" -o "./output_http.so -w ./www"
View the live stream:

http://<DEVICE_IP>:8080
9. Combined Launch (Optional)
Use the prepared script to start all modules:

cd scripts
./launch_all.sh
This launches:

GNSS nodes

Flask map server

Camera streaming

ngrok remote tunnels

10. Remote Access
10.1 Install and Configure ngrok
sudo snap install ngrok
ngrok config add-authtoken <YOUR_TOKEN>
10.2 Start All Tunnels
ngrok start --all
Access the Flask and camera services remotely using generated URLs.

11. Verification Checklist
Component	Check	Expected Result
GNSS Node	/fix topic publishing
Flask Server	Accessible at :8080/healthz
ESP32 Bridge	Receives and ACKs TCP commands
STM32	Motors/servos respond to commands
App Inventor	UI communicates correctly
Camera	Live stream visible on port 8080
ngrok	Remote access confirmed

12. License and Maintenance
All source code and documentation are provided for educational and research use.
No identifying information or organizational affiliation is included in this repository.