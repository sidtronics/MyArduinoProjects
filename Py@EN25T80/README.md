# Dump contents of flash memory EN25T80
This python program demonstrates the usage of my tool 4WireSerial. It is used to dump contents of flash memory in hex_dump.txt file
in plain text. Although this chip works on SPI protocol, 3-wire serial is compatible with SPI so it works out.

## Requirements:
1. EN25T80 (SPI flash memory)

## Dependencies:
1. 4WireSerial (my own creation)

## Setup:
1. Connect HOLD pin to pin 7.
2. Connect CLK pin to pin 8.
3. Connect DI pin to pin 9.
4. Configure the 4WireSerial firmware to use 3 Wire Serial.
5. Upload the Firmware to Arduino.
6. Execute using `python dump.py` 

## Output:
Contents of flash memory is stored on hex_dump.txt
