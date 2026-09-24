#include <Servo.h>

Servo myservo;

int trigPin = 10;                  
int echoPin = 11;                 
long duration, cm;
 
void setup() {
  Serial.begin (9600);    
  myservo.attach(9);
  myservo.write(0);          
  pinMode(trigPin, OUTPUT);        
  pinMode(echoPin, INPUT);
}
 
void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);     
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);             
  duration = pulseIn(echoPin, HIGH);  
 
  cm = (duration/2) / 29.1;       
  cm = constrain(cm, 0, 100);
  int data = map(cm, 0, 100, 0, 180);
  Serial.print("Distance : ");  
  Serial.print(cm);
  Serial.print("cm, angle = ");
  Serial.print(data);
  Serial.println();
  myservo.write(data);
  
  delay(250);
}