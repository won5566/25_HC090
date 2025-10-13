# Mobile Robot Equipped with GNSS-Based Remote Steering and Variable Wheels

> **All-Terrain Mobile Robot** integrating multi-layer communication, GNSS localization, ROS2-based visualization, and real-time steering control for terrain adaptability.

---

## Project Overview

This project presents an **all-terrain mobile robot** that integrates a **GNSS-based remote steering system** and a **variable-diameter wheel mechanism** to achieve precise motion control and terrain adaptability.

Developed by **Team KLON (KOREATECH)**, the system combines embedded hardware (STM32, Arduino, ESP32), ROS2-based GNSS visualization, and a Flask-based remote UI.

---

## System Architecture

<pre>
[Tablet / App Inventor UI]
        ↓ (TCP/IP commands)
[Flask Web Server]
        ↓
[ESP32]  ← Wi-Fi TCP Relay
        ↓
[STM32 Controller]
 ├─ RS-485 → BLDC Motors (4WD)
 ├─ PWM   → Steering Servos (4WIS)
 └─ UART5 → ESP32 Command Interface
        ↓
[Arduino Mega Sub #1] → Wheel Alignment (IR Sensors)
[Arduino Mega Sub #2] → 2-Axis Camera Gimbal (MPU6050 PID)
</pre>

---

## Key Features

| Category | Description |
|-----------|-------------|
| **GNSS Localization** | ZED-F9P RTK GNSS integrated with ROS2 NavSatFix; JSON bridge to Flask map visualization |
| **Remote Control** | Real-time teleoperation via Flask Web UI and App Inventor joystick |
| **Variable Wheel System** | 4-bar linkage mechanism allowing wheel radius change (140 mm ↔ 200 mm) |
| **Independent Steering** | Servo-driven 0°–270° Ackermann steering for 4-wheel control |
| **Auto Alignment** | IR-based wheel zero-position calibration (Arduino Sub #1) |
| **Camera Stabilization** | 2-axis gimbal controlled by MPU6050 + PID (Arduino Sub #2) |
| **Visualization** | Flask-based GNSS map + live video feed |
| **Modular Architecture** | ROS2 + Flask + MCU layers separated for maintainability |

---

## Repository Structure

<pre>
Mobile-Robot-Equipped-with-GNSS-Based-Remote-Steering-and-Variable-Wheels/
│
├─ appinventor/                  # Android joystick app (.aia + README)
│
├─ arduino/
│  ├─ mega_sub1_ir_alignment/    # IR-based wheel alignment
│  └─ mega_sub2_gimbal/          # 2-axis camera gimbal controller
│
├─ cad/
│  ├─ Variable Wheel/                   # Variable-diameter wheel assembly
│  ├─ Steering/                   # Steering gearbox assembly
│  └─ Camera/                     # Gimbal camera bracket
│
├─ docs/                         # Papers, reports, and posters
│
├─ esp32/                        # TCP relay between Flask and STM32
│
├─ ros2/                         # GNSS→JSON bridge + Flask web visualization
│
├─ scripts/                      # Auto-execution and deployment scripts
│
├─ server/                       # Flask + TCP server core
│
└─ stm32/GNSS_STM32/             # Firmware: RS-485 (BLDC), PWM (servo), UART5 (ESP32)
</pre>

---

## Software Highlights

### ROS2 Layer

- Converts **GNSS NavSatFix → JSON** for Flask integration  
- Publishes `/position` API for live GNSS visualization  
- Built with **ROS2 Humble** on **Jetson Orin Nano (Ubuntu 22.04)**  

---

### Flask Web Server

- Renders map visualization and streams live video  
- Relays TCP commands to ESP32  
- Accessible remotely via **port forwarding or ngrok**

---

### App Inventor Joystick

- Sends directional commands (Front / Stop / Back) via TCP  
- Switches **wheel modes (CW / NORMAL / CCW)**  
- Adjusts steering angle through slider input  
- Displays GNSS map + Flask live video feed  

---

### STM32 Main Controller

- Controls **BLDC motors (RS-485)** and **servo steering (PWM)**  
- Communicates with ESP32 via **UART5 (115200 bps)**  
- Performs **mode switching, offset correction, and motion control**

---

### Arduino Submodules

| Submodule | Function |
|------------|-----------|
| **Sub #1 (Mega)** | IR sensor-based automatic wheel alignment |
| **Sub #2 (Mega)** | 2-axis gimbal stabilization using MPU6050 PID |

---

## Mechanical Design

All CAD models are designed in **SolidWorks 2023**, divided into three major subsystems.

| Subsystem | Description |
|------------|-------------|
| **Variable Wheel** | Adjustable 4-bar linkage wheel (Ø140–200 mm) |
| **Steering Gearbox** | Servo-driven Ackermann steering assembly |
| **Camera Gimbal** | Dual-axis stabilization mount for onboard camera |

> Export formats: `.SLDPRT`, `.SLDASM`, `.STEP`, `.STL`

---

## Documentation

| File | Description |
|------|-------------|
| `25년_SW개발_HW제작성설계서_응용하드웨어.pptx` | Hardware and software design specification for the Applied Hardware project |
| `2025 한이음 드림업 발표.pptx` | Final presentation for the 2025 Hanium Dream-Up project |
| `2025년 한이음 드림업 개발보고서.hwp` | Development report for the 2025 Hanium Dream-Up project |
| `논문.hwp` | Research paper on the GNSS-based variable-wheel terrain robot |
| `졸작 포스터논문.pptx` | Capstone project poster presentation document |

---

## Technical Stack

| Domain | Tools / Hardware |
|--------|------------------|
| **Microcontrollers** | STM32F429ZIT6, ESP32, Arduino Mega 2560 |
| **Communication** | UART, RS-485, TCP/IP, PWM |
| **Software** | ROS2 Humble, Python 3.10, Flask, OpenCV |
| **Design Tools** | SolidWorks 2023, MIT App Inventor 2 |
| **Sensors** | ZED-F9P GNSS, MPU6050 IMU, IR Sensors |
| **Platform** | Jetson Orin Nano (Ubuntu 22.04), Windows 11 |

---

## Performance & Results

- **RTK-GNSS Precision:** RMS ≈ 2.3 cm (Max Error < 4 cm)  
- **Steering Response Delay:** < 100 ms  
- **Stair Climbing Capability:** up to 15 cm step height  
- **Long-term Stability:** > 30 min continuous operation  
- **Full Integration:** Indoor + Outdoor tested  

---

## Application Fields

| Field | Example Use |
|--------|--------------|
| **Disaster Response** | Remote rescue in hazardous environments |
| **Agriculture** | GNSS-based crop monitoring and control |
| **Defense / Surveillance** | Remote observation and reconnaissance |
| **Education** | Learning platform for GNSS, ROS2, and embedded systems |

---

## Summary

**Structurally Complete** – Independent HW · SW · Web · UI layers  
**Professionally Documented** – Each subsystem has its own README  
**Public & Reproducible** – Ready for academic or competition use  
**Demonstrated Integration** – GNSS-based, real-time, terrain-adaptive robot  

---

[GitHub Repository](https://github.com/won5566/Mobile-Robot-Equipped-with-GNSS-Based-Remote-Steering-and-Variable-Wheels)

