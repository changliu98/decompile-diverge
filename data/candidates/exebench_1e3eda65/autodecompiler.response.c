int Serial_WriteData(int portId, char *buffer, int size)
{
 return(write(portId, buffer, size));
}