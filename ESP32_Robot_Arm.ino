/*
========================================================
        ESP32 6-DOF ROBOTIC MANIPULATOR
========================================================

Features:
- 6 DOF Robot Arm Control
- WiFi Web-Based Interface
- Real-Time Servo Control
- Record & Playback Motion
- ESP32 Access Point Mode
- WebSocket Communication

DOF (Degrees of Freedom):
1. Base Rotation
2. Shoulder
3. Elbow
4. Wrist Pitch
5. Wrist Roll
6. Gripper

Author : Hemanth Balusu
Platform : ESP32
========================================================
*/

#define CONFIG_BT_ENABLED 0
#define CONFIG_BLUEDROID_ENABLED 0

// =====================================================
// REQUIRED LIBRARIES
// =====================================================

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>
#include <vector>

// =====================================================
// WIFI CONFIGURATION
// =====================================================

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// =====================================================
// WEB SERVER
// =====================================================

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// =====================================================
// SERVO STRUCTURE
// =====================================================

struct ServoData {

  Servo servo;
  int pin;
  String name;
  int pos;
};

// =====================================================
// 6 DOF SERVO DEFINITIONS
// =====================================================

std::vector<ServoData> servos = {

  // Joint 1 : Base Rotation
  {Servo(), 13, "Base", 90},

  // Joint 2 : Shoulder
  {Servo(), 12, "Shoulder", 90},

  // Joint 3 : Elbow
  {Servo(), 14, "Elbow", 90},

  // Joint 4 : Wrist Pitch
  {Servo(), 27, "WristPitch", 90},

  // Joint 5 : Wrist Roll
  {Servo(), 26, "WristRoll", 90},

  // Joint 6 : Gripper
  {Servo(), 25, "Gripper", 90}
};

// =====================================================
// RECORDING STRUCTURE
// =====================================================

struct Step {

  int servoIndex;
  int value;
  int delayMs;
};

std::vector<Step> steps;

bool recordMode = false;
bool playMode = false;

unsigned long lastTime = 0;

// =====================================================
// HTML WEBPAGE
// =====================================================

const char html[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html>

<head>

<title>ESP32 6DOF Robot Arm</title>

<style>

body{
  font-family:Arial;
  text-align:center;
  background:#f0f0f0;
}

.slider{
  width:300px;
}

button{
  padding:10px;
  margin:5px;
  font-size:16px;
}

.container{
  background:white;
  width:450px;
  margin:auto;
  padding:20px;
  border-radius:10px;
}

</style>

</head>

<body>

<div class="container">

<h2>ESP32 6DOF Robot Manipulator</h2>

<script>

// WebSocket Connection
var ws = new WebSocket("ws://" + location.host + "/ws");

// Send data to ESP32
function send(name,val){

  ws.send(name + "," + val);
}

</script>

<!-- ================= JOINT 1 ================= -->

<h3>Base Rotation</h3>

<input class="slider"
type="range"
min="0"
max="180"
value="90"
oninput="send('Base',this.value)">

<!-- ================= JOINT 2 ================= -->

<h3>Shoulder</h3>

<input class="slider"
type="range"
min="0"
max="180"
value="90"
oninput="send('Shoulder',this.value)">

<!-- ================= JOINT 3 ================= -->

<h3>Elbow</h3>

<input class="slider"
type="range"
min="0"
max="180"
value="90"
oninput="send('Elbow',this.value)">

<!-- ================= JOINT 4 ================= -->

<h3>Wrist Pitch</h3>

<input class="slider"
type="range"
min="0"
max="180"
value="90"
oninput="send('WristPitch',this.value)">

<!-- ================= JOINT 5 ================= -->

<h3>Wrist Roll</h3>

<input class="slider"
type="range"
min="0"
max="180"
value="90"
oninput="send('WristRoll',this.value)">

<!-- ================= JOINT 6 ================= -->

<h3>Gripper</h3>

<input class="slider"
type="range"
min="0"
max="180"
value="90"
oninput="send('Gripper',this.value)">

<br><br>

<!-- ================= RECORD BUTTONS ================= -->

<button onclick="send('Record',1)">
Record ON
</button>

<button onclick="send('Record',0)">
Record OFF
</button>

<br><br>

<!-- ================= PLAYBACK BUTTON ================= -->

<button onclick="send('Play',1)">
Play Motion
</button>

</div>

</body>
</html>

)rawliteral";

