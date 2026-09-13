int respin = A0;
int ledpin = 11;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(respin); //0到1023
  int brightness = map(value, 0, 1023, 0, 255);
  analogWrite(ledpin, brightness);

  Serial.print("Data is ");
  Serial.println(value);
  delay(300);
}
