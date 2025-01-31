#pragma once
#include <Arduino.h>

#define PUMP_ON 1
#define PUMP_OFF 0

class Pump {
    public:
        Pump(uint8_t pin, bool& pump);
        void power(bool status);
        bool& get();

    private:
        const uint8_t _pin;
        bool& _pump;
};
