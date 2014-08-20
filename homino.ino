// Temperature and humidity sensor library.
// https://github.com/markruys/arduino-DHT
#include "DHT.h"

// Ethernet shield libraries. 
#include <Ethernet.h>
#include <SPI.h>

#define SENSOR_DHT_PIN 2

DHT dht;

// MAC address and IP address for controller.
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192,168,1,100);

// Initialize the Ethernet server library with the IP address and port
// (port 80 is default for HTTP).
EthernetServer server(80);

// The setup routine runs once at startup.
void setup() {
  Serial.begin(9600);
  Serial.println("Status\tHumidity (%)\tTemperature (C)");

  dht.setup(SENSOR_DHT_PIN);

  // Start the Ethernet connection and the server.
  Ethernet.begin(mac, ip);
  server.begin();
}

// The loop routine runs over and over again forever.
void loop() {
  delay(dht.getMinimumSamplingPeriod());

  int humidity = dht.getHumidity();
  int temperature = dht.getTemperature();

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
