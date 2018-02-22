
const int ledPinRed = 11;
const int ledPinGreen = 10;
const int ledPinBlue = 9;
const int photoPin = A0;
int photoState;

//range threshold
const int highRange = 100;
const int midRange = 40;
const int lowRange = 20;

//3 modes of gradient counting
int ledMode = 0;


void setup() {
  Serial.begin(9600);
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT); 
}

void loop() {
  
  photoState = analogRead(photoPin);
  Serial.println(photoState);
  
  if (photoState > highRange){ 
    //3 modes of gradient fading
    ledMode ++;
    if(ledMode < 4){
      setMode(ledMode);
    }
    if (ledMode > 3){
      ledMode = 0;
    }
  }  else if (photoState > midRange && photoState <= highRange){
    //SOS signal blink  
    sos();
  } else if (photoState >= lowRange && photoState <= midRange){
    //disco ball
    rainbow();
  } else{
    //dark  
       analogWrite(ledPinRed, 255);
       analogWrite(ledPinBlue, 255);
       analogWrite(ledPinGreen, 255);
  }
}


void sos (){
  //s
        analogWrite(ledPinRed, 0);
        analogWrite(ledPinBlue, 0);
        analogWrite(ledPinGreen, 0);
        delay(300);
        analogWrite(ledPinRed, 255);
        analogWrite(ledPinBlue, 255);
        analogWrite(ledPinGreen, 255);
        delay(300);
        analogWrite(ledPinRed, 0);
        analogWrite(ledPinBlue, 0);
        analogWrite(ledPinGreen, 0);
        delay(300);
        analogWrite(ledPinRed, 255);
        analogWrite(ledPinBlue, 255);
        analogWrite(ledPinGreen, 255);
        delay(300);
        analogWrite(ledPinRed, 0);
        analogWrite(ledPinBlue, 0);
        analogWrite(ledPinGreen, 0);
        delay(300);     
        analogWrite(ledPinRed, 255);
        analogWrite(ledPinBlue, 255);
        analogWrite(ledPinGreen, 255);
        delay(700);
  //o
        analogWrite(ledPinRed, 0);
        analogWrite(ledPinBlue, 0);
        analogWrite(ledPinGreen, 0);
        delay(1000);
        analogWrite(ledPinRed, 255);
        analogWrite(ledPinBlue, 255);
        analogWrite(ledPinGreen, 255);
        delay(700);
        analogWrite(ledPinRed, 0);
        analogWrite(ledPinBlue, 0);
        analogWrite(ledPinGreen, 0);
        delay(1000);
        analogWrite(ledPinRed, 255);
        analogWrite(ledPinBlue, 255);
        analogWrite(ledPinGreen, 255);
        delay(700);
        analogWrite(ledPinRed, 0);
        analogWrite(ledPinBlue, 0);
        analogWrite(ledPinGreen, 0);
        delay(1000);
        analogWrite(ledPinRed, 255);
        analogWrite(ledPinBlue, 255);
        analogWrite(ledPinGreen, 255);
        delay(700);
   //s   
        analogWrite(ledPinRed, 0);
        analogWrite(ledPinBlue, 0);
        analogWrite(ledPinGreen, 0);
        delay(300);
        analogWrite(ledPinRed, 255);
        analogWrite(ledPinBlue, 255);
        analogWrite(ledPinGreen, 255);
        delay(300);
        analogWrite(ledPinRed, 0);
        analogWrite(ledPinBlue, 0);
        analogWrite(ledPinGreen, 0);
        delay(300);
        analogWrite(ledPinRed, 255);
        analogWrite(ledPinBlue, 255);
        analogWrite(ledPinGreen, 255);
        delay(300);
        analogWrite(ledPinRed, 0);
        analogWrite(ledPinBlue, 0);
        analogWrite(ledPinGreen, 0);
        delay(700);
}

void rainbow(){
  //red
      analogWrite(ledPinRed, 0);
      analogWrite(ledPinBlue, 255);
      analogWrite(ledPinGreen, 255);
      delay(30);
  //orange
      analogWrite(ledPinRed, 0);
      analogWrite(ledPinBlue, 255);
      analogWrite(ledPinGreen, 200);
      delay(30);
  //yellow
      analogWrite(ledPinRed, 0);
      analogWrite(ledPinBlue, 255);
      analogWrite(ledPinGreen, 20);
      delay(30);
  //green
      analogWrite(ledPinRed, 255);
      analogWrite(ledPinBlue, 255);
      analogWrite(ledPinGreen, 0);
      delay(30);
 //cyan
      analogWrite(ledPinRed, 255);
      analogWrite(ledPinBlue, 20);
      analogWrite(ledPinGreen, 20);
      delay(30);
 //blue
      analogWrite(ledPinRed, 255);
      analogWrite(ledPinBlue, 0);
      analogWrite(ledPinGreen, 255);
      delay(30);
 //blue
      analogWrite(ledPinRed, 20);
      analogWrite(ledPinBlue, 70);
      analogWrite(ledPinGreen, 255);
      delay(30);

}

void setMode(int mode){
  //purple gradient
  if (mode == 1){
     for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      analogWrite(ledPinRed, fadeValue);
      analogWrite(ledPinBlue, 0);
      analogWrite(ledPinGreen, 255);
      delay(100);
    }
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      analogWrite(ledPinRed, fadeValue);
      analogWrite(ledPinBlue, 0);
      analogWrite(ledPinGreen, 255);
      delay(100);
  }
 }
  //cyan gradient
  if (mode == 2){
     for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      analogWrite(ledPinRed, 255);
      analogWrite(ledPinBlue, fadeValue);
      analogWrite(ledPinGreen, 0);
      delay(100);
    }
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      analogWrite(ledPinRed, 255);
      analogWrite(ledPinBlue, fadeValue);
      analogWrite(ledPinGreen, 0);
      delay(100);
  }
 }
  //orange gradient
  if (mode == 3){
     for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      analogWrite(ledPinRed, 30);
      analogWrite(ledPinBlue, 255);
      analogWrite(ledPinGreen, fadeValue);
      delay(100);
    }
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      analogWrite(ledPinRed, 40);
      analogWrite(ledPinBlue, 255);
      analogWrite(ledPinGreen, fadeValue);
      delay(100);
  }
 }
 //OFF
  if (mode == 0){
      analogWrite(ledPinRed, 255);
      analogWrite(ledPinBlue, 255);
      analogWrite(ledPinGreen, 255);
     }
}

