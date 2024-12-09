const int potIn = A0;

void setup() {
    pinMode(potIn, INPUT);
    Serial.begin(9600);
}

void loop() {
    Serial.println(analogRead(potIn));
    delay(100);
}
