#pragma once

class Device {

public:
  Device(String _name, int _pin, double _power_rating)
      : name(_name), pin(_pin), power_rating(_power_rating) {

    pinMode(pin, OUTPUT);
  }

  void update() {

    if (state) {
      used_time = millis() - start_time + prev_time;
      units_consumed = (used_time / 3600000.f) * (power_rating / 1000);
      cost = unit_cost * units_consumed;
    }
  }

  void set(bool _state) {

    state = _state;
    if (_state) {
      start_time = millis();
    }
    else {
        prev_time = used_time;
    }
    digitalWrite(pin, _state);
  }

  static const double unit_cost;

  bool state = 0;

  String name;
  const double power_rating;
  const int pin;

  double units_consumed = 0;
  unsigned long used_time = 0;
  double cost = 0;

private:
  unsigned long start_time = 0;
  unsigned long prev_time = 0;
};
