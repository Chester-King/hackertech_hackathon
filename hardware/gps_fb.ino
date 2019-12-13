#include <TinyGPS++.h> // library for GPS module
#include <SoftwareSerial.h>

TinyGPSPlus gps;  // The TinyGPS++ object
SoftwareSerial ss(4, 5); // The serial connection to the GPS device

float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;


//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "hackertech-2f778.firebaseio.com"
#define FIREBASE_AUTH "24ju5ziYqpPm1acsTFSOUBke4JcsDexYsSH5BIjl"
#define WIFI_SSID "#roy"
#define WIFI_PASSWORD "Astapor22"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

String path = "/soldier1/gps";
String updateData = "{\"latitude\":\"Yes\", \"longitude\":\"No\"}}";

void setup()
{

  Serial.begin(115200);
  ss.begin(9600);

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

}




void loop()
{

  delay(1000);
while (ss.available() > 0) //while data is available
    if (gps.encode(ss.read())) //read gps data
    {
      //if (gps.location.isValid()) //check whether gps location is valid
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6); // latitude location is stored in a string
        longitude = gps.location.lng();
        lng_str = String(longitude , 6); //longitude location is stored in a string
        Serial.println(lat_str);
        Serial.println(lng_str);
        
      }
    }
    String s="{\"latitude\":\""+lng_str+"\", \"longitude\":\""+lat_str+"\"}";

  if (Firebase.updateNode(firebaseData, "/soldier1/gps", s))
  {}
  else {
  //Failed, then print out the error detail
  Serial.println(firebaseData.errorReason());
}
  }
