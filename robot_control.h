#include "config.h"
#include <Servo.h>

//forward declaration
void stopMotors();
void robotMove();
uint16_t getDistance();
uint8_t getServoPos();
uint8_t getRobotMode();

//variables
static Servo servo;
static uint8_t servoPos;
static uint8_t robotMode;
static uint16_t distance = DEFAULT_DISTANCE;

void robotMove(uint8_t direction, uint8_t speed)
{
    switch(direction)
    {
        case MOVE_BACKWARD:
            digitalWrite(RIGHT_MOTOR_B1A_PIN, LOW);
            analogWrite(RIGHT_MOTOR_B1B_PIN, speed);
            digitalWrite(LEFT_MOTOR_A1A_PIN, LOW);
            analogWrite(LEFT_MOTOR_A1B_PIN, speed);
            break;
        case MOVE_FORWARD:
            analogWrite(RIGHT_MOTOR_B1A_PIN, speed);
            digitalWrite(RIGHT_MOTOR_B1B_PIN, LOW);
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

void changeRobotMode()
{
  /*Task: Implement robot mode changing Change robot mode.
    - RESERVED PINS - 3,4, you shoud create constants in config.h with valid name
   */
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
    pinMode(RIGHT_MOTOR_B1B_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_B1A_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_A1A_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_A1B_PIN, OUTPUT);
    pinMode(SENSOR_TRIG_PIN, INPUT);
    pinMode(SENSOR_ECHO_PIN, OUTPUT); 
    robotMode = MOVING_MODE;
    servoPos = SERVO_FORWARD_TO_RIGHT;
    servo.attach(SERVO_PIN);
    servo.write(servoPos);                                                                                                           
}

void rotateServo(u8 rotation_angle)
{
      servoPos = rotation_angle;
      servo.write(servoPos);
}

void changeServoPos()
{
  switch (servoPos)
  {
    case SERVO_LEFT:
      rotateServo(SERVO_FORWARD_TO_RIGHT);
      break;
    case SERVO_FORWARD_TO_LEFT:
      rotateServo(SERVO_LEFT);
      break;
    case SERVO_FORWARD_TO_RIGHT:
      rotateServo(SERVO_RIGHT);
      break;
    case SERVO_RIGHT:
      rotateServo(SERVO_FORWARD_TO_LEFT);
      break;
    default:
      rotateServo(SERVO_FORWARD_TO_RIGHT);
      break;
  }
}

void sensorScan()
{
  /*Task: Implement ultransound signal sending(sensor) and get distance between robot and object.
       Bonus task: Try to find any solution where you can remove delay(10);
       distance shoud assigned to variable distance
     */
}

void setDistance(int inDistance)
{
  distance = inDistance;
}

uint16_t getDistance()
{
  return distance;
}

uint8_t getServoPos()
{
  return servoPos;
}

uint8_t getRobotMode()
{
  return robotMode;
}
