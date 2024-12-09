const int blue = 11;
const int red = 12;

void setup() {
    pinMode(blue, OUTPUT);
    pinMode(red, OUTPUT);
}

bool blue_state = 0, red_state =0;

void loop() {
    digitalWrite(blue, blue_state^1);
    delay(1000);
    digitalWrite(red, red_state^1);
    delay(1000);
}
