#include "robot_control.h"
#include "tasklib.h"
#include "config.h"
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

//Variable declaration
static uint8_t state = MOVE_FORWARD;
static uint8_t worldState = NO_OBJECTS; 
static uint64_t millisSensor = DEFAULT_VALUE;
static uint64_t millisServo = DEFAULT_VALUE;
static uint64_t millisStateTask = DEFAULT_VALUE;
static uint64_t millisCurrent = DEFAULT_VALUE;
void updateTime(uint64_t *millisVar)
{
  *millisVar = millis();
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
  if (worldState >= 1 && worldState <= 3)
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
  uint64_t millisCurrent = 0;
  updateTime(&millisCurrent);
  performTask(&changeServoPos, millisCurrent, &millisSensor, SERVO_DELAY);
}

void moveLeft()
{
  robotMove(MOVE_LEFT, SLOW_MOTOR_SPEED);
}

void moveRight()
{
  robotMove(MOVE_RIGHT, SLOW_MOTOR_SPEED);
}

void initRobotTasks()
{
  task inTasks[] = {&stopMoving, &moveForward, &moveLeft, &moveRight, &moveBackward, &servoScan};
  createTasks(inTasks);
}

void realWorld()
{
  uint8_t robotMode = getRobotMode();
  updateTime(&millisCurrent);
  performTask(&sensorScan, millisCurrent, &millisSensor, SENSOR_DELAY);
  uint16_t curDistance = getDistance();
  if (robotMode == MOVING_MODE)
  {
    if (curDistance <= COLLIDE_RANGE && curDistance >= 0)
    {
      switch(getServoPos())
      {
        case SERVO_LEFT:
          worldState = OBJECT_ON_LEFT;
          break;
        case SERVO_FORWARD_TO_LEFT:
        case SERVO_FORWARD_TO_RIGHT:
          worldState = OBJECT_ON_FORWARD;
          break;
        case SERVO_RIGHT:
          worldState = OBJECT_ON_RIGHT;
          break;
      }
    }
  }
  else if (robotMode == STAND_MODE)
  {
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
}

void performTaskByState()
{
  updateTime(&millisCurrent);
  performTask(getTask(state), millisCurrent, &millisStateTask, CALL_TASK_DELAY);
}
