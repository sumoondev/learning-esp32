const int ledPin = 2;
String cmd;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  Serial.println("Hello!");
}

void loop() {
  if(Serial.available()) {
    cmd = Serial.readString();

    if (cmd == "on") {
      digitalWrite(ledPin, HIGH);
    } else if (cmd == "off") {
      digitalWrite(ledPin, LOW);
    }
  }
  
}
