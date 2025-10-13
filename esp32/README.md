# ESP32 Firmware - GNSS-Based Remote Steering Bridge

This directory contains the **ESP32 firmware** that serves as a **TCP–UART bridge**  
between the Flask server (Python) and the STM32 main controller.

---

## Overview

The ESP32 acts as a **communication bridge** between the upper Flask server and the lower STM32 unit.

Main functions:
- Receives TCP commands from the Flask server (port 5001)
- Forwards parsed commands to STM32 via UART2 (Serial2)
- Sends acknowledgements or feedback to the Flask server
- Manages Wi-Fi connection stability and automatic reconnection

---

## System Configuration

| Interface | Purpose | Default Pin / Setting |
|------------|----------|------------------------|
| UART2 (Serial2) | STM32 command TX/RX | TX: GPIO17 / RX: GPIO16 |
| Wi-Fi (STA Mode) | Connects to local router | SSID and password defined in code |
| TCP Server | Receives Flask commands | Port 5001 |
| Baud Rate | Communication with STM32 | 115200 bps |

---

## Firmware Behavior

1. **Wi-Fi Initialization**  
   - Connects to the configured Wi-Fi network (STA mode)  
   - Starts a TCP server on port 5001  

2. **TCP Command Handling**  
   - Waits for Flask client connection  
   - Reads one line command (terminated by `\n`)  
   - Prints or forwards the command to STM32 via UART2  
   - Replies with `ACK:<cmd>` for confirmation  

3. **UART Forwarding**  
   - Commands such as `FWD`, `BACK`, `STEER:45`, `WHEEL:CW` are sent to STM32  
   - (Optional) Receives feedback from STM32 and relays it to Flask  

---

## Build & Flash Instructions

1. Open **Arduino IDE**  
2. Select the following:  
   - **Board:** ESP32 Dev Module  
   - **Port:** COMxx (Windows) or /dev/ttyUSBx (Linux)  
3. Open `GNSS_ESP32.ino`  
4. Update Wi-Fi credentials:

   ```cpp
   const char* ssid = "YOUR_SSID";
   const char* pass = "YOUR_PASS";
Click Upload (Ctrl + U) to flash the firmware.

Monitor serial output at 115200 bps to verify connection.

Flask–ESP32–STM32 Protocol Mapping
From	To	Example	Description
Flask	ESP32	FWD\n	Move forward
Flask	ESP32	STEER:45\n	Set steering angle to 45°
ESP32	Flask	ACK:FWD	Command acknowledgement
ESP32	STM32	FWD\n	Forwarded UART command

Typical Communication Flow
<pre> [App Inventor] → [Flask Server (Python)] → TCP → [ESP32] → UART → [STM32] </pre>
Integration Notes
Operates as an independent Wi-Fi relay node.

Can be used with any TCP client (Flask, Python, or mobile app).

Automatically reconnects to Wi-Fi when disconnected.

Designed for seamless integration in multi-layer GNSS-based control systems.

Maintained as part of the GNSS-Based Variable-Wheel Robot Project.
Module: ESP32 TCP–UART Bridge Firmware
Last updated: 2025-10-11