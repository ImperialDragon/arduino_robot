#include "fsm.h"
#include "config.h"
void setup()
{
   initialize();
   init_robot_tasks();
}
void loop()
{
  realWorld();
  run();
}
