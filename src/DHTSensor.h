#pragma once
#include "sensor.h"
#include <DHT.h>

#define DHTTEMP 0
#define DHTHUMID 1

class DHTSensor : public Sensor {
public:
  DHTSensor(uint8_t sensorPin, float &temperature, float &humidity);
  void update() override;
  float get(uint8_t parameter) override;

private:
  float _preprocess(float analogVal) override;

private:
  DHT _dht;
  float &_temperature;
  float &_humidity;
};
