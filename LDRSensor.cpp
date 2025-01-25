#include "LDRSensor.h"
#include <Arduino.h>

LDRSensor::LDRSensor(uint8_t sensorPin, float& light) : Sensor(sensorPin), _light(light) {

    pinMode(sensorPin, INPUT);
}

void LDRSensor::update() {

    _light =  _preprocess(analogRead(_sensorPin));
}

float LDRSensor::_preprocess(float analogVal) {

    return map(analogVal, 0, 1023, 0, 100);
}
