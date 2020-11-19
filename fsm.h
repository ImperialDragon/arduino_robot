/*
  fsm.h is used for states.
  Variables are used to store only time, states, task arrays.
*/
#include "robot_control.h"
//creating type void func named task
typedef void(*task)(); 

//forward declaration
void updateTime(uint64_t *millisVar);
void performTask(task myTask, uint64_t *elapsedTime, uint64_t constant);
void clearPathStates();
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
//time
static uint64_t millisSensor = 0;
static uint64_t millisServo = 0;
static uint64_t moveMillis = 0;

//specific vars
static int16_t curDistance = DEFAULT_DISTANCE;

//states
static uint8_t state = MOVE_FORWARD;
static uint8_t worldState = NO_OBJECTS;
static uint8_t pathState[] = {EMPTY,EMPTY}; //left, right

//robot tasks
static task stateTasks[] = {&stopMoving, &moveForward, &moveLeft, &moveRight, &moveBackward, &servoScan};
static task worldTasks[] = {&movingModeWorld, &standModeWorld};

void updateTime(uint64_t *millisVar)
{
  *millisVar = millis();
}

void updateAllTime()
{
  updateTime(&millisSensor);
  updateTime(&millisServo);
  updateTime(&moveMillis);
}

void clearPathStates()
{
  pathState[LEFT] = EMPTY;
  pathState[RIGHT] = EMPTY;
}

void performTask(task myTask, uint64_t *elapsedTime, uint64_t constant)
{
  uint64_t millisCurrent = 0;
  updateTime(&millisCurrent);
  if (millisCurrent - *elapsedTime > constant)
  {
    *elapsedTime = millisCurrent;
    myTask();
  }
}

void stopMoving()
{
  stopMotors();
  if (getRobotMode() == MOVING_MODE) state = SERVO_SCAN;
}

void moveForward()
{
  if (worldState == NO_OBJECTS) robotMove(MOVE_FORWARD, HIGH_MOTOR_SPEED);
  else state = STOP;
}

void moveBackward()
{
  robotMove(MOVE_BACKWARD, NORMAL_MOTOR_SPEED);
  if (getRobotMode() == MOVING_MODE && worldState == COLLISION_EVERYWHERE) 
  {
    performTask([]() {
      updateAllTime();
      worldState = COLLISION;
      state = STOP;
      }, &moveMillis, CHANGE_STATE_TO_SCAN_DELAY);
  }
}

void moveLeft()
{
  robotMove(MOVE_LEFT, SLOW_MOTOR_SPEED);
  performTask([](){state = MOVE_FORWARD;}, &moveMillis, CHANGE_STATE_TO_FORWARD_DELAY);
}

void moveRight()
{
  robotMove(MOVE_RIGHT, SLOW_MOTOR_SPEED);
  performTask([](){state = MOVE_FORWARD;}, &moveMillis, CHANGE_STATE_TO_FORWARD_DELAY);
}

void servoScan()
{
  performTask(&changeServoPos, &millisServo, SERVO_DELAY);
}

void movingModeWorld()
{
  bool isColliding = false;
  int16_t curDistance = DEFAULT_DISTANCE;
  if (worldState == NO_OBJECTS)
  {
    performTask(&sensorScan, &millisSensor, SENSOR_FAST_DELAY);
    curDistance = getDistance();
    isColliding = (curDistance <= COLLIDE_RANGE && curDistance >= 0);
  }
  if (state == MOVE_FORWARD && worldState == NO_OBJECTS) { 
    if (isColliding) worldState = COLLISION; }
  else if (worldState == COLLISION)
  {
    performTask(&sensorScan, &millisSensor, SENSOR_DELAY);
    curDistance = getDistance();
    isColliding = (curDistance <= COLLIDE_RANGE && curDistance >= 0);
    if (curDistance != DEFAULT_DISTANCE)
    {
      switch(getServoPos())
        {
          case SERVO_LEFT:
            pathState[LEFT] = (isColliding) ? COLLISION : NO_OBJECTS;
            break;
          case SERVO_RIGHT:
            pathState[RIGHT] = (isColliding) ? COLLISION : NO_OBJECTS;      
            break;
        }
    }
    if (pathState[RIGHT] == COLLISION && pathState[LEFT] == COLLISION)
    {
      worldState = COLLISION_EVERYWHERE;
      state = MOVE_BACKWARD;
    }
    else if (pathState[RIGHT] == NO_OBJECTS && pathState[LEFT] == NO_OBJECTS) state = random(2,4);
    else if (pathState[RIGHT] == NO_OBJECTS && pathState[LEFT] == COLLISION) state = MOVE_RIGHT;
    else if (pathState[LEFT] == NO_OBJECTS && pathState[RIGHT] == COLLISION) state = MOVE_LEFT;
    if (pathState[LEFT] != EMPTY && pathState[RIGHT] != EMPTY)
    {
      rotateServo(SERVO_FORWARD_TO_LEFT);
      updateAllTime();
      if (pathState[RIGHT] == NO_OBJECTS || pathState[LEFT] == NO_OBJECTS) worldState = NO_OBJECTS;
      clearPathStates();
    }
  }
}

void standModeWorld()
{
  int16_t curDistance = DEFAULT_DISTANCE;
  if (getServoPos() != SERVO_FORWARD_TO_LEFT)
  {
    rotateServo(SERVO_FORWARD_TO_LEFT);
    updateTime(&millisSensor);
  }
  performTask(&sensorScan, &millisSensor, SENSOR_FAST_DELAY);
  curDistance = getDistance();
  if (curDistance <= STANDMODE_COLLIDE_RANGE && curDistance >= 0)
  {
    state = MOVE_BACKWARD; 
    worldState = COLLISION;
  }
  else if (curDistance != DEFAULT_DISTANCE)
  {
    worldState = NO_OBJECTS;
    state = STOP;
  }
}

void realWorld()
{
  checkRobotMode();
  worldTasks[getRobotMode()]();
}

void performTaskByState()
{
  stateTasks[state]();
}
