
const int ledPinRed = 11;
const int ledPinGreen = 10;
const int ledPinBlue = 9;
const int photoPin = A0;
int photoState;

//range threshold
const int environmentRange = 370;
const int highRange = environmentRange * 1.5;
const int lowRange = environmentRange / 2;
const int darkRange = environmentRange / 7;

//3 modes of gradient fade
int ledMode = 0;
long time = 0;
int periode = 1000;
int fadeValue;


//SOS variables
long ShortTime = 250;
long LongTime = 850;
unsigned long previousMillis = 0;
int ledState = 255;
int counter = 0;

//rainbow variables
unsigned Rain_previousMillis = 0;
int Rain_interval = 400;
int Rain_counter = 0;

// edge detect
int previousMark = 380;
int currentMark;

void setup() {
  Serial.begin(9600);
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
}

void loop() {

  photoState = analogRead(photoPin);
  currentMark = photoState;
  Serial.println(photoState);

  if (photoState > highRange) {
    //flash light
    //3 modes of gradient fading
    
    if (previousMark < highRange && currentMark > highRange) {
      if (ledMode == 3) {
        ledMode = 0;
      }
      ledMode++;
    }
    
    setMode(ledMode);
    //Serial.println(ledMode);
  }  else if (photoState > lowRange && photoState <= highRange) {
    //default
    //OFF
    analogWrite(ledPinRed, 255);
    analogWrite(ledPinBlue, 255);
    analogWrite(ledPinGreen, 255);
  } else if (photoState <= lowRange && photoState >= darkRange) {
    //cover with finger
    //sos
    sos();
    //setMode();
  } else if (photoState < darkRange) {
    //wrap it in your fist
    rainbow();
  }

  previousMark = currentMark;
}

//SOS without delay()
//SOS without delay()
void sos () {
  unsigned long currentMillis = millis();
  //S Light-Dark-Light-Dark-Light
  if (counter < 6) {
    if ((ledState == 255) && (currentMillis - previousMillis >= ShortTime)) {
      ledState = 0;
      previousMillis = currentMillis;
      analogWrite(ledPinRed, ledState);
      analogWrite(ledPinBlue, ledState);
      analogWrite(ledPinGreen, ledState);
      counter ++;
    } else if ((ledState == 0) && (currentMillis - previousMillis >= ShortTime)) {
      ledState = 255;
      previousMillis = currentMillis;
      analogWrite(ledPinRed, ledState);
      analogWrite(ledPinBlue, ledState);
      analogWrite(ledPinGreen, ledState);
      counter ++;
    }
  }
  //o Dark-Light-Dark-Light-Dark-Light-Dark
  if (counter >= 6 && counter < 12) {
    if ((ledState == 255) && (currentMillis - previousMillis >= LongTime)) {
      ledState = 0;
      previousMillis = currentMillis;
      analogWrite(ledPinRed, ledState);
      analogWrite(ledPinBlue, ledState);
      analogWrite(ledPinGreen, ledState);
      counter ++;
    } else if ((ledState == 0) && (currentMillis - previousMillis >= LongTime)) {
      ledState = 255;
      previousMillis = currentMillis;
      analogWrite(ledPinRed, ledState);
      analogWrite(ledPinBlue, ledState);
      analogWrite(ledPinGreen, ledState);
      counter ++;
    }
  }
  //back to S
  if (counter >= 12) {
    counter = 0;
  }
}

//rainbow without delay()
void rainbow() {
  unsigned long Rain_currentMillis = millis();
  if (Rain_counter == 0) {
    if (Rain_currentMillis - Rain_previousMillis >= Rain_interval) {
      Rain_previousMillis = Rain_currentMillis;
      //red
      analogWrite(ledPinRed, 0);
      analogWrite(ledPinBlue, 255);
      analogWrite(ledPinGreen, 255);
      Rain_counter ++;
    }
  }
  if (Rain_counter == 1) {
    if (Rain_currentMillis - Rain_previousMillis >= Rain_interval) {
      Rain_previousMillis = Rain_currentMillis;
      //orange
      analogWrite(ledPinRed, 0);
      analogWrite(ledPinBlue, 255);
      analogWrite(ledPinGreen, 160);
      Rain_counter ++;
    }
  }
  if (Rain_counter == 2) {
    if (Rain_currentMillis - Rain_previousMillis >= Rain_interval) {
      Rain_previousMillis = Rain_currentMillis;
      //yellow
      analogWrite(ledPinRed, 0);
      analogWrite(ledPinBlue, 255);
      analogWrite(ledPinGreen, 10);
      Rain_counter ++;
    }
  }
  if (Rain_counter == 3) {
    if (Rain_currentMillis - Rain_previousMillis >= Rain_interval) {
      Rain_previousMillis = Rain_currentMillis;
      //green
      analogWrite(ledPinRed, 255);
      analogWrite(ledPinBlue, 255);
      analogWrite(ledPinGreen, 0);
      Rain_counter ++;
    }
  }
  if (Rain_counter == 4) {
    if (Rain_currentMillis - Rain_previousMillis >= Rain_interval) {
      Rain_previousMillis = Rain_currentMillis;
      //cyan
      analogWrite(ledPinRed, 255);
      analogWrite(ledPinBlue, 20);
      analogWrite(ledPinGreen, 20);
      Rain_counter ++;
    }
  }
  if (Rain_counter == 5) {
    if (Rain_currentMillis - Rain_previousMillis >= Rain_interval) {
      Rain_previousMillis = Rain_currentMillis;
      //blue
      analogWrite(ledPinRed, 255);
      analogWrite(ledPinBlue, 0);
      analogWrite(ledPinGreen, 255);
      Rain_counter ++;
    }
  }
  if (Rain_counter == 6) {
    if (Rain_currentMillis - Rain_previousMillis >= Rain_interval) {
      Rain_previousMillis = Rain_currentMillis;
      //purple
      analogWrite(ledPinRed, 200);
      analogWrite(ledPinBlue, 70);
      analogWrite(ledPinGreen, 255);
      //reset
      Rain_counter = 0;
    }
  }
}

void setMode(int mode) {
  //orange gradient
  if (mode == 1) {
    time = millis();
    fadeValue = 128 + 127 * cos(2 * PI / periode * time);
    analogWrite(ledPinRed, fadeValue);
    analogWrite(ledPinGreen, 155);
    analogWrite(ledPinBlue, 0);
  }
  //purple gradient
  if (mode == 2) {
    time = millis();
    fadeValue = 128 + 127 * cos(2 * PI / periode * time);
    analogWrite(ledPinRed, 0);
    analogWrite(ledPinGreen, 255);
    analogWrite(ledPinBlue, fadeValue);
  }
  //cyan gradient
  if (mode == 3) {
    time = millis();
    fadeValue = 128 + 127 * cos(2 * PI / periode * time);
    analogWrite(ledPinRed, 0);
    analogWrite(ledPinGreen, fadeValue);
    analogWrite(ledPinBlue, 255);
  }
}

