const int ledPin = 13;      
const int buttonPin = 2;    

int lastButtonState = HIGH; 

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); 
  
  Serial.begin(9600); 
}

void loop() {

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "ON") {
      digitalWrite(ledPin, HIGH);
    } 
    else if (command == "OFF") {
      digitalWrite(ledPin, LOW);
    }
  }

int currentState = digitalRead(buttonPin);
if (currentState != lastButtonState) {
    if (currentState == LOW) {
        Serial.println("BUTTON_PRESSED");
    } else {
        Serial.println("BUTTON_RELEASED");
    }
    lastButtonState = currentState;
    delay(50); // Debounce
}
}