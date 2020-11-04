#include <stdlib.h>
#include "config.h"
#include "robot_control.h"
typedef void(*task)();
task *tasks;
u8 state = MOVE_FORWARD;
u8 worldState = NO_OBJECTS;
unsigned short distance = 0;
void create_tasks(task *in_tasks)
{
  tasks = malloc(sizeof(in_tasks));
  int count = sizeof(in_tasks) / sizeof(task);
  for (int index = 0; index < count; index++)
  {
    tasks[index] = in_tasks[index];
  }
}

void stop_moving()
{
  stop();
  state = CHOOSING_DIRECTION;
}

void move_forward()
{
  if (worldState == OBJECT_IS_CLOSE)
  {
    move(MOVE_FORWARD, NORMAL_MOTOR_SPEED);
  }
  else
  {
    move(MOVE_FORWARD, HIGH_MOTOR_SPEED);
  }
}

void move_backward()
{
  move(MOVE_BACKWARD, NORMAL_MOTOR_SPEED);
}

void chooseDirection()
{
  
}

void move_left()
{
  move(MOVE_LEFT, SLOW_MOTOR_SPEED);
}
//if robot stoped, check getCurrentServoAngle() and then move depends on pos
void move_right()
{
  move(MOVE_RIGHT, SLOW_MOTOR_SPEED);
}


void init_robot_tasks()
{
  task in_tasks[] = {&stop_moving, &move_forward, &move_backward, &move_left, &move_right};
  create_tasks(in_tasks);
}
//realWolrd stat
void realWorld()
{
  
}

void run()
{
  tasks[state]();
}
