#include <Servo.h>

Servo servo1;

const int FLEX_PIN = A0;
const float VCC = 4.98;
const float R_DIV = 47500.0;
const float STRAIGHT_RESISTANCE = 37300.0;
const float BEND_RESISTANCE = 90000.0;
int flexADC;
float flexV;
float flexR;
float angle;

const int LEDOUT = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(FLEX_PIN, INPUT);
  pinMode(LEDOUT, OUTPUT);
  
  servo1.attach(9, 900, 2100);

}

void flexRead() {
  flexADC = analogRead(FLEX_PIN);
  flexV = flexADC * VCC / 1023.0;
  flexR = R_DIV * (VCC / flexV - 1.0);
  angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
  Serial.println("Bend: " + String(angle) + " degrees");
  Serial.println();
}

void ledOutput() {
  if (angle < 0)
  {
    digitalWrite(LEDOUT, HIGH);
    delay(800);
    digitalWrite(LEDOUT, LOW);
    delay(800);
  }
  else if (angle >= 0 && angle < 50)
  {
    digitalWrite(LEDOUT, HIGH);
    delay(500);
    digitalWrite(LEDOUT, LOW);
    delay(500);
  }
  else if (angle >= 50 && angle < 100)
  {
    digitalWrite(LEDOUT, HIGH);
    delay(200);
    digitalWrite(LEDOUT, LOW);
    delay(200);
  }
  else
  {
    digitalWrite(LEDOUT, HIGH);
    delay(50);
    digitalWrite(LEDOUT, LOW);
    delay(50);
  }
}

void servoMotor() {
  if (angle > 0)
  {
    if (angle >= 0 && angle < 50)
    {
      servo1.write(180);
      delay(400);
      servo1.write(90);
      delay(400);
    }
    else if (angle >= 50 && angle < 100)
    {
      servo1.write(180);
      delay(200);
      servo1.write(90);
      delay(200);
    }
    else
    {
      servo1.write(180);
      delay(100);
      servo1.write(90);
      delay(100);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  flexRead();
  ledOutput();
  servoMotor();
}



