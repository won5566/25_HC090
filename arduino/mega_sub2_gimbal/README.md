# Arduino Mega Sub #2 - Camera Stabilization Module

This directory contains the **Arduino Mega 2560 firmware**  
for the **2-axis camera stabilization (gimbal leveling) system** used in the GNSS-based all-terrain robot.

---

## Overview

This module ensures that the onboard camera remains **horizontally level**  
even when the robot chassis tilts or moves over uneven terrain.

The system uses an **MPU6050 IMU sensor** to measure pitch and roll angles  
and controls **two servo motors** (X-axis and Y-axis) to counteract tilt in real time.

---

## Hardware Configuration

| Component | Model / Type | Connection |
|------------|---------------|-------------|
| Microcontroller | Arduino Mega 2560 | Main board |
| IMU Sensor | MPU6050 (GY-521) | SDA → A4, SCL → A5 |
| Servo Motor (X-axis) | DS51150-270 | PWM pin (e.g., D9) |
| Servo Motor (Y-axis) | DS51150-270 | PWM pin (e.g., D10) |
| Power Supply | 5V DC (separate servo rail) | Shared GND with Mega |

*I2C bus used for IMU (Wire.h), PWM control via Servo.h library.*

---

## Firmware Description

### File: `camera_stabilizer.ino`

**Initialization**
- Starts serial monitor (115200 bps)  
- Initializes MPU6050 and sets offsets  

**Main Loop**
- Reads pitch and roll from MPU6050  
- Calculates correction angle for each axis  
- Maps output angle to servo PWM (0–180°)  
- Writes servo signals to maintain horizontal orientation  

**Simplified Example**
```cpp
int servoX = map(pitch, -45, 45, 0, 180);
int servoY = map(roll,  -45, 45, 0, 180);
servoX.write(servoX);
servoY.write(servoY);
Coordinate System
<pre> ↑ Y-axis servo (tilt) | |------→ X-axis servo (pan) / Camera </pre>
Both servos work together to stabilize the camera in roll and pitch directions.

Serial Output Example
Pitch: -2.36° | Roll: 1.45° | ServoX: 92 | ServoY: 87
Pitch: -2.29° | Roll: 1.38° | ServoX: 92 | ServoY: 87
Upload Instructions
Open Arduino IDE

Select Board: Arduino Mega 2560

Select the correct COM Port

Open camera_stabilizer.ino

Install required libraries:

Wire.h (default)

Servo.h

MPU6050.h or Adafruit_MPU6050.h

Click Upload (Ctrl + U)

Tuning Parameters
Parameter	Description	Typical Range
Kp	Proportional gain for stability	0.5 – 2.0
angleOffsetX / angleOffsetY	Trim offsets	±3°
updateRate	Refresh rate (ms)	10 – 20 ms

Use the serial monitor to observe pitch and roll in real time
and adjust the PID gains for smooth and stable motion.

Integration Notes
Operates independently (no communication link to STM32 required)

Provides stabilized video feed to upper systems (Flask / ROS2)

Mounted on the robot’s upper frame to ensure stable visual output