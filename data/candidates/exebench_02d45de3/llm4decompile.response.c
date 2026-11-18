int write_bus(WEATHERSTATION serdevice, unsigned char *buffer, int size)
{
 int ret = write(serdevice, buffer, size);
 return ret;
}