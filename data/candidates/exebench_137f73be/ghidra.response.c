int I2CSensor_Read(int *bus,uchar I2CAddress,uchar registry,uchar *buffer,int size)

{
  int iVar1;
  ssize_t sVar2;
  int size_local;
  uchar *buffer_local;
  uchar registry_local;
  uchar I2CAddress_local;
  int *bus_local;
  int local_c;
  
  registry_local = registry;
  I2CAddress_local = I2CAddress;
  bus_local = bus;
  iVar1 = ioctl(*bus,0x703,(ulong)I2CAddress);
  if (iVar1 < 0) {
    local_c = 3;
  }
  else {
    sVar2 = write(*bus_local,&registry_local,1);
    if (sVar2 == 1) {
      sVar2 = read(*bus_local,buffer,(long)size);
      if (sVar2 == size) {
        local_c = 0;
      }
      else {
        local_c = 3;
      }
    }
    else {
      local_c = 3;
    }
  }
  return local_c;
}