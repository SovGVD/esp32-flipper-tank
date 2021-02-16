/**
 * Motors
 */
void HAL_calcMove()
{  
  if (speed == 0 && yaw == 0) {
    leftMotor  = 0;
    rightMotor = 0;
    return;
  }

  normal = 1;


  rawLeftMotor  = speed+yaw;
  rawRightMotor = speed-yaw;

  if (abs(rawLeftMotor) > 1 || abs(rawRightMotor) > 1) {
    normal = 1/(max(abs(rawLeftMotor),abs(rawRightMotor)));
  }

  leftMotor  = rawLeftMotor*normal;
  rightMotor = rawRightMotor*normal;
}

void HAL_doMove()
{
  /**
   *        forward  reverse  standby  brake
   * IN1/3      PMW        0        0      1
   * IN2/4        0      PWM        0      1
   * 
   *  *standby - no power on motor
   *  *brake   - stuck motor
   */
   analogWrite(LEFT_MOTOR1_PIN, leftMotor > 0 ? leftMotor*MAX_SPEED*-1 : 0);
   analogWrite(LEFT_MOTOR2_PIN, leftMotor < 0 ? leftMotor*MAX_SPEED    : 0);

   analogWrite(RIGHT_MOTOR1_PIN, rightMotor > 0 ? rightMotor*MAX_SPEED*-1 : 0);
   analogWrite(RIGHT_MOTOR2_PIN, rightMotor < 0 ? rightMotor*MAX_SPEED    : 0);
}


/**
 * Servos
 */
uint16_t HAL_angleToMs(double angle)
{
  uint16_t servoMs = mapf(angle, 0, 180, SERVO_MIN, SERVO_MAX);

  if (servoMs < SERVO_MIN) servoMs = SERVO_MIN;
  if (servoMs > SERVO_MAX) servoMs = SERVO_MAX;

  return servoMs;
}

void HAL_doServos(){
  leftFlipper.writeMicroseconds(HAL_angleToMs(leftFlipperAng));
  rightFlipper.writeMicroseconds(HAL_angleToMs(rightFlipperAng));
}