// =====================================================
// MOVE SERVO FUNCTION
// =====================================================

void moveServo(int i, int value) {

  // Limit servo angle
  value = constrain(value, 0, 180);

  // Save steps during recording
  if (recordMode) {

    unsigned long now = millis();

    steps.push_back({

      i,
      value,
      (int)(now - lastTime)
    });

    lastTime = now;
  }

  // Move servo
  servos[i].servo.write(value);

  // Store current position
  servos[i].pos = value;
}

// =====================================================
// PLAY RECORDED STEPS
// =====================================================

void playSteps() {

  for (auto &s : steps) {

    if (!playMode)
      return;

    delay(s.delayMs);

    servos[s.servoIndex].servo.write(s.value);
  }

  playMode = false;
}

// =====================================================
// WEBSOCKET EVENT HANDLER
// =====================================================

void handleWebSocket(

  AsyncWebSocket *server,
  AsyncWebSocketClient *client,
  AwsEventType type,
  void *arg,
  uint8_t *data,
  size_t len
) {

  if (type == WS_EVT_DATA) {

    String msg = "";

    // Convert incoming data to string
    for (size_t i = 0; i < len; i++) {

      msg += (char)data[i];
    }

    // Split command
    int comma = msg.indexOf(',');

    String key = msg.substring(0, comma);

    int value = msg.substring(comma + 1).toInt();

    // ================= RECORD =================

    if (key == "Record") {

      recordMode = value;

      if (recordMode) {

        steps.clear();

        lastTime = millis();

        Serial.println("Recording Started");
      }
      else {

        Serial.println("Recording Stopped");
      }
    }

    // ================= PLAYBACK =================

    else if (key == "Play") {

      playMode = true;

      Serial.println("Playback Started");
    }

    // ================= SERVO CONTROL =================

    else {

      for (int i = 0; i < servos.size(); i++) {

        if (key == servos[i].name) {

          moveServo(i, value);

          Serial.print(servos[i].name);
          Serial.print(" : ");
          Serial.println(value);
        }
      }
    }
  }
}

// =====================================================
// SETUP FUNCTION
// =====================================================

void setup() {

  Serial.begin(115200);

  Serial.println("\nESP32 6DOF Robot Arm Starting...");

  // ================= ATTACH SERVOS =================

  for (auto &s : servos) {

    s.servo.setPeriodHertz(50);

    s.servo.attach(s.pin, 500, 2400);

    s.servo.write(s.pos);

    delay(300);
  }

  // ================= START WIFI ACCESS POINT =================

  WiFi.softAP(ssid, password);

  Serial.println("\nWiFi Access Point Started");

  Serial.print("IP Address : ");

  Serial.println(WiFi.softAPIP());

  // ================= WEBSOCKET =================

  ws.onEvent(handleWebSocket);

  server.addHandler(&ws);

  // ================= WEB PAGE =================

  server.on("/", HTTP_GET,

    [](AsyncWebServerRequest *request) {

      request->send_P(

        200,
        "text/html",
        html
      );
    }
  );

  // ================= START SERVER =================

  server.begin();

  Serial.println("Web Server Started");
}

// =====================================================
// LOOP FUNCTION
// =====================================================

void loop() {

  // Remove disconnected clients
  ws.cleanupClients();

  // Play recorded motion
  if (playMode) {

    playSteps();
  }
}
