#include "fsm.h"
void setup()
{
   initialize();
}
void loop()
{
  realWorld();
  performTaskByState();
}
