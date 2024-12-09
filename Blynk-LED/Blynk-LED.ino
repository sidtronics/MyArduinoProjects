#define BLYNK_TEMPLATE_ID "[REDACTED]"
#define BLYNK_TEMPLATE_NAME "[REDACTED]"
#define BLYNK_AUTH_TOKEN "[REDACTED]"
#define BLYNK_PRINT Serial
#define BLYNK_DEBUG

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "[REDACTED]";
char pass[] = "[REDACTED]";

BLYNK_WRITE(V0) {

    bool state = param.asInt();
    digitalWrite(LED_BUILTIN, !state); 
}

BLYNK_CONNECTED() {

    Blynk.syncVirtual(V0);
}

void setup() {

    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    Blynk.begin(auth, ssid, pass);
}

void loop() {

    Blynk.run();
}
