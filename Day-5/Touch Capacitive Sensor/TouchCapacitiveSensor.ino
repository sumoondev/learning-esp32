const int ledPin = 2;
int c;

void setup() {
    pinMode(ledPin, INPUT);
}

void loop() {
    c = touchRead(T0);

    if(c < 500) {
        digitalWrite(ledPin, HIGH);
    } else {
        digitalWrite(ledPin, LOW);
    }

    delay(200);
}