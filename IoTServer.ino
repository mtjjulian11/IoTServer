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
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected");
  }

  // Obtain values for field Y X

  long x = ThingSpeak.readIntField(readChannelNumber, Xdata, readAPIKey);
  // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();

  // Mapping of the Read Field parameter
  //float mapX= map(x,-4.0,4.0,1.0,10.0);

  if (statusCode == 200) {
    Serial.println("Value X: " + String(x));
    //Servo.write(inclinacionX);
   
  }
  else {
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode));
  }



  // Obtain values for field Y

  long y = ThingSpeak.readIntField(readChannelNumber, Ydata, readAPIKey);
  // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();

  // Mapping of the Read Field parameter
  //float mapY = map(y, -10.0, 4.0, 1.0, 10.0);


  if (statusCode == 200) {
    Serial.println("Value Y: " + String(y));
    //Servo.write(inclinacionY);
   
  }
  else {
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode));
  }

  // Obtain values for field Z

  long z = ThingSpeak.readIntField(readChannelNumber, Zdata, readAPIKey);
  // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();

  // Mapping of the Read Field parameter
  //float mapZ = map(z, -4.0, 4.0, 1.0, 10.0);


  if (statusCode == 200) {
    Serial.println("Value Z: " + String(z));
    //Servo.write(inclinacionZ);
  }
    
  else {
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode));
  }
  delay(3000); // No need to read the temperature too often.

}
