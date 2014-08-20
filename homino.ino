// Temperature and humidity sensor library.
// https://github.com/markruys/arduino-DHT
#include "DHT.h"

#define SENSOR_DHT_PIN 2

DHT dht;

// The setup routine runs once at startup.
void setup() {
  Serial.begin(9600);
  Serial.println("Status\tHumidity (%)\tTemperature (C)");

  dht.setup(SENSOR_DHT_PIN);
}

// The loop routine runs over and over again forever.
void loop() {
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 0);
  Serial.print("\t\t");
  Serial.println(temperature, 0);
}
