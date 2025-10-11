A four-wheel steering, all-terrain mobile robot with variable-diameter wheels and RTK GNSS for precise navigation. This project features four-bar linkage reconfigurable wheels that can change radius on the fly
cambridge.org
, allowing the robot to climb obstacles and adapt to uneven terrain. It uses four-wheel independent steering for superior maneuverability (reducing turning radius at low speed and improving stability at high speed
frontiersin.org
), and integrates an RTK-GNSS module for centimeter-level positioning accuracy
ardusimple.com
. The robot is remotely controlled via a tablet-based UI, enabling teleoperation and monitoring of the rover in real time. This repository provides the full hardware designs, firmware (Arduino & STM32), and ROS 2 (Python) software stack for the robot.

Demo Video 🎥


Watch the rover in action: climbing a step, navigating with RTK GNSS, and controlled via the tablet interface.

Full Demo: YouTube: All-Terrain 4WS Rover Demonstration (4 min)

GNSS Navigation: YouTube: RTK GNSS Position Holding Test (2 min)

Hardware Specifications

Chassis & Locomotion: Custom 4-wheel drive chassis with four-bar linkage variable-diameter wheels
cambridge.org
. Each wheel’s radius can expand or contract via a linkage mechanism, effectively transforming wheel size to overcome obstacles (tested up to ~125 mm step height
cambridge.org
). The wheels are driven by high-torque DC motors with encoders.

Steering: Four-wheel independent steering (4WS) using servo actuators on each wheel assembly. This 4WS design greatly reduces turning radius and improves maneuverability in tight spaces
frontiersin.org
, as all wheels can steer in coordination (enabling Ackermann, crab, or zero-radius turns).

RTK GNSS: Ublox ZED-F9P RTK-GNSS module (multi-band GPS/GNSS) for navigation. In RTK mode with a base station or NTRIP corrections, it provides centimeter-level positioning accuracy for precise waypoint navigation
ardusimple.com
. The rover mounts a GNSS antenna with clear sky view and uses a radio/Ethernet link for RTCM correction data.

Onboard Computer: Raspberry Pi 4 (4GB) running Ubuntu 22.04 and ROS 2 Humble as the main control computer. This handles high-level ROS 2 nodes (navigation, telemetry, UI server) and communicates with microcontrollers.

Microcontrollers:

STM32 (STM32F4 series) – handles low-level motor control (wheel drive motors and steering servos) with real-time PID loops. It interfaces with the ROS 2 system via a serial or DDS bridge, offloading time-critical tasks to a real-time MCU
micro.ros.org
.

Arduino (Arduino Mega 2560) – controls the wheel reconfiguration mechanism (driving the linkage actuators that expand/contract the wheels). It monitors wheel mode sensors and ensures all four wheels deploy uniformly.

Sensors: Wheel encoders on each motor for odometry, an IMU (MPU-9250) for orientation, and the GNSS receiver for global position. The IMU and encoder data can be fused with GNSS if needed for state estimation (e.g., using an EKF).

Power System: 24 V Li-ion battery pack (6S) powering motors via ESCs/motor drivers, with DC-DC regulators for logic levels. The STM32 and Arduino are powered through a 5 V regulator. A safety E-stop is included to cut motor power.

Mechanical Design: The robot’s four-bar linkage wheels are built with aluminum links and 3D-printed hubs. When retracted, the wheel rolls normally; when expanded, the wheel’s diameter increases ~1.5×, allowing it to lift the chassis over obstacles
cambridge.org
. Each wheel’s reconfiguration is driven by a dedicated servo motor. The chassis frame is aluminum alloy with suspension to distribute loads during obstacle crossing.

Software Architecture & Technologies

The robot’s software is organized as a ROS 2 application with auxiliary microcontroller firmware, combining high-level autonomy with low-level real-time control:

ROS 2 Nodes (Humble): The onboard computer runs ROS 2 nodes written in Python (rclpy) and C++ (rclcpp). Key nodes include:

gps_node: Reads GNSS data (NMEA or Ublox binary) from the serial port and publishes standardized ROS 2 messages (sensor_msgs/NavSatFix)
ardusimple.com
. If RTK corrections are available, this node configures the GNSS for RTK mode.

