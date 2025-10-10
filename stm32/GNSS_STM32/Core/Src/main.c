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
uint8_t cmdOn2 [] =  {0xFF,0xFE,0x02,0x03,0xEE,0x0C,0x00};  // MOTOR0 ON
uint8_t cmdOn3 [] =  {0xFF,0xFE,0x03,0x03,0xED,0x0C,0x00};  // MOTOR2 ON
uint8_t cmdOff0[] =  {0xFF,0xFE,0x00,0x03,0xEF,0x0C,0x01};  // MOTOR0 OFF
uint8_t cmdOff1[] =  {0xFF,0xFE,0x01,0x03,0xEE,0x0C,0x01};  // MOTOR1 OFF
uint8_t cmdOff2[] =  {0xFF,0xFE,0x02,0x03,0xED,0x0C,0x01};  // MOTOR2 OFF
uint8_t cmdOff3[] =  {0xFF,0xFE,0x03,0x03,0xEC,0x0C,0x01};  // MOTOR3 OFF
uint8_t rx_data = 0;
uint8_t offset_data = 0;
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

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART6_UART_Init();
  MX_LWIP_Init();
  MX_TIM4_Init();
  MX_UART5_Init();
  MX_TIM3_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */

  // BLDC MOTOR START Baudrate, Speed SET WITH RS485
  setMotorRatedSpeed(0, 5);   //BLDC MOTOR ID 0 SPEED 5 SET
  setMotorRatedSpeed(1, 5);   //BLDC MOTOR ID 1 SPEED 5 SET
  setMotorRatedSpeed(2, 5);   //BLDC MOTOR ID 2 SPEED 5 SET
  setMotorRatedSpeed(3, 5);   //BLDC MOTOR ID 3 SPEED 5 SET

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);   //STEERING LEFT FRONT, PC6
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);   //STEERING LEFT BACK, PC7
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);   //STEERING RIGHT FRONT, PC8
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);   //STEERING RIGHT BACK, PC9

  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);   //VARIABLE WHEEL LEFTFRONT, PD12
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);   //VARIABLE WHEEL LEFT BACK, PD13
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);   //VARIABLE WHEEL RIGHT FRONT, PD14
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);   //VARIABLE WHEEL RIGHT BACK, PD15


  HAL_UART_Receive_IT(&huart5, &rx_data, 1);
  Set_Servo_Angle(&htim4, TIM_CHANNEL_1, 135);    // STEERING LEFT FRONT 135
  Set_Servo_Angle(&htim4, TIM_CHANNEL_2, 130);    // STEERING LEFT BACK 135
  Set_Servo_Angle(&htim4, TIM_CHANNEL_3, 145);  // STEERING RIGHT FRONT 135
  Set_Servo_Angle(&htim4, TIM_CHANNEL_4, 132);  // STEERING RIGHT BACK 135
  ApplySteering(0);      //START VARIABLE WHEEL
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_2);
  HAL_Delay(500);
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  ApplySteering(-30);   // START STEERING
//	  ApplyTire(-60);      //START VARIABLE WHEEL
//	  HAL_Delay(3000);
//	  ApplySteering(0);   // START STEERING
//	  ApplyTire(0);      //START VARIABLE WHEEL
//
//	  HAL_Delay(3000);
//	  ApplySteering(30);   // START STEERING
//	  ApplyTire(60);      //START VARIABLE WHEEL
//	  HAL_Delay(3000);
//	  ApplyTire(0);      //START VARIABLE WHEEL
//	  ApplySteering(0);   // START STEERING
//	  HAL_Delay(3000);
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 83;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 20000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1500;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 83;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 20000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1500;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 115200;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin : PE2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : Wheel1_Pin Wheel2_Pin Wheel3_Pin Wheel4_Pin */
  GPIO_InitStruct.Pin = Wheel1_Pin|Wheel2_Pin|Wheel3_Pin|Wheel4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == UART5) {
	  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_2);
      switch (rx_data) {
        case 'f':   //BLDC MOTOR FRONT
          RS485_Send(cmdOn0, sizeof(cmdOn0));
          RS485_Send(cmdOn1, sizeof(cmdOn1));
          RS485_Send(cmdOn2, sizeof(cmdOn2));
          RS485_Send(cmdOn3, sizeof(cmdOn3));
          if(DriveState == ROTATE){
              setMotorRatedSpeed(0, ROTATE_Speed);
              setMotorRatedSpeed(1, ROTATE_Speed);
              setMotorRatedSpeed(2, ROTATE_Speed);
              setMotorRatedSpeed(3, ROTATE_Speed);
              accelerateSpeedControl(0, 1, 1.0f, ROTATE_Speed);
              accelerateSpeedControl(1, 1, 1.0f, ROTATE_Speed);
              accelerateSpeedControl(2, 1, 1.0f, ROTATE_Speed);
              accelerateSpeedControl(3, 1, 1.0f, ROTATE_Speed);
          }
          else if(DriveState == VERTICAL){
             setMotorRatedSpeed(0, VERTICAL_Speed);
           setMotorRatedSpeed(1, VERTICAL_Speed);
           setMotorRatedSpeed(2, VERTICAL_Speed);
           setMotorRatedSpeed(3, VERTICAL_Speed);
           accelerateSpeedControl(0, 1, 1.0f, VERTICAL_Speed);
           accelerateSpeedControl(1, 1, 1.0f, VERTICAL_Speed);
           accelerateSpeedControl(2, 0, 1.0f, VERTICAL_Speed);
           accelerateSpeedControl(3, 0, 1.0f, VERTICAL_Speed);
          }
          else{
           if(State == STATE_CENTER){
              setMotorRatedSpeed(0, CENTER_Speed);
              setMotorRatedSpeed(1, CENTER_Speed);
              setMotorRatedSpeed(2, CENTER_Speed);
              setMotorRatedSpeed(3, CENTER_Speed);
              accelerateSpeedControl(0, 0, 1.0f, CENTER_Speed);
              accelerateSpeedControl(1, 0, 1.0f, CENTER_Speed);
              accelerateSpeedControl(2, 1, 1.0f, CENTER_Speed);
              accelerateSpeedControl(3, 1, 1.0f, CENTER_Speed);
           }
           else if(State == STATE_CCW){
              setMotorRatedSpeed(0, CCW_Speed);
              setMotorRatedSpeed(1, CCW_Speed);
              setMotorRatedSpeed(2, CCW_Speed);
              setMotorRatedSpeed(3, CCW_Speed);
              accelerateSpeedControl(0, 0, 1.0f, CCW_Speed);
              accelerateSpeedControl(1, 0, 1.0f, CCW_Speed);
              accelerateSpeedControl(2, 1, 1.0f, CCW_Speed);
              accelerateSpeedControl(3, 1, 1.0f, CCW_Speed);
           }
           else if(State == STATE_CW){
              setMotorRatedSpeed(0, CW_Speed);
              setMotorRatedSpeed(1, CW_Speed);
              setMotorRatedSpeed(2, CW_Speed);
              setMotorRatedSpeed(3, CW_Speed);
              accelerateSpeedControl(0, 0, 1.0f, CW_Speed);
              accelerateSpeedControl(1, 0, 1.0f, CW_Speed);
              accelerateSpeedControl(2, 1, 1.0f, CW_Speed);
              accelerateSpeedControl(3, 1, 1.0f, CW_Speed);
           }
          }
          currentState = STATE_FORWARD;
          break;
        case 'b':   //BLDC MOTOR BACK
          RS485_Send(cmdOn0, sizeof(cmdOn0));
          RS485_Send(cmdOn1, sizeof(cmdOn1));
          RS485_Send(cmdOn2, sizeof(cmdOn2));
          RS485_Send(cmdOn3, sizeof(cmdOn3));
          if(DriveState == ROTATE){
              setMotorRatedSpeed(0, ROTATE_Speed);
              setMotorRatedSpeed(1, ROTATE_Speed);
              setMotorRatedSpeed(2, ROTATE_Speed);
              setMotorRatedSpeed(3, ROTATE_Speed);
              accelerateSpeedControl(0, 0, 1.0f, ROTATE_Speed);
              accelerateSpeedControl(1, 0, 1.0f, ROTATE_Speed);
              accelerateSpeedControl(2, 0, 1.0f, ROTATE_Speed);
              accelerateSpeedControl(3, 0, 1.0f, ROTATE_Speed);
          }
          else if(DriveState == VERTICAL){
           setMotorRatedSpeed(0, VERTICAL_Speed);
           setMotorRatedSpeed(1, VERTICAL_Speed);
           setMotorRatedSpeed(2, VERTICAL_Speed);
           setMotorRatedSpeed(3, VERTICAL_Speed);
           accelerateSpeedControl(0, 1, 1.0f, VERTICAL_Speed);
           accelerateSpeedControl(1, 1, 1.0f, VERTICAL_Speed);
           accelerateSpeedControl(2, 0, 1.0f, VERTICAL_Speed);
           accelerateSpeedControl(3, 0, 1.0f, VERTICAL_Speed);
          }
          else{
           if(State == STATE_CENTER){
              setMotorRatedSpeed(0, CENTER_Speed);
              setMotorRatedSpeed(1, CENTER_Speed);
              setMotorRatedSpeed(2, CENTER_Speed);
              setMotorRatedSpeed(3, CENTER_Speed);
              accelerateSpeedControl(0, 1, 1.0f, CENTER_Speed);
              accelerateSpeedControl(1, 1, 1.0f, CENTER_Speed);
              accelerateSpeedControl(2, 0, 1.0f, CENTER_Speed);
              accelerateSpeedControl(3, 0, 1.0f, CENTER_Speed);
           }
           else if(State == STATE_CCW){
              setMotorRatedSpeed(0, CCW_Speed);
              setMotorRatedSpeed(1, CCW_Speed);
              setMotorRatedSpeed(2, CCW_Speed);
              setMotorRatedSpeed(3, CCW_Speed);
              accelerateSpeedControl(0, 1, 1.0f, CCW_Speed);
              accelerateSpeedControl(1, 1, 1.0f, CCW_Speed);
              accelerateSpeedControl(2, 0, 1.0f, CCW_Speed);
              accelerateSpeedControl(3, 0, 1.0f, CCW_Speed);
           }
           else if(State == STATE_CW){
              setMotorRatedSpeed(0, CW_Speed);
              setMotorRatedSpeed(1, CW_Speed);
              setMotorRatedSpeed(2, CW_Speed);
              setMotorRatedSpeed(3, CW_Speed);
              accelerateSpeedControl(0, 1, 1.0f, CW_Speed);
              accelerateSpeedControl(1, 1, 1.0f, CW_Speed);
              accelerateSpeedControl(2, 0, 1.0f, CW_Speed);
              accelerateSpeedControl(3, 0, 1.0f, CW_Speed);
           }
          }
          currentState = STATE_BACKWARD;
          break;
        case 's':   //BLDC MOTOR STOP
          RS485_Send(cmdOff0, sizeof(cmdOff0));
          RS485_Send(cmdOff1, sizeof(cmdOff1));
          RS485_Send(cmdOff2, sizeof(cmdOff2));
          RS485_Send(cmdOff3, sizeof(cmdOff3));
          currentState = STATE_STOP;
          break;
        case 'e':   //VARIABLE MODE CCW
          if(currentState == STATE_STOP){
             Set_Servo_Angle(&htim4, TIM_CHANNEL_1, 185);   // STEERING LEFT FRONT 162
             Set_Servo_Angle(&htim4, TIM_CHANNEL_2, 182);   // STEERING LEFT BACK 162
             Set_Servo_Angle(&htim4, TIM_CHANNEL_3, 202);     // STEERING RIGHT FRONT 90
             Set_Servo_Angle(&htim4, TIM_CHANNEL_4, 65);     // STEERING RIGHT BACK 90
          }
          State = STATE_CCW;   //HUMBLE
          break;
        case 'w':   //VARIABLE MODE CW
          if(currentState == STATE_STOP){
             Set_Servo_Angle(&htim4, TIM_CHANNEL_1, 90);    // STEERING LEFT FRONT 90
             Set_Servo_Angle(&htim4, TIM_CHANNEL_2, 90);    // STEERING LEFT BACK 90
             Set_Servo_Angle(&htim4, TIM_CHANNEL_3, 60);  // STEERING RIGHT FRONT 162
              Set_Servo_Angle(&htim4, TIM_CHANNEL_4, 222);  // STEERING RIGHT BACK 162
          }
          State = STATE_CW;
          break;
        case 'c':   //VARIABLE MODE CENTER
          if(currentState == STATE_STOP){
             if(State == STATE_CCW){
            	  Set_Servo_Angle(&htim4, TIM_CHANNEL_1, 130);    // STEERING LEFT FRONT 135
            	  Set_Servo_Angle(&htim4, TIM_CHANNEL_2, 135);    // STEERING LEFT BACK 135
            	  Set_Servo_Angle(&htim4, TIM_CHANNEL_3, 135);  // STEERING RIGHT FRONT 135
            	  Set_Servo_Angle(&htim4, TIM_CHANNEL_4, 135);  // STEERING RIGHT BACK 135
             }
             else if(State == STATE_CW){
            	  Set_Servo_Angle(&htim4, TIM_CHANNEL_1, 142);    // STEERING LEFT FRONT 135
            	  Set_Servo_Angle(&htim4, TIM_CHANNEL_2, 137);    // STEERING LEFT BACK 135
            	  Set_Servo_Angle(&htim4, TIM_CHANNEL_3, 143);  // STEERING RIGHT FRONT 135
            	  Set_Servo_Angle(&htim4, TIM_CHANNEL_4, 128);  // STEERING RIGHT BACK 135
             }
             else{
            	  Set_Servo_Angle(&htim4, TIM_CHANNEL_1, 135);    // STEERING LEFT FRONT 135
            	  Set_Servo_Angle(&htim4, TIM_CHANNEL_2, 130);    // STEERING LEFT BACK 135
            	  Set_Servo_Angle(&htim4, TIM_CHANNEL_3, 145);  // STEERING RIGHT FRONT 135
            	  Set_Servo_Angle(&htim4, TIM_CHANNEL_4, 132);
             }
          }
          State = STATE_CENTER;
          break;
        case 'a':   //DRIVE MODE SET
           DriveState = DRIVE;
           ApplySteering(-45);   //ALL STEERING -45 SET
           break;
        case 'd':   //DRIVE MODE SET
           DriveState = DRIVE;
           ApplySteering(-36);   //ALL STEERING -36 SET
           break;
        case 'g':   //DRIVE MODE SET
           DriveState = DRIVE;
           ApplySteering(-27);   //ALL STEERING -27 SET
           break;
        case 'h':   //DRIVE MODE SET
           DriveState = DRIVE;
           ApplySteering(-18);   //ALL STEERING -18 SET
           break;
        case 'i':   //DRIVE MODE SET
           DriveState = DRIVE;
           ApplySteering(-9);   //ALL STEERING -9 SET
           break;
        case 'j':   //DRIVE MODE SET
           DriveState = DRIVE;
           ApplySteering(0);   //ALL STEERING 0 SET
           break;
        case 'k':   //DRIVE MODE SET
           DriveState = DRIVE;
           ApplySteering(9);   //ALL STEERING 9 SET
           break;
        case 'm':   //DRIVE MODE SET
           DriveState = DRIVE;
           ApplySteering(18);   //ALL STEERING 18 SET
           break;
        case 'n':   //DRIVE MODE SET
           DriveState = DRIVE;
           ApplySteering(27);   //ALL STEERING 27 SET
           break;
        case 'o':   //DRIVE MODE SET
           DriveState = DRIVE;
           ApplySteering(36);   //ALL STEERING 36 SET
           break;
        case 'p':   //DRIVE MODE SET
           DriveState = DRIVE;
           ApplySteering(45);   //ALL STEERING 45 SET
           break;
        case 'q':   //ROTATE MODE SET
           DriveState = ROTATE;
           if(currentState == STATE_STOP && State == STATE_CENTER){
           Set_Servo_Angle(&htim3, TIM_CHANNEL_1, 180);
           Set_Servo_Angle(&htim3, TIM_CHANNEL_2, 90);
           Set_Servo_Angle(&htim3, TIM_CHANNEL_3, 90);
           Set_Servo_Angle(&htim3, TIM_CHANNEL_4, 180);
           }
           break;
        case 't':   //VERTICAL MODE SET
           DriveState = VERTICAL;
           if(currentState == STATE_STOP && State == STATE_CENTER){
           Set_Servo_Angle(&htim3, TIM_CHANNEL_1, 225);
           Set_Servo_Angle(&htim3, TIM_CHANNEL_2, 45);
           Set_Servo_Angle(&htim3, TIM_CHANNEL_3, 45);
           Set_Servo_Angle(&htim3, TIM_CHANNEL_4, 225);
           }
           break;
        case 'z':   //?��?��
          if(currentState == STATE_STOP){
          	  RS485_Send(cmdOn0, sizeof(cmdOn0));
          	  RS485_Send(cmdOn1, sizeof(cmdOn1));
          	  RS485_Send(cmdOn2, sizeof(cmdOn2));
          	  RS485_Send(cmdOn3, sizeof(cmdOn3));
              setMotorRatedSpeed(0, CW_Speed);
              setMotorRatedSpeed(1, CW_Speed);
              setMotorRatedSpeed(2, CW_Speed);
              setMotorRatedSpeed(3, CW_Speed);
              accelerateSpeedControl(0, 1, 1.0f, CW_Speed);
              accelerateSpeedControl(1, 1, 1.0f, CW_Speed);
              accelerateSpeedControl(2, 0, 1.0f, CW_Speed);
              accelerateSpeedControl(3, 0, 1.0f, CW_Speed);
              while((Wheel1 < 1) || (Wheel2 < 1) || (Wheel3 < 1) || (Wheel4 < 1)) {
            	  if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == GPIO_PIN_SET && Wheel1 == 0){
                      RS485_Send(cmdOff2, sizeof(cmdOff2));
                      Wheel1++;
            	  }
            	  if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == GPIO_PIN_SET && Wheel2 == 0){
                      RS485_Send(cmdOff3, sizeof(cmdOff3));
                      Wheel2++;
            	  }
            	  if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == GPIO_PIN_SET && Wheel3 == 0){
                      RS485_Send(cmdOff0, sizeof(cmdOff0));
                      Wheel3++;
            	  }
            	  if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == GPIO_PIN_SET && Wheel4 == 0){
                      RS485_Send(cmdOff1, sizeof(cmdOff1));
                      Wheel4++;
              }
          }
          Wheel1 = 0;
          Wheel2 = 0;
          Wheel3 = 0;
          Wheel4 = 0;
          }
          break;
        default:
           break;
      }
    HAL_UART_Receive_IT(&huart5, &rx_data, 1);
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

