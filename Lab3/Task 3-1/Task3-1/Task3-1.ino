#include <TimerOne.h>

const int buttonApin = 2;
const int ledA_Pin = 12;
const int buttonBpin = 3;
const int ledB_Pin = 13;

void timerISR() {
  int AState = digitalRead(buttonApin);
  
  if (AState == LOW) {
    digitalWrite(ledA_Pin, HIGH); 
  } else {
    digitalWrite(ledA_Pin, LOW);  
  }
}

void setup() {
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(ledA_Pin, OUTPUT);
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(ledB_Pin, OUTPUT);

  Timer1.initialize(50000);
  Timer1.attachInterrupt(timerISR);
}

void loop() {
  int BState = digitalRead(buttonBpin);
  
  if (BState == LOW) {
    digitalWrite(ledB_Pin, HIGH); 
  } else {
    digitalWrite(ledB_Pin, LOW);  
  }

  delay(1000);
}