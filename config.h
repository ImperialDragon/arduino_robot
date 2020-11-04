//pins
#define RIGHT_MOTOR_B1B_PIN 12
#define RIGHT_MOTOR_B1A_PIN 11
#define LEFT_MOTOR_A1A_PIN 8
#define LEFT_MOTOR_A1B_PIN 7
#define SERVO_PIN 1
#define SENSOR_TRIG_PIN 6
#define SENSOR_ECHO_PIN 7

//Move directions and states
#define STOP 0
#define MOVE_FORWARD 1
#define MOVE_BACKWARD 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4
//Just states
#define CHOOSING_DIRECTION 5
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
#define SERVO_FORWARD 60
//multitasking constants
#define SCAN_DELAY 850
#define SERVO_DELAY 850
//FSM world states
#define NO_OBJECTS 0
#define OBJECT_IS_CLOSE 1
#define OBJECT_ON_FORWARD 2
#define OBJECT_ON_LEFT 3
#define OBJECT_ON_RIGHT 4
//FSM state
//sensor_range constants
#define COLLIDE_RANGE 4
#define MAX_MIDDLE_RANGE  7
#define MIN_MIDDLE_RANGE 13
//INTIAL_ZERO
#define DEFAULT_VALUE 0
