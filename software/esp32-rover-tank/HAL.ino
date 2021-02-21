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

   float LM1 = leftMotor > 0.0 ? leftMotor*MAX_SPEED      : 0.0;
   float LM2 = leftMotor < 0.0 ? leftMotor*MAX_SPEED*-1.0 : 0.0;

   float RM1 = rightMotor > 0.0 ? rightMotor*MAX_SPEED      : 0.0;
   float RM2 = rightMotor < 0.0 ? rightMotor*MAX_SPEED*-1.0 : 0.0;

//   cliSerial->print(LM1);
//   cliSerial->print(" ");
//   cliSerial->print(LM2);
//   cliSerial->print(" ");
//   cliSerial->print(RM1);
//   cliSerial->print(" ");
//   cliSerial->println(RM2);

   leftMotor1.writeScaled(LM1);
   leftMotor2.writeScaled(LM2);

   rightMotor1.writeScaled(RM1);
   rightMotor2.writeScaled(RM2);
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
  fl[LEFT].servo.write(getAngle(LEFT));
  fl[RIGHT].servo.write(getAngle(RIGHT));
}
