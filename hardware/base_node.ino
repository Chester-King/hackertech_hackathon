#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "poopssid";
const char *password = "pingu4prez";

ESP8266WebServer server(80);

void handleSentVar() {
  
  if (server.hasArg("sensor_gps")) { // this is the variable sent from the client
    String val1=server.arg("sensor_gps");
    Serial.println("GPS Location");
    Serial.print(val1);
    Serial.println();
    server.send(200, "text/html", "Data received");
  }
  if (server.hasArg("sensor_bpm")) { // this is the variable sent from the client
    String val2=server.arg("sensor_bpm");
    Serial.println("HeartBeat");
    Serial.print(val2);
    Serial.println();
    server.send(200, "text/html", "Data received");
  }
  if (server.hasArg("sensor_temp")) { // this is the variable sent from the client
    String val3=server.arg("sensor_temp");
    Serial.println("Body Temperature");
    Serial.print(val3);
    Serial.println();
    server.send(200, "text/html", "Data received");
  }
  
}

void setup() {
  delay(1000);

Serial.begin(9600);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();

  server.on("/data/", HTTP_GET, handleSentVar); // when the server receives a request with /data/ in the string then run the handleSentVar function
  server.begin();
}

void loop() {
  server.handleClient();
}
