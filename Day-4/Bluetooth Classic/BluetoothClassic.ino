#include "BluetoothSerial.h"

BluetoothSerial serialBT;
char cmd;

void setup() {
  serialBT.begin("Esp32-BT");
  pinMode(2, OUTPUT);
}

void loop() {
  if(serialBT.available()) {
    cmd = serialBT.read();
  }

  if(cmd == '1') {
    digitalWrite(2, HIGH);
  }
  if(cmd == '0') {
    digitalWrite(2, LOW);
  }
  delay(20);
}