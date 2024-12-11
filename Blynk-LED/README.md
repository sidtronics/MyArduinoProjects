# Control LED from anywhere using Blynk
This sketch demonstrates usage of Blynk platform. We can control built-in LED of ESP8266 from anywhere in the world through
Blynk platform.

## Requirements:
1. ESP8266

## Dependencies:
+ Arduino Libraries:
    + Blynk
    + BlynkNcpDriver

## Setup:
0. Install Blynk library and ESP8266 core in arduino IDE/CLI.
1. Create a Blynk Template consisting of single Switch.
2. Set HARDWARE to ESP8266 and CONNECTION TYPE to WiFi. Configure other related settings.
3. Select V0 in Datastream in Switch settings.
4. Create a Device from your created Template.
5. Now in Developer tools of your device copy the BLYNK_TEMPLATE_ID, BLYNK_TEMPLATE_NAME and BLYNK_AUTH_TOKEN.
6. Paste it in Blynk-LED.ino accordingly.
7. Setup your SSID and Password as well.
8. Compile and Upload

## Output:
LED can be toggled from a switch on Blynk.cloud from anywhere in the world.
