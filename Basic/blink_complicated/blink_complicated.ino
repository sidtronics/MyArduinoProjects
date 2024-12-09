
// Challenged myself to write the most simple program in most complicated way possible.

namespace sid {

    const unsigned long delay = 1000*1;
}

void setup() {

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

    static unsigned long currentTime = millis(),
        lastTime = 0;

    static bool led_state = 0;

    if(currentTime - lastTime >= sid::delay) {

        led_state ^= 1;
        digitalWrite(LED_BUILTIN, led_state);
        lastTime = currentTime;
    }

    currentTime = millis();
}
