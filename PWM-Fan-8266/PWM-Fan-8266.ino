const int fan_control = D7;
const int fan_rpm = D6;

unsigned long start_time;
int count = 0;
int rpm;

void setup() {

    Serial.begin(9600);
    pinMode(fan_control, OUTPUT);
    analogWriteFreq(490);
    analogWrite(fan_control, 0);


    attachInterrupt(digitalPinToInterrupt(fan_rpm), counter, RISING);
    Serial.println("Waiting......");
    while(!Serial.available()) {} 
}

void loop() {


    for(int pwm = 51; pwm <= 255; pwm += 51) {

        Serial.print ("PWM = ");
        Serial.print (map(pwm, 0, 255, 0, 100));
        Serial.print ("%");

        analogWrite(fan_control, pwm);
        delay (5000); //stablize speed.

        start_time = millis();
        count = 0;
        while ((millis() - start_time) < 1000) {}
        rpm = count * 30; //60/2


        Serial.print(" , Speed = ");
        Serial.print (rpm) ;
        Serial.println(" rpm");
    }

}

ICACHE_RAM_ATTR void counter() {
    count++;
}
