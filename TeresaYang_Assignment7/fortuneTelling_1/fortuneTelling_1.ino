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

String goodStrings[] = {"Excellent", "Seize your moment", "Reward of kindness",
                        "New vision", "Pleasant surprise"
                       };

String mehStrings[] = {"Restless mind", "Need a break", "trivial arguments",
                       "Minor health issue", "Tough decision"
                      };

String badStrings[] = {"Break of trust", "Inspiration block", "Everything sucks",
                       "Misunderstanding", "Watch out for shark"
                      };

long ranNum;

byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};


void setup() {
  // set up the LCD's number of columns and rows:
  //lcd.createChar(0, smiley);
  lcd.begin(16, 2);
  //lcd.write(byte(0));
  // Print a message to the LCD.
  lcd.print("Fortune Stones");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
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
    Serial.println("Out of range");
    newDistance = oldDistance;
  } else {
    newDistance = distance;
    Serial.println(newDistance);
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
      ranNum = random(0, 5);
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

  //DISPLAY
  if (GOOD == true) {
    delay(200);
    lcd.setCursor(0, 0);
    lcd.print("GOOD");
    lcd.setCursor(0, 1);
    lcd.print(goodStrings[ranNum]);
    //scroll if too long
    if (goodStrings[ranNum].length() > 16) {
      delay(1000);
      for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
        // scroll one position left:
        lcd.scrollDisplayLeft();
        // wait a bit:
        delay(250);
      }
    }
  } else if (BAD == true) {
    delay(200);
    lcd.setCursor(0, 0);
    lcd.print("BAD");
    lcd.setCursor(0, 1);
    lcd.print(badStrings[ranNum]);
    //scroll if too long
    if (badStrings[ranNum].length() > 16) {
      delay(1000);
      for (int positionCounter = 0; positionCounter < 16; positionCounter++) { 
        lcd.scrollDisplayLeft();
        delay(250);
      }
    }
  } else if (MEH == true) {
    delay(200);
    lcd.setCursor(0, 0);
    lcd.print("MEH");
    lcd.setCursor(0, 1);
    lcd.print(mehStrings[ranNum]);
    //scroll if too long
    if (mehStrings[ranNum].length() > 16) {
      delay(1000);
      for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
        lcd.scrollDisplayLeft();
        delay(250);
      }
    }
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Fortune Stones");
  }

  //UPDATE
  oldDistance = newDistance;
  delay(20);
}
