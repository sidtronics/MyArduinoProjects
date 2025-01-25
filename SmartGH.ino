#include "secrets.h"
#include "thingProperties.h"

#include "DHTSensor.h"
#include "LDRSensor.h"
#include "SoilSensor.h"

DHTSensor dht(13, cloud::temperature, cloud::humidity);
LDRSensor ldr(14, cloud::light);
SoilSensor soil(15, cloud::moisture);

unsigned long previousTime = 0;

void setup() {

  Serial.begin(9600);
  delay(1500); 

  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {

  unsigned long currentTime = millis();
  if(currentTime - previousTime >= 2000) {

    dht.update();
    ldr.update();
    soil.update();
    previousTime = currentTime;
  }

  ArduinoCloud.update();
}

void cloud::onPumpChange()  {
}

