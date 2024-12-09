const int fan_control = 9;
const int tach = 2;

unsigned long start_time;
int count = 0;
int rpm;

void setup() {

    pinMode(fan_control, OUTPUT);
    analogWrite(fan_control, 0);
    Serial.begin(9600);
    Serial.println("Fan init...Waiting...");
    while(!Serial.available()) {}
    attachInterrupt(digitalPinToInterrupt(tach), counter, RISING);
}


void loop() {

    for(int pwm = 0; pwm <= 255; pwm += 51) {
        analogWrite(fan_control, pwm);
        delay (5000);
        start_time = millis();
        count = 0;
        while ((millis() - start_time) < 1000) {}
        rpm = count * 30; //60/2
        Serial.print ("PWM = ");
        Serial.print (map(pwm, 0, 255, 0, 100));
        Serial.print("% , Speed = ");
        Serial.print (rpm) ;
        Serial.println(" rpm");
    }
}

void counter() {
    count++;
}
