float mapf(float val, float in_min, float in_max, float out_min, float out_max) {
  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void disableControl()
{
  CONTROL_ENABLED = false;
  cliSerial->println("Control disabled");
}

void enableControl()
{
  CONTROL_ENABLED = true;
  cliSerial->println("Control enabled");
}

void i2cSelect(uint8_t id) {
  if (id > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << id);
  Wire.endTransmission();  
}
