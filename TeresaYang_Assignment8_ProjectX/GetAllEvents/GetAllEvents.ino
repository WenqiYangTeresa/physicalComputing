#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 2;   // Maximum number of times the Choreo should be executed

//#define CALENDAR_CREDENTIALS  "GoogleCalendar"
//#define CALENDAR_ID         "jademorgannyc@gmail.com"

void setup() {
  Serial.begin(9600);

  // For debugging, wait until the serial console is connected
  delay(4000);
  while (!Serial);
  Bridge.begin();
}

void loop() {
  if (calls <= maxCalls) {
    Serial.println("Running GetAllEvents - Run #" + String(calls++));

    TembooChoreo GetAllEventsChoreo;

    // Invoke the Temboo client
    GetAllEventsChoreo.begin();

    // Set Temboo account credentials
    GetAllEventsChoreo.setAccountName(TEMBOO_ACCOUNT);
    GetAllEventsChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    GetAllEventsChoreo.setAppKey(TEMBOO_APP_KEY);

    // Set profile to use for execution
    GetAllEventsChoreo.setProfile("GoogleCalendarAccount");

    // Set Choreo inputs
    GetAllEventsChoreo.addInput("CalendarID", "6fqpe60r34f7komikovpgaa0mk@group.calendar.google.com");

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

  Serial.println("Waiting...");
  delay(30000); // wait 30 seconds between GetAllEvents calls
}
