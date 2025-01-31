#pragma once
#include <Arduino.h>

class Sensor {
public:
  Sensor(uint8_t sensorPin) : _sensorPin(sensorPin) {}
  virtual void update() = 0;
  virtual float get(uint8_t parameter) = 0;

protected:
  virtual float _preprocess(float analogVal) = 0;

protected:
  const uint8_t _sensorPin;
};
