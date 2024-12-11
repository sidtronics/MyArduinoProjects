int ThermistorPin = A0;
double R1 = 10000;
double c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

// More information on coefficients and formula here: https://en.wikipedia.org/wiki/Thermistor

void setup() {
Serial.begin(9600);
}

void loop() {

  double Vo = analogRead(ThermistorPin); 
  double R2 = R1 * (1023.0/Vo - 1.0);  //Resistance of Thermistor
  double logR2 = log(R2);
  double T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); //Steinhart-Hart equation
  T = T - 273.15; //Kelvin to Celcius conversion

  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" C"); 

  delay(500);
}
