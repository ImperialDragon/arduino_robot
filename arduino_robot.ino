#include "fsm.h"
void setup()
{
   initialize();
   Serial.begin(9600);
}
void loop()
{
  realWorld();
  performTaskByState();
}
