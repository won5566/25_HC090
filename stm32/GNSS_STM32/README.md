# STM32 Firmware — GNSS-Based Remote Steering & Variable-Wheel Robot

This directory contains the **firmware source code for the STM32F429ZIT6** microcontroller,  
which serves as the **main control unit** of the GNSS-based remote-steering all-terrain robot.

---

## 🧠 Overview

The STM32 board handles all **low-level actuation and feedback control**:
- **RS-485 communication** with the BLDC motor driver (BLC-400R4E)
- **PWM control** of 8 × servo motors (steering + variable wheels)
- **UART-based command reception** from the ESP32 (TCP bridge)
- **Mode switching** between manual, steering, and terrain adaptation
- **Real-time feedback and servo angle correction**

It acts as the “hardware brain” between the upper communication layer (ESP32 + Flask server)  
and the physical driving hardware (motors, servos, sensors).

---

## ⚙️ System Configuration

| Interface | Purpose | Pin / Peripheral |
|------------|----------|------------------|
| **USART6 (RS-485)** | BLDC driver control | TX/RX via RS-485 converter |
| **UART5** | Command RX from ESP32 | PC12 (TX) / PD2 (RX) |
| **TIM3 / TIM4** | PWM for 8 servo motors | CH1–CH4 each |
| **PB13 (GPIO)** | Buzzer output | Optional alert |
| **5V Servo Rail** | Variable wheel + steering servos | TIM output pins |
| **RS-485 Driver IC** | BLDC motor interface | TX only (half-duplex) |

---

## 🧩 Firmware Structure

stm32/
└── GNSS_STM32/
├── Core/ # main.c, interrupt handlers, user code
│ ├── Src/
│ └── Inc/
├── Drivers/ # HAL and CMSIS drivers
├── LWIP/ # Optional networking (if enabled)
├── Middlewares/ # External stacks or libraries
├── GNSS_STM32.ioc # CubeMX project configuration
├── .project / .cproject # CubeIDE build metadata
└── README.md # ← this file

yaml
코드 복사

---

## 🧾 Command Protocol

STM32 receives commands from the ESP32 via UART (TCP relay from Flask):
FWD → Move forward
BACK → Move backward
LEFT / RIGHT → Rotate in place
STOP → Stop all motors
STEER:<deg> → Set steering offset angle (e.g., STEER:45)
WHEEL:CW → Switch wheel to climbing mode
WHEEL:CCW → Switch wheel to terrain mode
WHEEL:NORMAL → Return to flat mode

yaml
코드 복사

Each command is terminated by a newline `\n` and parsed in the UART5 RX interrupt handler.

---

## 🛠️ Build & Flash Instructions

1. Open STM32CubeIDE → *File → Import → Existing Projects into Workspace*  
   → Select folder: `stm32/GNSS_STM32`
2. Connect the **Nucleo-F429ZI** board via ST-Link
3. Select **Debug** or **Release** build configuration
4. Click **Build** → **Run → Debug/Run**
5. The firmware will handle serial input over UART5 and control servos via TIM3/TIM4.

---

## 🔌 Hardware Connections (Summary)

| Module | Connection | Notes |
|--------|-------------|-------|
| ESP32 | UART5 (PD2, PC12) | Receives TCP-translated commands |
| BLDC Driver | USART6 (RS-485) | TX-only command link |
| Servo Motors | TIM3/TIM4 PWM | 8 channels total |
| Power | 12V → DC-DC 5V & 3.3V | Separate servo power rail |
| Buzzer | PB13 | Optional |

---

## 🧱 Dependencies

- **STM32CubeIDE v1.14.0+**
- **STM32 HAL Drivers** (auto-generated)
- **FreeRTOS (optional)** for scheduling
- **RS485 driver module**
- **Servo DS51150-270 (x8)**

---

## 🧩 Future Work

- Add encoder feedback to BLDC via RS-485 RX  
- Integrate GNSS correction data parsing (UART2 option)  
- Implement servo feedback and auto-alignment sequence  
- Synchronize with ROS2 node (via serial bridge)

---

## 👨‍💻 Author / Maintainer

**Team L&K — Korea University of Technology and Education (KOREATECH)**  
- 김진겸 (Team Lead)  
- 김형준  
- 이광민  
- 이원무  

> Firmware Development: *이원무 (STM32 & control logic)*

---

© 2025 L&K Robotics Team. All rights reserved.

yaml
코드 복사

---

## ✅ Commit Tag Convention
| Type | Example | Meaning |
|-------|----------|---------|
| `feat(stm32):` | `feat(stm32): add servo offset calibration logic` | New feature |
| `fix(stm32):` | `fix(stm32): correct RS485 packet framing` | Bug fix |
| `refactor(stm32):` | `refactor(stm32): merge TIM3 and TIM4 init` | Code cleanup |

---

To build:
1. Open GNSS_STM32 in CubeIDE
2. Build → Run
To upload:
Connect ST-Link to Nucleo-F429ZI and click Debug/Run
yaml
코드 복사

---

### 🔗 Related Layers
- [ESP32 Firmware](../esp32/)
- [Server (Flask Bridge)](../server/)
- [ROS2 GNSS Integration](../ros2/)

---

Last updated: 2025-10-11