#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

#include <ArduinoJson.h>
#include "./devices.h"
#include "./device.h"

const double Device::unit_cost = 50;

const char* ssid = "[REDACTED]";          
const char* password = "[REDACTED]";  

ESP8266WebServer server(80); 

Device devices[] = {Device("bulb",D3,10), Device("fan",D2,65)};
Devices dev(devices, 2);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  if (!MDNS.begin("esp8266")) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");

  server.on("/data", HTTP_GET, handleData);
  server.on("/control", HTTP_GET, handleControl);

  server.enableCORS(true);
  server.begin();

}

void loop() {
  server.handleClient();
  MDNS.update();
  dev.update();
}

String buildJSON(Devices devices) {

  StaticJsonDocument<512> doc;

  doc["unit_cost"] = Device::unit_cost;
  doc["total_consumption"] = devices.total_consumption;
  doc["total_cost"] = devices.total_cost;

  JsonArray devicesArray = doc.createNestedArray("devices");

  for (int i = 0; i < devices.get_count(); i++) {
    JsonObject deviceObj = devicesArray.createNestedObject();
    deviceObj["name"] = devices[i].name;
    deviceObj["state"] = devices[i].state;
    deviceObj["power_rating"] = devices[i].power_rating;
    deviceObj["units_consumed"] = devices[i].units_consumed;
    deviceObj["used_time"] = devices[i].used_time;
    deviceObj["cost"] = devices[i].cost;
  }

  String output;
  serializeJson(doc, output);

  return output;
}

void handleData() {
  String jsonData = buildJSON(dev); 
  server.send(200, "application/json", jsonData);
}

void handleControl() {
  if (server.hasArg("state") && server.hasArg("name")) {
    String state = server.arg("state");
    String name = server.arg("name");

    dev.get(name).set(state == "ON");
    server.send(200, "text/plain", "Success");
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}
