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
void servoStandScan();
void servoMoveScan();
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
static uint8_t state = MOVE_FORWARD_STATE;
static uint8_t worldState = NO_OBJECTS;
static uint8_t pathState[] = {EMPTY,EMPTY}; //left, right

//robot tasks
static task stateTasks[] = {(task) stopMoving, (task) moveForward, (task) moveLeft, (task) moveRight, (task) moveBackward, (task) servoStandScan, (task) servoMoveScan};
static task worldTasks[] = {(task) movingModeWorld, (task) standModeWorld};

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
  if (getRobotMode() == MOVING_MODE)
  {
    if (worldState == NO_OBJECTS) worldState = COLLISION; //used for correct mode changing
    state = SERVO_STAND_SCAN_STATE;
  }
}

void moveForward()
{
  robotMove(MOVE_FORWARD, HIGH_MOTOR_SPEED);
  state = SERVO_MOVE_SCAN_STATE;
}

void moveBackward()
{
  robotMove(MOVE_BACKWARD, NORMAL_MOTOR_SPEED);
  if (getRobotMode() == MOVING_MODE) 
  {
    performTask([]() {
      updateAllTime();
      worldState = COLLISION;
      state = STOP_STATE;
      }, &moveMillis, CHANGE_STATE_TO_STAND_SCAN_DELAY);
  }
}

void moveLeft()
{
  robotMove(MOVE_LEFT, SLOW_MOTOR_SPEED);
  performTask([](){state = MOVE_FORWARD_STATE;}, &moveMillis, CHANGE_STATE_TO_FORWARD_DELAY);
}

void moveRight()
{
  robotMove(MOVE_RIGHT, SLOW_MOTOR_SPEED);
  performTask([](){state = MOVE_FORWARD_STATE;}, &moveMillis, CHANGE_STATE_TO_FORWARD_DELAY);
}

void servoStandScan()
{
  performTask(&changeServoPos, &millisServo, SERVO_DELAY);
}

void servoMoveScan()
{
  if (worldState == NO_OBJECTS) performTask(&smallChangeServoPos, &millisServo, SERVO_FAST_DELAY);
  else state = STOP_STATE;
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
  if (state == SERVO_MOVE_SCAN_STATE && worldState == NO_OBJECTS) 
  { 
    if (isColliding) 
    {
      worldState = COLLISION;
      rotateServo(SERVO_FORWARD_TO_LEFT);
    }
  }
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
          case SERVO_HALF_LEFT:
            if (pathState[LEFT] == EMPTY || pathState[LEFT] == NO_OBJECTS) pathState[LEFT] = (isColliding) ? COLLISION : NO_OBJECTS;
            break;
          case SERVO_RIGHT:
          case SERVO_HALF_RIGHT:
            if (pathState[RIGHT] == EMPTY || pathState[RIGHT] == NO_OBJECTS) pathState[RIGHT] = (isColliding) ? COLLISION : NO_OBJECTS;      
            break;
        }
    }
    if (getServoPos() == SERVO_HALF_RIGHT_TO_LEFT)
    {
      if (pathState[RIGHT] == COLLISION && pathState[LEFT] == COLLISION)
      {
        worldState = COLLISION_EVERYWHERE;
        state = MOVE_BACKWARD_STATE;
      }
      else if (pathState[RIGHT] == NO_OBJECTS && pathState[LEFT] == NO_OBJECTS) state = random(2,4);
      else if (pathState[RIGHT] == NO_OBJECTS && pathState[LEFT] == COLLISION) state = MOVE_RIGHT_STATE;
      else if (pathState[LEFT] == NO_OBJECTS && pathState[RIGHT] == COLLISION) state = MOVE_LEFT_STATE;
      if (pathState[LEFT] != EMPTY && pathState[RIGHT] != EMPTY)
      {
        rotateServo(SERVO_FORWARD_TO_LEFT);
        updateAllTime();
        if (pathState[RIGHT] == NO_OBJECTS || pathState[LEFT] == NO_OBJECTS) worldState = NO_OBJECTS;
        clearPathStates();
      }
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
  performTask(&sensorScan, &millisSensor, SENSOR_ULTRA_FAST_DELAY);
  curDistance = getDistance();
  if (curDistance <= STANDMODE_COLLIDE_RANGE && curDistance >= 0)
  {
    state = MOVE_BACKWARD_STATE; 
    worldState = COLLISION;
  }
  else if (curDistance != DEFAULT_DISTANCE)
  {
    worldState = NO_OBJECTS;
    state = STOP_STATE;
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
