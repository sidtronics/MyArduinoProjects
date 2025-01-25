#include "DHTSensor.h"
#include <Arduino.h>

DHTSensor::DHTSensor(uint8_t sensorPin, float &temperature, float &humidity)
    : Sensor(sensorPin), _dht(sensorPin, DHT11), _temperature(temperature),
      _humidity(humidity) {

  _dht.begin();
}

float DHTSensor::_preprocess(float analogVal) {}

void DHTSensor::update() {

  _temperature = _dht.readTemperature();
  _humidity = _dht.readHumidity();
}

float DHTSensor::get(uint8_t parameter) {

    if(parameter == DHTTEMP) return _temperature;
    else return _humidity;
}
