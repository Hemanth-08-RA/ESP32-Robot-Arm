/*
========================================================
        ESP32 WiFi Controlled Robot Arm
========================================================

Features:
- Web-based robot arm control
- Real-time servo movement
- Record and playback functionality
- ESP32 Access Point mode
- WebSocket communication

Author : Hemanth Balusu
Platform : ESP32
========================================================
*/

// ================= DISABLE BLUETOOTH =================
// Reduces memory usage since Bluetooth is not needed

#define CONFIG_BT_ENABLED 0
#define CONFIG_BLUEDROID_ENABLED 0

// ================= REQUIRED LIBRARIES =================

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>
#include <vector>

// ================= WIFI CONFIGURATION =================
// Replace with your own WiFi credentials if needed

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ================= SERVER CONFIGURATION =================

// Create web server on port 80
AsyncWebServer server(80);

// Create WebSocket endpoint
AsyncWebSocket ws("/ws");

// ================= SERVO DATA STRUCTURE =================
// Stores servo object and details

struct ServoData {
  Servo servo;      // Servo object
  int pin;          // GPIO pin
  String name;      // Servo name
  int pos;          // Initial position
};

// ================= SERVO DEFINITIONS =================
// Add all robot arm servos here

std::vector<ServoData> servos = {

  // Base rotation servo
  {Servo(), 27, "Base", 90},

  // Shoulder movement servo
  {Servo(), 26, "Shoulder", 90},

  // Elbow movement servo
  {Servo(), 25, "Elbow", 90},

  // Gripper servo
  {Servo(), 33, "Gripper", 90}
};

// ================= RECORDING STRUCTURE =================
// Stores movement data for playback

struct Step {
  int servoIndex;   // Which servo moved
  int value;        // Servo angle
  int delayMs;      // Delay between steps
};

// Vector to store recorded steps
std::vector<Step> steps;

// Flags
bool recordMode = false;
bool playMode = false;

// Timing variable
unsigned long lastTime = 0;

// ================= HTML WEBPAGE =================
// Web interface served by ESP32

const char html[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html>

<head>
  <title>ESP32 Robot Arm</title>
</head>

<body style="text-align:center; font-family:Arial;">

<h2>ESP32 Robot Arm Controller</h2>

<script>

// Create WebSocket connection
var ws = new WebSocket("ws://" + location.host + "/ws");

// Function to send data to ESP32
function send(name, val) {
  ws.send(name + "," + val);
}

</script>

<!-- Base Servo -->
Base
<input type="range"
       min="0"
       max="180"
       value="90"
       oninput="send('Base', this.value)">
<br><br>

<!-- Shoulder Servo -->
Shoulder
<input type="range"
       min="0"
       max="180"
       value="90"
       oninput="send('Shoulder', this.value)">
<br><br>

<!-- Elbow Servo -->
Elbow
<input type="range"
       min="0"
       max="180"
       value="90"
       oninput="send('Elbow', this.value)">
<br><br>

<!-- Gripper Servo -->
Gripper
<input type="range"
       min="0"
       max="180"
       value="90"
       oninput="send('Gripper', this.value)">
<br><br>

<!-- Recording Controls -->
<button onclick="send('Record', 1)">
  Record ON
</button>

<button onclick="send('Record', 0)">
  Record OFF
</button>

<br><br>

<!-- Playback Button -->
<button onclick="send('Play', 1)">
  Play Recorded Motion
</button>

</body>
</html>

)rawliteral";

// ========================================================
// FUNCTION: moveServo()
// Moves servo and records movement if recording enabled
// ========================================================

void moveServo(int i, int value) {

  // If recording mode is active
  if (recordMode) {

    unsigned long now = millis();

    // Save step information
    steps.push_back({
      i,                          // Servo index
      value,                      // Servo angle
      (int)(now - lastTime)       // Delay from previous step
    });

    // Update timing
    lastTime = now;
  }

  // Move servo
  servos[i].servo.write(value);
}

// ========================================================
// FUNCTION: playSteps()
// Plays all recorded movements
// ========================================================

void playSteps() {

  // Loop through recorded steps
  for (auto &s : steps) {

    // Stop playback if disabled
    if (!playMode)
      return;

    // Wait required delay
    delay(s.delayMs);

    // Move corresponding servo
    servos[s.servoIndex].servo.write(s.value);
  }

  // Disable playback after completion
  playMode = false;
}

// ========================================================
// FUNCTION: handleWebSocket()
// Handles incoming WebSocket messages
// ========================================================

void handleWebSocket(
  AsyncWebSocket *server,
  AsyncWebSocketClient *client,
  AwsEventType type,
  void *arg,
  uint8_t *data,
  size_t len
) {

  // If message data received
  if (type == WS_EVT_DATA) {

    String msg = "";

    // Convert byte data to string
    for (size_t i = 0; i < len; i++) {
      msg += (char)data[i];
    }

    // Split message
    int comma = msg.indexOf(',');

    String key = msg.substring(0, comma);
    int value = msg.substring(comma + 1).toInt();

    // ================= RECORD MODE =================

    if (key == "Record") {

      recordMode = value;

      // Clear old steps when recording starts
      if (recordMode) {

        steps.clear();

        // Reset timer
        lastTime = millis();
      }
    }

    // ================= PLAYBACK MODE =================

    else if (key == "Play") {

      playMode = true;
    }

    // ================= SERVO CONTROL =================

    else {

      // Find matching servo
      for (int i = 0; i < servos.size(); i++) {

        if (key == servos[i].name) {

          moveServo(i, value);
        }
      }
    }
  }
}

// ========================================================
// SETUP FUNCTION
// ========================================================

void setup() {

  // Start Serial Monitor
  Serial.begin(115200);

  Serial.println("\nESP32 Robot Arm Starting...");

  // ================= ATTACH SERVOS =================

  for (auto &s : servos) {

    // Attach servo to pin
    s.servo.attach(s.pin);

    // Move to initial position
    s.servo.write(s.pos);
  }

  // ================= START WIFI ACCESS POINT =================

  WiFi.softAP(ssid, password);

  Serial.println("WiFi Access Point Started");

  // Print IP Address
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // ================= WEBSOCKET SETUP =================

  ws.onEvent(handleWebSocket);

  server.addHandler(&ws);

  // ================= WEBPAGE ROUTE =================

  server.on("/", HTTP_GET,
    [](AsyncWebServerRequest *req) {

      req->send_P(
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

// ========================================================
// LOOP FUNCTION
// ========================================================

void loop() {

  // Remove disconnected WebSocket clients
  ws.cleanupClients();

  // Play recorded motion
  if (playMode) {

    playSteps();
  }
}
