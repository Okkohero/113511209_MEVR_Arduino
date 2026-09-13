int resPin = A0;
int buttonPin = 2;
int buttonState = 1;
int greenState = 0;
const int redPin = 9;        
const int greenPin = 10;     
const int bluePin = 11;      
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);     
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.println("Green Light Brightness Controller");
}



void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available() > 0) {
    char a = Serial.read();
    if (a == '1') {
      greenState = 255; // 1 點亮綠燈
      Serial.print("Green Light Brightness: ");
      Serial.println(greenState);
    } else if (a == '0') {
      greenState = 0;   // 0 熄滅綠燈
      Serial.print("Green Light Brightness: ");
      Serial.println(greenState);
    }
  }

  int buttonState = digitalRead(buttonPin);
  int redValue = 0;
  if (buttonState == LOW) {
    redValue = 255;     
  } else {
    redValue = 0;       
  }

  int resValue = analogRead(resPin);
  int blueValue = map(resValue, 0, 1023, 0, 255); // 將 0-1023 對應到 PWM 0-255

  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenState);
  analogWrite(bluePin, blueValue);

  
}