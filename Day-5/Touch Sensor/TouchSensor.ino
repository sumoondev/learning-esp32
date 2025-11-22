const int ledPin = 2;
const int touchPin = 13;

int c; // for touchPin reading

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(touchPin, INPUT);
}

void loop() {
    c = digitalRead(touchPin);

    if(c == 0) {
        digitalWrite(ledPin, LOW);
    } else {
        digitalWrite(ledPin, HIGH);
    }

    delay(20);
}