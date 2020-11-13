#include "fsm.h"
void setup()
{
   initialize();
   initRobotTasks();
}
void loop()
{
  realWorld();
  performTaskByState();
}
