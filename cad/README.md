# ?㎟ CAD Models ??GNSS-Based Remote Steering and Variable-Wheel Robot

This directory contains all **3D CAD design files** created in SolidWorks for the all-terrain mobile robot.  
The mechanical design is divided into **three main subsystems**: the Variable Wheel, Steering Gearbox, and Camera Gimbal.

---

## ?뱛 Folder Structure

cad/
?쒋?? 媛蹂諛뷀? # Variable-diameter wheel design (4-bar linkage)
?쒋?? 議고뼢?μ튂/ # Steering gearbox & servo mount
?붴?? 移대찓?? # Two-axis gimbal camera bracket system


---

## ?숋툘 1. Variable Wheel (媛蹂諛뷀?

**Description:**  
Four-bar linkage structure that adjusts diameter between 140 mm and 200 mm.  
Optimized for both flat-surface driving and rough-terrain climbing.

**Key Parts:**
| File | Description |
|------|--------------|
| `?댁뀍釉붾━1.SLDASM` | Full wheel assembly including linkage and outer shell |
| `諛뷀대컮源?SLDPRT` | Outer wheel shell |
| `諛뷀대쭔?댁뀍.SLDASM` | Linkage and hub integration |
| `?몃?.SLDPRT` / `?몃? dc紐⑦꽣 泥닿껐遺遺?SLDPRT` | Motor coupling parts |
| `bldc紐⑦꽣.SLDPRT` | BLDC motor mount |
| `怨꾨떒.SLDPRT` | Test object used for stair-climbing simulation |

**Highlights:**
- 4-bar linkage variable-radius mechanism  
- Supports both CW (stair-climbing) and CCW (rough-terrain) modes  
- SolidWorks Motion used for linkage motion analysis  
- 12 mm shaft and 40 mm bearing interfaces applied  

---

## ?숋툘 2. Steering Gearbox (議고뼢?μ튂)

**Description:**  
Servo motor-based steering unit applying Ackermann geometry for independent 4-wheel steering.

**Key Parts:**
| File | Description |
|------|--------------|
| `湲곗뼱諛뺤뒪.SLDPRT` / `湲곗뼱諛뺤뒪 v2.SLDASM` | Main steering gearbox assembly |
| `?ㅽ떚?대쭅 湲곗뼱諛뺤뒪.SLDPRT` | Ackermann steering pair model |
| `議고뼢?μ튂 ?댁뀍釉붾━.SLDASM` | Full assembled steering system |
| `紐⑦꽣 異??곗옣.SLDPRT` | Shaft coupler extension |
| `釉뚮씪耳?SLDPRT` / `?щ━?묒쇅遺2.SLDPRT` | Support brackets and bearing housings |
| `17mbar_h100.SLDPRT`, `?꾨줈?뚯씪 340mm.SLDPRT` | Frame connection parts |

**Highlights:**
- 0째 ??270째 steering range  
- Servo-motor actuation with reduction gears  
- Bearing-supported shaft for vibration stability  
- Symmetric design for left/right module reuse  

---

## ?벜 3. Camera Gimbal (移대찓??

**Description:**  
Two-axis gimbal system for camera stabilization, controlled by Arduino Mega + MPU6050.

**Key Parts:**
| File | Description |
|------|--------------|
| `移대찓?쇰툕?쇱폆1~4.SLDPRT` | Multi-layer camera bracket components |
| `?댁뀍釉붾━3.SLDASM` | Assembled gimbal mount |
| `移대찓?쇱뼱?덈툝由?SLDASM` | Complete camera mount assembly |
| `釉뚮씪耳볥???SLDPRT` | Servo connection plate |

**Highlights:**
- Dual-axis rotation (Pitch/Roll)  
- Modular mounting for various webcams  
- Compact 3D-printed bracket optimized for 9 g servo  
- Stable frame connection to upper robot plate  

---

## ?룛截?Design Tools & Export

- **Software:** SolidWorks 2023  
- **File Types:** `.SLDPRT`, `.SLDASM`  
- **Export Options:** `.STEP`, `.STL` available for fabrication (3D printing / CNC)  
- **Unit System:** mm (ISO)  

---

## ?벝 Preview

> *(Insert rendered images later ??e.g., `images/wheel_render.png`, `images/steering_render.png`, `images/gimbal_render.png`)*

---

## ?㎨ Notes

- All assemblies reference relative paths; keep folder structure intact when moving.  
- Ensure mates are fully defined before motion simulation.  
- STL versions can be used directly for 3D printing (TPU + PLA recommended).  

---

**Maintained by Team KLON**  
KOREATECH ??Department of Mechatronics Engineering  
Designed by: ?닿킅誘

