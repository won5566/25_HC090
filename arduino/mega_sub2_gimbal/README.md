# Arduino Mega Sub #2 — Camera Stabilization Module

This directory contains the **Arduino Mega 2560 firmware**  
for the **2-axis camera stabilization (gimbal leveling) system** used in the GNSS-based all-terrain robot.

---

## 🧠 Overview

This module ensures that the onboard camera remains **horizontally level**  
even when the robot’s chassis tilts or moves over uneven terrain.

The system uses an **MPU6050 IMU sensor** to measure pitch and roll angles  
and controls **two servo motors** (X-axis, Y-axis) to counteract tilt in real time.

---

## ⚙️ Hardware Configuration

| Component | Model / Type | Connection |
|------------|---------------|-------------|
| **Microcontroller** | Arduino Mega 2560 | Main board |
| **IMU Sensor** | MPU6050 (GY-521) | SDA → A4, SCL → A5 |
| **Servo Motor (X-axis)** | DS51150-270 | PWM pin (e.g., D9) |
| **Servo Motor (Y-axis)** | DS51150-270 | PWM pin (e.g., D10) |
| **Power Supply** | 5V DC (separate servo rail) | Shared GND with Mega |

> I²C bus used for IMU (Wire.h), PWM control via Servo.h library.

---

## 🧩 Firmware Description

### File: `camera_stabilizer.ino`

- **Initialization**
  - Starts serial monitor (115200 bps)
  - Initializes MPU6050 and sets offsets

- **Main Loop**
  - Reads pitch/roll from MPU6050
  - Calculates correction angle for each axis
  - Maps output angle to servo PWM (0–180°)
  - Writes servo signal to maintain horizontal orientation

### Example Logic (simplified)
```cpp
int servoX = map(pitch, -45, 45, 0, 180);
int servoY = map(roll,  -45, 45, 0, 180);
servoX.write(servoX);
servoY.write(servoY);
📐 Coordinate System
           ↑ Y-axis servo (tilt)
           |
           |------→ X-axis servo (pan)
          / Camera
Both servos work together to stabilize the camera in roll and pitch directions.

🧾 Serial Output Example
Pitch: -2.36° | Roll: 1.45° | ServoX: 92 | ServoY: 87
Pitch: -2.29° | Roll: 1.38° | ServoX: 92 | ServoY: 87
🛠️ Upload Instructions
Open Arduino IDE

Board: Arduino Mega 2560

Port: Select the correct COM port

Open camera_stabilizer.ino

Install required libraries:

Wire.h (default)

Servo.h

MPU6050.h or Adafruit_MPU6050.h

Click Upload (Ctrl + U)

⚙️ Tuning
Parameter	Description	Typical Range
Kp	Proportional gain (stability)	0.5 – 2.0
angleOffsetX, angleOffsetY	Trim offsets	±3°
updateRate	Refresh rate (ms)	10 – 20 ms

Use the serial monitor to observe real-time pitch/roll and adjust gains for smooth motion.

🔗 Integration
Operates independently (no communication link)

Provides stabilized camera feed to upper systems (Flask/ROS2)

Mounted on robot’s upper frame to ensure stable visual output

👨‍💻 Maintainer
Team L&K — Korea University of Technology and Education (KOREATECH)
Camera Stabilization Firmware: 김형준