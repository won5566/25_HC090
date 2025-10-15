# 🚀 Mobile Robot Equipped with GNSS-Based Remote Steering and Variable Wheels  

> **All-Terrain Mobile Robot** integrating multi-layer communication, GNSS localization, ROS2-based visualization, and real-time steering control for terrain adaptability.  

---

## 💡 1. 프로젝트 개요  

### **1-1. 프로젝트 소개**  
- **프로젝트 명:** Mobile Robot Equipped with GNSS-Based Remote Steering and Variable Wheels  
- **프로젝트 정의:**  
  GNSS 기반 원격 조향 및 가변 휠 메커니즘을 결합하여 지형 적응성과 정밀 제어를 동시에 구현한 전지형 모바일 로봇  
- **대표 이미지:**  
  [이미지 첨부 또는 링크 입력]

---

### **1-2. 개발 배경 및 필요성**  
현대의 이동 로봇은 특정 지형에서만 동작하거나 제어 안정성이 떨어지는 경우가 많습니다. 본 프로젝트는 **GNSS 기반 위치 인식**과 **가변 반경 휠 구조**를 통해, 다양한 지형 환경(도로, 모래, 잔디, 경사면 등)에서도 안정적인 이동과 원격 제어가 가능하도록 개발되었습니다.  
또한 **ROS2 기반 실시간 위치 시각화 시스템**과 **Flask 웹 서버**, **App Inventor 원격 UI**를 통해 로봇의 위치, 자세, 영상 정보를 실시간으로 통합 관리할 수 있습니다.

---

### **1-3. 프로젝트 특장점**  
- GNSS 기반 고정밀 위치 인식 (RTK 보정으로 ±2.3cm 정확도 확보)  
- ROS2 기반 실시간 위치 데이터 송수신 및 시각화  
- Flask 웹 서버를 통한 실시간 GNSS 지도 및 영상 스트리밍  
- App Inventor로 제작된 모바일 조이스틱 원격 제어  
- 휠 반경 가변(140mm ↔ 200mm) 메커니즘으로 다양한 지형 대응  
- 독립 4륜 조향(4WIS) 및 4륜 구동(4WD) 지원  
- IR 센서를 활용한 휠 정렬 자동 보정  
- 2축 짐벌 기반 카메라 안정화 제어  

---

### **1-4. 주요 기능**  

| 구분 | 기능 설명 |
|------|------------|
| **GNSS Localization** | ZED-F9P RTK GNSS 기반 위치 추적, ROS2 NavSatFix 메시지 변환 |
| **Remote Control** | Flask Web UI + App Inventor 조이스틱 원격 제어 |
| **Variable Wheel System** | 휠 반경 가변 메커니즘(140~200mm)으로 지형 대응 |
| **Independent Steering** | 서보모터 기반 0°~270° 범위 조향 |
| **Auto Alignment** | IR 센서 기반 휠 자동 보정 기능 |
| **Camera Stabilization** | MPU6050 + PID 기반 2축 짐벌 제어 |
| **Visualization** | Flask 웹맵 및 실시간 비디오 스트리밍 |
| **Modular Architecture** | ROS2, Flask, MCU 계층 분리로 유지보수 용이 |

---

### **1-5. 기대 효과 및 활용 분야**  

- **기대 효과:**  
  - 지형 적응형 로봇 플랫폼 개발로 실험적·산업적 활용 가능성 확대  
  - GNSS·ROS2·임베디드 통합 시스템 학습용 교육 플랫폼 제공  
  - 이동 로봇 분야의 정밀 제어 및 자율주행 응용 확장  

- **활용 분야:**  
  - 재난 대응 및 원격 구조  
  - 농업 자동화 (GNSS 기반 주행)  
  - 국방/감시 시스템  
  - 로봇 교육 및 연구 실험 플랫폼  

---

### **1-6. 기술 스택**  

| 분야 | 기술 |
|------|------|
| **임베디드 하드웨어** | STM32F429ZIT6, ESP32, Arduino Mega 2560 |
| **통신** | UART, RS-485, TCP/IP, PWM |
| **소프트웨어** | ROS2 Humble, Python 3.10, Flask, OpenCV |
| **디자인 툴** | SolidWorks 2023, MIT App Inventor 2 |
| **센서** | ZED-F9P GNSS, MPU6050 IMU, IR Sensor |
| **플랫폼** | Jetson Orin Nano (Ubuntu 22.04) |
| **버전 관리 및 배포** | GitHub Actions, Docker, AWS (선택사항) |

---

## 💡 2. 팀원 소개  

| 사진 | 이름 | 역할 |
|:---:|:---:|:---:|
| [사진 첨부] | [이름] | 하드웨어 설계 및 메커니즘 개발 |
| [사진 첨부] | [이름] | 임베디드 제어 (STM32 / Arduino) |
| [사진 첨부] | [이름] | Flask 서버 및 ROS2 통신 모듈 개발 |
| [사진 첨부] | [이름] | App Inventor 모바일 UI 설계 |
| [사진 첨부] | [멘토 이름] | 프로젝트 멘토 / 기술 자문 |

---

## 💡 3. 시스템 구성도  

> 시스템 아키텍처, 통신 흐름도, 하드웨어 블록도를 첨부해주세요.  

**예시 텍스트 구조도:**  

```
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
```

**시스템 구성도 이미지:**  
[이미지 첨부 또는 링크 입력]  

**엔티티 관계도 (선택):**  
[이미지 첨부 또는 링크 입력]

---

## 💡 4. 작품 소개영상  

[![영상 제목](유튜브 썸네일 URL)](유튜브 영상 URL)

예시:  
[![한이음 드림업 프로젝트 소개](https://github.com/user-attachments/assets/16435f88-e7d3-4e45-a128-3d32648d2d84)](https://youtu.be/YcD3Lbn2FRI?si=isERqIAT9Aqvdqwp)

---

## 💡 5. 핵심 소스코드  

대표적인 Flask 기반 GNSS 위치 송신 코드 예시입니다.

```python
from flask import Flask, jsonify
import serial, json

app = Flask(__name__)
ser = serial.Serial('/dev/ttyUSB0', 115200)

@app.route('/position')
def position():
    line = ser.readline().decode().strip()
    data = json.loads(line)
    return jsonify({"lat": data['lat'], "lon": data['lon']})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
```

[작성칸: 다른 핵심 소스코드로 교체 가능]

---

## 💡 추가 정보  

| 항목 | 내용 |
|------|------|
| **프로젝트 번호** | [예: 25_HCXXX] |
| **GitHub 저장소 주소** | https://github.com/[깃허브계정]/[프로젝트번호] |
| **문서 자료** | 발표자료, 보고서, 논문 등은 `/docs` 폴더 참고 |
| **CAD 설계 파일** | SolidWorks `.SLDPRT`, `.SLDASM`, `.STEP` 형식 제공 |

---

> ✨ 본 README는 [GPT Online (https://gptonline.ai/ko/)](https://gptonline.ai/ko/) 의 도움으로 작성되었습니다.  
> 자유롭게 수정 및 확장하여 한이음 드림업 공모전에 맞게 제출하세요 🙌
