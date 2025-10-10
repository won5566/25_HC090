# GNSS Remote-Steering Variable-Wheel Robot (Mono-Repo Skeleton)

- **server/**: Python server (App Inventor ¡æ Flask ¡æ ESP32 bridge)
- **stm32/**: Motor/steering/variable-wheel firmware
- **esp32/**: Wi-Fi TCP bridge to STM32
- **arduino/**: Mega sub #1 IR alignment, sub #2 gimbal leveling
- **ros2/**: GNSS, camera nodes, launch/config, ngrok scripts
- **appinventor/**: Exported .aia
- **cad/**: Native CAD + exports (STEP/STL) + drawings
- **docs/**: Posters, papers, figures; **data/**: logs/datasets; **scripts/**: utility scripts

## How to drop your existing code
- Put Flask code into `server/app/` (+ services/ if needed).
- STM32 CubeIDE project into `stm32/`.
- ESP32 Arduino sketch into `esp32/src/`.
- Arduino Mega submodules into `arduino/mega_sub1_ir_align/`, `arduino/mega_sub2_gimbal/`.
- ROS2 pkgs into `ros2/src/`, launch into `ros2/launch/`, scripts into `ros2/scripts/`.
- App Inventor `.aia` into `appinventor/`.
- CAD native files into `cad/mechanical` & `cad/electronics`; export STEP/STL into `cad/exports`.

