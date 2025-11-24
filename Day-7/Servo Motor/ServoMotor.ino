#include <ESP32Servo.h> //library: ESP32Servo by Kevin Harrington, John K. Bennett

Servo myServo;
int servoPin = 5;
int angle;

void setup() {
  myServo.attach(servoPin);
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()) {
    angle = Serial.parseInt();
    myServo.write(angle);
  }
  delay(20);
}
