# 🧱 CAD Models — GNSS-Based Remote Steering and Variable-Wheel Robot

This directory contains all **3D CAD design files** created in SolidWorks for the all-terrain mobile robot.  
The mechanical design is divided into **three main subsystems**: the Variable Wheel, Steering Gearbox, and Camera Gimbal.

---

## 📂 Folder Structure

cad/
├── 가변바퀴/ # Variable-diameter wheel design (4-bar linkage)
├── 조향장치/ # Steering gearbox & servo mount
└── 카메라/ # Two-axis gimbal camera bracket system


---

## ⚙️ 1. Variable Wheel (가변바퀴)

**Description:**  
Four-bar linkage structure that adjusts diameter between 140 mm and 200 mm.  
Optimized for both flat-surface driving and rough-terrain climbing.

**Key Parts:**
| File | Description |
|------|--------------|
| `어셈블리1.SLDASM` | Full wheel assembly including linkage and outer shell |
| `바퀴바깥.SLDPRT` | Outer wheel shell |
| `바퀴만어셈.SLDASM` | Linkage and hub integration |
| `외부.SLDPRT` / `외부 dc모터 체결부분.SLDPRT` | Motor coupling parts |
| `bldc모터.SLDPRT` | BLDC motor mount |
| `계단.SLDPRT` | Test object used for stair-climbing simulation |

**Highlights:**
- 4-bar linkage variable-radius mechanism  
- Supports both CW (stair-climbing) and CCW (rough-terrain) modes  
- SolidWorks Motion used for linkage motion analysis  
- 12 mm shaft and 40 mm bearing interfaces applied  

---

## ⚙️ 2. Steering Gearbox (조향장치)

**Description:**  
Servo motor-based steering unit applying Ackermann geometry for independent 4-wheel steering.

**Key Parts:**
| File | Description |
|------|--------------|
| `기어박스.SLDPRT` / `기어박스 v2.SLDASM` | Main steering gearbox assembly |
| `스티어링 기어박스.SLDPRT` | Ackermann steering pair model |
| `조향장치 어셈블리.SLDASM` | Full assembled steering system |
| `모터 축 연장.SLDPRT` | Shaft coupler extension |
| `브라켓.SLDPRT` / `슬리핑외부2.SLDPRT` | Support brackets and bearing housings |
| `17mbar_h100.SLDPRT`, `프로파일 340mm.SLDPRT` | Frame connection parts |

**Highlights:**
- 0° – 270° steering range  
- Servo-motor actuation with reduction gears  
- Bearing-supported shaft for vibration stability  
- Symmetric design for left/right module reuse  

---

## 📷 3. Camera Gimbal (카메라)

**Description:**  
Two-axis gimbal system for camera stabilization, controlled by Arduino Mega + MPU6050.

**Key Parts:**
| File | Description |
|------|--------------|
| `카메라브라켓1~4.SLDPRT` | Multi-layer camera bracket components |
| `어셈블리3.SLDASM` | Assembled gimbal mount |
| `카메라어셈블리.SLDASM` | Complete camera mount assembly |
| `브라켓부품.SLDPRT` | Servo connection plate |

**Highlights:**
- Dual-axis rotation (Pitch/Roll)  
- Modular mounting for various webcams  
- Compact 3D-printed bracket optimized for 9 g servo  
- Stable frame connection to upper robot plate  

---

## 🏗️ Design Tools & Export

- **Software:** SolidWorks 2023  
- **File Types:** `.SLDPRT`, `.SLDASM`  
- **Export Options:** `.STEP`, `.STL` available for fabrication (3D printing / CNC)  
- **Unit System:** mm (ISO)  

---

## 📸 Preview

> *(Insert rendered images later — e.g., `images/wheel_render.png`, `images/steering_render.png`, `images/gimbal_render.png`)*

---

## 🧾 Notes

- All assemblies reference relative paths; keep folder structure intact when moving.  
- Ensure mates are fully defined before motion simulation.  
- STL versions can be used directly for 3D printing (TPU + PLA recommended).  

---

**Maintained by Team L&K**  
KOREATECH — Department of Mechatronics Engineering  
Designed by: 이광민