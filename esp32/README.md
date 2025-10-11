# ESP32 Firmware — GNSS-Based Remote Steering Bridge

This directory contains the **ESP32 firmware** that serves as a **TCP–UART bridge**
between the Flask server (Python) and the STM32 main controller.

---

## 🧠 Overview

The ESP32 acts as a **middle communication layer**:
- Receives TCP commands from the Flask server (port 5001)
- Forwards parsed commands to STM32 via UART2 (Serial2)
- Sends acknowledgements or feedback to the server
- Manages Wi-Fi connection stability and reconnection

---

## ⚙️ System Configuration

| Interface | Purpose | Default Pin |
|------------|----------|-------------|
| **UART2 (Serial2)** | STM32 Command TX/RX | TX: GPIO17 / RX: GPIO16 |
| **Wi-Fi STA Mode** | Connect to local router | SSID, PASS defined in code |
| **TCP Server** | Receives Flask commands | Port **5001** |
| **Baud Rate** | Communication with STM32 | 115200 bps |

---

## 🧩 Firmware Behavior

1. **Wi-Fi Initialization**  
   ESP32 connects to a predefined SSID and starts a TCP server.

2. **TCP Command Handling**  
   - Waits for a client (Flask) connection  
   - Reads one line of command (terminated by `\n`)  
   - Prints or forwards it to STM32 via UART2  
   - Replies with `"ACK:<cmd>"` to confirm receipt

3. **UART Forwarding**  
   - Commands like `FWD`, `BACK`, `STEER:45`, `WHEEL:CW`  
     are sent to STM32  
   - Optional: Receive STM32 feedback and relay to Flask

---

## 🛠️ Build & Flash

1. Open **Arduino IDE**  
2. Select:
   - **Board:** ESP32 Dev Module  
   - **Port:** (check COMxx or /dev/ttyUSBx)
3. Open `GNSS_ESP32.ino`
4. Update Wi-Fi credentials:
   ```cpp
   const char* ssid = "YOUR_SSID";
   const char* pass = "YOUR_PASS";
Upload to the board.

🔍 Flask ↔ ESP32 Protocol
From	To	Example	Description
Flask	ESP32	FWD\n	Command to move forward
Flask	ESP32	STEER:45\n	Set steering angle
ESP32	Flask	ACK:FWD	Acknowledgement
ESP32	STM32	FWD\n	Forwarded UART command

📶 Typical Connection Flow
[App Inventor] → [Flask Server (Python)] → TCP → [ESP32] → UART → [STM32]
👨‍💻 Author
Team L&K — GNSS-Based Remote Steering Robot
Firmware: 이원무 (ESP32 bridge communication)

Last updated: 2025-10-11