const int ledPinRed = 11;
const int ledPinGreen = 10;
const int ledPinBlue = 9;
const int flexPin = A0;

int currentMap;
int pastMap = 0;
bool flat = true;
bool bent;
bool fist;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);

}

void loop() {
  int currentMap = readDegrees();
  //Serial.println(currentMap);

  //edge detection
  // hand just opens
  if (currentMap > 90) {
    if (pastMap <= 90) {
      flat = true;
      bent = false;
      fist = false;
    }
  } else if (currentMap >= 45) {
    //hand just bends
    if (pastMap < 45 || pastMap > 90) {
      flat = false;
      bent = true;
      fist = false;
    }
  } else {
    //hand just curls into a fist
    if (pastMap > 45) {
      flat = false;
      bent = false;
      fist = true;
    }
  }
  
  //update pastMap
  pastMap = currentMap;
  
  //LED reacts at different states
  if (flat == true) {
    messaging();
  }
  if (bent == true) {
    warming();
  }
  if (fist == true) {
    tuning();
  }

  // delay to ensure accurate sensor readings
  delay(1);
}

//map flexPin reading to positive degrees
int readDegrees() {
  int flexValue = analogRead(flexPin);
  Serial.println(flexValue);
  // convert the value to one that is relative to 0 and positive
  int normalized = abs(flexValue - 76);
  // convert the range to degrees (must be recalibrated according to resistor strength)
  return map(normalized, 0, 35, 0, 90);
}

void tuning() {
  // tunes mode is yellow
  //Serial.println("Tunes");
  analogWrite(ledPinRed, 255);
  analogWrite(ledPinBlue, 0);
  analogWrite(ledPinGreen, 0);
}

void messaging() {
  // message mode is purple
  //Serial.println("Messaging");
  analogWrite(ledPinRed, 0);
  analogWrite(ledPinBlue, 0);
  analogWrite(ledPinGreen, 255);
}

void warming() {
  // warming mode is blue
 // Serial.println("Warming");
  analogWrite(ledPinRed, 0);
  analogWrite(ledPinBlue, 255);
  analogWrite(ledPinGreen, 0);
}

