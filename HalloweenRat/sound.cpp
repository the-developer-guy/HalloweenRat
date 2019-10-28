#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>

DFRobotDFPlayerMini player;

void soundInit(void)
{
  Serial.begin(9600);
  player.begin(Serial);
  player.volume(5);
}

void soundSqueak(void)
{
  player.play(1);
}

