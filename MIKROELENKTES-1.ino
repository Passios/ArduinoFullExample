#include <Servo.h>

Servo myservo;            // create servo object
int servo = 7;            // servo connected to digital pin 9
int pos = 0;              // angle = 0 degrees
const int led_1=3;
const int led_2=5;
const int dc=6;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  pinMode(dc, OUTPUT);
  pinMode(servo, OUTPUT);
  myservo.attach(servo);  // attach servo on pin 9
  myservo.write(pos);     // initialize servo
  delay(150);              // 15 ms to reach position
  
  pinMode(led_1, OUTPUT);
  analogWrite(led_1, LOW);
  pinMode(led_2, OUTPUT);
  analogWrite(led_2, LOW);
}

void loop() {
  if(Serial.available()>0){
  // put your main code here, to run repeatedly:
     String command = Serial.readString();
	 if ((command.charAt(0) == 'L') && (command.charAt(1) == 'E') && (command.charAt(2) == 'D')){
		 if ((command.charAt(4) == 'O') && (command.charAt(5) == 'N')){
			analogWrite(led_1, HIGH);
			analogWrite(led_2, HIGH);
		else{
			analogWrite(led_1, LOW);
			analogWrite(led_2, LOW);
		}
	 }
     if ((command.charAt(0) == 'D') && (command.charAt(1) == 'C') ){
      String test = command.substring(3);
      int value=test.toInt();
      analogWrite(dc, value);
     }
     else if ((command.charAt(0) == 'S') && (command.charAt(1) == 'M') ){
      String test = command.substring(3);
      int value=test.toInt();
      //analogWrite(dc, value);
      value = map(value, 0, 180, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
      myservo.write(value);                  // sets the servo position according to the scaled value
      delay(15);         
     }
  }
 
  }
