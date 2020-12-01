/*
  robot_control.h is used for basic robot functions and pin intialization.
  Variables are used to store robot parameters. Exam.: servoPos - servo position
*/
#include "config.h"
#include <Servo.h>

//forward declaration
void robotMove();
void checkRobotMode();
void stopMotors();
void initialize();
void rotateServo(uint8_t rotation_angle);
void changeServoPos();
void sensorScan();
int16_t getDistance();
uint8_t getServoPos();
uint8_t getRobotMode();

//variables
static Servo servo;
static int16_t distance;
static uint8_t servoPos;
static uint8_t robotMode;
static bool modeLock = false;

void robotMove(uint8_t direction, uint8_t speed)
{
    switch(direction)
    {
        case MOVE_BACKWARD:
            analogWrite(RIGHT_MOTOR_B1A_PIN, speed);
            digitalWrite(RIGHT_MOTOR_B1B_PIN, LOW);
            digitalWrite(LEFT_MOTOR_A1A_PIN, LOW);
            analogWrite(LEFT_MOTOR_A1B_PIN, speed);
            break;
        case MOVE_FORWARD:
            digitalWrite(RIGHT_MOTOR_B1B_PIN, speed);
            analogWrite(RIGHT_MOTOR_B1A_PIN, LOW);
            analogWrite(LEFT_MOTOR_A1A_PIN, speed);
            digitalWrite(LEFT_MOTOR_A1B_PIN, LOW);
            break;
        case MOVE_LEFT:
            analogWrite(RIGHT_MOTOR_B1A_PIN, speed);
            digitalWrite(RIGHT_MOTOR_B1B_PIN, LOW);
            digitalWrite(LEFT_MOTOR_A1A_PIN, LOW);
            digitalWrite(LEFT_MOTOR_A1B_PIN, LOW);
            break;
        case MOVE_RIGHT:
            digitalWrite(RIGHT_MOTOR_B1A_PIN, LOW);
            digitalWrite(RIGHT_MOTOR_B1B_PIN, LOW);
            analogWrite(LEFT_MOTOR_A1A_PIN, speed);
            digitalWrite(LEFT_MOTOR_A1B_PIN, LOW);
            break;
        default:
            stopMotors();
            break;
    }
}

void checkRobotMode()
{
   uint8_t readPin = (robotMode == MOVING_MODE)? STAND_MODE_PIN : MOVING_MODE_PIN;
   uint8_t digitalValue = digitalRead(readPin);
   if (modeLock == false && digitalValue == HIGH) modeLock = true;
   else if(modeLock == true && digitalValue == LOW) 
   {
    switch(readPin)
    {
      case STAND_MODE_PIN:
        robotMode = STAND_MODE;
        pinMode(STAND_MODE_PIN, OUTPUT);
        pinMode(MOVING_MODE_PIN, INPUT);
        digitalWrite(STAND_MODE_PIN, HIGH);
        break;
      case MOVING_MODE_PIN:
        robotMode = MOVING_MODE;
        pinMode(MOVING_MODE_PIN, OUTPUT);
        pinMode(STAND_MODE_PIN, INPUT);
        digitalWrite(MOVING_MODE_PIN, HIGH);
        break;
    }
    modeLock = false;
   }
}


void stopMotors()
{
    digitalWrite(RIGHT_MOTOR_B1A_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_B1B_PIN, LOW);
    digitalWrite(LEFT_MOTOR_A1A_PIN, LOW);
    digitalWrite(LEFT_MOTOR_A1B_PIN, LOW);
}

void initialize()
{
  robotMode = MOVING_MODE;
  servoPos = SERVO_FORWARD_TO_LEFT;
  distance = DEFAULT_DISTANCE;
  randomSeed(analogRead(RANDOM_VALUE_PIN));
  pinMode(RIGHT_MOTOR_B1B_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_B1A_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_A1A_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_A1B_PIN, OUTPUT);
  pinMode(SENSOR_TRIG_PIN, OUTPUT);
  pinMode(SENSOR_ECHO_PIN, INPUT);
  pinMode(MOVING_MODE_PIN, OUTPUT);
  pinMode(STAND_MODE_PIN, INPUT); 
  digitalWrite(MOVING_MODE_PIN, HIGH);
  servo.attach(SERVO_PIN);
  servo.write(servoPos);                                                                                                           
}

void rotateServo(uint8_t rotation_angle)
{
  servoPos = rotation_angle;
  servo.write(servoPos);
}

void changeServoPos()
{
  switch (servoPos)
  {
    case SERVO_LEFT:
      rotateServo(SERVO_HALF_LEFT_TO_RIGHT);
      break;
    case SERVO_HALF_LEFT_TO_RIGHT:
      rotateServo(SERVO_FORWARD_TO_RIGHT);
      break;
    case SERVO_FORWARD_TO_RIGHT:
      rotateServo(SERVO_HALF_RIGHT);
      break;
    case SERVO_HALF_RIGHT:
      rotateServo(SERVO_RIGHT);
      break;
    case SERVO_RIGHT:
      rotateServo(SERVO_HALF_RIGHT_TO_LEFT);
      break;
    case SERVO_HALF_RIGHT_TO_LEFT:  
      rotateServo(SERVO_FORWARD_TO_LEFT);
      break;
    case SERVO_FORWARD_TO_LEFT:
      rotateServo(SERVO_HALF_LEFT);
      break;
    case SERVO_HALF_LEFT: 
      rotateServo(SERVO_LEFT);
      break;
    default:
      rotateServo(SERVO_FORWARD_TO_LEFT);
      break;
  }
}

void smallChangeServoPos()
{
  switch (servoPos)
  {
    case SERVO_QUATER_HALF_LEFT:
      rotateServo(SERVO_FORWARD_TO_RIGHT);
      break;
    case SERVO_FORWARD_TO_RIGHT:
      rotateServo(SERVO_QUATER_HALF_RIGHT);
      break;
    case SERVO_QUATER_HALF_RIGHT:
      rotateServo(SERVO_QUATER_HALF_LEFT);
      break;
    case SERVO_FORWARD_TO_LEFT:
      rotateServo(SERVO_QUATER_HALF_LEFT);
      break;
  }
}

void sensorScan()
{
  int64_t duration = 0;
  digitalWrite(SENSOR_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SENSOR_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENSOR_TRIG_PIN, LOW);
  duration = pulseIn(SENSOR_ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;
}

int16_t getDistance()
{
  int16_t curDistance = distance;
  distance = DEFAULT_DISTANCE;
  return curDistance;
}

uint8_t getServoPos()
{
  return servoPos;
}

uint8_t getRobotMode()
{
  return robotMode;
}
