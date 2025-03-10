# Traffic Scheduler
This sketch is proof of concept to calculate waiting time based on traffic on each lane. Each lane is allocated a portion of fixed
time duration. Allocated time is proportional to traffic on that respective lane. This technique can vastly reduce any unnecessary 
waiting time. To reduce complexity only green lights are simulated but it can be easily extended to include other signals. Number
of vehicles on each lane are sent using serial port. Syntax: 'RXLXUXDX', X represents number of vehicles on that lane \
Idea by [@abhishekabhang314](https://github.com/abhishekabhang314).

## Requirements:
1. 4 LEDs preferably green
2. 220 ohm resistor

## Setup:
1. Connect positive terminal of LEDs to Pin 7,8,9,10 respectively. (Lane order: RIGHT, LEFT, UP, DOWN)
2. Connect negative terminals through resistor to GND.
3. Compile and Upload.

## Output:
On sending lane information in proper syntax, green light turns on for amount of time proportional to 
traffic on that lane. Syntax for communication is given above.

### Rough Diagram:
Coming Soon
