🚀 Mobile Robot Equipped with GNSS-Based Remote Steering and Variable Wheels

All-Terrain Mobile Robot integrating multi-layer communication, GNSS localization, ROS2-based visualization, and real-time steering control for terrain adaptability.

💡 1. 프로젝트 개요
1-1. 프로젝트 소개

프로젝트 명: Mobile Robot Equipped with GNSS-Based Remote Steering and Variable Wheels

프로젝트 정의: GNSS 기반 원격 조향 및 가변 휠 메커니즘을 결합하여 지형 적응성과 정밀 제어를 동시에 구현한 전지형 모바일 로봇

대표 이미지:
[이미지 첨부 또는 링크 입력]

1-2. 개발 배경 및 필요성

[작성칸]

1-3. 프로젝트 특장점

GNSS 기반 고정밀 위치 인식 (RTK 기반 2cm 오차 이내)

ROS2 기반의 시각화 및 실시간 위치 추적

Flask 웹 UI 및 App Inventor 원격 조작

가변 지름 휠 메커니즘 (140mm ↔ 200mm)

독립 조향(4WIS) 및 전륜 구동(4WD)

통신 모듈(ESP32)과 메인 컨트롤러(STM32) 간 TCP/IP 기반 제어

1-4. 주요 기능
구분	기능 설명
GNSS Localization	ZED-F9P RTK GNSS 기반 실시간 위치 추적
Remote Control	Flask 기반 UI + App Inventor 조이스틱 제어
Variable Wheel System	휠 반경 조절 (140mm~200mm)
Independent Steering	서보모터 기반 0°~270° 조향
Auto Alignment	IR 센서 기반 휠 자동 보정
Camera Stabilization	MPU6050 + PID 기반 2축 짐벌 제어
Visualization	Flask 웹맵 + 실시간 영상 스트리밍
1-5. 기대 효과 및 활용 분야

기대 효과:

지형 적응형 로봇 설계로 실험적/산업적 활용 가능성 확대

GNSS, ROS2, 임베디드 통합 시스템 학습용 오픈 플랫폼

활용 분야:

재난 대응, 농업 자동화, 국방·감시, 교육·연구 등

1-6. 기술 스택
분야	기술
임베디드	STM32F429ZIT6, ESP32, Arduino Mega 2560
통신	UART, RS-485, TCP/IP, PWM
소프트웨어	ROS2 Humble, Python 3.10, Flask, OpenCV
디자인	SolidWorks 2023, MIT App Inventor 2
센서	ZED-F9P GNSS, MPU6050 IMU, IR Sensor
플랫폼	Jetson Orin Nano (Ubuntu 22.04)
기타	Docker, GitHub Actions, AWS (선택 사항)
💡 2. 팀원 소개
사진	이름	역할
[사진 첨부]	[이름]	[역할]
[사진 첨부]	[이름]	[역할]
[사진 첨부]	[이름]	[역할]
[사진 첨부]	[이름]	[역할]
[사진 첨부]	[멘토 이름]	[멘토 역할]
💡 3. 시스템 구성도

시스템 전체 구성, 통신 흐름, 하드웨어 블록도, ROS2-플라스크 연동 구조 등을 이미지로 표현해주세요.

시스템 구성도:
[이미지 첨부 또는 링크 입력]

엔티티 관계도 (선택):
[이미지 첨부 또는 링크 입력]

💡 4. 작품 소개영상

아래 형식으로 유튜브 썸네일 및 링크를 등록해주세요.

[![영상 제목](유튜브 썸네일 URL)](유튜브 영상 URL)


📹 예시:


💡 5. 핵심 소스코드

대표적인 코드(예: Flask 제어, GNSS ROS2 변환, STM32 통신 등)를 첨부해주세요.

# [작성칸] 예시: Flask 서버에서 GNSS 좌표를 실시간 송신하는 코드 예시

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

💡 추가 정보
항목	내용
프로젝트 번호	[예: 25_HCXXX]
GitHub 저장소 주소	https://github.com/[깃허브계정]/[프로젝트번호]
문서 자료	발표자료, 보고서, 논문 등은 /docs 폴더 참고
CAD 설계 파일	SolidWorks .SLDPRT, .SLDASM, .STEP 형식 지원
