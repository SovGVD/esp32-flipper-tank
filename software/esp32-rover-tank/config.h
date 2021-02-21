// Serial
#define SERIAL_BAUD 115200 

// main loop
#define LOOP_TIME 20   // milliseconds

// failsafe
#define FS_WS_THR 20  // 1 second = FS_WS_THR*LOOP_TIME

// define motors pins
#define LEFT_MOTOR1_PIN  33
#define LEFT_MOTOR2_PIN  32
#define RIGHT_MOTOR1_PIN 18
#define RIGHT_MOTOR2_PIN 19

// Speed
#define MAX_SPEED 1.0   // [0.0f ... 1,0f]

//CLI
#define CLI_BUFFER_LENGTH 126

// i2c
#define TCAADDR 0x70
#define TOFADDR 0x29

// servos
#define LEFT_FLIPPER  23
#define RIGHT_FLIPPER 4
#define SERVO_MIN 1000
#define SERVO_MAX 2000