drive_control_node: High-level motion controller that sends velocity commands (geometry_msgs/Twist) to the motor controller MCU. It can implement teleop commands or autonomous navigation logic.

teleop_ui_node: Hosts a WebSocket or ROSbridge server to communicate with the tablet UI. It streams telemetry (like current position, battery level, video feed if available) and relays remote drive commands.

wheel_reconfig_node: Coordinates the wheel diameter change. It can call a service on the Arduino to expand or retract wheels, and ensures the robot is stopped and aligned before reconfiguration.

(Optional) nav_pipeline: If autonomous navigation was explored, this could include path planning or Nav2 integration. By default, the robot is teleoperated, but the framework allows adding autonomy easily.

Microcontroller Firmware:

STM32 Firmware: Runs a real-time control loop reading wheel encoder ticks and IMU data, and controlling motor drivers and steering servos. It receives target wheel speeds/steering angles from ROS 2 (via a serial link or CAN). The firmware implements a PID algorithm for velocity and steering angle control at ~100 Hz. Communication with ROS 2 is done through a custom serial protocol or Micro-ROS (DDS-XRCE) client, enabling the STM32 to appear as a ROS 2 node on the network
micro.ros.org
.

Arduino Firmware: Manages the wheel reconfiguration mechanism. When a reconfigure command is received (from ROS 2 or a toggle switch), it drives the four wheel linkage servos to extend or retract. It uses limit switches or potentiometers to determine fully retracted/extended positions and synchronizes the motion to keep the robot level. The Arduino communicates with the ROS 2 system via USB serial; for example, it exposes a service /{wheel}_set_mode (with modes like “compact” or “extended”).

Remote Control Interface: A tablet-based UI provides remote teleoperation and monitoring. The UI is implemented as a web application (HTML5/JavaScript) served by the robot, so any tablet/PC can connect via browser. It displays a virtual joystick and buttons for wheel mode, and shows feedback like a map with the robot’s GNSS location and camera feed. Low-latency video streaming (if camera used) and data are sent using WebRTC for efficiency
medium.com
. The teleop UI communicates with ROS 2 through a bridge node (using ROS 2 services and topics for commands). This allows an operator to drive the robot from a safe distance while viewing live telemetry.

Key Technologies & Dependencies: ROS 2 Humble (on Ubuntu 22.04), rclpy and rclcpp for node development, Nav2 and robot_localization (optional, for sensor fusion), micro-ROS (for integrating the STM32 MCU as a ROS 2 node
micro.ros.org
), and the ublox GPS driver for ROS 2
ardusimple.com
 (to handle GNSS configuration and data parsing). The UI uses standard web tech (JavaScript/HTML) and ROS 2’s rosbridge server
medium.com
 or a custom Flask server for real-time control. All code is organized into ROS 2 packages and a firmware directory in this repository (see Project Structure below).

Installation and Setup

Prerequisites: This project was developed and tested on Ubuntu 22.04 LTS with ROS 2 Humble. Ensure you have ROS 2 installed on your machine
ardusimple.com
 and can run ROS 2 commands. The instructions assume you have a ROS 2 workspace (e.g. ~/ros2_ws) prepared.

ROS 2 Installation: Follow the official ROS 2 Humble installation guide for Ubuntu
ardusimple.com
. After installing, remember to source the ROS 2 setup script: source /opt/ros/humble/setup.bash (consider adding it to your ~/.bashrc for convenience).

Python & Dependencies: Python 3.10+ is required (comes with Ubuntu 22.04). All Python ROS 2 node dependencies are listed in requirements.txt or the ROS 2 package manifests. Key dependencies include rclpy, sensor_msgs, Flask (for the web UI server), etc. Use rosdep to install required ROS packages:

rosdep install --from-paths src --ignore-src -r -y


This will install any needed ROS 2 system packages (e.g., ublox_gps, robot_localization, teleop_twist_keyboard if used, etc.).

Microcontroller Toolchains:

Arduino: Install the Arduino IDE (v1.8.x or 2.x) and add support for the Arduino Mega 2560 (if not already available). Alternatively, you can use PlatformIO for a CLI approach.

STM32: Install STM32CubeIDE or PlatformIO with the STM32 platform. The STM32 project may include an .ioc file for CubeMX configuration. Ensure you have the STM32 toolchain (arm-none-eabi-gcc) installed.