void Set_Servo_Angle(TIM_HandleTypeDef* htim, uint32_t Channel, int16_t angle)
{
  if (angle > 270) angle = 270;
  if (angle < 0)   angle = 0;
  uint16_t pulse = SERVO_MIN_PULSE + (angle * (SERVO_MAX_PULSE - SERVO_MIN_PULSE) / SERVO_MAX_ANGLE);
  if (pulse > 2500) pulse = 2500;
  if (pulse < 500) pulse = 500;
  __HAL_TIM_SET_COMPARE(htim, Channel, pulse);

}

void RS485_Send(uint8_t *pData, uint16_t size)
{
  HAL_UART_Transmit(&huart4, pData, size, HAL_MAX_DELAY);
}

void accelerateSpeedControl(uint8_t id, uint8_t dir, float rpm, uint8_t t)
{
  uint16_t speedVal = (uint16_t)(rpm * 10);
  uint8_t LSB = speedVal & 0xFF;
  uint8_t MSB = (speedVal >> 8) & 0xFF;
  uint8_t mode = 0x03;
  uint8_t dataSize = 0x06;
  uint16_t sum = id + dataSize + mode + dir + LSB + MSB + t;
  uint8_t chk = (uint8_t)~(sum & 0xFF);
  uint8_t pkt[10] = {0xFF,0xFE, id, dataSize, chk, mode, dir, LSB, MSB, t};
  RS485_Send(pkt, sizeof(pkt));
}

void setCommBaudrate(uint8_t id, uint32_t baud)
{
  uint8_t mode = 0x08;
  uint8_t dataSize = 0x03;
  uint8_t baudCode = 0x01;
  uint16_t sum = id + dataSize + mode + baudCode;
  uint8_t chk = (uint8_t)~(sum & 0xFF);
  uint8_t pkt[7] = {0xFF,0xFE, id, dataSize, chk, mode, baudCode};
  RS485_Send(pkt, sizeof(pkt));
}
void setMotorRatedSpeed(uint8_t id, uint16_t rpm)
{
  uint8_t mode = 0x09;
  uint8_t dataSize = 0x04;
  uint8_t LSB = rpm & 0xFF;
  uint8_t MSB = (rpm >> 8) & 0xFF;
  uint16_t sum = id + dataSize + mode + LSB + MSB;
  uint8_t chk = (uint8_t)~(sum & 0xFF);
  uint8_t pkt[8] = {0xFF,0xFE, id, dataSize, chk, mode, LSB, MSB};
  RS485_Send(pkt, sizeof(pkt));
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
