#include <Keypad.h>
#include <string.h>

const byte ROWS = 4;
const byte COLS = 4;
const int ledPin = 12;
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};

String pass;

Keypad customKeypad = Keypad(makeKeymap(hexaKeys),rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Keypad Reader Initialized. Press a key.");
}

void loop() {
  // put your main code here, to run repeatedly:
  char customKey = customKeypad.getKey();

  if (customKey) {
    if(customKey == '#') {
      Serial.println(pass);
      if(pass == "123") {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
      pass = "";
    } else {
      pass = pass + customKey;
    }
    
  }

  
}