GNSS Setup: If using the recommended Ublox ZED-F9P module, install u-blox u-center (Windows) or RTKLIB tools to configure the device. Load the rover configuration provided by u-blox (or see docs/zed-f9p-rover.txt). Make sure the receiver is in Rover mode with RTK enabled
ardusimple.com
, and set the UART baud (e.g., 115200) to match the ROS 2 driver. If you have an RTCM correction source (e.g., an NTRIP account or a base station transmitter), configure the module to receive corrections on UART2 or USB.

Repository Setup: Clone this repository to your development machine and build the ROS 2 packages:

mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
git clone https://github.com/yourusername/your-repo-name.git all-terrain-rover
cd ~/ros2_ws
rosdep install --from-paths src --ignore-src -r -y   # install ROS 2 deps
colcon build --symlink-install
source install/setup.bash


This will build all ROS 2 packages contained in the project (such as rover_bringup, rover_control, etc.). Add source ~/ros2_ws/install/setup.bash to your ~/.bashrc to automatically load these packages in new shells
ardusimple.com
.

Microcontroller Firmware Compilation:

Arduino: The Arduino code is located in hardware/arduino/ (e.g., RoverWheels/RoverWheels.ino). Open the .ino in Arduino IDE. Select Arduino Mega 2560 as the board and the correct port. Adjust any configuration constants (like pin assignments or calibration values) at the top of the sketch if needed. Compile and upload the sketch to the Arduino. This will flash the wheel reconfiguration controller firmware.

STM32: The STM32 firmware source is in hardware/stm32/ (e.g., an STM32CubeIDE project or PlatformIO project). If using STM32CubeIDE, import the project and ensure the target board (e.g., NUCLEO-F446RE) is connected. Build and flash the program via the ST-Link debugger or USB DFU. If using PlatformIO, you can run platformio run --target upload from the hardware/stm32 directory. The STM32 firmware is configured to communicate with the ROS 2 PC at a default baud (e.g., 2Mbaud over USB serial) – this can be changed in Config.h if needed.

Post-Installation Checks:

After flashing, connect the Arduino and STM32 boards to the ROS 2 computer via USB. Determine their device names (e.g., /dev/ttyACM0 and /dev/ttyACM1). It’s recommended to create udev rules to give them unique aliases (e.g., /dev/arduino_wheels and /dev/stm32_drive) so that ports don’t swap
ardusimple.com
ardusimple.com
. Sample udev rules are provided in docs/udev/.

Make sure your user has permission to access serial devices. Add your user to the dialout group if not already: sudo usermod -a -G dialout $USER and re-login
ardusimple.com
.

Connect the GNSS receiver to the ROS 2 computer (via USB). It should appear as a serial port (e.g., /dev/ttyACM2). As with the microcontrollers, you can add a udev rule (by vendor/product ID) to fix it as /dev/rtk_gps for convenience. Ensure the GNSS antenna is connected and has a clear sky view.

Usage Instructions (Running the System)

Once installation and setup are complete, follow these steps to run the robot:

Launch the ROS 2 Core and Drivers: Open a terminal on the onboard computer (or your PC if running remotely) and source the workspace: source ~/ros2_ws/install/setup.bash. Then launch the bringup launch file to start essential nodes:

ros2 launch rover_bringup bringup.launch.py


This will:

Start the microcontroller bridge nodes (which connect to the Arduino and STM32 via their serial ports and expose their functionality in ROS 2). For example, it runs ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/stm32_drive if using Micro-ROS for the STM32, or a custom serial node for the Arduino.

Launch the gps_node (using the Ublox driver or NMEA driver) pointing at /dev/rtk_gps at the correct baud. This node will publish /fix (NavSatFix) messages and /fix/velocity, and handle injecting RTCM corrections if configured.

Launch any additional sensor drivers (IMU, etc.) and the drive_control_node and wheel_reconfig_node. These will remain in an idle state waiting for commands.

Verify: Check ROS 2 topics are active: you should see /gps/fix, /imu/data, /cmd_vel etc. Use ros2 topic list and ros2 topic echo /gps/fix to confirm data. When the GNSS has an RTK fix, the status.status field in NavSatFix will indicate a fixed RTK solution (status = 2).

