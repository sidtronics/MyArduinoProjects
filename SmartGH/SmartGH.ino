#include "secrets.h"
#include "thingProperties.h"

#include "src/DHTSensor.h"
#include "src/LDRSensor.h"
#include "src/SoilSensor.h"
#include "src/Pump.h"

#define MOISTURE_TRIGGER 10
#define MOISTURE_THRESHOLD 40

DHTSensor dht(27, temperature, humidity);
LDRSensor ldr(35, light);
SoilSensor soil(34, moisture);
Pump pmp(14, pump);

bool autoTriggered = false;
unsigned long previousTime = 0;

void setup() {

  Serial.begin(9600);
  delay(1500); 

  // analogSetPinAttenuation(35, ADC_ATTENDB_MAX);

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

    if(soil.get() <= MOISTURE_TRIGGER) {
        pmp.power(PUMP_ON);
        autoTriggered = true;
    }

    if(autoTriggered && soil.get() >= MOISTURE_THRESHOLD) {
        pmp.power(PUMP_OFF);
        autoTriggered = false;
    }

    previousTime = currentTime;
  }

  ArduinoCloud.update();
}

void onPumpChange()  {

    autoTriggered = false;
    pmp.power(pump);
}
