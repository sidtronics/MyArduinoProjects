#include <ESP8266WiFi.h>
#include <DHT.h>
#include "secrets.h"

const char* server = "api.thingspeak.com";

// Intialise DHT
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

void setup() {

  Serial.begin(115200);
  delay(10);
  dht.begin();

  // Connect to WiFi network
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
}

void loop() {

  // Read sensor values.
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int uptime = millis() / 1000;

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (client.connect(server, 80)) {
    String postStr = "api_key=" + String(api_key) + "&field1=" + String(temperature) + "&field2=" + String(humidity)
    + "&field3=" + String(uptime);
   
    // Send HTTP POST request to update sensor values.
    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(postStr.length()));
    client.println();
    client.println(postStr);

    Serial.println("Temperature: " + String(temperature));
    Serial.println("Humidity: " + String(humidity));
    Serial.println("Uptime: " + String(uptime));
    Serial.println("Data sent to ThingSpeak!");
  }
  
  client.stop();

  // Wait for 20 seconds before sending data again.
  delay(20000);
}