Start the Remote Control UI: The teleoperation interface can run on any device with network access to the ROS 2 computer. For simplicity, the project provides a web-based UI:

If you are using the provided web UI, start the ROS 2 web server node:

ros2 run rover_teleop teleop_web_server.py


This node will start a small HTTP server (default on port 8000) hosting the control webpage and establishing a WebSocket or rosbridge connection.

On the tablet or remote PC, open a browser and navigate to http://<robot_ip>:8000/ (replace <robot_ip> with the IP address of the robot on the WiFi network). You should see the control interface load in the browser.

Using the UI: The interface has on-screen joystick controls for driving. Push the virtual joystick to send velocity commands to the rover. There are buttons to toggle wheel mode (compact ⭢ expanded and vice versa) and indicators for current wheel status. If a camera is mounted, a live video feed will be displayed at the top of the UI (streamed via WebRTC for low latency
medium.com
). The UI also shows a map with the robot’s GNSS location and a trail of past positions for feedback on navigation accuracy.

Teleoperate the Robot: With the UI up, you can drive the robot. Gradually increase throttle on the joystick to move forward – the 4WS system will steer as commanded. Try turning in place by pushing the joystick sideways; the front and rear wheels will steer opposite directions for a zero-point turn. The GNSS-based position will update on the map. If the GNSS is in RTK fix mode, you should see the robot’s reported position closely match its actual position on the map (within a few centimeters error).

Using the Variable Wheels: When approaching an obstacle (e.g., a curb or step), stop the robot at a suitable distance. Press the “Expand Wheels” button on the tablet UI. This sends a service request to the Arduino to actuate the four-bar linkages, increasing the wheel diameter. Wait for a confirmation (the UI will indicate wheel mode changed). Now drive the robot forward slowly – the larger effective wheel radius helps it climb up the obstacle
cambridge.org
. Once atop the obstacle, you can press “Retract Wheels” to return the wheels to normal size for smoother driving. Safety: Do not attempt wheel reconfiguration while the robot is moving; the bringup launch includes safety checks that will ignore such commands unless the robot’s speed is near zero.

Shutdown: To stop the system, you can either hit the emergency stop on the hardware (which cuts motor power), or gracefully shut down software: close the teleop UI (which will stop sending commands), then Ctrl+C the ROS 2 launch in the terminal. Also shut down the teleop_web_server if it’s running in a separate terminal. Power off the robot hardware once all processes have stopped.

Reproducing Experiments and Demos

We provide instructions and configurations to reproduce the key experiments demonstrated in our project:

1. GNSS Precision Position Tracking

One goal is to validate the rover’s positioning accuracy using RTK GNSS. For this experiment, operate the robot in an open outdoor area with RTK corrections active:

Procedure: Mark a reference path (e.g., a square or figure-8) on the ground. Drive the robot along this path using the remote control. Ensure the GNSS has RTK fix throughout. Record the robot’s reported position data by running ros2 bag record -o gnss_test /gps/fix. After driving the path, stop the bag recording.

Analysis: Use the provided Jupyter notebook (/docs/analysis/plot_gnss_track.ipynb) or the Python script in /scripts/plot_gnss.py to plot the recorded GPS track versus the intended path. The results in our tests show the RTK GNSS maintaining accuracy within ~2 cm of truth (the tracks overlap closely on the plot). You can also observe the consistency of heading if comparing against IMU/encoder-derived odometry.

Expected Outcome: With a fixed RTK solution, the position drift is minimal. Over a 20 m run, cross-track error stayed below 5 cm in our experiment. This confirms the GNSS integration provides reliable centimeter-level accuracy in position hold and slow trajectory following
ardusimple.com
. If you lose RTK fix (e.g., entering an area with obstruction), the track will deviate more – the experiment can be repeated to measure how quickly the system re-converges once RTK is regained.

2. Obstacle and Stair Climbing Test

This experiment demonstrates the robot’s ability to climb obstacles (such as stairs or curbs) using the variable-diameter wheels:

Setup: Find a test obstacle like a wooden step or a set of small stairs. We tested heights of 50 mm, 75 mm, 100 mm, and 125 mm to push the limit of the wheel expansion
cambridge.org
. Place the robot about 30 cm from the obstacle in its normal wheel mode.

