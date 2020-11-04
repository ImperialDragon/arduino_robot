#include "config.h"
#include <Servo.h>
Servo servo;
//forward declaration
void stop();
void move();
short getDistance();
u8 getCurrentServoAngle();
u8 getRobotMode();
//variables
u8 currentServoAngle;
u8 robotMode;
unsigned long millisSensor;
unsigned long millisServo;
void move(u8 direction, u8 speed)
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
            break;
    }
}

void changeRobotMode()
{
  /*Task: Implement robot mode changing Change robot mode.
    - RESERVED PINS - 3,4, you shoud create constants in config.h with valid name
   */
}

void stop()
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
    millisSensor = 0;
    millisServo = 0;
    currentServoAngle = SERVO_LEFT;
    servo.attach(1);
    servo.write(SERVO_LEFT);                                                                                                           
}

void rotate_servo(u8 rotation_angle)
{
    unsigned long millisCurrent = millis();
    if (millisCurrent - millisServo > SERVO_DELAY)
    {
      millisServo = millisCurrent;
      currentServoAngle = rotation_angle;
      servo.write(rotation_angle);
    }
}

short getDistance()
{
     /*Task: Implement ultransound signal sending(sensor) and get distance between robot and object.
       Bonus task: Try to find any solution where you can remove delay(10);
       Returning value of function is a distance between robot and object. Distance shoud be measured in cm
     */
    return 0; 
}

u8 getCurrentServoAngle()
{
  return currentServoAngle;
}

u8 getRobotMode()
{
  return robotMode;
}
