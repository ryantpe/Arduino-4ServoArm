#include <SoftwareSerial.h>

#include <Servo.h>


SoftwareSerial myBt(5,6);
Servo servHead;
Servo servLeft;
Servo servRight;
Servo servTurn;
int sHeadPin = 8;
int sLeftPin = 9;
int sRightPin = 10;
int sTurnPin = 11;


void setup() {
  // put your setup code here, to run once:
  myBt.begin(9600);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Serial.println("Bluetooth Started~~");

  pinMode(sHeadPin, OUTPUT);
  pinMode(sLeftPin, OUTPUT);
  pinMode(sRightPin, OUTPUT);
  pinMode(sTurnPin, OUTPUT);
  servHead.attach(sHeadPin);
  servLeft.attach(sLeftPin);
  servRight.attach(sRightPin);
  servTurn.attach(sTurnPin);
  servHead.write(30);
  servLeft.write(30);
  servRight.write(30);
  servTurn.write(65);

}

void moveAngle(Servo s1, int angle, int min, int max) {
  
  if (angle > max) angle = max;
  if (angle < min) angle = min;
  int curr = s1.read();
  if (curr > angle) {
    for (int i = curr; i >= angle; i--) {
      s1.write(i);
      delay(10);
    }
  } else {
    for (int i = curr; i <= angle; i++) {
      s1.write(i);
      delay(10);
    }
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  

  if (myBt.available()) {
    char ch = myBt.read();
    int angle = myBt.parseInt();

    Serial.print(ch);
    Serial.println(angle);
    if ( ch == 'H' || ch == 'h') {
      moveAngle(servHead, angle, 30, 65);
      Serial.println("ServHead ...");
    } else if ( ch == 'L' || ch == 'l') {
      moveAngle(servLeft, angle, 30, 100);
      Serial.println("ServLeft ...");
    } else if ( ch == 'R' || ch == 'r') {
      moveAngle(servRight, angle, 30, 90);
      Serial.println("ServRight ...");
    } else if ( ch == 'T' || ch == 't') {
      moveAngle(servTurn, angle, 10, 120);
      Serial.println("ServTurn ...");
    }

  }
  
  delay(500);
}
