# ⚙️ Arduino Mega Sub #1 — Wheel Alignment Controller

This module is an **independent calibration controller** designed to align all four steering wheels  
to their default zero position using **infrared (IR) sensors** before normal driving begins.  
It operates autonomously and does not require communication with the main STM32 controller.

---

## 🧭 Overview

| Item | Description |
|------|--------------|
| **Board** | Arduino Mega 2560 |
| **Sensor** | IR Reflective Sensors (x4) |
| **Actuators** | Servo motors for steering wheels |
| **Purpose** | Align each wheel to a neutral reference position before robot operation |
| **Main File** | `Wheel Alignment.ino` |

---

## 🧩 System Architecture

[IR Sensors] → detect alignment mark
↓
[Arduino Mega #1] → PID-based servo correction
↓
[Servo Motors] → adjust to 90° (neutral position)


- Each wheel has one IR sensor detecting a reflective mark on the shaft.
- When reflection is detected, the servo is stopped and held at the reference angle.
- A short calibration routine runs at startup.

---

## 🔌 Pin Configuration

| Component | Arduino Pin | Description |
|------------|--------------|--------------|
| Servo FL (Front-Left) | D3 | PWM output |
| Servo FR (Front-Right) | D5 | PWM output |
| Servo RL (Rear-Left) | D6 | PWM output |
| Servo RR (Rear-Right) | D9 | PWM output |
| IR Sensor FL | A0 | Analog input |
| IR Sensor FR | A1 | Analog input |
| IR Sensor RL | A2 | Analog input |
| IR Sensor RR | A3 | Analog input |

> **Note:** Pin numbers can be reconfigured in the code depending on servo shield or wiring layout.

---

## 🧠 Control Logic Summary

1. On power-up, each wheel begins to rotate slowly to search for the IR reflection mark.  
2. When reflection intensity exceeds threshold → servo stops and angle saved as zero position.  
3. After all four wheels are aligned, the system signals completion via LED or serial output.  
4. The robot’s STM32 controller can then start its motion sequence with aligned steering geometry.

**Pseudo-code:**
```cpp
if (analogRead(IR_pin) > threshold) {
    servo.write(90); // stop at center
} else {
    servo.write(servo_angle + offset);
}
💡 Features
Independent operation — no serial link with STM32 required

Quick calibration (< 3 seconds) on startup

Prevents wheel misalignment caused by power resets

Reduces cumulative steering offset errors during long runs

🔧 Troubleshooting
Issue	Possible Cause	Solution
Servo not stopping	IR sensor threshold too high	Adjust threshold value in code
Alignment drift	Servo horn mounting offset	Recalibrate physical center
No IR detection	Sensor not aligned to reflective tape	Reposition sensor angle (≈ 15°)

📄 File List
File	Description
Wheel Alignment.ino	Main Arduino sketch for IR-based wheel alignment
README.md	Module documentation (this file)

Maintained by Team L&K
KOREATECH — GNSS-Based Variable Wheel Robot Project
Sub Controller #1 (Wheel Alignment Unit)
Developed by: 김진겸