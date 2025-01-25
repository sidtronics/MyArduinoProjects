#pragma once
#include "sensor.h"

class LDRSensor : public Sensor {

    public:
        LDRSensor(uint8_t sensorPin, float& light);
        void update() override;
        float get(uint8_t parameter = 0) override {return _light;}

    private:
        float _preprocess(float analogVal) override;

    private:
        float& _light;
};
