/**
 * TODO:
 *  - [x] low voltage to 10V
 *  - [x] one module per motor
 *  - [ ] heatsink somehow
 */

#include <Wire.h>
#include "SparkFun_VL53L1X.h"
#include <ESP32Servo.h>

#include "def.h"
#include "config.h"
#include "cli.h"
#include "config_wifi.h"
#include "WiFi.h"
#include <DNSServer.h>
#include "ESPAsyncWebServer.h"
#include "web/index.html.gz.h"

unsigned long currentTime;
unsigned long previousTime;
unsigned long loopTime;

// define move params
float speed         = 0;
float yaw           = 0;
float normal        = 1;
float rawLeftMotor  = 0;
float rawRightMotor = 0;

/**
 * 
 * 
 * 
 *          ^ speed
 *          |
 *          0---> yaw
 * 
 * 
 */

// define HAL state
bool CONTROL_ENABLED = true;

// define motor values
float leftMotor  = 0;
float rightMotor = 0;

// Failsafe
bool FS_FAIL        = false;
uint8_t FS_WS_count = 0;

// Is rover upsidedown
bool invert  = false;
bool enabled = true;

// PWM settings
int PWMfreq = 10000;

// Init hardware
ESP32PWM leftMotor1;
ESP32PWM leftMotor2;

ESP32PWM rightMotor1;
ESP32PWM rightMotor2;

Servo leftFlipper;
Servo rightFlipper;
int leftFlipperAng  = 90;
int rightFlipperAng = 90;

// WiFi
// WebServer
bool clientOnline = false;
IPAddress WiFiIP;
DNSServer dnsServer;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

//CLI
Stream *cliSerial;

void setup() {
  Serial.begin (SERIAL_BAUD);
  cliSerial = &Serial;
  delay(2000);

  //init i2c
  Wire.begin();
  setupTof(LEFT);
  setupTof(RIGHT);




  // init WiFi access point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_ssid, AP_pass);
  WiFi.softAPsetHostname(AP_ssid);
  WiFiIP = WiFi.softAPIP();
  cliSerial->print(WiFiIP);
  cliSerial->println();

  initWebServer();

  dnsServer.start(53, "*", WiFiIP); // this force all request goes to EPS32 (captive portal)... and it does not work =(


  // Init ESP32Servo
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  //init flippers servos
  leftFlipper.attach(LEFT_FLIPPER);
  leftFlipper.setPeriodHertz(50);
  rightFlipper.attach(RIGHT_FLIPPER);
  rightFlipper.setPeriodHertz(50);

  // Init motor pins
  leftMotor1.attachPin(LEFT_MOTOR1_PIN, PWMfreq);
  leftMotor2.attachPin(LEFT_MOTOR2_PIN, PWMfreq);

  rightMotor1.attachPin(RIGHT_MOTOR1_PIN, PWMfreq);
  rightMotor2.attachPin(RIGHT_MOTOR2_PIN, PWMfreq);

  delay(1000);
  cliSerial->println("Go");
}

void loop() {
  currentTime = millis();
  if (currentTime - previousTime >= LOOP_TIME) {
    previousTime = currentTime;
    if (CLI_get(CLI_BUFFER)){
      CLI_doCommand();
    }
    getPowerSensor();
    getIMU();
    updateFailsafe();
    doFlippers();
    doMotors();

    FS_WS_count++;

    loopTime = millis() - currentTime;
  }
}

void getPowerSensor()
{
}

void getIMU()
{
}

void doMotors()
{
    if (CONTROL_ENABLED) HAL_calcMove();
    HAL_doMove();  
}

void doFlippers()
{
    getToF(LEFT);
    getToF(RIGHT);
    if (CONTROL_ENABLED) updateFlippers();  
    HAL_doServos();
}