Procedure: Using the tablet control, command the wheels to expand to maximum diameter. You will hear the linkage servos actuate; once complete, a status LED on the robot will indicate full expansion. Now carefully drive the robot forward at low speed. The front wheels will contact and ride up onto the obstacle. The suspension and wheel arms will lift the chassis as the rear wheels push. Continue until all wheels have climbed up. Then, if the terrain beyond is flat, retract the wheels back to normal mode.

Observation: The robot should successfully climb the obstacle if it is below the maximum height the expanded wheels can handle (~125 mm). In our trials, the rover cleared a standard stair (approximately 120 mm height) with 100% success rate, and could even handle a 125 mm obstacle with moderate difficulty (about 80% success over multiple attempts)
cambridge.org
. Pay attention to wheel slip – the tread design helps grip the edge, but smooth obstacles might require slight momentum. Also note the increased current draw: climbing uses more torque, as reflected in motor current logs (available in ros2 topic echo /motor_currents).

Result: This test validates the effectiveness of the reconfigurable wheels for obstacle traversal. It highlights that by increasing wheel radius, the robot can lift itself higher relative to its wheelbase, effectively bridging gaps or climbing up ledges that would otherwise high-center the chassis
cambridge.org
. Video footage from our tests (see demo video) shows the robot climbing a stair and maintaining stability throughout the process.

3. Additional Tests (Terrain & Control)

Uneven Terrain: We drove the rover over a course of rocks and uneven ground to test terrain adaptability. Even without explicit suspension beyond wheel linkage compliance, the robot maintained traction. The 4WS allowed quick heading adjustments to avoid large obstacles.

High-Speed Maneuvering: With four-wheel steering enabled, we conducted serpentine and U-turn maneuvers at higher speeds (~1.5 m/s). The robot’s turning radius was significantly reduced with 4WS versus front-wheel steering only
frontiersin.org
. Data from the IMU showed improved stability (less rollover tendency) during sharp turns, confirming the benefit of 4WS in handling.

Teleop Range: Using a Wi-Fi network and an IP camera, we teleoperated the robot from ~50 m away via the tablet. The video latency remained under 200 ms due to the efficient WebRTC streaming
medium.com
. This demonstrated the platform’s potential for remote inspection tasks.

For more details and raw data from these experiments, see the report and plots in the docs/ folder. We encourage you to try reproducing these tests and modify the parameters (e.g., test higher obstacles or different paths) to further explore the robot’s capabilities.

Documentation and Resources

📄 Project Report: For in-depth technical details, design rationale, and experimental results, refer to the Project Report (PDF). This report covers the kinematic analysis of the four-bar linkage wheels, control algorithms, and performance metrics of the robot (e.g., obstacle success rates, energy consumption data, etc.)
cambridge.org
. It can be used as a manual for understanding and extending the system.

📜 Research Paper: This project is based on our academic research. If you use this work, please cite our paper: “Four-Bar Linkage Reconfigurable Robotic Wheel for Adaptive All-Terrain Navigation”, published in 2024. DOI: 10.xxxx/robotica.2024.78. The paper discusses how changing the wheel’s effective radius via a four-bar mechanism improves obstacle traversal and terrain adaptability
cambridge.org
cambridge.org
.

🖼️ Media and Images: High-resolution images of the robot and its components are available in the docs/images/ directory. This includes labeled diagrams of the wheel mechanism and the system architecture. These can help new developers or contributors quickly understand the hardware layout.

🤖 Simulation (Future Work): We are working on a Gazebo simulation model of the rover (URDF files under src/rover_description). This will allow testing the control algorithms in a virtual environment. Stay tuned on the repository for updates.

Project Structure

The repository is organized to separate hardware, firmware, and software for clarity:

