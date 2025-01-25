#include "SoilSensor.h"
#include <Arduino.h>

SoilSensor::SoilSensor(uint8_t sensorPin, float& moisture) : Sensor(sensorPin), _moisture(moisture) {

    pinMode(sensorPin, INPUT);
}

void SoilSensor::update() {

    _moisture = _preprocess(analogRead(_sensorPin));
}

float SoilSensor::_preprocess(float analogVal) {

    return map(analogVal, 0, 1023, 0, 100);
}
