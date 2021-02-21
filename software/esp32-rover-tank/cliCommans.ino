double cliHelp()
{
  for (int i = 0; i < CLI_COMMANDS; i++) {
    cliSerial->print(cliCommands[i].commandName);
    cliSerial->print(" ");
    cliSerial->println(cliCommands[i].params);
  }
}

double cliHal()
{
  enableControl();
}

double cliFlippers()
{
  disableControl();
  fl[LEFT].ang  = CLI_readInt();
  fl[RIGHT].ang = CLI_readInt();

  cliSerial->print("Flippers [");
  cliSerial->print(fl[LEFT].ang);
  cliSerial->print("] [");
  cliSerial->print(fl[RIGHT].ang);
  cliSerial->println("]");
}

double cliI2cScan()
{
  for (byte s = 0; s <= 7; s++) {
    i2cSelect(s);
    cliSerial->print(s);
    cliSerial->println(" i2c line: ");
    for (byte i = 1; i < 127; i++) {
      Wire.beginTransmission (i);        // Begin I2C transmission Address (i)
      if (Wire.endTransmission () == 0)  // Receive 0 = success (ACK response) 
      {
        cliSerial->print (i, DEC);
        cliSerial->print (" (0x");
        cliSerial->print (i, HEX);
        cliSerial->print ("), ");
      }
    }
    cliSerial->println("");
  }
  cliSerial->println("DONE");
}
