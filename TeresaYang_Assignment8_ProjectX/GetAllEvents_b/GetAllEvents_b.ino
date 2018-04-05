#include <SPI.h>
#include <WiFi101.h>
#include <WiFiSSLClient.h>
#include <TembooSSL.h>
#include "TembooAccount.h"// Contains Temboo account information

WiFiSSLClient client;
int calls = 1;// Execution count, so this doesn't run forever
int maxCalls = 2;// Maximum number of times the Choreo should be executed

void setup() {
 Serial.begin(9600);
 // For debugging, wait until the serial console is connected
 delay(4000);
 while (!Serial);
 int wifiStatus = WL_IDLE_STATUS;
 // Determine if the WiFi Shield is present
 Serial.print("\n\nShield:");
 if (WiFi.status() == WL_NO_SHIELD) {
   Serial.println("FAIL");
   // If there's no WiFi shield, stop here
   while (true);
 }
 
 Serial.println("OK");
 // Try to connect to the local WiFi network
 while (wifiStatus != WL_CONNECTED) {
   Serial.print("WiFi:");
   wifiStatus = WiFi.begin(WIFI_SSID, WPA_PASSWORD);
   if (wifiStatus == WL_CONNECTED) {
     Serial.println("OK");
   } else {
     Serial.println("FAIL");
   }
   delay(5000);
 }
 Serial.println("Setup complete.\n");
 
}

void loop() {
 if (calls <= maxCalls) {
   Serial.println("Running GetAllEvents - Run #" + String(calls++));
   TembooChoreoSSL GetAllEventsChoreo(client);
   
   // Invoke the Temboo client
   GetAllEventsChoreo.begin();
   
   // Set Temboo account credentials
   GetAllEventsChoreo.setAccountName(TEMBOO_ACCOUNT);
   GetAllEventsChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
   GetAllEventsChoreo.setAppKey(TEMBOO_APP_KEY);
   GetAllEventsChoreo.setDeviceType(TEMBOO_DEVICE_TYPE);
   
   // Set profile to use for execution
   GetAllEventsChoreo.setProfile("GoogleCalendarAccount");
   // Set Choreo inputs
   String CalendarIDValue = "6fqpe60r34f7komikovpgaa0mk@group.calendar.google.com";
   GetAllEventsChoreo.addInput("CalendarID", CalendarIDValue);
   // Identify the Choreo to run
   GetAllEventsChoreo.setChoreo("/Library/Google/Calendar/GetAllEvents");
   // Run the Choreo; when results are available, print them to serial
   GetAllEventsChoreo.run();
   
   while (GetAllEventsChoreo.available()) {
     char c = GetAllEventsChoreo.read();
     Serial.print(c);
   }
   
   GetAllEventsChoreo.close();
 }
 
 Serial.println("\nWaiting...\n");
 delay(30000); // wait 30 seconds between GetAllEvents calls
}
