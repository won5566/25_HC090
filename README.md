# ?쎇截?Mobile Robot Equipped with GNSS-Based Remote Steering and Variable Wheels

> **All-Terrain Mobile Robot** integrating multi-layer communication, GNSS localization, ROS2-based visualization, and real-time steering control for terrain adaptability.

---

## ?뱲 Project Overview

This project presents an **all-terrain mobile robot** that integrates a **GNSS-based remote steering system** and a **variable-diameter wheel mechanism** to achieve precise motion control and terrain adaptability.

Developed by **Team L&K (KOREATECH)**, the system combines embedded hardware (STM32, Arduino, ESP32), ROS2-based GNSS visualization, and a Flask-based remote UI.

---

## ?㎛ System Architecture

[Tablet / App Inventor UI]
??(TCP/IP commands)
[Flask Web Server]
??[ESP32] ??Wi-Fi TCP Relay
??[STM32 Controller]
?쒋? RS-485 ??BLDC Motors (4WD)
?쒋? PWM ??Steering Servos (4WIS)
?붴? UART5 ??ESP32 Command Interface
??[Arduino Mega Sub #1] ??Wheel Alignment (IR Sensors)
[Arduino Mega Sub #2] ??2-Axis Camera Gimbal (MPU6050 PID)


---

## ?숋툘 Key Features

| Category | Description |
|-----------|-------------|
| ?쎇截?**GNSS Localization** | ZED-F9P RTK GNSS module integrated with ROS2 NavSatFix; JSON bridge to Flask for map visualization |
| ?렜 **Remote Control** | Real-time teleoperation via Flask Web UI and App Inventor Joystick |
| ?숋툘 **Variable Wheel System** | 4-bar linkage mechanism allowing wheel radius change (140 mm ??200 mm) |
| ?㎛ **Independent Steering** | Servo-driven 0째??70째 Ackermann steering for 4-wheel control |
| ?뵩 **Auto Alignment** | IR-based wheel zero-position calibration (Arduino Sub #1) |
| ?렏 **Camera Stabilization** | 2-axis gimbal controlled by MPU6050 + PID (Arduino Sub #2) |
| ?뙋 **Visualization** | Flask-based GNSS map + live video feed |
| ?㎥ **Modular Architecture** | ROS2 + Flask + MCU layers separated for maintainability |

---

## ?뱚 Repository Structure

Mobile-Robot-Equipped-with-GNSS-Based-Remote-Steering-and-Variable-Wheels/
???쒋?? appinventor/ # Android joystick app (.aia + README)
???쒋?? arduino/
???쒋?? mega_sub1_ir_alignment/ # IR-based wheel alignment
???붴?? mega_sub2_gimbal/ # 2-axis camera gimbal controller
???쒋?? cad/
???쒋?? 媛蹂諛뷀? # Variable-diameter wheel assembly
???쒋?? 議고뼢?μ튂/ # Steering gearbox assembly
???붴?? 移대찓?? # Gimbal camera bracket
???쒋?? docs/ # Papers, reports, and posters
???쒋?? esp32/ # TCP relay between Flask and STM32
???쒋?? ros2/ # GNSS JSON bridge + Flask web visualization
???쒋?? scripts/ # Auto-execution and deployment scripts
???쒋?? server/ # Flask + TCP server core
???붴?? stm32/GNSS_STM32/ # Firmware: RS-485 (BLDC), PWM (servo), UART5 (ESP32)


---

## ?쭬 Software Highlights

### ?㎛ ROS2 Layer
- Converts **GNSS NavSatFix ??JSON** for Flask integration  
- Publishes `/position` API for live GNSS visualization  
- Built with **ROS2 Humble** on **Jetson Orin Nano (Ubuntu 22.04)**  

### ?뙋 Flask Web Server
- Renders map visualization and streams live video  
- Relays TCP commands to ESP32  
- Accessible remotely via **port forwarding or ngrok**

### ?벑 App Inventor Joystick
- Sends directional commands (Front / Stop / Back) via TCP  
- Switches **wheel modes (CW / NORMAL / CCW)**  
- Adjusts steering angle through slider input  
- Displays GNSS map + Flask live video feed  

### ?숋툘 STM32 Main Controller
- Controls **BLDC motors (RS-485)** and **servo steering (PWM)**  
- Communicates with ESP32 via **UART5 (115200 bps)**  
- Performs **mode switching, offset correction, and motion control**

### ?쨼 Arduino Submodules

| Submodule | Function |
|------------|-----------|
| **Sub #1 (Mega)** | IR sensor-based automatic wheel alignment |
| **Sub #2 (Mega)** | 2-axis gimbal stabilization using MPU6050 PID |

---

## ?㎟ Mechanical Design

All CAD models are designed in **SolidWorks 2023**, divided into three major subsystems:

| Subsystem | Description |
|------------|-------------|
| ?? **Variable Wheel** | Adjustable 4-bar linkage wheel (횠140??00 mm) |
| ?숋툘 **Steering Gearbox** | Servo-driven Ackermann steering assembly |
| ?렏 **Camera Gimbal** | Dual-axis stabilization mount for onboard camera |

> Export formats: `.SLDPRT`, `.SLDASM`, `.STEP`, `.STL`

---

## ?㎨ Documentation

| Type | File | Description |
|------|------|-------------|
| ?뱞 **Final Report** | `寃곌낵蹂닿퀬??GNSS湲곕컲濡쒕큸.pdf` | WE-Meet Project Final Report |
| ?벐 **Paper** | `?쇰Ц.pdf` | ICROS 2025 Conference Paper |
| ?㎎ **Poster** | `?ъ뒪???쇰Ц ?묒떇.pdf` | KROS Poster Submission |
| ?럳 **Presentation** | `議몄옉 3李?諛쒗몴?먮즺.pptx` | Capstone Design Presentation |

---

## ?뮲 Technical Stack

| Domain | Tools / Hardware |
|--------|------------------|
| **Microcontrollers** | STM32F429ZIT6, ESP32, Arduino Mega 2560 |
| **Communication** | UART, RS-485, TCP/IP, PWM |
| **Software** | ROS2 Humble, Python 3.10, Flask, OpenCV |
| **Design Tools** | SolidWorks 2023, MIT App Inventor 2 |
| **Sensors** | ZED-F9P GNSS, MPU6050 IMU, IR Sensors |
| **Platform** | Jetson Orin Nano (22.04 Ubuntu), Windows 11 |

---

## ?? Performance & Results

- ??**RTK-GNSS Precision** : RMS ??2.3 cm (Max Error < 4 cm)  
- ??**Steering Response Delay** : < 100 ms  
- ??**Stair Climbing Capability** : up to 15 cm step height  
- ??**Long-term Stability** : > 30 min continuous operation  
- ??**Full Integration** : Indoor + Outdoor tested  

---

## ?뙇 Application Fields

| Field | Example Use |
|--------|--------------|
| ?쉾 **Disaster Response** | Remote rescue in hazardous environments |
| ?슌 **Agriculture** | GNSS-based crop monitoring and control |
| ?첉 **Defense / Surveillance** | Remote observation and reconnaissance |
| ?럳 **Education** | Learning platform for GNSS, ROS2, and embedded systems |

---

## ?뫁 Team L&K ??KOREATECH

| Name | Role |
|------|------|
| **源吏꾧껴** | Team Leader / System Integration |
| **源?뺤?** | ROS2 & Software Development |
| **?닿킅誘?* | Mechanical Design / CAD Modeling |
| **?댁썝臾?* | Hardware Control / Embedded Firmware / Network Integration |

---

## ?뢾 Summary

??**Structurally complete** ??Independent HW 쨌 SW 쨌 Web 쨌 UI layers  
??**Professionally documented** ??All modules with individual READMEs  
??**Public & reproducible** ??Ready for academic or competition submission  
??**Demonstrated integration** ??GNSS-based, real-time, terrain-adaptive robot  

---

**Maintained by Team L&K ??KOREATECH**  
?뱧 [GitHub Repository](https://github.com/won5566/Mobile-Robot-Equipped-with-GNSS-Based-Remote-Steering-and-Variable

