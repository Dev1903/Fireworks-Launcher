#include <WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

#define RELAY_PIN 5
#define BUZZER_PIN 22
#define COUNTDOWN 3

// Wi-Fi
const char* ssid = "bristidev-4G";
const char* password = "Br@190304";

// Sinric Pro
#define APP_KEY       "f518d5fe-0868-401f-b65a-7d5248159d71"       // Sinric Pro API Key
#define APP_SECRET    "f1192782-faf8-45c5-8f2e-b3a5a5cab16d-f1037a21-814d-4cba-a692-aedea6b83929"    // Sinric Pro API Secret
#define DEVICE_ID     "68f7787aba649e246c1018d8"     // Your device ID

bool onPowerState(const String &deviceId, bool &state) {
  if (state) {
    // Countdown beep
    for(int i=COUNTDOWN; i>0; i--){
      digitalWrite(BUZZER_PIN, HIGH);
      delay(200);
      digitalWrite(BUZZER_PIN, LOW);
      delay(800);
    }
    // Relay ON
    digitalWrite(BUZZER_PIN, HIGH);
    delay(300);
    digitalWrite(RELAY_PIN, HIGH);
    delay(3000);
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
  return true;
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");

  SinricProSwitch &mySwitch = SinricPro[DEVICE_ID];
  mySwitch.onPowerState(onPowerState);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {
  SinricPro.handle();
}
