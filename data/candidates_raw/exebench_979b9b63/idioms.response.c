int open_device(int *bus, char *device)
{
  *bus = open(device, 02);
  if (*bus < 0)
    return 1;
  return 0;
}