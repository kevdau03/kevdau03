#include<SoftwareSerial.h>

char i;
SoftwareSerial bluetooth(0,1);
#define enA 5
#define enB 6
#define in1 7
#define in2 8
#define in3 9
#define in4 11
#define LED 13

enum Directions {
  STATIONARY,
  FORWARD,
  BACKWARD
};
// right motors
int spdA = 170;
// left motors
int spdB = (0.689/0.69)*spdA - 15.12/0.69;
Directions dir = STATIONARY;
void setup()
{
  bluetooth.begin(9600);
  Serial.begin(9600);
  // set all the motor control pins outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
void forward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, spdA);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, spdB);
  dir = FORWARD;
  Serial.println(dir);
}

void turnOff()
{
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
  dir = STATIONARY;
  Serial.println(dir);
}
void left()
{
  for (int i = 0; i <=7000; i++) {
  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, LOW);
  digitalWrite (in4, LOW);
  digitalWrite (enA, spdA);
  digitalWrite (enB, spdB);
}
delay(300);
}
void right()
{
  
  for (int i = 0; i <=7000; i++) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, spdA);
    analogWrite(enB, spdB);
  }
delay(300);
  
}
void backward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, spdA);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  analogWrite(enB, spdB);
  dir = BACKWARD;
  Serial.println(dir);
}

void loop()
{
  if(bluetooth.available())
  {
    i = bluetooth.read();
   if(i == 'f')
 
     forward();

   else if(i == 'b')
   
     backward();
   
   else if(i == 'l'){
      if (dir == BACKWARD) {
        left();
        delay(300);
        backward();

        }
      else if (dir == FORWARD){
        left();
        delay(300);
        forward();
      }
      else if (dir == STATIONARY) {
        left();
        delay(300);
        turnOff();
      }
      }

   else if(i == 'r'){
      if (dir == BACKWARD){
        right();
        delay(300);
        backward();

        }
      else if (dir == FORWARD){
        right();
        delay(300);
        forward();
        }
        
       else if (dir == STATIONARY){
        right();
        delay(300);
        turnOff();
      }
   }
   else if(i == 'x') {
   
     turnOff();
   
  }
}
}
