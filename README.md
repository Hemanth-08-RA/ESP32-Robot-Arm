# ESP32 6DOF WiFi Controlled Robotic Manipulator

<img src="https://img.shields.io/badge/ESP32-Robot%20Arm-blue?style=for-the-badge"/>
<img src="https://img.shields.io/badge/IoT-WiFi%20Control-green?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Robotics-6DOF-orange?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Web-Control-red?style=for-the-badge"/>
<img src="https://img.shields.io/badge/ESP32-Embedded%20Systems-black?style=for-the-badge"/>

---

# 🤖 ESP32 6DOF WiFi Controlled Robotic Manipulator

An IoT-enabled 6DOF robotic manipulator built using ESP32 and servo motors.  
The robotic arm can be controlled wirelessly through a web interface using WiFi communication and supports real-time robotic movement.

---

# 🚀 Project Overview

This project demonstrates the implementation of a smart robotic manipulator integrated with IoT technology using an ESP32 microcontroller. The system creates its own WiFi access point and hosts a web-based control panel that allows users to remotely operate all six joints of the robotic arm.

The project combines:

- 🤖 Robotics
- 🌐 IoT
- 📡 Wireless Communication
- ⚙️ Embedded Systems
- 🎛️ Servo Automation

---

# ✨ Features

✅ WiFi Based Robotic Arm Control  
✅ Real-Time Servo Movement  
✅ Web-Based Interface  
✅ 6DOF Manipulator Control  
✅ ESP32 Wireless Communication  
✅ Smooth Joint Rotation  
✅ Embedded Robotics System  
✅ IoT Enabled Control System  

---

# 🧰 Components Used

| Component | Quantity |
|---|---|
| ESP32 Development Board | 1 |
| Servo Motors (SG90 / MG996R) | 6 |
| Robotic Arm Chassis | 1 |
| External Power Supply (5V/6V) | 1 |
| Breadboard / PCB | 1 |
| Jumper Wires | Multiple |
| USB Cable | 1 |
| WiFi Web Interface | 1 |

---

# 🔌 Servo Connections

| Servo Joint | GPIO Pin |
|---|---|
| Base Rotation | GPIO 13 |
| Shoulder | GPIO 12 |
| Elbow | GPIO 14 |
| Wrist Pitch | GPIO 27 |
| Wrist Roll | GPIO 26 |
| Gripper | GPIO 25 |

---

# 🖼️ Project Images

## Robot Manipulator

```markdown
![Robot Arm](images/robot_arm.jpg)
```

## Hardware Setup

```markdown
![Hardware Setup](images/setup.jpg)
```

## Web Control Interface

```markdown
![Web Interface](images/web_control.jpg)
```

---

# 💻 Software Requirements

- Arduino IDE
- ESP32 Board Package

## Required Libraries

- WiFi.h
- AsyncTCP.h
- ESPAsyncWebServer.h
- ESP32Servo.h

---

# ⚙️ Installation and Setup

## Step 1: Install Arduino IDE

Download Arduino IDE:

https://www.arduino.cc/en/software

---

## Step 2: Install ESP32 Board Package

Open:

```text
File → Preferences
```

Add the following URL:

```text
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

Then install ESP32 boards from:

```text
Tools → Board → Board Manager
```

---

## Step 3: Install Required Libraries

Install these libraries from Arduino Library Manager:

- ESPAsyncWebServer
- AsyncTCP
- ESP32Servo

---

## Step 4: Upload the Code

1. Connect ESP32 using USB cable
2. Select ESP32 board
3. Select correct COM Port
4. Upload the code

---

# 🌐 How to Use

1. Power ON the robotic arm
2. Connect mobile/laptop to ESP32 WiFi
3. Open browser
4. Enter ESP32 IP Address
5. Control robotic arm using sliders

---

# 📊 Output

- Wireless robotic arm control
- Real-time joint movement
- Smooth servo operation
- WiFi-enabled automation
- IoT robotic manipulation

---

# 👨‍💻 Author

## Hemanth Balusu

B.Tech Student  
Vignan University

### Domains

- 🤖 Robotics
- 🌐 IoT
- ⚙️ Embedded Systems
- 🧠 AI

---

# 📜 License

This project is licensed under the MIT License.

---

