# Flask Server - GNSS-Based Remote Control Bridge

This directory hosts the **Python Flask application**  
that manages remote communication between the App Inventor interface and the ESP32 module.

---

## Overview

The Flask server performs as the main communication bridge between the mobile App Inventor UI and the hardware layer.

Main functions:
- Provides REST API endpoints for remote control  
- Sends TCP commands to the ESP32 bridge  
- Optionally integrates camera streaming and GNSS map visualization  
- Supports basic token-based authentication for secure access  

---

## Architecture

| Layer | Role | Folder |
|-------|------|--------|
| App Inventor | User control interface (mobile/tablet) | - |
| Flask (Python) | Command API and TCP relay bridge | `server/app/` |
| ESP32 | Wi-Fi TCP server (port 5001) | `esp32/` |
| STM32 | Hardware control via UART | `stm32/` |

---

## REST API Summary

| Method | Endpoint | Description |
|--------|-----------|-------------|
| `GET` | `/healthz` | Health check – returns `{ "ok": true }` |
| `POST` | `/api/cmd` | Send a control command to the ESP32 |
| `POST` | `/api/video` | (optional) Start or stop camera streaming |
| `POST` | `/api/gnss` | (optional) Update GNSS coordinates |

**Example request (from App Inventor):**
```json
{
  "token": "changeme-robot",
  "cmd": "FWD"
}
File Structure
server/
├─ app/
│  ├─ GNSS_SERVER.py         # Flask main application
│  ├─ services/
│  │  └─ tcp_client.py       # TCP communication handler (Flask ↔ ESP32)
│  └─ templates/             # (optional) HTML templates for visualization
├─ requirements.txt
└─ README.md
TCP Connection Details
Parameter	Description
ESP32 Host	192.168.0.xx (set in tcp_client.py)
Port	5001
Timeout	1.5 seconds
Protocol	Plain text, newline (\n) terminated commands

Each Flask POST request triggers a TCP send event and waits for "ACK" response from the ESP32.

How to Run
1. Install Dependencies
cd server
python -m venv .venv
source .venv/bin/activate        # Linux/Mac
# OR
.\.venv\Scripts\activate         # Windows PowerShell
pip install -r requirements.txt
2. Run the Flask Server
python app/GNSS_SERVER.py
Default API Endpoint for App Inventor:

arduino
http://<SERVER_IP>:8080/api/cmd
Security Notes
Uses a static API token (API_TOKEN = "changeme-robot") for all incoming requests.

Add authentication or IP whitelisting for better protection.

When using remote access, set up ngrok or port forwarding with a secure tunnel.

Related Components
ESP32 Firmware: TCP–UART Bridge for command forwarding

STM32 Firmware: Motor and servo controller

ROS2 Layer: GNSS + Flask integration for data visualization

Maintained as part of the GNSS-Based Variable-Wheel Robot Project.
Module: Flask Web Server and Control Bridge
Last updated: 2025-10-11