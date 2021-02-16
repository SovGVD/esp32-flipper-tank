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
  leftFlipperAng  = CLI_readInt();
  rightFlipperAng = CLI_readInt();

  cliSerial->print("Flippers [");
  cliSerial->print(leftFlipperAng);
  cliSerial->print("] [");
  cliSerial->print(rightFlipperAng);
  cliSerial->println("]");
}