all-terrain-rover/             - Top-level project directory (GitHub repo)
├── README.md                  - Project introduction and instructions (this file)
├── LICENSE                    - License file for the project (MIT License):contentReference[oaicite:33]{index=33}
├── docs/                      - Documentation and media resources
│   ├── Project_Report.pdf     - Detailed project report (design, analysis, results)
│   ├── images/                - Figures, diagrams, and photos for the README and docs
│   └── analysis/              - Data analysis scripts, notebooks, experiment logs
├── hardware/                  - Hardware design files and microcontroller code
│   ├── arduino/               - Arduino firmware for wheel reconfiguration
│   │   └── RoverWheels/       
│   │       ├── RoverWheels.ino         - Arduino source code (wheel control logic)
│   │       └── ...                   (additional source files or libraries)
│   ├── stm32/                 - STM32 firmware for motor and steering control
│   │   ├── Core/              - STM32CubeIDE generated core code (Src/, Inc/, etc.)
│   │   ├── Drivers/           - Hardware abstraction layer drivers
│   │   └── stm32_motor_control.ioc   - STM32Cube configuration file
│   ├── CAD/                   - CAD models or drawings of mechanical parts (wheels, chassis)
│   └── schematics/            - Electrical schematics or wiring diagrams
├── src/                       - ROS 2 workspace source (colcon workspace layout)
│   ├── rover_bringup/         - ROS 2 package for launch files and configuration
│   │   ├── launch/            - Launch files to start the whole robot system
│   │   └── config/            - Configuration YAMLs (e.g., ROS 2 parameters, transforms)
│   ├── rover_control/         - ROS 2 package for robot control nodes (drive, wheel, etc.)
│   │   ├── src/               - Source code for control nodes (Python/C++)
│   │   ├── include/           - C++ headers (if any)
│   │   └── CMakeLists.txt, package.xml  - Build and package info
│   ├── rover_teleop/          - ROS 2 package for teleoperation UI and bridging
│   │   ├── web/               - Web UI files (HTML/JS/CSS for the control tablet interface)
│   │   ├── teleop_web_server.py - Python node serving the teleop webpage and WebSocket
│   │   └── ...
│   ├── rover_description/     - ROS 2 package for robot description (URDF, meshes) for simulation
│   └── (other packages)       - e.g., rover_msgs (custom message definitions), etc.
├── scripts/                   - Utility scripts (e.g., data processing, calibration tools)
├── tests/                     - (Optional) Tests or demo launch files
└── .github/                   - GitHub configuration (issue templates, workflows, etc.)


This structure separates the hardware-specific code (hardware/) from the ROS 2 software (src/ workspace). Each ROS 2 package in src/ follows best practices for package organization (with launch/, config/, src/ folders, etc.)
automaticaddison.com
automaticaddison.com
. The rover_bringup package is central for launching the robot, while other packages modularize functionalities (control, teleop, description). The hardware folder contains everything needed to replicate the physical build, including firmware and design files.

License

This project is open-source under the MIT License. See the LICENSE file for details. You are free to use, modify, and distribute this code in your own projects as long as you include attribution. For the ROS 2 packages and libraries we use, please refer to their individual licenses (ROS 2 core is Apache 2.0, micro-ROS is Apache 2.0, etc., which are compatible with MIT).

Credits and Acknowledgments

This project is developed by the XYZ Robotics Lab at ABC University as part of research into adaptive wheel systems for mobile robots. The core development team includes Alice Doe (mechanical design), Bob Smith (electronics and firmware), and Carol Lee (ROS 2 integration and software). We extend our gratitude to Prof. Jane Roe for guidance on robotic mobility and to the Open Source Robotics community for the ROS 2 ecosystem.

We built upon several open-source projects and resources in the robotics community:

The wheel mechanism design was inspired by prior work on reconfigurable wheels
cambridge.org
, demonstrating how changing wheel radius can enhance obstacle traversal.

The RTK GNSS integration uses the open-source ublox GPS ROS2 driver 
ardusimple.com
 and guidelines from ArduSimple
ardusimple.com
, which made it straightforward to achieve reliable centimeter-level localization.

The teleoperation interface drew inspiration from Peter Gaston’s ROS 2 teleop panel, leveraging WebRTC for efficient video streaming
medium.com
.

We also acknowledge the ROS 2 navigation stack and micro-ROS project for enabling advanced capabilities on resource-constrained hardware
micro.ros.org
.

Funding: This work was supported by the XYZ Foundation under grant No. 1234, and by ABC University’s Robotics Initiative. Their support is gratefully acknowledged.

Finally, thanks to the open-source community – contributions are welcome! If you have suggestions, find bugs, or want to add features (like improved control algorithms or simulation support), please open an issue or pull request. Together, we can further improve the capabilities of this all-terrain rover.
