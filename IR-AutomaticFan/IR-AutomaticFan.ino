// For DHT11
#include<DHT.h>

// Custom library for ET6202 library
#include<HM_Display.h>
#include"HM_ET6202_config.h"

// DHT11 init
DHT dht(8, DHT11);

// ET6202 init
HM_Display display(5,6,7, ET6202_config);

const int fan_control = 9;
const int ir = 4;

int state = 0;
float threshold = 33;
unsigned long lastTime = 0;
byte speed = 0;

void setSpeed(byte spd) {

    if(spd != 0) analogWrite(fan_control, 255);
    delay(100);
    analogWrite(fan_control, spd);
}

void setup() {

    dht.begin();

    display.mode(0);
    display.init(7);
    
    pinMode(fan_control, OUTPUT);
    analogWrite(fan_control, LOW);

    pinMode(ir, INPUT_PULLUP);

    Serial.begin(9600);
    Serial.println("Smart Fan Initialised....");
}

void loop() {


    if(digitalRead(ir) == 0) {

       state++;
       state = state % 5;

       //if(state > 0) analogWrite(fan_control, (state - 1) * 85);
       if(state > 0 ) {

            speed = (state-1) * 85;
            setSpeed(speed);
            display.clear();
            display.print(state-1);
        }

       else {
            
            speed = 0;
            setSpeed(speed);
            display.clear();
            display.print("AUTO");
            delay(1700);
        }

       delay(300);
    }

    if(millis() - lastTime > 2500) {
        
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();

        Serial.println("Temperature: " + String(temperature) + " °C" );
        Serial.println("Humidity: " + String(humidity) + "%");
        Serial.println("Mode: " + String(state == 0 ? "Auto (" + String(threshold) + " °C)" : "Manual"));
        Serial.println("Speed: " + String(map(speed, 0, 255, 0, 100)) + "%");
        Serial.println();

        if(state == 0) {

            if(isnan(humidity) || isnan(temperature)) {
                return;
            }

            display.clear();
            display.print((int)temperature);
            display.print(" C");
            
            //if(temperature >= threshold) analogWrite(fan_control, map(temperature, threshold, 50, 85, 255)); 
            if(temperature >= threshold) {
                speed = map(temperature, threshold, 50, 85, 255);  
                setSpeed(speed);
                Serial.println("Temperature above threshold detected!");
            }

            else {

                speed = 0;
                setSpeed(speed);
            }
        }

        lastTime = millis();
    }
}
