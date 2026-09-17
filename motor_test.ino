//motor 1
#define ENA 5
#define IN1 3
#define IN2 4
//motor 2
#define ENB 10
#define IN3 8
#define IN4 9

void setup() {
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

}

void loop() {
 //both motors forward
 analogWrite(ENA,180);
 digitalWrite(IN1,HIGH);
 digitalWrite(IN2,LOW);
 analogWrite(ENB,180);
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
//both motors stop
 delay(2000);
digitalWrite(ENA,LOW);
digitalWrite(ENB,LOW);
//both motors reverse
delay(1000);
analogWrite(ENA,180);
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
analogWrite(ENB,180);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
//both motors stop
delay(2000);
digitalWrite(ENA,LOW);
digitalWrite(ENB,LOW);
delay(1000);
}
