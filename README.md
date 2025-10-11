🛰️ Mobile Robot Equipped with GNSS-Based Remote Steering and Variable Wheels

🏆 All-Terrain Robot integrating multi-layer communication, GNSS localization, ROS2-based visualization,
and real-time steering control for terrain adaptability.

📘 Project Overview

This project presents an all-terrain mobile robot that integrates
a GNSS-based remote steering system and a variable-diameter wheel mechanism
to achieve precise motion control and terrain adaptability in real environments.

Developed as part of the KOREATECH L&K Team,
the system combines embedded hardware (STM32, Arduino, ESP32),
ROS2-based GNSS visualization, and a Flask-web remote UI.

🧩 System Architecture
[Tablet / App Inventor UI]
        ↓  (TCP/IP commands)
[Flask Web Server]
        ↓
[ESP32]  ← Wi-Fi TCP Relay
        ↓
[STM32 Controller]
 ├── RS-485 → BLDC Motors (4WD)
 ├── PWM → Steering Servos (4WIS)
 └── UART5 → ESP32 Command Interface
        ↓
[Arduino Mega Sub #1] → Wheel Alignment via IR Sensors
[Arduino Mega Sub #2] → 2-Axis Camera Gimbal (MPU6050 PID)

⚙️ Key Features
Category	Description
🛰️ GNSS Localization	ZED-F9P RTK GNSS module integrated with ROS2 NavSatFix; JSON bridge to Flask map visualization
🧭 Remote Control	Real-time teleoperation through Flask UI & App Inventor joystick
⚙️ Variable Wheel System	4-bar linkage design allowing wheel radius change (140 mm ↔ 200 mm)
🔄 Independent Steering	Servo-based 0°–270° steering using Ackermann geometry
🧠 Auto Alignment	IR-based wheel zero-position calibration (Arduino Sub #1)
🎥 Camera Stabilization	Dual-axis gimbal with MPU6050 PID (Arduino Sub #2)
🧰 Visualization	Web-based GNSS map and live video feed integration
🪛 Scalable Architecture	Modular ROS2 + Flask + MCU hierarchy for easy expansion
🧱 Repository Structure
Mobile-Robot-Equipped-with-GNSS-Based-Remote-Steering-and-Variable-Wheels/
│
├── appinventor/       # Android joystick .aia + README (remote control UI)
├── arduino/
│   ├── mega_sub1_ir_alignment/  # IR-based wheel alignment code
│   └── mega_sub2_gimbal/        # 2-axis camera stabilization code
│
├── cad/
│   ├── 가변바퀴/    # Variable-diameter wheel assembly
│   ├── 조향장치/    # Steering gearbox assembly
│   └── 카메라/      # Gimbal camera bracket
│
├── docs/              # Paper, report, poster, and documentation PDFs
├── esp32/             # TCP relay code between Flask ↔ STM32
├── ros2/              # GNSS → JSON bridge + Flask web server (visualization)
├── scripts/           # Auto-execution and deployment scripts
├── server/            # Flask + TCP core server
└── stm32/GNSS_STM32/  # BLDC, RS-485, servo, and UART control firmware

🧠 Software Highlights
🧭 ROS2 Layer

Converts GNSS NavSatFix → JSON stream for Flask

Publishes /position API for live map updates

Built with ROS2 Humble on Jetson Orin / Ubuntu 22.04

🌐 Flask Web Server

Hosts map visualization and TCP command relay

Receives GNSS JSON → renders real-time position on browser

Streams live video (OpenCV camera module)

📱 App Inventor Joystick

TCP-based command sender (Front / Stop / Back / Mode Switch)

Embedded map + Flask stream view

Adjustable steering slider integrated with wheel mode

⚙️ STM32 Main Controller

BLDC drive via RS-485

Servo control (4WIS) using PWM (TIM4)

Wi-Fi (ESP32) via UART5 (115200 bps)

Real-time mode switching logic & offset calibration

🤖 Arduino Submodules
Module	Function
Sub #1 (Mega)	IR sensor-based wheel alignment
Sub #2 (Mega)	2-axis gimbal stabilization with MPU6050 PID
🧩 Mechanical Design

All CAD models were created in SolidWorks 2023,
comprising three major assemblies:

Subsystem	Description
🌀 Variable Wheel	4-bar linkage adjustable wheel radius
⚙️ Steering Gearbox	Servo-driven Ackermann geometry
🎥 Camera Gimbal	2-axis bracket for stabilization and monitoring

Files include .SLDPRT, .SLDASM, and exported .STEP formats for fabrication.

🧾 Documentation
Type	File	Description
📄 Final Report	(250607) 결과보고서_지능형로봇_GNSS기반...pdf	WE-Meet Project Final Report
📰 Paper	논문.pdf	ICROS 2025 Conference Paper
🧷 Poster	포스터 논문 양식.pdf	KROS Poster Submission
🎓 Presentation	졸작 3차 발표자료.pptx	Capstone Design Presentation
🧩 Technical Stack
Domain	Tools / Hardware
MCU & Firmware	STM32F429ZIT6, ESP32, Arduino Mega 2560
Control Protocols	UART (115200 bps), RS-485, PWM, TCP/IP
Software	ROS2 Humble, Python 3.10, Flask, OpenCV
Design Tools	SolidWorks 2023, MIT App Inventor 2
OS / Platform	Ubuntu 22.04, Jetson Orin Nano, Windows 11
Sensors	ZED-F9P GNSS, MPU6050 IMU, IR Reflective Sensors
🚀 Results & Performance

✅ RTK-GNSS Precision: RMS ≈ 2.3 cm (Max Error < 4 cm)

✅ Real-time Steering Response: < 100 ms delay over TCP

✅ Stair-climbing Capability: up to 15 cm step height

✅ Web + App Control Stability: sustained for > 30 min sessions

✅ Full-System Integration: verified in indoor/outdoor tests

🌍 Applications
Field	Example
🚒 Disaster Response	Search & Rescue in debris or rubble
🚜 Agriculture	Autonomous crop monitoring in rough soil
🪖 Defense	Surveillance or recon in local terrain
🎓 Education	ROS2, GNSS, and embedded systems learning platform
🧑‍💻 Team L&K — Korea University of Technology and Education
Name	Role
김진겸	Team Leader / System Integration
김형준	ROS2 & Software Development
이광민	Mechanical Design / CAD Modeling
이원무	Hardware Control / Embedded Firmware / Network Integration
🏁 Summary

✅ Fully modular architecture:
Hardware ↔ Software ↔ Web ↔ UI layers independently operable

✅ High-level documentation:
Structured READMEs for each subsystem (ROS2, Arduino, CAD, etc.)

✅ Public and reproducible:
Open repository with academic & competition-ready structure

✅ Practical outcome:
GNSS-based all-terrain robot capable of real-time remote control and adaptive mobility

Maintained by Team L&K — KOREATECH
Mobile Robot Equipped with GNSS-Based Remote Steering and Variable Wheels
📍 https://github.com/won5566/Mobile-Robot-Equipped-with-GNSS-Based-Remote-Steering-and-Variable-Wheels