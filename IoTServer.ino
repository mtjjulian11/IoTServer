#include "ThingSpeak.h"
#include <WiFiNINA.h>
#include "secrets.h"

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

// Weather station channel details
unsigned long Modulo2ChannelNumber = SECRET_CH_ID_MODULO2;
unsigned int inclinacionXFieldNumber = 1;
unsigned int inclinacionYFieldNumber = 2;
const char * Modulo2ReadAPIKey = SECRET_READ_APIKEY_MODULO2;

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
  long inclinacionX = ThingSpeak.readLongField(Modulo2ChannelNumber, inclinacionXFieldNumber, Modulo2ReadAPIKey);    
  // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("La inclinacion de X es: " + String(inclinacionX) + "º");
    //Servo.write(inclinacionX);
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }

  // Leemos del campo correspondiente al eje Y
  long inclinacionY = ThingSpeak.readLongField(Modulo2ChannelNumber, inclinacionYFieldNumber, Modulo2ReadAPIKey);    
  // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("La inclinacion de Y es: " + String(inclinacionY) + "º");
    //Servo.write(inclinacionY);
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }
  
  delay(3000); // No need to read the temperature too often.

}
