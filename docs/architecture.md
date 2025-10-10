## System Architecture (Final)
- Tablet (Remote): GNSS map (ngrok), camera stream (ngrok), Control UI (Flask)
- Laptop (Flask Server): Python TCP server, ngrok stream, GNSS & webcam streaming
- ESP32: TCP command relay → UART
- STM32: BLDC (RS485), Steering/Variable Wheel (PWM), Mode logic
- Arduino Sub#1: Wheel alignment (IR)
- Arduino Sub#2: 2-axis gimbal (MPU6050 PID, standalone)
