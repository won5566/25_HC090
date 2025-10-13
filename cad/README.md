# CAD Models — GNSS-Based Remote Steering & Variable-Wheel Robot

This directory contains all **3D CAD design files** (SolidWorks) for the all-terrain mobile robot.  
The mechanical design is organized into **three subsystems**: **Variable Wheel**, **Steering Gearbox**, and **Camera Gimbal**.

---

## Folder Structure

cad/
├─ variable-wheel/ # Variable-diameter wheel (4-bar linkage)
├─ steering-gearbox/ # Steering gearbox & servo mounts (4WIS/Ackermann)
└─ camera-gimbal/ # Two-axis camera gimbal bracket set


> Keep this structure when moving the project to preserve assembly reference paths.

---

## 1) Variable Wheel (4-Bar Variable-Diameter)

**Summary**  
A four-bar linkage wheel that adjusts its effective diameter between **140 mm** and **200 mm** for terrain adaptability (flat ↔ rough terrain ↔ stair climbing).

**Typical Files**
- `wheel_assembly.SLDASM` — Full wheel assembly (linkage + outer shell)  
- `outer_shell.SLDPRT` — Outer flexible shell/rim  
- `linkage_hub_assembly.SLDASM` — Linkage to hub integration  
- `motor_coupler_A.SLDPRT`, `motor_coupler_B.SLDPRT` — BLDC/servo couplers  
- `bldc_mount.SLDPRT` — BLDC motor mount  
- `stair_test_block.SLDPRT` — Test object for stair-climb simulation

**Highlights**
- **Variable radius**: 140–200 mm (adjustable in motion)  
- **Dual mode**:
  - **CW Mode**: “claw-like” profile for step (stair) climbing  
  - **CCW Mode**: curved profile for uneven/rough terrain
- **Analysis**: SolidWorks Motion study for linkage & clearance  
- **Interfaces**: 12 mm shaft, 40 mm bearing seats

---

## 2) Steering Gearbox (4-Wheel Independent Steering)

**Summary**  
Servo-driven steering module applying **Ackermann geometry** with reduction gears for precise turning and on-spot rotation.

**Typical Files**
- `steering_gearbox_v1.SLDASM` / `steering_gearbox_v2.SLDASM` — Main gearbox assemblies  
- `ackermann_pair.SLDPRT` — Knuckle/pair model for geometry verification  
- `steering_full.SLDASM` — Assembled steering system module  
- `shaft_coupler_ext.SLDPRT` — Coupler/extension parts  
- `support_bracket.SLDPRT`, `bearing_housing_v2.SLDPRT` — Brackets & housings  
- `frame_connector_17mm_h100.SLDPRT`, `long_plate_340mm.SLDPRT` — Frame connection parts

**Highlights**
- **Steering range**: 0°–270° (servo + reduction)  
- **4WIS**: independent steering per wheel; symmetric L/R reuse  
- **Bearing-supported shafts** for vibration stability

---

## 3) Camera Gimbal (2-Axis)

**Summary**  
Compact **pitch/roll** gimbal for camera stabilization, driven by small servos; designed to pair with **Arduino Mega + MPU6050** control.

**Typical Files**
- `gimbal_plate_1.SLDPRT` … `gimbal_plate_4.SLDPRT` — Multi-layer plates  
- `gimbal_mount.SLDASM` — Gimbal assembly  
- `camera_stack_full.SLDASM` — Camera + gimbal + mount stack  
- `servo_link_plate.SLDPRT` — Servo horn/link plate

**Highlights**
- **2-axis** stabilization (Pitch/Roll)  
- **Modular** mounts for webcams/action cams  
- **9 g servo-optimized** 3D-printable parts  
- Rigid connection to top frame for reduced jitter

---

## Design Tools & Export

- **CAD**: SolidWorks 2023  
- **Native**: `.SLDPRT`, `.SLDASM`  
- **Export**: `.STEP` (machining/CNC), `.STL` (3D printing)  
- **Units**: millimeter (ISO)

> **Printing tip**: TPU for outer contact surfaces (grip/damping), PLA/PETG for structural plates.

---

## Quick Specs (for reference)

- **Robot mass**: ~15–20 kg (prototype range)  
- **Footprint**: ~500–590 × 300–520 × 300–370 mm (variants)  
- **Wheel radius**: 140–200 mm (variable)  
- **Steering**: 0°–270° servo-based (independent per wheel)  
- **Modes**: Flat / Rough-terrain (CCW) / Stair-climb (CW)

---

## Notes

- **Mates**: Fully define all mates before motion analysis to avoid over-constraints.  
- **Assembly paths**: Use **relative paths**; keep subfolder names intact.  
- **STL slicing**: High infill for gear teeth & couplers; TPU shells benefit from 2–3 wall lines and 15–25% gyroid.  
- **Clearance**: Verify linkage clearance at max/min radius with steering at extremes.  
- **Fasteners/Bearings**: Document sizes in a BOM before machining/printing.

---

## Preview Placeholders

images/
├─ wheel_render.png
├─ steering_render.png
└─ gimbal_render.png
