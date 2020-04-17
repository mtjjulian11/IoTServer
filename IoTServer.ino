#include "ThingSpeak.h"
#include <WiFiNINA.h>
#include "secrets.h"

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

// Weather station channel details
unsigned long readChannelNumber = SECRET_CH_ID;
unsigned int Xdata = 1;
unsigned int Ydata = 2;
unsigned int Zdata = 3;

const char * readAPIKey = SECRET_READ_APIKEY;

void setup() {
  Serial.begin(115200);      // Initialize serial 
  ThingSpeak.begin(client);  // Initialize ThingSpeak 
}

void loop() {

  int statusCode = 0;
  
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected");
  }

  // Leemos del campo correspondiente al eje X



  
  long x = ThingSpeak.readLongField(readChannelNumber, Xdata, readAPIKey);    
  // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
   Serial.println("Valor de X es: " + String(x) + "Gs");
    //Servo.write(inclinacionX);
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }

  // Leemos del campo correspondiente al eje Y
 long y = ThingSpeak.readLongField(readChannelNumber, Ydata, readAPIKey);    
 // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("Valor de Y es: " + String(y) + "Gs");
    //Servo.write(inclinacionY);
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }

  // We read Z
 
   long z = ThingSpeak.readLongField(readChannelNumber, Zdata, readAPIKey);    
  // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
   Serial.println("Vslor de Z es: " + String(z) + "Gs");
    //Servo.write(inclinacionZ);
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }
  delay(3000); // No need to read the temperature too often.

}
