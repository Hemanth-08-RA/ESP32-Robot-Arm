# ESP32 6DOF WiFi Controlled Robotic Manipulator

🤖 An IoT-enabled 6DOF robotic manipulator built using ESP32 and servo motors.  
The robotic arm can be controlled wirelessly through a web interface using WiFi communication and supports real-time movement recording and playback.

---

# 🚀 Project Overview

This project demonstrates the implementation of a smart robotic manipulator integrated with IoT technology using an ESP32 microcontroller. The system creates its own WiFi access point and hosts a web-based control panel that allows users to remotely operate all six joints of the robotic arm.

The manipulator supports:

- 📡 Real-time wireless control
- 🎛️ Servo angle adjustment
- ⏺️ Motion recording
- ▶️ Playback automation
- 🌐 WebSocket communication
- ☁️ IoT integration

The project combines robotics, embedded systems, networking, and automation into a single intelligent robotic platform.

---

# 🧰 Components Required

| Component | Quantity |
|---|---|
| ESP32 Development Board | 1 |
| Servo Motors | 6 |
| External Power Supply | 1 |
| Jumper Wires | Multiple |
| Robotic Arm Chassis | 1 |
| Breadboard / PCB | 1 |

---

# 🔌 Servo Pin Connections

| Servo Joint | GPIO Pin |
|---|---|
| Base | GPIO 13 |
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

## IoT Communication Diagram

```markdown
![IoT Integration](images/iot_integration.png)
```

---

# 💻 Software Requirements

- Arduino IDE
- ESP32 Board Package
- Required Libraries:
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

Add this URL:

```text
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

Then install ESP32 boards from:

```text
Tools → Board → Board Manager
```

---

## Step 3: Install Required Libraries

Install the following libraries from Library Manager:

- ESPAsyncWebServer
- AsyncTCP
- ESP32Servo

---

## Step 4: Upload Code

1. Connect ESP32 using USB cable
2. Select correct COM port
3. Upload the code

---

# ▶️ Usage Instructions

1. Power ON the robotic manipulator
2. Connect to ESP32 WiFi network
3. Open browser and enter ESP32 IP address
4. Control joints using sliders
5. Enable Record Mode to store movements
6. Press Play to replay recorded motion

---

# 📊 Output

- Wireless robotic arm control
- Smooth servo operation
- Automated playback
- Real-time movement response
- IoT-enabled robotic system

---

# 👨‍💻 Author

Hemanth Balusu

B.Tech Student  
Vignan University  

🔹 Robotics  
🔹 IoT  
🔹 Embedded Systems  
🔹 AI

---

# 📜 License

This project is licensed under the MIT License.

---

# 🏷️ Badges for GitHub README

Add these at the top of your README:

```markdown
<img src="https://img.shields.io/badge/ESP32-Robot%20Arm-blue?style=for-the-badge"/>
<img src="https://img.shields.io/badge/IoT-WiFi%20Control-green?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Robotics-6DOF-orange?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Web-Control-red?style=for-the-badge"/>
<img src="https://img.shields.io/badge/ESP32-Embedded%20Systems-black?style=for-the-badge"/>
```

---
