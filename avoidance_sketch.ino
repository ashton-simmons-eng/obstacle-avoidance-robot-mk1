//calibrate ultrasound sensor
#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04(ECHO_PIN,TRIG_PIN);
long distance;
//calibrate motors
#define ENA 5
#define IN1 3
#define IN2 4

#define ENB 10
#define IN3 8
#define IN4 9

int motorPins[]={ENA,IN1,IN2,ENB,IN3,IN4};
void setup() {
  Serial.begin(9600);
  delay(2000);
  sr04.Distance(); //discard first reading
  delay(200);
  sr04.Distance(); //discard second reading
  delay(500);

  for (int i=0;i<6;i++){
    pinMode(motorPins[i],OUTPUT);
  }

}

void loop() {
  distance=sr04.Distance();
  Serial.print(distance);
  Serial.println("cm");
  delay(100);

digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
//main avoidance logic
if (distance<35){
analogWrite(ENA,120);
analogWrite(ENB,40);
delay(300);
}
else {
analogWrite(ENA,120); 
analogWrite(ENB,120); 
}
}
