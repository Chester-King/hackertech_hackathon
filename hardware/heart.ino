int UpperThreshold = 518;
int LowerThreshold = 490;
int reading = 0;
float BPM = 0.0;
bool IgnoreReading = false;
bool FirstPulseDetected = false;
unsigned long FirstPulseTime = 0;
unsigned long SecondPulseTime = 0;
unsigned long PulseInterval = 0;
const unsigned long delayTime = 10;
const unsigned long delayTime2 = 1000;
const unsigned long baudRate = 9600;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;


//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "hackertech-2f778.firebaseio.com"
#define FIREBASE_AUTH "24ju5ziYqpPm1acsTFSOUBke4JcsDexYsSH5BIjl"
#define WIFI_SSID "#roy"
#define WIFI_PASSWORD "Astapor22"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

String path = "/soldier1/bv";
String updateData = "{\"hr\":\"Yes\", \"temp\":\"No\"}}";

void setup(){
  Serial.begin(baudRate);
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

void loop(){

  // Get current time
  unsigned long currentMillis = millis();

  // First event
  if(myTimer1(delayTime, currentMillis) == 1){

    reading = analogRead(A0); 

    // Heart beat leading edge detected.
    if(reading > UpperThreshold && IgnoreReading == false){
      if(FirstPulseDetected == false){
        FirstPulseTime = millis();
        FirstPulseDetected = true;
      }
      else{
        SecondPulseTime = millis();
        PulseInterval = SecondPulseTime - FirstPulseTime;
        FirstPulseTime = SecondPulseTime;
      }
      IgnoreReading = true;
      
    }

    // Heart beat trailing edge detected.
    if(reading < LowerThreshold && IgnoreReading == true){
      IgnoreReading = false;
     
    }  

    // Calculate Beats Per Minute.
    BPM = (1.0/PulseInterval) * 60.0 * 1000;
  }

  // Second event
  if(myTimer2(delayTime2, currentMillis) == 1){
    Serial.print(reading);
    Serial.print("\t");
    Serial.print(PulseInterval);
    Serial.print("\t");
    Serial.print(BPM);
    Serial.println(" BPM");
    Serial.flush();
  }
  String s="{\"hr\":\""+String(BPM)+"\", \"temp\":\"20.21\"}";

  if (Firebase.updateNode(firebaseData, "/soldier1/bv", s))
  {}
  else {
  //Failed, then print out the error detail
  Serial.println(firebaseData.errorReason());
}
delay(1000);
}

// First event timer
int myTimer1(long delayTime, long currentMillis){
  if(currentMillis - previousMillis >= delayTime){previousMillis = currentMillis;return 1;}
  else{return 0;}
}

// Second event timer
int myTimer2(long delayTime2, long currentMillis){
  if(currentMillis - previousMillis2 >= delayTime2){previousMillis2 = currentMillis;return 1;}
  else{return 0;}
}
