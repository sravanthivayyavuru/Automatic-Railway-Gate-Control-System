#include <Servo.h>

Servo gate;

const int approachButton = 2;
const int passedButton = 3;
const int redLED = 6;
const int greenLED = 7;
const int buzzer = 8;

bool gateClosed = false;

void setup() {
  pinMode(approachButton, INPUT_PULLUP);
  pinMode(passedButton, INPUT_PULLUP);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  gate.attach(9);
  gate.write(0);  // Gate open

  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, LOW);
}

void loop() {
  // Train approaching
  if (digitalRead(approachButton) == LOW
      && !gateClosed) {
    gateClosed = true;

    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);

    gate.write(90);  // Close gate
    delay(500);
    digitalWrite(buzzer, LOW);
  }

  // Train has passed
  if (digitalRead(passedButton) == LOW
      && gateClosed) {
    gateClosed = false;

    gate.write(0);  // Open gate
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, LOW);
  }

  delay(50);
}
