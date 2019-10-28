#include <Arduino.h>
#include "distance.h"

Ultrasonic::Ultrasonic()
{
  echoPin = -1;
  triggerPin = -1;
  distance = -1;
}

Ultrasonic::Ultrasonic(int echoPin, int triggerPin)
{
  if(echoPin >= 0 && triggerPin >= 0)
  {
    this->echoPin = echoPin;
    this->triggerPin = triggerPin;
    distance = 200;
    pinMode(echoPin, INPUT);
    pinMode(triggerPin, OUTPUT);
    digitalWrite(triggerPin, LOW);
  }
  else
  {
    this->echoPin = -1;
    this->triggerPin = -1;
    distance = -1;
  }
}

void Ultrasonic::measure(void)
{
  /*  distance  = speed of sound * time until echo comes / 2
   *  pulseIn: returns in us
   *  speed of sound: 340 m/s = 0.00034‬ m/us = 0.34 mm/us
   *  --> 1 us from pulseIn means 0.17 mm
   *  To avoid floating-point calculation, ~1.2% measurement error is added with fixpoint math
   *  with float: distance = echoTime * 0.17
   *  0.17 * (1 << 8) = 43.52
   *  without float: distance = (echoTime * 43) >> 8  
   */
  if(echoPin >= 0 && triggerPin >= 0)
  {
    // send 10 us trigger signal
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    echoTime = pulseIn(echoPin, HIGH);
    distance = (echoTime * 43) >> 8;    
  }
}

int Ultrasonic::getDistance(void)
{
  return distance;
}


