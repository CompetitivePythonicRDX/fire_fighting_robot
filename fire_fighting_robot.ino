/*------ Arduino Fire Fighting Robot Code by hobby project---- */
 
#include <Servo.h>  //include servo.h library
#include <AFMotor.h>

Servo myservo;
AF_DCMotor motor_right(1);
AF_DCMotor motor_left(2);
AF_DCMotor pump(3);
 
int pos = 0;    
boolean fire = false;
 
#define Left A0      // left sensor
#define Right A1    // right sensor
#define Forward A2   //front sensor
 
void setup()
{
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  
  motor_left.setSpeed(225);
  motor_right.setSpeed(225);
  pump.setSpeed(225);
  
  motor_left.run(RELEASE);
  motor_right.run(RELEASE);
  pump.run(RELEASE);
  
  myservo.attach(10);
  myservo.write(90); 
}
 
void put_off_fire()
{
  delay (500);
 
  motor_left.run(RELEASE);
  motor_right.run(RELEASE);
  
  pump.run(FORWARD);
  delay(500);
    
  for (pos = 50; pos <= 130; pos += 1) { 
    myservo.write(pos); 
    delay(10);  
  }
  for (pos = 130; pos >= 50; pos -= 1) { 
    myservo.write(pos); 
    delay(10);
  }

  pump.run(RELEASE);
  myservo.write(90);
  
  fire=false;
}
 
void loop()
{
  myservo.write(90); //Sweep_Servo();  
 
  if (digitalRead(Left) ==1 && digitalRead(Right)==1 && digitalRead(Forward) ==1) 
  {
    motor_left.run(RELEASE);
    motor_right.run(RELEASE);
  }
    
  else if (digitalRead(Forward) ==0) 
  {
    motor_left.run(FORWARD);
    motor_right.run(FORWARD);
    fire = true;
  }
    
  else if (digitalRead(Left) ==0)
  {
    motor_left.run(FORWARD);
    motor_right.run(RELEASE);
  }
    
  else if (digitalRead(Right) ==0) 
  {
    motor_left.run(RELEASE);
    motor_right.run(FORWARD);
  }
    
  delay(300);//change this value to increase the distance
 
  while (fire == true)
  {
    put_off_fire();
  }
}
