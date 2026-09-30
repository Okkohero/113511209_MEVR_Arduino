#include <SoftwareSerial.h>

// Arduino Pin 10 接 HC-05 TXD，Pin 11 接 HC-05 RXD
SoftwareSerial BTSerial(10, 11); // RX, TX

const int ledPin = 13;      
const int buttonPin = 2;    

int lastButtonState = HIGH; 

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); 
  
  Serial.begin(9600); 

  BTSerial.begin(9600); 
}

void loop() {
  // 接收來自藍牙模組（C# 上位機）的指令 ===
  if (BTSerial.available() > 0) {
    String command = BTSerial.readStringUntil('\n');
    command.trim();

    Serial.print("BT Received: ");
    Serial.println(command);

    if (command == "ON") {
      digitalWrite(ledPin, HIGH);
    } 
    else if (command == "OFF") {
      digitalWrite(ledPin, LOW);
    }
  }

  // 偵測按鈕狀態變化，並透過藍牙回傳給 C# 
  int currentState = digitalRead(buttonPin);
  if (currentState != lastButtonState) {
    if (currentState == LOW) {
      BTSerial.println("BUTTON_PRESSED");   // 透過藍牙發送
      Serial.println("Sent: BUTTON_PRESSED"); // 透過 USB 印出監控
    } else {
      BTSerial.println("BUTTON_RELEASED");  // 透過藍牙發送
      Serial.println("Sent: BUTTON_RELEASED");
    }
    lastButtonState = currentState;
    delay(50); //  Debounce
  }
}