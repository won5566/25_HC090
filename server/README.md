```markdown
# Flask Server — GNSS-Based Remote Control Bridge

This directory hosts the **Python Flask application** that manages
remote communication between the App Inventor interface and the ESP32 module.

---

## 🧠 Overview

The Flask server:
- Provides REST API endpoints for App Inventor  
- Sends TCP commands to the ESP32 bridge  
- Integrates camera stream and GNSS map visualization (optional)  
- Supports token-based access for safety

---

## ⚙️ Architecture

| Layer | Role | Folder |
|-------|------|--------|
| **App Inventor** | User control UI (mobile/tablet) | - |
| **Flask (Python)** | Command API + TCP relay | `server/app/` |
| **ESP32** | Wi-Fi TCP server (port 5001) | `esp32/` |
| **STM32** | Hardware control via UART | `stm32/` |

---

## 🧩 REST API Summary

| Method | Endpoint | Description |
|--------|-----------|-------------|
| `GET` | `/healthz` | Health check (returns `{ok:true}`) |
| `POST` | `/api/cmd` | Send control command to ESP32 |
| `POST` | `/api/video` | (optional) Start/stop camera stream |
| `POST` | `/api/gnss` | (optional) Update GNSS coordinates |

Example request (from App Inventor):
```json
{
  "token": "changeme-robot",
  "cmd": "FWD"
}
🧰 File Structure
server/
├── app/
│   ├── GNSS_SERVER.py        # Flask main app
│   ├── services/
│   │   └── tcp_client.py     # TCP communication with ESP32
│   └── templates/            # (optional) HTML UI templates
├── requirements.txt
└── README.md
🧾 TCP Connection Details
ESP32 Host: 192.168.0.xx (set in tcp_client.py)

Port: 5001

Timeout: 1.5 sec

Protocol: Plain text with \n line ending

Each Flask POST → triggers TCP send → waits for "ACK" from ESP32.

🚀 How to Run
Install dependencies:

cd server
python -m venv .venv
.\.venv\Scripts\activate
pip install -r requirements.txt
Run server:

python app\GNSS_SERVER.py
App Inventor endpoint:

arduino
http://<SERVER_IP>:8080/api/cmd
⚠️ Security
Uses static token (API_TOKEN = "changeme-robot") for API calls

Add simple authentication or network whitelist if needed

For external access, configure ngrok or port forwarding

🔗 Related Layers
ESP32 Firmware

STM32 Firmware

ROS2 Integration

👨‍💻 Author
Team L&K — Korea University of Technology and Education
Software: 이원무 (Python Flask server & control bridge)

Last updated: 2025-10-11