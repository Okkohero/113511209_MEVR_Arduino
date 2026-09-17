const int PIN_1A = 7;
const int PIN_2A = 8;
const int EN1 = 11;
const int resPin = A0;
int resvalue = 0;
void setup() {
pinMode(PIN_1A, OUTPUT);
pinMode(PIN_2A, OUTPUT);
pinMode(EN1, OUTPUT);
pinMode(resPin, INPUT);
}
void loop() {
  int resvalue = analogRead(resPin); // 讀取可變電阻數值 (0 ~ 1023)
  int deadzone = 20;                 // 中間停止的範圍

  if (resvalue >= (512 - deadzone) && resvalue <= (512 + deadzone)) {
    digitalWrite(PIN_1A, LOW);
    digitalWrite(PIN_2A, LOW);
    analogWrite(EN1, 0);
  } 
  else if (resvalue < 512) {
    digitalWrite(PIN_1A, HIGH);
    digitalWrite(PIN_2A, LOW);
    
    int pwm = map(resvalue, 512 - deadzone, 0, 0, 255);
    pwm = constrain(pwm, 0, 255); // 限制在 0-255 範圍內
    analogWrite(EN1, pwm);
  } 
  else {
    digitalWrite(PIN_1A, LOW);
    digitalWrite(PIN_2A, HIGH);
    
    int pwm = map(resvalue, 512 + deadzone, 1023, 0, 255);
    pwm = constrain(pwm, 0, 255); // 限制在 0-255 範圍內
    analogWrite(EN1, pwm);
  }
  
  delay(50);

}