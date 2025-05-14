#include <WiFi.h>
#include <HTTPClient.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <ESP32Servo.h>

// WiFi credentials
const char* ssid = "enter your wifi name";
const char* password = "enter your wifi password";

// Telegram Bot Token and Chat ID
const char* botToken = "enter your telegram bot token";
const char* chatID = "enter your chat id";

// MQ135 analog pin
const int gasSensorPin = 34;

// Alcohol detection threshold
const int gasThreshold = 1200;

// GPS setup
TinyGPSPlus gps;
HardwareSerial GPSserial(1);  // RX=16, TX=17

// Variables to store location
double latitude = 0.0;
double longitude = 0.0;


// Servo setup
Servo myServo;
const int servoPin = 14;

// Telegram message handling
String lastReceivedMessage = "";
long lastUpdateId = 0;

void setup() {
  Serial.begin(115200);

  // WiFi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  // Start GPS serial
  GPSserial.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("GPS Module Initialized.");

  // Attach servo
  myServo.attach(servoPin);
  myServo.write(90);  // Start at 0°
}

int lock = 0;
int unlock = 0;

void loop() {
  if(lock ==1 && unlock ==1){
    Serial.println("          ✅ Ignition will Remain Unlocked for 2 hours");
    //sendTelegramMessage("          ✅ Ignition Unlocked");
    delay(1*1*60*1000);
    lock =0;
    unlock = 0;
  }
  
  int gasValue = analogRead(gasSensorPin);
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  while (GPSserial.available() > 0) {
    gps.encode(GPSserial.read());
  }

  if (gasValue > gasThreshold) {
    
    Serial.println("🚨 Alcohol Detected!");

    if (gps.location.isValid()) {
      latitude = gps.location.lat();
      longitude = gps.location.lng();
      Serial.print("Latitude: "); Serial.println(latitude, 6);
      Serial.print("Longitude: "); Serial.println(longitude, 6);
    } else {
      Serial.println("Waiting for GPS fix...");
    }

    // Rotate servo to 180° (lock ignition)
    if(lock == 0){
    myServo.write(180);
    Serial.println("          🔒 Ignition Locked ");
    sendTelegramMessage("          🔒 Ignition Locked ");
    delay(300);
    myServo.write(90);
    lock = 1;
    //Serial.println("locked once");
    }

    // Compose alert message
    String message = "🚨 Alcohol Detected!\n";
    message += "📍 Location: https://www.google.com/maps/search/?api=1&query=";

    if (gps.location.isValid()) {
      message += String(latitude, 6) + "," + String(longitude, 6);
    } else {
      message += String(26.516427, 6) + "," + String(80.231706, 6);
    }

    sendTelegramMessage(message);
    delay(5000);
  }

  // Check for Telegram commands
  getTelegramUpdates();

  // If 'reverse' command received
  Serial.print("lastReceiveMessage : ");
  Serial.println(lastReceivedMessage);
  Serial.print("Unlock : ");
  Serial.println(unlock);
  
  if (lastReceivedMessage == "On" && unlock ==0) {
    Serial.println("          🔄 Command Received: Unlocking the ignition...");

    myServo.attach(servoPin);
    myServo.write(0);
    delay(500);
    myServo.write(90);
   // Serial.println("✅ Servo rotated .");
    unlock = 1;

    sendTelegramMessage("          ✅ Ignition Unlocked");
    lastReceivedMessage = "";
    //Serial.println("unlocked once");
  }

  delay(1000);
  
}

void sendTelegramMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Encode message for URL
    message.replace(" ", "%20");
    message.replace("\n", "%0A");

    String url = "https://api.telegram.org/bot" + String(botToken)
                 + "/sendMessage?chat_id=" + String(chatID)
                 + "&text=" + message;

    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.println("✅ Telegram message sent!");
    } else {
      Serial.print("❌ Error sending message. HTTP code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected.");
  }
}

void getTelegramUpdates() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = "https://api.telegram.org/bot" + String(botToken)
                 + "/getUpdates?offset=" + String(lastUpdateId + 1);

    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();

      int updateIdIndex = payload.indexOf("\"update_id\":");
      if (updateIdIndex != -1) {
        int startId = updateIdIndex + 12;
        int endId = payload.indexOf(",", startId);
        long updateId = payload.substring(startId, endId).toInt();
        lastUpdateId = updateId;

        int messageIndex = payload.indexOf("\"text\":\"");
        if (messageIndex != -1) {
          int start = messageIndex + 8;
          int end = payload.indexOf("\"", start);
          String message = payload.substring(start, end);

          Serial.println("Last received message: " + message);

          if (message == "On") {
            lastReceivedMessage = "On";
          }
        }
      }
    } else {
      Serial.print("❌ Error fetching updates. HTTP code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected.");
  }
}
