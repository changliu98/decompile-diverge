int serial_write(int portId, char *buffer, int size)
{
 return(write(portId, buffer, size));
}