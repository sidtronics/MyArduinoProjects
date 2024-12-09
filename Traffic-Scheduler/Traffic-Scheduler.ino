
/***LED PINS***/
const int led_r = 7;
const int led_l = 8;
const int led_u = 9;
const int led_d = 10;
/*************/

int right = 0;
int left = 0;
int up = 0;
int down = 0;
bool complete = false;

void setup() {
    
    Serial.begin(9600);
    pinMode(led_r, OUTPUT);
    pinMode(led_l, OUTPUT);
    pinMode(led_u, OUTPUT);
    pinMode(led_d, OUTPUT);
}

void loop() {

    if(Serial.available()) {

        char cmd = Serial.read();
        switch(cmd) {

            case 'R':
                right = Serial.parseInt();
                break;
            case 'L':
                left = Serial.parseInt();
                break;
            case 'U':
                up = Serial.parseInt();
                break;
            case 'D':
                down = Serial.parseInt();
                complete = true;
                break;
        }
    }

    if(complete) {

        double sum = right + left + up + down;
        int time = 30;

        double r_delay = time * right/sum;
        double l_delay = time * left/sum;
        double u_delay = time * up/sum;
        double d_delay = time * down/sum;

        digitalWrite(led_r, HIGH);
        Serial.println("R: " + String(r_delay));
        delay(1000 * r_delay);
        digitalWrite(led_r, LOW);

        digitalWrite(led_l, HIGH);
        Serial.println("L: " + String(l_delay));
        delay(1000 * l_delay);
        digitalWrite(led_l, LOW);

        digitalWrite(led_u, HIGH);
        Serial.println("U: " + String(u_delay));
        delay(1000 * u_delay);
        digitalWrite(led_u, LOW);

        digitalWrite(led_d, HIGH);
        Serial.println("D: " + String(d_delay));
        delay(1000 * d_delay);
        digitalWrite(led_d, LOW);

        complete = false;
        Serial.println("cycle complete");
        Serial.println("-------------------");
    }
}
