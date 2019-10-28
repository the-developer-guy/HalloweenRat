#include <Servo.h>
#include "sound.h"
#include "distance.h"

#define ULTRASONIC_TRIGGER_PIN 3
#define ULTRASONIC_ECHO_PIN 2
#define SERVO_PIN 5
#define SERVO_REST_POSITION 10
#define SERVO_HIGH_POSITION 50

void servoJump(Servo servo, int top, int bottom);

Ultrasonic ultrasonic(ULTRASONIC_ECHO_PIN, ULTRASONIC_TRIGGER_PIN);
Servo servo;

unsigned long taskTimestamp = 0;
unsigned long taskPeriod = 100;

// in mm, limited to 3000 mm by the ultrasonic sensor
int triggerDistance = 200;

void setup() {
  soundInit();
  servo.attach(SERVO_PIN);
  servo.write(10);
}

void loop() {
  if(taskTimestamp <= millis())
  {
    taskTimestamp += taskPeriod;
    ultrasonic.measure();
    if(ultrasonic.getDistance() < triggerDistance)
    {
      soundSqueak();
      servoJump(servo, SERVO_HIGH_POSITION, SERVO_REST_POSITION);
      taskTimestamp += 10000;
    }  
  }
}

void servoJump(Servo servo, int top, int bottom)
{
  servo.write(top);
  delay(1000);
  for(int pos = top; pos > bottom; pos--)
  {
    servo.write(pos);
    delay(40);
  }
}

