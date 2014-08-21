// Temperature and humidity sensor library.
// https://github.com/markruys/arduino-DHT
#include "DHT.h"

// Ethernet shield libraries. 
#include <Ethernet.h>
#include <SPI.h>

#define SENSOR_DHT_PIN 2

#define RED_LED_PIN 3
#define GREEN_LED_PIN 6
#define BLUE_LED_PIN 5

DHT dht;

// MAC address and IP address for controller.
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192,168,1,100);

// Initialize the Ethernet server library with the IP address and port
// (port 80 is default for HTTP).
EthernetServer server(80);

int brightness = 0; // How bright the LED is.
int fadeAmount = 5; // How many points to fade the LED by.

// The setup routine runs once at startup.
void setup() {
  Serial.begin(9600);
  Serial.println("Status\tHumidity (%)\tTemperature (C)");

  dht.setup(SENSOR_DHT_PIN);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  // Start the Ethernet connection and the server.
  Ethernet.begin(mac, ip);
  server.begin();
}

// The loop routine runs over and over again forever.
void loop() {
  delay(dht.getMinimumSamplingPeriod());

  int humidity = dht.getHumidity();
  int temperature = dht.getTemperature();

  analogWrite(RED_LED_PIN, brightness);
  analogWrite(GREEN_LED_PIN, brightness);
  analogWrite(BLUE_LED_PIN, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }

  // Listen for incoming clients.
  EthernetClient client = server.available();

  if (client) {
    Serial.println("New client connected!");

    while (client.connected()) {
      if (client.available()) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // The connection will be closed after completion of the response.
          client.println("Refresh: 60");  // Refresh the page automatically every 60 sec.
          client.println();
          client.println("<!DOCTYPE html>");
          client.println("<html><body>");
          client.print(dht.getStatusString());
          client.print(" ");
          client.print(humidity);
          client.print(" ");
          client.print(temperature);
          client.println("</body></html>");
          break;
      }
    }

    // Close the connection.
    client.stop();
    Serial.println("Client disconnected!");
  }

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity);
  Serial.print("\t\t");
  Serial.println(temperature);
}
