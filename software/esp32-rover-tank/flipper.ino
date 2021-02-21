void updateFlippers()
{
  updateFlipper(LEFT);
  updateFlipper(RIGHT);
}

void updateFlipper(uint8_t id)
{
  // VERY STUPID
  if (getDistance(id, 0) < T1) {
    fl[id].ang++;
  }
  if (getDistance(id, 3) > T4) {
    fl[id].ang--;
  }

//  cliSerial->print("L ");
//  cliSerial->print(getDistance(LEFT, 0));
//  cliSerial->print(" ");
//  cliSerial->print(getDistance(LEFT, 1));
//  cliSerial->print(" ");
//  cliSerial->print(getDistance(LEFT, 2));
//  cliSerial->print(" ");
//  cliSerial->print(getDistance(LEFT, 3));
//
//  cliSerial->print(" R ");
//  cliSerial->print(getDistance(RIGHT, 0));
//  cliSerial->print(" ");
//  cliSerial->print(getDistance(RIGHT, 1));
//  cliSerial->print(" ");
//  cliSerial->print(getDistance(RIGHT, 2));
//  cliSerial->print(" ");
//  cliSerial->println(getDistance(RIGHT, 3));

  if (fl[id].ang > 180 ) fl[id].ang = 180;
  if (fl[id].ang < 0 ) fl[id].ang = 0;
}

void setupFlipper(uint8_t id)
{
    // TODO this is not great
  if (id == LEFT) {
    fl[LEFT].sensorId = 1;
    fl[LEFT].roiList[0] = 107;
    fl[LEFT].roiList[1] = 75;
    fl[LEFT].roiList[2] = 43;
    fl[LEFT].roiList[3] = 11;

    fl[LEFT].servo.attach(LEFT_FLIPPER);
    fl[LEFT].servo.setPeriodHertz(50);
    fl[LEFT].ang = 90;
    fl[LEFT].inverted = true;
  }
  if (id == RIGHT) {
    fl[RIGHT].sensorId = 0;
    fl[RIGHT].roiList[0] = 11;
    fl[RIGHT].roiList[1] = 43; 
    fl[RIGHT].roiList[2] = 75; 
    fl[RIGHT].roiList[3] = 107;

    fl[RIGHT].servo.attach(RIGHT_FLIPPER);
    fl[RIGHT].servo.setPeriodHertz(50);
    fl[RIGHT].ang = 90;
    fl[RIGHT].inverted = false;
  }
  
  selectToF(id);
  
  if (fl[id].sensor.begin() != 0) //Begin returns 0 on a good init
  {
    cliSerial->print(id);
    cliSerial->println(" sensor failed to begin.");
    failLoop();
  }
  cliSerial->print(id);
  cliSerial->println(" sensor online.");

  fl[id].sensor.setDistanceModeShort();
  fl[id].sensor.setTimingBudgetInMs(20);
  fl[id].sensor.setIntermeasurementPeriod(25);
  fl[id].sensor.startRanging(); // Start once


}

void selectToF(uint8_t id)
{
  i2cSelect(fl[id].sensorId);
}


void getToF(uint8_t id)
{
  selectToF(id);
  
  fl[id].sensor.setROI(4,6, fl[id].roiList[getROIIndex(id)]);
  delay(1);
  while (!fl[id].sensor.checkForDataReady())
  {
    delay(1);
  }
  fl[id].status[getROIIndex(id)] = fl[id].sensor.getRangeStatus();
  fl[id].distance[getROIIndex(id)] = fl[id].sensor.getDistance(); 
  fl[id].sensor.clearInterrupt();

  nextROIIndex(id);
}

uint8_t getROIIndex(uint8_t id)
{
  return fl[id].roiIndex;
}

void nextROIIndex(uint8_t id)
{
  fl[id].roiIndex++;

  if (fl[id].roiIndex == ROIPOINTS) {
    fl[id].roiIndex = 0;
  }
}

uint16_t getDistance(uint8_t id, uint8_t roiIndex)
{
  return fl[id].distance[roiIndex];
}

int getAngle(uint8_t id)
{
  if (fl[id].inverted) {
    return 180 - fl[id].ang;
  }
  
  return fl[id].ang;
}

/**Table of Optical Centers**
  *
  * 128,136,144,152,160,168,176,184,  192,200,208,216,224,232,240,248
  * 129,137,145,153,161,169,177,185,  193,201,209,217,225,233,241,249
  * 130,138,146,154,162,170,178,186,  194,202,210,218,226,234,242,250
  * 131,139,147,155,163,171,179,187,  195,203,211,219,227,235,243,251
  * 132,140,148,156,164,172,180,188,  196,204,212,220,228,236,244,252
  * 133,141,149,157,165,173,181,189,  197,205,213,221,229,237,245,253
  * 134,142,150,158,166,174,182,190,  198,206,214,222,230,238,246,254
  * 135,143,151,159,167,175,183,191,  199,207,215,223,231,239,247,255
  
  * 127,119,111,103, 95, 87, 79, 71,  63, 55, 47, 39, 31, 23, 15, 7
  * 126,118,110,102, 94, 86, 78, 70,  62, 54, 46, 38, 30, 22, 14, 6
  * 125,117,109,101, 93, 85, 77, 69,  61, 53, 45, 37, 29, 21, 13, 5
  * 124,116,108,100, 92, 84, 76, 68,  60, 52, 44, 36, 28, 20, 12, 4
  * 123,115,107, 99, 91, 83, 75, 67,  59, 51, 43, 35, 27, 19, 11, 3
  * 122,114,106, 98, 90, 82, 74, 66,  58, 50, 42, 34, 26, 18, 10, 2
  * 121,113,105, 97, 89, 81, 73, 65,  57, 49, 41, 33, 25, 17, 9, 1
  * 120,112,104, 96, 88, 80, 72, 64,  56, 48, 40, 32, 24, 16, 8, 0             ^ Y
  *                                                                            |
  * pin1                                                      bottom view  X <-+
  */
