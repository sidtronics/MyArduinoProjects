# Control Fan RPM using PWM signals
This is sketch is slightly modified version of PWM-Fan to support ESP8266.
This sketch is used to demonstrate PWM functionality to control Fan speed. 

## Requirements:
1. 4-Wire Computer Fan
2. 12V Power source

## Setup:
1. Connect PWM Pin of Fan to Pin D7.
2. Connect Tach Pin to Pin D6. 
3. Connect Fan to 12V power supply.
4. Connect GND of ESP8266 to GND of power supply.
5. Compile and Upload.

## Output:
Serial monitor prints current PWM % and RPM. PWM is increased every 5s. Loops after reaching 100%.

### Rough Diagram:
Coming Soon
