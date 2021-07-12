const byte ledPin = 13;
const byte buttonPin1 = 2;
const byte buttonPin2 = 4;
void setup() {
 pinMode(ledPin, OUTPUT);
 pinMode(buttonPin1, INPUT_PULLUP);
 pinMode(buttonPin2, INPUT_PULLUP);
}

bool state = false;
void loop() {
      if(digitalRead(buttonPin1) == 0) {
      while (digitalRead(buttonPin1) == 0);
       digitalWrite(ledPin,1);
      }
       if(digitalRead(buttonPin2) == 0) {
      digitalWrite(ledPin, 0);
      }
} 
