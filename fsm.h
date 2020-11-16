#include "robot_control.h"
typedef void(*task)(); 

//forward declaration
void updateTime(uint64_t *millisCurrent);
void performTask(task myTask, uint64_t millisCurrent, uint64_t *elapsedTime, uint64_t constant);
void stopMoving();
void moveForward();
void moveBackward();
void moveLeft();
void moveRight();
void servoScan();
void initRobotTasks();
void realWorld();
void performTaskByState();
void movingModeWorld();
void standModeWorld();

//Variable declaration
static uint8_t state = MOVE_FORWARD;
static uint8_t isPathBlocked[] = {EMPTY,EMPTY}; //left, right
static uint8_t worldState = NO_OBJECTS; 
static uint64_t millisSensor = DEFAULT_VALUE;
static uint64_t millisServo = DEFAULT_VALUE;
static uint64_t millisStateTask = DEFAULT_VALUE;
static uint64_t millisCurrent = DEFAULT_VALUE;
static uint64_t moveMillis = 0;
static uint64_t backwardMillis = 0;
static task stateTasks[] = {&stopMoving, &moveForward, &moveLeft, &moveRight, &moveBackward, &servoScan};
static task worldTasks[] = {&movingModeWorld, &standModeWorld};
void updateTime(uint64_t *millisVar)
{
  *millisVar = millis();
}

void clearPathIsBlocked()
{
  isPathBlocked[0] = EMPTY;
  isPathBlocked[1] = EMPTY;
}

void updateAllTime()
{
  updateTime(&millisCurrent);
  updateTime(&millisSensor);
  updateTime(&millisServo);
  updateTime(&millisStateTask);
}

void performTask(task myTask, uint64_t millisCurrent, uint64_t *elapsedTime, uint64_t constant)
{
  if (millisCurrent - *elapsedTime > constant)
  {
    *elapsedTime = millisCurrent;
    myTask();
  }
}

void stopMoving()
{
  stopMotors();
  if (getRobotMode() != STAND_MODE)
  {
    state = SERVO_SCAN;
  }
}

void moveForward()
{
  if (worldState == COLLISION)
  {
    state = STOP;
  }
  else
  {
    robotMove(MOVE_FORWARD, HIGH_MOTOR_SPEED);
  }
}

void moveBackward()
{
  robotMove(MOVE_BACKWARD, NORMAL_MOTOR_SPEED);
}

void servoScan()
{
  updateTime(&millisCurrent);
  performTask(&changeServoPos, millisCurrent, &millisServo, SERVO_DELAY);
}

void moveLeft()
{
  robotMove(MOVE_LEFT, SLOW_MOTOR_SPEED);
  if (millisCurrent - moveMillis >= 1000)
  {
    state = MOVE_FORWARD;
  }
}

void moveRight()
{
  robotMove(MOVE_RIGHT, SLOW_MOTOR_SPEED);
  if (millisCurrent - moveMillis >= 1000)
  {
    state = MOVE_FORWARD;
  }
}

void movingModeWorld()
{
  updateTime(&millisCurrent);
  if (state != MOVE_LEFT && state != MOVE_RIGHT)
  {
    performTask(&sensorScan, millisCurrent, &millisSensor, SENSOR_DELAY);
    uint16_t curDistance = getDistance();
    if (curDistance <= COLLIDE_RANGE && curDistance >= 0)
      {
        switch(getServoPos())
        {
          case SERVO_LEFT:
            isPathBlocked[LEFT] = COLLISION;
            break;
          case SERVO_FORWARD_TO_LEFT:
          case SERVO_FORWARD_TO_RIGHT:
            worldState = COLLISION;
            break;
          case SERVO_RIGHT:
            isPathBlocked[RIGHT] = COLLISION;
            break;
        }
      }
      else
      {
        worldState = NO_OBJECTS;
      }
  }
  if (worldState == COLLISION)
  {
    updateTime(&moveMillis);
    if (isPathBlocked[LEFT] != EMPTY || isPathBlocked[RIGHT] != EMPTY) rotateServo(SERVO_FORWARD_TO_LEFT);
    if (isPathBlocked[RIGHT] == COLLISION && isPathBlocked[LEFT] == COLLISION)
    {
      clearPathIsBlocked();
      state = MOVE_BACKWARD;
    }
    else if (isPathBlocked[RIGHT] == NO_OBJECTS && isPathBlocked[LEFT] == NO_OBJECTS && state != MOVE_BACKWARD)
    {
      worldState = NO_OBJECTS;
      rotateServo(SERVO_FORWARD_TO_LEFT);
      state = random(2,4);
    }
    else if (isPathBlocked[RIGHT] == NO_OBJECTS && isPathBlocked[LEFT] != EMPTY)
    { 
      worldState = NO_OBJECTS;
      state = 1;
    }
  }
}

void standModeWorld()
{
  updateTime(&millisCurrent);
  performTask(&sensorScan, millisCurrent, &millisSensor, SENSOR_DELAY);
  uint16_t curDistance = getDistance();
  if (getServoPos() != SERVO_FORWARD_TO_LEFT)
    {
      rotateServo(SERVO_FORWARD_TO_LEFT);
      updateAllTime();
      setDistance(DEFAULT_DISTANCE);
      curDistance = getDistance();
    }
    if (curDistance <= STANDMODE_COLLIDE_RANGE && curDistance != DEFAULT_DISTANCE)
    {
      state = MOVE_BACKWARD;
      worldState = OBJECT_ON_FORWARD;
    }
    else
    {
      state = STOP;
    }
}

void realWorld()
{
  worldTasks[getRobotMode()]();
}

void performTaskByState()
{
  updateTime(&millisCurrent);
  performTask(stateTasks[state], millisCurrent, &millisStateTask, CALL_TASK_DELAY);
}
