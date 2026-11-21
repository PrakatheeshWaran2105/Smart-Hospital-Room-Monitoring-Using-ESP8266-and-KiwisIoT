
#include <ESP8266WiFi.h>
#include <DHT.h>

// WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Sensor Pins
#define DHTPIN D4
#define DHTTYPE DHT11

#define MQ135_PIN A0
#define PIR_PIN D5

DHT dht(DHTPIN, DHTTYPE);

// WiFi Client
WiFiClient client;

// KiwisIoT Configuration
// Replace these with your actual KiwisIoT details
const char* server = "www.kiwisiot.in";
const char* deviceToken = "YOUR_DEVICE_TOKEN";

void setup() {
  Serial.begin(115200);

  dht.begin();
  pinMode(PIR_PIN, INPUT);

  Serial.println();
  Serial.println("Smart Hospital Room Monitoring");

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.println(WiFi.localIP());
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int airQuality = analogRead(MQ135_PIN);
  int motion = digitalRead(PIR_PIN);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT11 sensor reading failed!");
    delay(2000);
    return;
  }

  Serial.println("\n--- Hospital Room Monitoring ---");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("MQ135 Raw Value: ");
  Serial.println(airQuality);

  Serial.print("Room Movement: ");
  Serial.println(motion ? "Detected" : "Not Detected");

  // Send data to KiwisIoT
  // Add your platform's actual API publishing method here.

  delay(5000);
}
