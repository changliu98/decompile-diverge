int openI2CBus(int *bus,char *device)

{
  int iVar1;
  char *device_local;
  int *bus_local;
  uint local_c;
  
  iVar1 = open(device,2);
  *bus = iVar1;
  local_c = (uint)(*bus < 0);
  return local_c;
}