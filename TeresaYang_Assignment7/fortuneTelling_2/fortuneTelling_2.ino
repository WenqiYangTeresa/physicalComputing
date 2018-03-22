// include the library code:
#include <ShiftedLCD.h>
#include <SPI.h>

// initialize the library with the number of the sspin
// (or the latch pin of the 74HC595)
//data clock latch
LiquidCrystal lcd(9);

#define trigPin 6
#define echoPin 7

int oldDistance = 1;
int newDistance;

bool GOOD, MEH, BAD = false;
int thresholdTop = 12;
int thresholdHigh = 8;
int thresholdMid = 4;

String goodStrings[] = {"Excellent", "Seize ur chance", "Kindness Reward",
                        "New Chapter", "Good surprise", "Not good",
                       };

String mehStrings[] = {"Restless mind", "Need a break", "Trivial argument",
                       "Be attentive", "Tough decision", "Safe & Sound"
                      };

String badStrings[] = {"Break of trust", "Idea block", "Everything sucks",
                       "Misunderstanding", "Shark alert" , "Amazing"
                      };

long ranNum;

int moon = 2, sun = 8, stars = 4;


void setup() {
  // set up the LCD's number of columns and rows:
  //lcd.createChar(0, smiley);
  lcd.begin(16, 2);
  //lcd.write(byte(0));
  // Print a message to the LCD.
  lcd.print("ASTROLOGY");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //light
  pinMode(moon, OUTPUT);
  pinMode(sun, OUTPUT);
  pinMode(stars, OUTPUT);
  Serial.begin(9600);
  digitalWrite(sun, LOW);
  digitalWrite(stars, LOW);
  digitalWrite(moon, HIGH);
}

void loop() {
  //READ SENSOR
  float duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  //FILTER
  if (distance > 200 || distance <= 0) {
    //Serial.println("Out of range");
    newDistance = 20;
  } else {
    newDistance = distance;
    // Serial.println(newDistance);
  }

  //ACTION
  if (newDistance < thresholdMid) {
    if (oldDistance >= thresholdMid) {
      //Good Luck Closest to sensor
      GOOD = true;
      MEH = false;
      BAD = false;
      ranNum = random(0, 5);
      lcd.clear();
    }
  } else if (newDistance < thresholdHigh) {
    if (oldDistance >= thresholdHigh) {
      //Meh Luck in the middle distance from sensor
      GOOD = false;
      MEH = true;
      BAD = false;
      ranNum = random(0, 6);
      lcd.clear();
    }
  } else if (newDistance < thresholdTop) {
    if (oldDistance >= thresholdTop) {
      //Bad Luck far from sensor
      GOOD = false;
      MEH = false;
      BAD = true;
      ranNum = random(0, 5);
      lcd.clear();
    }
  } else if (newDistance > thresholdTop) {
    if (oldDistance <= thresholdTop) {
      //off
      GOOD = false;
      MEH = false;
      BAD = false;
      lcd.clear();
    }
  }
delay(200);
  //DISPLAY
  if (GOOD == true) {
    delay(200);
    digitalWrite(sun, LOW);
    digitalWrite(stars, LOW);
    digitalWrite(moon, HIGH);


    lcd.setCursor(0, 0);
    lcd.print("MOON:");
    lcd.setCursor(0, 1);
    lcd.print(goodStrings[ranNum]);
  } else if (BAD == true) {
    delay(200);
    digitalWrite(moon, LOW);
    digitalWrite(stars, LOW);
    digitalWrite(sun, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("SUN:");
    lcd.setCursor(0, 1);
    lcd.print(badStrings[ranNum]);
  } else if (MEH == true) {
    delay(200);
    digitalWrite(moon, LOW);
    digitalWrite(sun, LOW);
    digitalWrite(stars, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("STARS:");
    lcd.setCursor(0, 1);
    lcd.print(mehStrings[ranNum]);
  } else {
    digitalWrite(moon, LOW);
    digitalWrite(sun, LOW);
    digitalWrite(stars, LOW);
    lcd.setCursor(0, 0);
    lcd.print("ASTROLOGY");
  }

  //UPDATE
  oldDistance = newDistance;
  delay(100);
}
