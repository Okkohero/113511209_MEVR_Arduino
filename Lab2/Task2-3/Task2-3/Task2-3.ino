const int buttonPinA = 2;
const int ledPinA = 13;
const int buttonPinB = 3;
const int ledPinB = 12;
volatile bool ledStateA = LOW;
bool ledStateB = LOW;

bool ButtonStateB1 = HIGH; 
bool ButtonStateB2;
void setup ( ) {
pinMode(ledPinA, OUTPUT);
pinMode(ledPinB, OUTPUT);
pinMode(buttonPinA, INPUT_PULLUP);
pinMode(buttonPinB, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(buttonPinA), buttonISR, FALLING);
}
void buttonISR( ) {
ledStateA = !ledStateA;
digitalWrite(ledPinA, ledStateA);
}
void loop ( ) {
  ButtonStateB2 = digitalRead(buttonPinB);

  if (ButtonStateB1 == HIGH && ButtonStateB2 == LOW) {
    ledStateB = !ledStateB;
    digitalWrite(ledPinB, ledStateB);
  }
  ButtonStateB1 = ButtonStateB2;
  delay(2000);
}