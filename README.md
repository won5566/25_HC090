
# 2025년 한이음 드림업 공모전 README

## 프로젝트 개요

### 1-1. 프로젝트 소개
- **프로젝트 명:** Mobile Robot Equipped with GNSS-Based Remote Steering and Variable Wheels
- **프로젝트 정의:** GNSS 기반 원격 조향과 가변 지름 휠 메커니즘을 결합해 지형 적응성과 정밀 제어를 구현한 전지형(ATV) 모바일 로봇
![대표 이미지](https://github.com/user-attachments/assets/c05cce6f-0488-4bf0-afa9-3d8789106f38)


### 1-2. 개발 배경 및 필요성
현대의 이동 로봇은 특정 지형에 국한되거나 제어 안정성이 떨어지는 경우가 많습니다. 본 프로젝트는 **RTK-GNSS 기반 고정밀 위치 인식**, **가변 반경 휠 구조(Ø140–200mm)**, **ROS2 + Flask + MCU 계층형 아키텍처**를 통해 다양한 지형(도로, 모래, 잔디, 경사면)에서도 안정적인 주행과 원격 제어를 가능하게 합니다.

### 1-3. 프로젝트 특장점
- RTK 보정 GNSS(±수 cm급)와 ROS2 시각화 연동
- Flask 웹 UI + App Inventor 원격 조작(조이스틱/모드 전환)
- 가변 휠 반경(140 ↔ 200 mm)로 지형 대응성 향상
- 독립 4륜 조향(4WIS) + 4륜 구동(4WD)
- IR 센서 기반 휠 자동 정렬, 2축 짐벌 카메라 안정화
- 계층형 구조(ROS2/서버/MCU)로 유지보수 및 확장 용이

### 1-4. 주요 기능
| 구분 | 설명 |
|---|---|
| GNSS Localization | ZED-F9P RTK GNSS → ROS2 NavSatFix → JSON/맵 시각화 |
| Remote Control | Flask Web UI + App Inventor 조이스틱 |
| Variable Wheel | 반경 가변(Ø140–200mm) 4-bar 링크 |
| Independent Steering | 0°–270° 서보 조향(4WIS) |
| Auto Alignment | IR 기반 휠 제로 포지션 보정 |
| Camera Stabilization | MPU6050 + PID 2축 짐벌 |
| Visualization | GNSS 맵 + 라이브 비디오 스트림 |
| Modular Architecture | ROS2 / Flask / MCU 분리 설계 |

### 1-5. 기대 효과 및 활용 분야
- **기대 효과:** 지형 적응형 로봇 플랫폼, 정밀 원격 제어, 연구·교육용 통합 학습 자료화
- **활용 분야:** 재난 대응, 농업 자동화, 국방/감시, 교육·연구

### 1-6. 기술 스택
| 분야 | 기술 |
|---|---|
| 임베디드 | STM32F429, ESP32, Arduino Mega 2560 |
| 통신 | UART, RS-485, TCP/IP, PWM |
| 소프트웨어 | ROS2 Humble, Python 3.10, Flask, OpenCV |
| 디자인 | SolidWorks 2023, MIT App Inventor 2 |
| 센서 | ZED-F9P GNSS, MPU6050 IMU, IR Sensor |
| 플랫폼 | Jetson Orin Nano (Ubuntu 22.04) |


---

## 팀원 소개

| 사진 | 이름 | 역할 |
|:---:|:---:|:---|
| <img src="https://github.com/user-attachments/assets/52430eb1-d622-41ce-b475-ce35062142aa" width="100" height="120" alt="김진겸"> | **김진겸 (팀장)** | 모바일 UI(App Inventor) 개발 · 휠 정렬(IR 센서) 제어 담당 |
| <img src="https://github.com/user-attachments/assets/89d5b5e9-3e84-4370-8a89-fe7a86e171c1" width="100" height="120" alt="김형준"> | **김형준** | RTK-GNSS 위치 인식 · 2축 카메라 짐벌 제어 |
| <img src="https://github.com/user-attachments/assets/3e6b5a1c-4460-4a50-a415-82bbf676019e" width="100" height="120" alt="이광민"> | **이광민** | 기구 및 샤시 설계 · 전장 하드웨어 통합 |
| <img src="https://github.com/user-attachments/assets/3c08e585-0d89-45f7-9535-9dab7630240f" width="100" height="120" alt="이원무"> | **이원무** | STM32 펌웨어 개발 · 포트포워딩 · 통신 프로토콜 설계 |
| <img src="https://github.com/user-attachments/assets/b9469bf2-5497-46ec-899a-6d73a6699721" width="100" height="120" alt="김관영"> | **김관영 (멘토)** | 임베디드 시스템 및 로보틱스 기술 자문 |


---

## 시스템 구성도

- **시스템 구성도:**
![시스템 구성도](https://github.com/user-attachments/assets/3ca71442-1af0-4a4f-8f23-4eb5f44d2ca8)
- **Flow Chart:**
![Flow Chart](https://github.com/user-attachments/assets/4de063cc-3acd-4e09-9371-e8ec3ee3c217)

---

## 작품 소개영상

<a href="https://youtu.be/KRKrqYnISS0?si=5UeAExnnUVnlLwTY" target="_blank">
  <img src="https://github.com/user-attachments/assets/aa436e09-79fd-4b26-84e7-2259dffecb78" width="600" alt="GNSS 기반 원격제어 스티어링 가변 휠 주행 로봇 영상 썸네일">
</a>

> ▶ 이미를 클릭하면 유튜브 영상이 새 탭에서 재생됩니다.

---

## 핵심 소스코드

> STM32 + RS-485 + TCP(LwIP) 기반 BLDC 제어 및 가변 휠/조향 제어의 메인 루프 발췌본입니다.

```c
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body - Motor Control via RS485 and TCP
  * @details        : This firmware sets up TCP server communication using LwIP
  *                   and controls BLDC motors via RS-485 commands. PWM output removed.
  ******************************************************************************
  */

#include <stdlib.h>
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define SERVO_MIN_PULSE 500
#define SERVO_MAX_PULSE 2500
#define SERVO_MAX_ANGLE 270
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
uint8_t cmdOn0 [] =  {0xFF,0xFE,0x00,0x03,0xF0,0x0C,0x00};  // MOTOR0 ON
uint8_t cmdOn1 [] =  {0xFF,0xFE,0x01,0x03,0xEF,0x0C,0x00};  // MOTOR1 ON
uint8_t cmdOn2 [] =  {0xFF,0xFE,0x02,0x03,0xEE,0x0C,0x00};  // MOTOR2 ON
uint8_t cmdOn3 [] =  {0xFF,0xFE,0x03,0x03,0xED,0x0C,0x00};  // MOTOR3 ON
uint8_t cmdOff0[] =  {0xFF,0xFE,0x00,0x03,0xEF,0x0C,0x01};  // MOTOR0 OFF
uint8_t cmdOff1[] =  {0xFF,0xFE,0x01,0x03,0xEE,0x0C,0x01};  // MOTOR1 OFF
uint8_t cmdOff2[] =  {0xFF,0xFE,0x02,0x03,0xED,0x0C,0x01};  // MOTOR2 OFF
uint8_t cmdOff3[] =  {0xFF,0xFE,0x03,0x03,0xEC,0x0C,0x01};  // MOTOR3 OFF
uint8_t rx_data = 0;
uint8_t CENTER_Speed = 8;
uint8_t CW_Speed = 2;
uint8_t CCW_Speed = 2;
uint8_t ROTATE_Speed = 5;
uint8_t VERTICAL_Speed = 5;
uint8_t Wheel1 = 0;
uint8_t Wheel2 = 0;
uint8_t Wheel3 = 0;
uint8_t Wheel4 = 0;

typedef enum {STATE_STOP, STATE_FORWARD, STATE_BACKWARD} MotorState;   //BLDC MOTOR STATE
typedef enum {STATE_CENTER, STATE_CW, STATE_CCW} WheelState;   //VARIABLE WHEEL STATE
typedef enum {DRIVE, ROTATE, VERTICAL} ModeState;   //DRIVEMODE STATE
MotorState currentState = STATE_STOP;     //BLDC MOTOR START STATE
WheelState State = STATE_CENTER;   //VARIABLE WHEEL START STATE
ModeState DriveState = DRIVE;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_TIM4_Init(void);
static void MX_UART5_Init(void);
static void MX_TIM3_Init(void);
static void MX_UART4_Init(void);
/* USER CODE BEGIN PFP */
void RS485_Send(uint8_t *pData, uint16_t size);
void accelerateSpeedControl(uint8_t id, uint8_t dir, float rpm, uint8_t t);
void setCommBaudrate(uint8_t id, uint32_t baud);
void setMotorRatedSpeed(uint8_t id, uint16_t rpm);
void Set_Servo_Angle(TIM_HandleTypeDef* htim, uint32_t Channel, int16_t angle);
void ApplyTire(int8_t offset);
void ApplySteering(int8_t offset);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART6_UART_Init();
  MX_LWIP_Init();
  MX_TIM4_Init();
  MX_UART5_Init();
  MX_TIM3_Init();
  MX_UART4_Init();

  setMotorRatedSpeed(0, 5);
  setMotorRatedSpeed(1, 5);
  setMotorRatedSpeed(2, 5);
  setMotorRatedSpeed(3, 5);

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);

  HAL_UART_Receive_IT(&huart5, &rx_data, 1);

  Set_Servo_Angle(&htim4, TIM_CHANNEL_1, 135);
  Set_Servo_Angle(&htim4, TIM_CHANNEL_2, 130);
  Set_Servo_Angle(&htim4, TIM_CHANNEL_3, 145);
  Set_Servo_Angle(&htim4, TIM_CHANNEL_4, 132);
  ApplySteering(0);

  while (1) {
    // main loop
  }
}

void ApplyTire(int8_t offset)
{
  int16_t base_angle = 135;
  int16_t target = base_angle + offset;
  if (target > 270) target = 270;
  if (target < 0)   target = 0;
  Set_Servo_Angle(&htim4, TIM_CHANNEL_1, target);
  Set_Servo_Angle(&htim4, TIM_CHANNEL_2, target);
  Set_Servo_Angle(&htim4, TIM_CHANNEL_3, target);
  Set_Servo_Angle(&htim4, TIM_CHANNEL_4, target);
}

void ApplySteering(int8_t offset)
{
  int16_t base_angle = 135;
  int16_t target = base_angle + offset;
  int16_t target1 = base_angle - offset;
  if (target > 270) target = 270;
  if (target < 0)   target = 0;
  Set_Servo_Angle(&htim3, TIM_CHANNEL_1, target);
  Set_Servo_Angle(&htim3, TIM_CHANNEL_2, target1);
  Set_Servo_Angle(&htim3, TIM_CHANNEL_3, target);
  Set_Servo_Angle(&htim3, TIM_CHANNEL_4, target1);
}
```


## 프로젝트 번호 및 저장소 정보 

- **프로젝트 번호:** `25_HC090`  
- **GitHub 저장소:** https://github.com/won5566/25_HC090.git


---

## 참고: 저장소 구조

```
.
├─ appinventor/                # Android 조이스틱 앱 (.aia + README)
├─ arduino/
│  ├─ mega_sub1_ir_alignment/  # IR 휠 자동 정렬
│  └─ mega_sub2_gimbal/        # 2축 짐벌 PID 제어
├─ cad/                        # Variable Wheel, Steering, Camera CAD
├─ docs/                       # 발표, 보고서, 논문
├─ esp32/                      # Flask ↔ STM32 TCP 릴레이
├─ ros2/                       # GNSS→JSON 브리지 + 웹 시각화
├─ server/                     # Flask + TCP 서버
├─ stm32/                      # RS-485(BLDC), PWM(Servo), UART5(ESP32)
└─ README.md
```

---
