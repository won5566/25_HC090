# 📱 App Inventor — GNSS Remote Steering Controller

This folder contains the **App Inventor project (.aia)** used to remotely control  
the all-terrain robot equipped with GNSS-based steering and variable wheels.  
The app provides an intuitive interface for driving, mode switching, and map-based tracking.

---

## 🧭 Overview

The App Inventor project (`joystick.aia`) was developed to send **TCP/IP control commands**  
to the Flask server, which relays them to the **ESP32 → STM32 → motor system**.

It integrates:
- **Real-time GNSS map visualization**
- **Joystick-style remote control (Forward / Stop / Back)**
- **Wheel mode switching (CW / NORMAL / CCW)**
- **Steering angle slider control**
- **Embedded live video streaming via Flask web server**

---

## 📸 Application UI

![App Screenshot](./ui_preview.png)

> **Figure:** App interface displaying live video, GNSS location, and control panel.

**UI Elements:**

| Section | Description |
|----------|--------------|
| 🛰️ *GNSS 위치 지도* | Displays real-time robot position from Flask `/position` API |
| 🎥 *Live Video* | Streams camera feed via Flask URL (`http://192.168.137.208`) |
| 🕹️ *Control Buttons* | Forward / Stop / Back control (TCP commands) |
| ⚙️ *Wheel Mode* | Switch between terrain modes (CCW, NORMAL, CW) |
| 🔄 *Steering Slider* | Adjusts steering value between 0° and 270° |

---

## ⚙️ Communication Flow

[App Inventor UI]
↓ (TCP/IP commands)
[Flask Web Server]
↓
[ESP32]
↓
[STM32 Controller]
↓
[BLDC + Steering + Variable Wheel System]

---

## 🧩 Technical Details

| Parameter | Description |
|------------|--------------|
| App Platform | MIT App Inventor 2 |
| Protocol | TCP/IP Socket |
| Host Address | 192.168.137.208 (Server IP via port forwarding) |
| Data Format | ASCII string commands (e.g., `F`, `B`, `S`, `CW`, `CCW`) |
| Update Rate | ~100 ms per command |
| Compatibility | Android 7.0+ |

---

## 🚀 How to Use

1. Open **MIT App Inventor** → *Import project (.aia)* → select `joystick.aia`
2. Edit IP field (`http://192.168.137.208`) to match your Flask server address
3. Connect your Android device via **AI2 Companion** or build `.apk`
4. Start the Flask server (`server/app.py`)
5. Tap **Front / Stop / Back** to move the robot, or adjust steering and wheel mode
6. View GNSS map updates and live video feed in real time

---

## 🧠 Design Notes

- The app UI was optimized for **7~10 inch tablets**
- The GNSS map uses a **web-view** component linked to Flask `/map` route
- The steering slider outputs an integer value (0–270), normalized for servo PWM
- Each mode button triggers a distinct packet for **STM32 mode switching logic**

---

**Maintained by Team L&K**  
KOREATECH — GNSS-Based Variable Wheel Robot Project  
Developed by: 김진겸