#include "Pump.h"

Pump::Pump(uint8_t pin, bool &pump) : _pin(pin), _pump(pump) {

    pinMode(pin, OUTPUT);
    _pump = PUMP_OFF;
}

void Pump::power(bool status) {

    digitalWrite(_pin, !status);
    _pump = status;
}

bool& Pump::get() {
    return _pump;
}
