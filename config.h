//pins
#ifndef _config_h
#define RIGHT_MOTOR_B1B_PIN 12
#define RIGHT_MOTOR_B1A_PIN 11
#define LEFT_MOTOR_A1A_PIN 8
#define LEFT_MOTOR_A1B_PIN 7
#define SERVO_PIN 1
#define SENSOR_TRIG_PIN 6
#define SENSOR_ECHO_PIN 7
#define MOVING_MODE_PIN 3
#define STAND_MODE_PIN 4
//Move directions and states
#define STOP 0
#define MOVE_FORWARD 1
#define MOVE_LEFT 2
#define MOVE_RIGHT 3
#define MOVE_BACKWARD 4
//Just states
#define SERVO_SCAN 5
//motor speed
#define SLOW_MOTOR_SPEED 150
#define NORMAL_MOTOR_SPEED 175
#define HIGH_MOTOR_SPEED 225
//robot modes
#define MOVING_MODE 0
#define STAND_MODE 1
//servo angles
#define SERVO_RIGHT 110
#define SERVO_LEFT 0
#define SERVO_FORWARD_TO_LEFT 60
#define SERVO_FORWARD_TO_RIGHT 61
//multitasking constants
#define CALL_TASK_DELAY 50
#define SENSOR_DELAY 450
#define SERVO_DELAY 900
//FSM world states
#define NO_OBJECTS 0
#define OBJECT_IS_CLOSE 1
#define OBJECT_ON_FORWARD 2
#define OBJECT_ON_LEFT 3
#define OBJECT_ON_RIGHT 4
//FSM state
//sensor_range constants
#define COLLIDE_RANGE 7
#define STANDMODE_COLLIDE_RANGE 13
//INTIAL_ZERO
#define DEFAULT_VALUE 0
//Distance const
#define DEFAULT_DISTANCE -1
#endif
