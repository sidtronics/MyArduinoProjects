#define BLYNK_TEMPLATE_ID "[REDACTED]"
#define BLYNK_TEMPLATE_NAME "[REDACTED]"
#define BLYNK_AUTH_TOKEN "[REDACTED]"
//#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 
const int fan_control = D7;
const int fan_rpm = D6;
const int temp_in = A0;

const float c1 = 1.009249522e-03,
c2 = 2.378405444e-04,
c3 = 2.019202697e-07;

int count = 0;
float temp = 0;
int threshold = 37;
int manual_speed = 0;
bool control = 1;

BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "[REDACTED]";
char pass[] = "[REDACTED]";
 
float get_temp() {

    float logR2, R2, T;

    int Vo = analogRead(temp_in);
    R2 = 10000 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
    T = T - 273.15 - 5;
    return T;
}

void update() {

    temp = get_temp();
    Blynk.virtualWrite(V4, temp);

    if(control) {

        if (temp >= threshold) {

            int fanSpeed = map(temp, threshold, 55, 48, 255);
            analogWrite(fan_control, fanSpeed);

        } else {

            analogWrite(fan_control, 0);
        }

    } else {

        int fanSpeed = map(manual_speed, 0, 100, 38, 255);
        analogWrite(fan_control, fanSpeed);
    }

    Blynk.virtualWrite(V3, count*30);
    count = 0;
}


ICACHE_RAM_ATTR void counter() {
 
    count++;
}

//Auto-Manual switch
BLYNK_WRITE(V0) { 

    control = param.asInt();
}

//Threshold slider
BLYNK_WRITE(V1) {

    threshold = param.asInt();
}

//Speed slider
BLYNK_WRITE(V2) {

    manual_speed = param.asInt();
}

BLYNK_CONNECTED() {

    Blynk.syncAll();
}

void setup() {

    Serial.begin(9600);
    pinMode(fan_control, OUTPUT);
    pinMode(temp_in, INPUT);
    pinMode(fan_rpm, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(fan_rpm), counter, RISING);

    analogWriteFreq(490);
    analogWrite(fan_control, 0);

    timer.setInterval(1000L, update);

    Blynk.begin(auth, ssid, pass);
}
 
 
void loop() {

    Blynk.run();
    timer.run();
}
