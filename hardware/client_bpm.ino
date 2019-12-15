#include <ESP8266WiFi.h>

const char *ssid = "poopssid";
const char *password = "pingu4prez";


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

String hrt;

void setup() {
  Serial.begin(115200);
  delay(10);


  // Explicitly set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

}

void bPM()
{
  
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
    /*Serial.print(reading);
    Serial.print("\t");
    Serial.print(PulseInterval);
    Serial.print("\t");
    Serial.print(BPM);
    Serial.println(" BPM");
    Serial.flush();*/
  }
hrt=String(BPM);
}
void loop() {
 

bPM();
 
  
  

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const char * host = "192.168.4.1";
  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request. Something like /data/?sensor_reading=123
  String url = "/data/";
  url += "?sensor_bpm=";
  url += hrt;

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  delay(500);
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
