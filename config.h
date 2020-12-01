#ifndef _config_h
//pins
#define RANDOM_VALUE_PIN 0
#define MOVING_MODE_PIN 3
#define STAND_MODE_PIN 4
#define RIGHT_MOTOR_B1A_PIN 5
#define RIGHT_MOTOR_B1B_PIN 6
#define LEFT_MOTOR_A1B_PIN 7
#define LEFT_MOTOR_A1A_PIN 8
#define SERVO_PIN 11
#define SENSOR_TRIG_PIN 12
#define SENSOR_ECHO_PIN 13

//move directions
#define STOP 0
#define MOVE_FORWARD 1
#define MOVE_LEFT 2
#define MOVE_RIGHT 3
#define MOVE_BACKWARD 4

//states
#define STOP_STATE 0
#define MOVE_FORWARD_STATE 1
#define MOVE_LEFT_STATE 2
#define MOVE_RIGHT_STATE 3
#define MOVE_BACKWARD_STATE 4
#define SERVO_STAND_SCAN_STATE 5
#define SERVO_MOVE_SCAN_STATE 6

//motor speed
#define SLOW_MOTOR_SPEED 190
#define NORMAL_MOTOR_SPEED 225
#define HIGH_MOTOR_SPEED 250

//robot modes
#define MOVING_MODE 0
#define STAND_MODE 1

//servo angles
#define SERVO_RIGHT 0
#define SERVO_HALF_RIGHT 48
#define SERVO_HALF_RIGHT_TO_LEFT 49
#define SERVO_HALF_LEFT 143
#define SERVO_HALF_LEFT_TO_RIGHT 142
#define SERVO_LEFT 180
#define SERVO_FORWARD_TO_LEFT 95
#define SERVO_FORWARD_TO_RIGHT 96
//servo half quater angles
#define SERVO_QUATER_HALF_RIGHT 65
#define SERVO_QUATER_HALF_LEFT 125

//multitasking constants
#define SENSOR_DELAY 600
#define SERVO_DELAY 600
#define SENSOR_FAST_DELAY 280
#define SENSOR_ULTRA_FAST_DELAY 60
#define SERVO_FAST_DELAY 280
#define CHANGE_STATE_TO_STAND_SCAN_DELAY 800
#define CHANGE_STATE_TO_FORWARD_DELAY 1000

//world states
#define NO_OBJECTS 0
#define COLLISION 1
#define COLLISION_EVERYWHERE 2
#define EMPTY 3

//Collide range
#define COLLIDE_RANGE 22
#define STANDMODE_COLLIDE_RANGE 15

//Distance const
#define DEFAULT_DISTANCE -1

//path const
#define LEFT 0
#define RIGHT 1

#endif
