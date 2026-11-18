int __cdecl openI2CBus(int *bus, char *device)
{
  *bus = open(device, 2);
  return *bus < 0;
}