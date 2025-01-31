#pragma once
#include "Sensor.h"

class SoilSensor : public Sensor {

    public:
        SoilSensor(uint8_t sensorPin, float& moisture);
        void update() override;
        float get(uint8_t parameter = 0) override {return _moisture;}

    private:
        float _preprocess(float analogVal) override;

    private:
        float& _moisture;
};
