
//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
int outputpin= A0;
#define FIREBASE_HOST "hackertech-2f778.firebaseio.com"
#define FIREBASE_AUTH "24ju5ziYqpPm1acsTFSOUBke4JcsDexYsSH5BIjl"
#define WIFI_SSID "#roy"
#define WIFI_PASSWORD "Astapor22"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
int x=0,y=0;
String path = "/soldier1/bv";
String updateData = "{\"hr\":\"Yes\", \"temp\":\"No\"}}";
void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  
  String jsonStr;

 
/*if (Firebase.updateNode(firebaseData, "/soldier1/bv", "{\"hr\":\"Yes\", \"temp\":\"No\"}")) {

  

} else {
  //Failed, then print out the error detail
  Serial.println(firebaseData.errorReason());*/
}

  
 
 
 


void loop()
{

  delay(1000);

 int analogValue = analogRead(outputpin);
float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU
float celsius = millivolts/10;
Serial.print("in DegreeC=   ");
Serial.println(celsius);
 String s="{\"hr\":\"No\", \"temp\":\""+String(celsius)+"\"}";

  if (Firebase.updateNode(firebaseData, "/soldier1/bv", s))
  {}
  else {
  //Failed, then print out the error detail
  Serial.println(firebaseData.errorReason());
}
  }
