#include <Servo.h>

#define trigpin 5
#define echopin 7
#define enable 6
Servo frontServo;
Servo rearServo;


  int centerPos = 90;
  int frontRightUp = 72;
  int frontLeftUp = 108;
  int backRightForward = 75;
  int backLeftForward = 105;
  int walkSpeed = 150; // How long to wait between steps in milliseconds
  int centerTurnPos = 81;
  int frontTurnRightUp = 63;
  int frontTurnLeftUp = 117;
  int backTurnRightForward = 66;
  int backTurnLeftForward = 96;
  /* Ping distance measurement - global variables */
  int pingPin = 4;
   int duration, distance;
  int distanceFront = 0; //cm
  int startAvoidanceDistance = 20; //cm
 


int delayTime = 1000;


void setup()
{
  //myServo.attach(2);
  Serial.begin(9600);
  pinMode(echopin,INPUT);
  pinMode(trigpin,OUTPUT);
  pinMode(enable,OUTPUT);
  frontServo.attach(9);
  rearServo.attach(10);
  frontServo.write(90);
  rearServo.write(90);  
}





void moveForward()
{
  frontServo.write(frontRightUp);
  rearServo.write(backLeftForward);
  delay(125);
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(65);
  frontServo.write(frontLeftUp);
  rearServo.write(backRightForward);
  delay(125);
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(65);
}


void moveBackward()
{
  frontServo.write(frontRightUp);
  rearServo.write(backRightForward);
  delay(125);
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(65);
  frontServo.write(frontLeftUp);
  rearServo.write(backLeftForward);
  delay(125);
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(65);
       /*{
        frontServo.attach(2);
        rearServo.attach(3);
       }*/
}



void moveBackRight()
{
  frontServo.write(frontRightUp);
  rearServo.write(backRightForward - 6);
  delay(125);
  frontServo.write(centerPos);
  rearServo.write(centerPos - 6);
  delay(65);
  frontServo.write(frontLeftUp + 9);
  rearServo.write(backLeftForward - 6);
  delay(125);
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(65);
  /*{
    frontServo.attach(2);
    rearServo.attach(3);
  }*/
}

void moveTurnLeft()
{
  frontServo.write(frontTurnRightUp);
  rearServo.write(backTurnLeftForward);
  delay(125);
  frontServo.write(centerTurnPos);
  rearServo.write(centerTurnPos);
  delay(65);
  frontServo.write(frontTurnLeftUp);
  rearServo.write(backTurnRightForward);
  delay(125);
  frontServo.write(centerTurnPos);
  rearServo.write(centerTurnPos);
  delay(65);
 /* {
    frontServo.attach(2);
    rearServo.attach(3);
  }*/
}



  /*long microsecondsToInches(long microseconds)
  {
    return microseconds / 74 / 2;
  }
  long microsecondsToCentimeters(long microseconds)
  {
    return microseconds / 29 / 2;
  }*/
  
  
  void center()
  {
    frontServo.write(centerPos);
    rearServo.write(centerPos);
  }


int distanceCm() 
  {
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(2);
    digitalWrite(trigpin, LOW);
    
    duration = pulseIn(echopin, HIGH);
    distance=(duration/2)/29.1;
  //  Serial.print(distance);
   // Serial.print("\n");
    return (distance);
    /*distanceInches = microsecondsToInches(duration);
    Serial.print(distanceInches);
    return microsecondsToCentimeters(duration);*/
  }
void loop()
{
   
   
    moveForward();
  delay(150); //time between each step taken, speed of walk
  moveBackward();
  delay(150); //time between each step taken, speed of walk
  moveBackRight();
  delay(150); //time between each step taken, speed of walk
  moveTurnLeft();
  delay(150); //time between each step taken, speed of walk


  distanceFront = distanceCm();
  if (distanceFront > 1)
  { 
    if (distanceFront < startAvoidanceDistance) 
    {
      for (int i = 0; i <= 8; i++)
      {
        moveBackRight();
        delay(walkSpeed);
      }
      for (int i = 0; i <= 10; i++)
      {
        moveTurnLeft();
        delay(walkSpeed);
      }
    }
    else {
      moveForward();
      delay(walkSpeed);
    }
  }
}

