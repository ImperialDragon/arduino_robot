#include "config.h"
#include <Servo.h>
Servo servo;
u8 currentSpeedMode = SLOW_MOTOR_MODE;
void move(u8 direction, u8 speed)
{
    switch(direction)
    {
        case MOVE_BACKWARDS:
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
          stop();
            break;
    }
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
    
    servo.attach(1);
    servo.write(0);                                                                                                           
}

void servo_rotation(u8 rotation_angle)
{
    servo.write(rotation_angle);
}
