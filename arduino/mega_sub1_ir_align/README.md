# Arduino Mega Sub #1 - Wheel Alignment Controller

This module is an independent calibration controller designed to align all four steering wheels  
to their default zero position using infrared (IR) sensors before normal driving begins.  
It operates autonomously and does not require communication with the main STM32 controller.

---

## Overview

| Item | Description |
|------|--------------|
| Board | Arduino Mega 2560 |
| Sensor | IR reflective sensors (x4) |
| Actuators | Servo motors for steering wheels |
| Purpose | Align each wheel to a neutral reference position before robot operation |
| Main File | `Wheel Alignment.ino` |

---

## System Architecture

<pre>
[IR Sensors] → detect alignment mark
        ↓
[Arduino Mega #1] → PID-based servo correction
        ↓
[Servo Motors] → adjust to 90° (neutral position)
</pre>

- Each wheel has one IR sensor detecting a reflective mark on the shaft.  
- When reflection is detected, the servo is stopped and held at the reference angle.  
- A short calibration routine runs automatically at startup.

---

## Pin Configuration

| Component | Arduino Pin | Description |
|------------|--------------|-------------|
| Servo FL (Front-Left) | D3 | PWM output |
| Servo FR (Front-Right) | D5 | PWM output |
| Servo RL (Rear-Left) | D6 | PWM output |
| Servo RR (Rear-Right) | D9 | PWM output |
| IR Sensor FL | A0 | Analog input |
| IR Sensor FR | A1 | Analog input |
| IR Sensor RL | A2 | Analog input |
| IR Sensor RR | A3 | Analog input |

*Note: Pin numbers can be reconfigured in the code depending on the servo shield or wiring layout.*

---

## Control Logic Summary

1. On power-up, each wheel slowly rotates to search for the reflective mark.  
2. When reflection intensity exceeds the threshold, the servo stops and the current angle is saved as the zero position.  
3. After all four wheels are aligned, the system indicates completion via LED or serial output.  
4. Once alignment is complete, the STM32 controller can begin motion control using the aligned steering geometry.

**Pseudo-code:**
```cpp
if (analogRead(IR_pin) > threshold) {
    servo.write(90); // stop at center
} else {
    servo.write(servo_angle + offset);
}
Features
Independent operation (no serial link with STM32 required)

Quick calibration (<3 seconds) on startup

Prevents wheel misalignment after resets

Reduces cumulative steering offset during long runs

Troubleshooting
Issue	Possible Cause	Solution
Servo not stopping	IR sensor threshold too high	Adjust threshold value in code
Alignment drift	Servo horn mounting offset	Recalibrate the physical center
No IR detection	Sensor not aligned to reflective tape	Reposition sensor angle (~15°)