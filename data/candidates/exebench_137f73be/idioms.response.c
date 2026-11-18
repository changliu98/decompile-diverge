int I2CSensor_Read(int *bus, int I2CAddress, int registry, void *buffer, int size){
  if ( ioctl(*bus, 0x0703, I2CAddress) < 0){
    return 3;
  }
  if ( write(*bus, &registry, 1) != 1){
    return 3;
  }
  if ( read(*bus, buffer, size) != size){
    return 3;
  }
  return 0;
}