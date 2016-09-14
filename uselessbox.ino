#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int ledPin = 13;
const int btnPin = 7;

#define SERVO_CLOSED   175
#define SERVO_SWITCH  35
#define SERVO_OPEN    80
#define SERVO_LOOM    150

int pos = 0;    // variable to store the servo position

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(SERVO_CLOSED);
}

void waitForHigh()
{
  while(digitalRead(btnPin) == LOW);
  delay(50);
}

void moveSlowly(int to, int speed)
{
  for (pos = 180; pos >= to; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(speed);                       // waits 15ms for the servo to reach the position
  }
}

void justlooking(int del)
{ 
  delay(3*del/6);
  moveSlowly(SERVO_OPEN, random(3, 50));
  delay(3*del/6);
}

void justlooming(int del)
{
  delay(3*del/6);
  moveSlowly(SERVO_LOOM, random(3, 50));
  delay(3*del/6);
}

void lookandhide(int del)
{
  delay(3*del/6);
  moveSlowly(SERVO_OPEN, random(3, 50));
  delay(3*del/6);
  moveSlowly(SERVO_CLOSED, random(3, 50));
  delay(del/6);
}

void loop() 
{
  if( digitalRead(btnPin) == LOW )
  {
    int rndDelay = random(200, 8000);
    int rndSelect = random(1,6);
    /*for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }*/
    switch(rndSelect) {
      case 1:
          moveSlowly(SERVO_SWITCH, random(3, 25));
          break;
      case 2:
          justlooking(rndDelay);
          myservo.write(SERVO_SWITCH);
          break;
      case 3:
          lookandhide(rndDelay);
          myservo.write(SERVO_SWITCH);
          break;
      case 4:
          justlooming(rndDelay);
          myservo.write(SERVO_SWITCH);
          break;
      case 5:
          justlooming(rndDelay);
          moveSlowly(SERVO_CLOSED, random(3, 25));
          delay(3*rndDelay/6);
          justlooking(rndDelay);
          myservo.write(SERVO_SWITCH);
          break;
      default:
          delay(rndDelay);
          myservo.write(SERVO_SWITCH);
          break;
    }
    waitForHigh();
  } else {
    myservo.write(SERVO_CLOSED);
  }

  /*
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  */
}
