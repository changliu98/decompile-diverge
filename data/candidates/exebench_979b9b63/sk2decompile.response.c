int openI2CBus(int *i2cBus, char *i2cBusName) {
  *i2cBus = open(i2cBusName, 2);
  if (*i2cBus < 0) {
    return 1;
  }
  return 0;
}