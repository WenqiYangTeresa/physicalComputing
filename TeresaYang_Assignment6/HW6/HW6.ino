//speed control press sensor
int sensorPin = A0;
int sensorValue;
int motorSpeed;

//Motor
int enable = 9;  // PWM pin control speed
int motorPinA = 7;
int motorPinB = 8;

//peak detection
int peakValue = 10;
int thresholdHigh = 100;
int noise = 0;

bool moveForward = false;
//bool moveBackward = false;
int currentSpeed;

//press button to brake
const int buttonPin = 2;
int lastButton = 0;
int currentButton;

void setup() {
  Serial.begin(9600);
  pinMode(enable, OUTPUT);
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue);
  //unsigned long currentMillis;


  //PRESSURE determines speed
  if (sensorValue > thresholdHigh) {
    delay(100);
    // currentMillis = millis();
  }

  if (sensorValue > peakValue) {
    peakValue = sensorValue;
  }

  // do something if you have reached the peak and released your press
  if (sensorValue <= thresholdHigh - noise) {
    if (peakValue > thresholdHigh + noise) {
      Serial.println(peakValue);
      currentSpeed = peakValue;
      moveForward = true;
      //        if (currentMillis - millis() >= 5000) {
      //          moveForward = true;
      //          moveBackward = false;
      //        } else if ( currentMillis - millis() < 5000) {
      //          moveBackward = true;
      //          moveForward = false;
      //        }
      peakValue = 0;
    }
  }

  //Serial.println(currentMillis);

  //    if (sensorValue > 550) {
  //      motorSpeed = map(sensorValue, 0, 1023, 0, 255);
  //      forward(motorSpeed);
  //    }
  //    if (sensorValue < 350 && sensorValue > 60) {
  //      motorSpeed = map(sensorValue, 351, 549, 0, 255);
  //      reverse(motorSpeed);
  //    }
  //
  //    if (sensorValue > 349 && sensorValue < 551) {
  //      brake();
  //    }
  //
  //    if (sensorValue < 61) {
  //      brake();
  //    }

  //BRAKE! if button pressed
  currentButton = digitalRead(buttonPin);
  //edge detect
  if (currentButton != lastButton) {
    //debounce
    delay(10);
    currentButton = digitalRead(buttonPin);

    if (currentButton == HIGH) {
      moveForward = false;
      //moveBackward = false;
    }
    delay(50);
  }
  lastButton = currentButton;


  //MOTOR ON OFF
  if (moveForward == true) {
    motorSpeed = map(currentSpeed, 90, 1023, 0, 255);
    forward(motorSpeed);
    Serial.println("forward");
  } else {
    brake();
    Serial.println("off");
  }
//  if (moveForward == true) {
//    motorSpeed = map(currentSpeed, 90, 1023, 0, 255);
//    forward(motorSpeed);
//    Serial.println("forward");
//  } else if (moveBackward == true) {
//    motorSpeed = map(currentSpeed, 90, 1023, 0, 255);
//    reverse(motorSpeed);
//    Serial.println("backward");
//  } else {
//  brake();
//  Serial.println("off");
//}

}


//FUNCTIONS
void forward(int s) {
  digitalWrite(enable, LOW);
  digitalWrite(motorPinA, HIGH);
  digitalWrite(motorPinB, LOW);
  analogWrite(enable, s);
}

void reverse(int s) {
  digitalWrite(enable, LOW);
  digitalWrite(motorPinA, LOW);
  digitalWrite(motorPinB, HIGH);
  analogWrite(enable, s);
}

void brake() {
  digitalWrite(enable, LOW);
  digitalWrite(motorPinA, LOW);
  digitalWrite(motorPinB, LOW);
  digitalWrite(enable, HIGH);
}
