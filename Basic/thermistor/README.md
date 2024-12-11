# Thermistor Interfacing
This sketch is used to measure ambient temperature using a thermistor. To calculate temperature we first calculate resistance of
thermistor by creating a voltage divider using a known resistor. Once we know the resistance of thermistor we can plug it into
Steinhart-Hart equation. This will yield us temperature in Kelvin. We can convert it into Celsius by subtracting 273.15. 

## Requirements:
1. Thermistor (any value)
2. Resistor (same value as Thermistor)

## Setup:
1. Connect Thermistor and Resistor serially.
2. Connect Thermistor end to 5V.
3. Connect Resistor end to GND.
4. Connect Thermistor-Resistor junction to A0.
5. Update value of known resistor in thermistor.ino (R1)
6. Compile and Upload.

## Output:
Serial monitor outputs ambient temperature in Celsius on every 500ms.

### Rough Diagram:
Coming Soon
